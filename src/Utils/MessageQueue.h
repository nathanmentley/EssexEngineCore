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
#include <mutex>

#include <EssexEngineCore/IMessageResponse.h>
#include <EssexEngineCore/IMessage.h>
#include <EssexEngineCore/BaseMessage.h>
#include <EssexEngineCore/ThreadPool.h>
#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineCore/UniquePointer.h>

namespace EssexEngine{
namespace Core{
namespace Utils{
    class MessageQueue
    {
        public:
            MessageQueue() {
                msgQueue = std::queue<WeakPointer<Models::IMessage>>();
            }
            virtual ~MessageQueue() {}

            void Push(WeakPointer<Models::IMessage> message) {
                //load queue
                queueAccess.lock();
                msgQueue.push(message);
                queueAccess.unlock();
                
                //cleanup the response in the background
                pool.AddTask(
                    [](WeakPointer<Models::IMessage> msg) {
                        WeakPointer<Models::IMessageResponse> resp = msg->GetResponse();

                        if(resp.HasValue()) {
                            UniquePointer<Models::IMessageResponse>(
                                resp.Get()        
                            ).Reset();
                        }

                        UniquePointer<Models::IMessage>(
                            msg.Get()
                        ).Reset();
                    },
                    message
                );
            }

            template<class ResponseType> UniquePointer<ResponseType> Push(WeakPointer<Models::IMessage> message) {
                queueAccess.lock();
                msgQueue.push(message);
                queueAccess.unlock();

                WeakPointer<ResponseType> resp = message->GetResponse().Cast<ResponseType>();

                UniquePointer<Models::IMessage>(
                    message.Get()        
                ).Reset();

                if(resp.HasValue()) {
                    return UniquePointer<ResponseType>(
                        resp.Get()
                    );
                } else {
                    return UniquePointer<ResponseType>();
                }
            }

            WeakPointer<Models::IMessage> Pop() {
                if(!IsEmpty()) {
                    queueAccess.lock();
                    WeakPointer<Models::IMessage> value = msgQueue.front();
                    msgQueue.pop();
                    queueAccess.unlock();
                    
                    return WeakPointer<Models::IMessage>(
                        value.Get()
                    );
                }

                return WeakPointer<Models::IMessage>();
            }

            bool IsEmpty() {
                queueAccess.lock();
                bool ret = msgQueue.empty();
                queueAccess.unlock();

                return ret;
            }
        private:
            std::queue<WeakPointer<Models::IMessage>> msgQueue;
            std::mutex queueAccess;
            ThreadPool pool;
    };
}}};

