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

using EssexEngine::WeakPointer;

using EssexEngine::Core::IMessage;

using EssexEngine::Core::Logging::LogDaemon;
using EssexEngine::Core::Logging::Messages::MessageType;

LogDaemon::LogDaemon(WeakPointer<Context> _context):BaseQueuedDaemon(_context) {
}

LogDaemon::~LogDaemon() {}

//Message Generator
void LogDaemon::DebugLine(std::string format, ...) {
    va_list args;
    va_start(args, format);

    char* buffer;
    vasprintf(&buffer, format.c_str(), args);
    std::string message = std::string(buffer);

    va_end(args);

    PushMessage(
        WeakPointer<LogDaemonMessage>(
            new LogDaemonMessage(
                MessageType::DebugLine,
                message
            )
        )
    );
}

void LogDaemon::LogLine(std::string format, ...) {
    va_list args;
    va_start(args, format);

    char* buffer;
    vasprintf(&buffer, format.c_str(), args);
    std::string message = std::string(buffer);

    va_end(args);

    PushMessage(
        WeakPointer<LogDaemonMessage>(
            new LogDaemonMessage(
                MessageType::LogLine,
                message
            )
        )
    );
}

//Message Parser
void LogDaemon::ProcessMessage(WeakPointer<LogDaemonMessage> msg) {
    switch(msg->GetType()) {
        case MessageType::DebugLine:
            _DebugLine(msg);
            break;
        case MessageType::LogLine:
            _LogLine(msg);
            break;
    }
}

//Logic
void LogDaemon::_DebugLine(WeakPointer<LogDaemonMessage> message) {
    if(HasDriver()) {
        GetDriver()->LogLine("DEBUG: " + message->GetMessage());
    }
}

void LogDaemon::_LogLine(WeakPointer<LogDaemonMessage> message) {
    if(HasDriver()) {
        GetDriver()->LogLine(message->GetMessage());
    }
}
