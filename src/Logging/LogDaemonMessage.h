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

#include <EssexEngineCore/IMessage.h>

namespace EssexEngine{
namespace Core{
namespace Logging{
    namespace Messages {
        enum MessageType {
            LogLine = 1,
            DebugLine = 2
        };
    }

    class LogDaemonMessage: public IMessage
    {
        public:
            LogDaemonMessage(Messages::MessageType _type, std::string _message):
            IMessage() {
                type = _type;
                message = _message;
            }

            Messages::MessageType GetType() {
                return type;
            }

            std::string GetMessage() {
                return message;
            }
        private:
            Messages::MessageType type;
            std::string message;
    };
}}};

