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

#include <queue>
#include <thread>
#include <chrono>

#include <EssexEngineCore/BaseDaemon.h>
#include <EssexEngineCore/MessageQueue.h>

namespace EssexEngine{
    namespace Daemons{
        template <class DriverType, class MessageType> class BaseQueuedDaemon: public BaseDaemon<DriverType>
        {
            public:
                BaseQueuedDaemon(WeakPointer<Context> _context):
                BaseDaemon<DriverType>(_context),
                thread(
                    UniquePointer<std::thread>()
                ),
                messageQueue(
                    UniquePointer<Core::Utils::MessageQueue<MessageType>>(
                        new Core::Utils::MessageQueue<MessageType>()
                    )
                ) {
                    running = true;
                }

                ~BaseQueuedDaemon() {
                    Stop();
                }
                
                void Start() {
                    running = true;

                    thread.Replace(
                        new std::thread(&BaseQueuedDaemon::Execute, this)
                    );
                }

                void Execute() {
                    while(running) {
                        if(!messageQueue->IsEmpty()) {
                            UniquePointer<MessageType> message = messageQueue->Pop();

                            ProcessMessage(message.ToWeakPointer());
                        }

                        std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    }
                }

                void Stop() {
                    running = false;
                }
            protected:
                virtual void ProcessMessage(WeakPointer<MessageType> message) = 0;
                void PushMessage(WeakPointer<MessageType> message) { messageQueue->Push(message); }
            private:
                UniquePointer<std::thread> thread;
                UniquePointer<Core::Utils::MessageQueue<MessageType>> messageQueue;
                bool running;
        };
    }};
