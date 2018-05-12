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

#include <string>

#include <EssexEngineCore/EssexEnvironment.h>
#include <EssexEngineCore/UniquePointer.h>
#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineCore/IState.h>

namespace EssexEngine{
namespace Core{
    class BaseApp
    {
        public:
            BaseApp() {}
            virtual ~BaseApp() {}

            virtual std::string GetAppName() = 0;
            virtual std::string GetAppVersion() = 0;
            virtual WeakPointer<Models::IState> GetInitState() = 0;
    };
}};
