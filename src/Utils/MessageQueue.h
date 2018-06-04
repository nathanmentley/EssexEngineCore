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
#include <vector>
#include <algorithm>

#include <EssexEngineCore/IMessageResponse.h>
#include <EssexEngineCore/IMessage.h>
#include <EssexEngineCore/IWakeable.h>
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
                listeners = std::vector<WeakPointer<IWakeable>>();
                msgQueue = std::queue<WeakPointer<Models::IMessage>>();
            }
            virtual ~MessageQueue() {}

            void Subscribe(WeakPointer<IWakeable> listener) {
                listeners.push_back(listener);
            }

            void Unsubscribe(WeakPointer<IWakeable> listener) {
                listeners.erase(
                    std::remove(listeners.begin(), listeners.end(), listener),
                    listeners.end()
                );
            }

            void Push(WeakPointer<Models::IMessage> message) {
                _Push(message);
                
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
                _Push(message);

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
            void _Push(WeakPointer<Models::IMessage> message) {
                queueAccess.lock();
                msgQueue.push(message);
                queueAccess.unlock();

                for (auto &listener : listeners)
                {
                    listener->Wake();
                }
            }
                
            std::queue<WeakPointer<Models::IMessage>> msgQueue;
            std::mutex queueAccess;
            std::vector<WeakPointer<IWakeable>> listeners;
            ThreadPool pool;
    };
}}};

