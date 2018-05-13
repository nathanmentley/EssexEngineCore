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

#include <EssexEngineCore/StateStack.h>

using EssexEngine::WeakPointer;
using EssexEngine::Core::Models::IState;
using EssexEngine::Core::Utils::StateStack;

StateStack::StateStack()
{
    data = std::vector<WeakPointer<Models::IState>>();
}

StateStack::~StateStack() {}

void StateStack::Push(WeakPointer<Models::IState> state) {
    state->Setup();
    data.push_back(state);
}

void StateStack::Pop() {
    if(!data.empty()) {
        data.pop_back();
    }
}

bool StateStack::IsEmpty() {
    return data.empty();
}

void StateStack::Clear() {
    data.clear();
}

bool StateStack::TopStateComplete() {
    if(!data.empty()) {
        return data.back()->completed;
    }
    
    return true;
}

std::vector<WeakPointer<IState>> StateStack::GetRawData() {
    return data;
}

int StateStack::GetLength() {
    return (int)data.size();
}

