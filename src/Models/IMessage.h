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

#include <future>

#include <EssexEngineCore/IMessageResponse.h>
#include <EssexEngineCore/WeakPointer.h>

namespace EssexEngine{
namespace Core{
namespace Models{
    class IMessage
    {
        public:
            IMessage() {
                future = promise.get_future();
            }
            virtual ~IMessage() {}

            virtual int GetType() = 0;

            void Resolve(WeakPointer<IMessageResponse> data) {
                promise.set_value(data);
            }
            
            WeakPointer<IMessageResponse> GetResponse() {
                return future.get();
            }
            /*
            std::future<WeakPointer<IMessageResponse>> GetFuture() {
                return future;
            }*/
        protected:
            /*
             * TODO: Setup failure for the message queue.
            void _Fail() {

            }
            */
        private:
            std::promise<WeakPointer<IMessageResponse>> promise;
            std::future<WeakPointer<IMessageResponse>> future;
    };
}}};
