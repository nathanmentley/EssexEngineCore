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

#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineCore/StateStack.h>

namespace EssexEngine{
namespace Core{
    class IApp
    {
        public:
            IApp() {}
            virtual ~IApp() {}
            
            virtual void Execute() = 0;
            virtual WeakPointer<Core::Utils::StateStack> GetStateStack() = 0;
    };
}};

