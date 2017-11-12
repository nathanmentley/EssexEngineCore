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

#include <vector>

#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineCore/IState.h>

namespace EssexEngine{
namespace Core{
namespace Utils{
    class StateStack
	{
		public:
			StateStack();
			~StateStack();

			void Push(WeakPointer<Models::IState> state);
			void Pop();
			bool IsEmpty();
			bool TopStateComplete();
            		void Clear();
			
            		std::vector<WeakPointer<Models::IState>> GetRawData();
			int GetLength();
		private:
            		std::vector<WeakPointer<Models::IState>> data;
	};
}}};
