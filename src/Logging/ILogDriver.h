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

#include <EssexEngineCore/IDriver.h>

namespace EssexEngine{
namespace Core{
namespace Logging{
    class ILogDriver:public IDriver
    {
        public:
            virtual void LogLine(std::string message) = 0;
        private:
    };
}}};
