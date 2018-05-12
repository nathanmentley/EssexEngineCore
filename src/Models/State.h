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
#include <EssexEngineCore/Context.h>
#include <EssexEngineCore/IState.h>

namespace EssexEngine{
namespace Core{
namespace Models{
    class State: public IState
    {
        public:
            State(WeakPointer<Context> _context);
            ~State();
        protected:
            WeakPointer<Context> context;
        private:
    };
}}};
