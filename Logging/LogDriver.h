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

#include <stdio.h>

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
            void Init() {
                if(GetContext()->HasDriver<Logging::ILogDriver>()) {
                    GetContext()->GetDriver<Logging::ILogDriver>()->LogLine(
                        "Loading Driver [%s] [%s]",
                        GetDriverName().c_str(),
                        GetDriverVersion().c_str()
                    );
                }
            }

            //ILogDriver
            void LogLine(const char *format, ...);
            
            //BaseDriver
            std::string GetDriverName() { return "Console Log"; }
            std::string GetDriverVersion() { return ESSEX_ENGINE_VERSION; }
        private:
    };
}}};