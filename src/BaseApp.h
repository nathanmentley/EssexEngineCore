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
#include <EssexEngineCore/StateStack.h>
#include <EssexEngineCore/Context.h>
#include <EssexEngineCore/IApp.h>

namespace EssexEngine{
namespace Core{
    class BaseApp: public IApp
    {
        public:
            BaseApp(WeakPointer<Context> _context): IApp(),
            stateStack(
                UniquePointer<Core::Utils::StateStack>(
                    new Core::Utils::StateStack()
                )
            ) {
                context = _context;
            }
            
            virtual ~BaseApp() {
                while(!GetStateStack()->IsEmpty()) {
                    GetStateStack()->Pop();
                }
            }

            virtual std::string GetAppName() = 0;
            virtual std::string GetAppVersion() = 0;
            virtual WeakPointer<Models::IState> GetInitState() = 0;

            virtual void Execute() = 0;
            
            WeakPointer<Core::Utils::StateStack> GetStateStack() {
                return stateStack.ToWeakPointer();
            }
        protected:
            UniquePointer<Core::Utils::StateStack> stateStack;
            WeakPointer<Context> context;
    };
}};
