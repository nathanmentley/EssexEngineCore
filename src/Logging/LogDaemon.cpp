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

using EssexEngine::Core::Models::IMessage;
using EssexEngine::Core::Models::IMessageResponse;

using EssexEngine::Core::Logging::LogDaemon;
using EssexEngine::Core::Logging::LogDaemonMessageResponse;
using EssexEngine::Core::Logging::Messages::MessageType;

LogDaemon::LogDaemon(WeakPointer<Context> _context):BaseProcessDaemon(_context) {}
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
        WeakPointer<IMessage>(
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
        WeakPointer<IMessage>(
            new LogDaemonMessage(
                MessageType::LogLine,
                message
            )
        )
    );
}

//Message Parser
WeakPointer<IMessageResponse> LogDaemon::ProcessMessage(WeakPointer<IMessage> msg) {
    switch(msg->GetType()) {
        case MessageType::DebugLine:
            return _DebugLine(msg.Cast<LogDaemonMessage>()).Cast<IMessageResponse>();
        case MessageType::LogLine:
            return _LogLine(msg.Cast<LogDaemonMessage>()).Cast<IMessageResponse>();
    }

    return WeakPointer<IMessageResponse>();
}

//Logic
WeakPointer<LogDaemonMessageResponse> LogDaemon::_DebugLine(WeakPointer<LogDaemonMessage> message) {
    if(HasDriver()) {
        GetDriver()->LogLine("DEBUG: " + message->GetMessage());
    }

    return WeakPointer<LogDaemonMessageResponse>(
        new LogDaemonMessageResponse()
    );
}

WeakPointer<LogDaemonMessageResponse> LogDaemon::_LogLine(WeakPointer<LogDaemonMessage> message) {
    if(HasDriver()) {
        GetDriver()->LogLine(message->GetMessage());
    }

    return WeakPointer<LogDaemonMessageResponse>(
        new LogDaemonMessageResponse()
    );
}
