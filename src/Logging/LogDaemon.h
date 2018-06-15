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
#include <stdarg.h>

#include <EssexEngineCore/BaseProcessDaemon.h>
#include <EssexEngineCore/ILogDriver.h>
#include <EssexEngineCore/IMessage.h>
#include <EssexEngineCore/LogDaemonMessage.h>

namespace EssexEngine{ 
namespace Core{
namespace Logging{
    class LogDaemon: public Daemons::BaseProcessDaemon<ILogDriver>
    {
        public:
            LogDaemon(WeakPointer<Context> _context);
            ~LogDaemon();

            void Init() {}
            std::string GetDaemonName() { return "Logging"; }
            std::string GetDaemonVersion() { return ESSEX_ENGINE_VERSION; }

            void LogLine(std::string format, ...);
            void DebugLine(std::string format, ...);
        protected:
            WeakPointer<Models::IMessageResponse> ProcessMessage(WeakPointer<Core::Models::IMessage> message);

            WeakPointer<LogDaemonMessageResponse> _LogLine(WeakPointer<LogDaemonMessage> message);
            WeakPointer<LogDaemonMessageResponse> _DebugLine(WeakPointer<LogDaemonMessage> message);
        private:
    };
}}};
