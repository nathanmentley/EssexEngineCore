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

#include <EssexEngineCore/IMessage.h>
#include <EssexEngineCore/IMessageResponse.h>
#include <EssexEngineCore/UniquePointer.h>
#include <EssexEngineCore/WeakPointer.h>

namespace EssexEngine{
namespace Core{
namespace Models{
    template<class ResponseType> class BaseMessage: public IMessage
    {
        public:
            BaseMessage(): IMessage() {}
            virtual ~BaseMessage() {}
    };
}}};
