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

#include <EssexEngineCore/LogDriver.h>

using EssexEngine::Core::Logging::LogDriver;

LogDriver::LogDriver(WeakPointer<Context> _context): BaseDriver(_context) {}

LogDriver::~LogDriver() { }

void LogDriver::LogLine(std::string format, va_list args) {
    vprintf(format.c_str(), args);
    printf("\n");
}
