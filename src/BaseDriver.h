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

#include <EssexEngineCore/EssexEnvironment.h>
#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineCore/Context.h>
#include <EssexEngineCore/ILogDriver.h>
#include <EssexEngineCore/IDriver.h>

namespace EssexEngine{
namespace Core{
namespace Drivers{
namespace Base{
    class BaseDriver: public IDriver
    {
        public:
            BaseDriver(WeakPointer<Context> _context) {
                context = _context;
            }
            ~BaseDriver() {}
            virtual std::string GetDriverName() = 0;
            virtual std::string GetDriverVersion() = 0;
        protected:
            WeakPointer<Context> GetContext() {
                return context;
            }
        private:
            WeakPointer<Context> context;
    };
}}}};
