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
#include <EssexEngineCore/IWakeable.h>
#include <EssexEngineCore/MWakeableSleeper.h>
#include <EssexEngineCore/MessageQueue.h>

namespace EssexEngine{
    namespace Daemons{
        template <class DriverType> class BaseProcessDaemon: public BaseDaemon<DriverType>, public Core::MWakeableSleeper
        {
            public:
                BaseProcessDaemon(WeakPointer<Context> _context):
                BaseDaemon<DriverType>(_context),
                thread(
                    UniquePointer<std::thread>()
                ),
                messageQueue(
                    UniquePointer<Core::Utils::MessageQueue>(
                        new Core::Utils::MessageQueue()
                    )
                ) {
                    messageQueue->Subscribe(WeakPointer<Core::IWakeable>(this));

                    running = true;
                }

                ~BaseProcessDaemon() {
                    messageQueue->Unsubscribe(WeakPointer<Core::IWakeable>(this));

                    Stop();
                }
                
                void Start() {
                    running = true;

                    thread.Replace(
                        new std::thread(&BaseProcessDaemon::Execute, this)
                    );
                }

                void Execute() {
                    while(running) {
                        while(!messageQueue->IsEmpty()) {
                            WeakPointer<Core::Models::IMessage> message = messageQueue->Pop();

                            message->Resolve(
                                ProcessMessage(message)
                            );
                        }

                        WakeableSleep(1000);
                    }
                }

                void Stop() {
                    running = false;
                }
            protected:
                virtual WeakPointer<Core::Models::IMessageResponse> ProcessMessage(WeakPointer<Core::Models::IMessage> message) = 0;
                
                void PushMessage(WeakPointer<Core::Models::IMessage> message) {
                    messageQueue->Push(message);
                }

                template <class ResponseType> UniquePointer<ResponseType> PushMessage(WeakPointer<Core::Models::IMessage> message) {
                    return messageQueue->Push<ResponseType>(message);
                }
            private:
                UniquePointer<std::thread> thread;
                UniquePointer<Core::Utils::MessageQueue> messageQueue;
                bool running;
        };
    }};
