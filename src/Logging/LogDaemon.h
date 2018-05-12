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

#include <stdio.h>

#include <EssexEngineCore/BaseDaemon.h>
#include <EssexEngineCore/ILogDriver.h>

namespace EssexEngine{ 
namespace Core{
namespace Logging{
    class LogDaemon:public Daemons::BaseDaemon<ILogDriver>
    {
        public:
            LogDaemon(WeakPointer<Context> _context);
            ~LogDaemon();

            void Init() {
                LogLine(
                    "Loading Daemon [%s] [%s]",
                    GetDaemonName().c_str(),
                    GetDaemonVersion().c_str()
                );
            }
            std::string GetDaemonName() { return "Logging"; }
            std::string GetDaemonVersion() { return ESSEX_ENGINE_VERSION; }

            void LogLine(std::string format, ...);
            void DebugLine(std::string format, ...);
        private:
    };
}}};
