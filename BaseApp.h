/* 
 * Essex Engine
 * 
 * Copyright (C) 2017 Nathan Mentley - All Rights Reserved
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
#include <EssexEngineCore/IState.h>

namespace EssexEngine{
namespace Core{
    class BaseApp
    {
        public:
            //TODO: This shouldn't get passed in. We should create it in GetInitState
            BaseApp(Models::IState* _initState) {
                initState = _initState;
            }
            ~BaseApp() {}

            virtual std::string GetAppName() = 0;
            virtual std::string GetAppVersion() = 0;

            UniquePointer<Models::IState> GetInitState() {
                return UniquePointer<Models::IState>(initState);
            }
        protected:
            Models::IState* initState;
    };
}};