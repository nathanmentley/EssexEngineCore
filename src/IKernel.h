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
#include <EssexEngineCore/IApp.h>

namespace EssexEngine{
namespace Core{
    class IKernel
    {
        public:
            IKernel() {}
            virtual ~IKernel() {}
            
            virtual void Start() = 0;
            virtual void Stop() = 0;
            virtual void RunApp(WeakPointer<IApp> app) = 0;
    };
}};

