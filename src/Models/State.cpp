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

#include <EssexEngineCore/State.h>

using EssexEngine::Core::Models::State;

State::State(WeakPointer<Context> _context)
{
    completed = false;
    
    context = _context;
}

State::~State()
{
}
