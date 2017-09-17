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

#include <string>
#include <list>

#include <EssexEngineCore/EssexEnvironment.h>
#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineCore/Context.h>
#include <EssexEngineCore/ILogDriver.h>
#include <EssexEngineCore/IDaemon.h>

namespace EssexEngine{
namespace Daemons{
	template <class DriverType> class BaseDaemon: public Core::IDaemon
	{
	      public:
                  BaseDaemon(WeakPointer<Context> _context) {
                        context = _context;
                  }
                  ~BaseDaemon() {}
                  virtual void Init() = 0;
                  virtual std::string GetDaemonName() = 0;
                  virtual std::string GetDaemonVersion() = 0;

            protected:
                  bool HasDriver() { return GetContext()->template HasDriver<DriverType>(); }
                  WeakPointer<DriverType> GetDriver() { return GetContext()->template GetDriver<DriverType>(); }
                  WeakPointer<Context> GetContext() { return context; }

	      private:
                  WeakPointer<Context> context;
	};
}};