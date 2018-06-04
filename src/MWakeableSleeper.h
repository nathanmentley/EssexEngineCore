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
#include <mutex>
#include <thread>
#include <chrono>
#include <atomic>

#include <EssexEngineCore/IWakeable.h>

namespace EssexEngine{
namespace Core{
    class MWakeableSleeper: public IWakeable {
        public:
            MWakeableSleeper() {
                Lock();
            }

            ~MWakeableSleeper() {
                if(locked) {
                    Unlock();
                }
            }
            
            void Wake() {
                if(locked) {
                    Unlock();
                }
            }
        protected:
            void WakeableSleep(int milliseconds) {
                if(mut.try_lock_for(std::chrono::milliseconds(milliseconds))) {
                    mut.unlock();
                }
            }

        private:
            void Lock() {
                mut.lock();
                locked = true;
            }

            void Unlock() {
                locked = false;
                mut.unlock();
            }

            std::timed_mutex mut;
            std::atomic_bool locked;
    };
}};
