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

#include <EssexEngineCore/LogDriver.h>

EssexEngine::Core::Logging::LogDriver::LogDriver(WeakPointer<Context> _context): BaseDriver(_context) {}

EssexEngine::Core::Logging::LogDriver::~LogDriver() { }

void EssexEngine::Core::Logging::LogDriver::LogLine(const char *format, ...) {
    va_list args;
    va_start(args, format);

    vprintf(format, args);
    printf("\n");

    va_end(args);
}
