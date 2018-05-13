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

#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineCore/UniquePointer.h>

namespace EssexEngine{
namespace Core{
namespace Utils{
    template<class Type> class MessageQueue
    {
        public:
            MessageQueue() {
                queue = std::queue<WeakPointer<Type>>();
            }
            virtual ~MessageQueue() {}

            void Push(WeakPointer<Type> message) {
                queue.push(message);
            }

            UniquePointer<Type> Pop() {
                if(!IsEmpty()) {
                    WeakPointer<Type> value = queue.front();
                    queue.pop();

                    return UniquePointer<Type>(
                        value.Get()
                    );
                }

                return UniquePointer<Type>();
            }

            bool IsEmpty() {
                return queue.empty();
            }
        private:
            std::queue<WeakPointer<Type>> queue;
    };
}}};

