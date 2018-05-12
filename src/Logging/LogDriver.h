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

#include <EssexEngineCore/BaseDriver.h>
#include <EssexEngineCore/ILogDriver.h>

namespace EssexEngine{
namespace Core{
namespace Logging{
    class LogDriver:public Drivers::Base::BaseDriver, public ILogDriver
    {
        public:
            LogDriver(WeakPointer<Context> _context);
            ~LogDriver();
            
            //IDriver
            void Init() {}

            //ILogDriver
            void LogLine(std::string format, va_list args);
            
            //BaseDriver
            std::string GetDriverName() { return "Console Log"; }
            std::string GetDriverVersion() { return ESSEX_ENGINE_VERSION; }
        private:
    };
}}};
