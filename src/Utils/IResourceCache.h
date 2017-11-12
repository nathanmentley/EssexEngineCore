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

namespace EssexEngine{
namespace Core{
namespace Utils{
    template<class Type> class IResourceCache
	{
		public:
            virtual void IncrementUsage(std::string key) = 0;
            virtual void ClearUsage(std::string key) = 0;
		private:
	};
}}};
