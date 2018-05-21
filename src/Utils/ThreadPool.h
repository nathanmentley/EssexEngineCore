/* 
 * Essex Engine
 * 
 * Copyright (C) 2018 Nathan Mentley - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 *
 * You should have received a copy of the BSD license with
 * this file. If not, please visit: https://github.com/nathanmentley/EssexEngine
 */
#pragma once

#include <iostream>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <functional>
#include <string>
#include <chrono>

namespace EssexEngine{
namespace Core{
namespace Utils{
    class ITask {
        public:
            virtual void Run() const = 0;
            virtual ~ITask() {};
    };   
    
    template < typename task_, typename... args_ >
    class Task : public ITask {
        public:
            Task( task_&& task, args_&&... args ) : fun_( std::bind( std::forward<task_>(task), std::forward<args_>(args)... ) ) {}
            void Run() const override {
                fun_();
            }
        private:
            decltype( std::bind(std::declval<task_>(), std::declval<args_>()... ) ) fun_;
    };

    class ThreadPool {
        public:
            ThreadPool() {
                for( auto & t : pool_ )
                    t = std::thread( [=] {
                        while ( true ) {
                            std::unique_ptr<ITask> task;
                            {
                                auto lock = std::unique_lock<std::mutex>{mtx_};
                                if ( q_.empty() && stop_ ) 
                                    break;
                                if ( q_.empty() )
                                    continue;
                                task = std::move(q_.front());
                                q_.pop();
                            }
                            if (task)
                                task->Run();
                        
                            //std::this_thread::sleep_for(std::chrono::milliseconds(10));
                        }
                    } );
            }
            ~ThreadPool() {
                {
                    auto lock = std::unique_lock<std::mutex>{mtx_};
                    stop_ = true;
                }
                for( auto & t : pool_ )
                    t.join();
            }

            template < typename task_, typename... args_ >
            void AddTask( task_&& task, args_&&... args ) {
                auto lock = std::unique_lock<std::mutex>{mtx_};
                using FinalTask = Task<task_, args_... >;
                q_.push( std::unique_ptr<ITask>( new FinalTask( std::forward<task_>(task), std::forward<args_>(args)... ) ) );
            }
        private:
            std::queue<std::unique_ptr<ITask>> q_;
            std::thread pool_[8]; 
            std::mutex mtx_;
            volatile bool stop_ {};
    };
}}};
