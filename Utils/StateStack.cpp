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

#include <EssexEngineCore/StateStack.h>

EssexEngine::Core::Utils::StateStack::StateStack()
{
    data = std::vector<WeakPointer<Models::IState>>();
}

EssexEngine::Core::Utils::StateStack::~StateStack()
{
}

void EssexEngine::Core::Utils::StateStack::Push(WeakPointer<Models::IState> state) {
	state->Setup();
	data.push_back(state);
}

void EssexEngine::Core::Utils::StateStack::Pop() {
    if(!data.empty()) {
        data.pop_back();
    }
}

bool EssexEngine::Core::Utils::StateStack::IsEmpty() {
    return data.empty();
}

void EssexEngine::Core::Utils::StateStack::Clear() {
    data.clear();
}

bool EssexEngine::Core::Utils::StateStack::TopStateComplete() {
    if(!data.empty()) {
        return data.back()->completed;
    }
    
    return true;
}

std::vector<EssexEngine::WeakPointer<EssexEngine::Core::Models::IState>> EssexEngine::Core::Utils::StateStack::GetRawData() {
	return data;
}

int EssexEngine::Core::Utils::StateStack::GetLength() {
	return (int)data.size();
}
