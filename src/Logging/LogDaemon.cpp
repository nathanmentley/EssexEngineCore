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

#include <EssexEngineCore/LogDaemon.h>

using EssexEngine::Core::Logging::LogDaemon;

LogDaemon::LogDaemon(WeakPointer<Context> _context):BaseDaemon(_context) {
}

LogDaemon::~LogDaemon() {}

void LogDaemon::DebugLine(std::string format, ...) {
    if(HasDriver()) {
        va_list args;
        va_start(args, format);

        GetDriver()->LogLine("DEBUG: " + format, args);
        
        va_end(args);
    }
}

void LogDaemon::LogLine(std::string format, ...) {
    if(HasDriver()) {
        va_list args;
        va_start(args, format);

        GetDriver()->LogLine(format, args);
        
        va_end(args);
    }
}
