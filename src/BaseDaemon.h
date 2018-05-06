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
      //!  A test class. 
      /*!
      A more elaborate class description.
      */
    template <class DriverType> class BaseDaemon: public Core::IDaemon
    {
            public:
                  //! A constructor.
                  /*!
                        A more elaborate description of the constructor.
                  */
                  BaseDaemon(WeakPointer<Context> _context) {
                        context = _context;
                  }
                  //! A destructor.
                  /*!
                        A more elaborate description of the destructor.
                  */
                  ~BaseDaemon() {}
                  //! A normal member taking two arguments and returning an integer value.
                  virtual void Init() = 0;
                  //! A normal member taking two arguments and returning an integer value.
                  /*!
                        \return The test results
                  */
                  virtual std::string GetDaemonName() = 0;
                  //! A normal member taking two arguments and returning an integer value.
                  /*!
                        \return The test results
                  */
                  virtual std::string GetDaemonVersion() = 0;

            protected:
                  //! A normal member taking two arguments and returning an integer value.
                  /*!
                        \return The test results
                  */
                  bool HasDriver() { return GetContext()->template HasDriver<DriverType>(); }
                  //! A normal member taking two arguments and returning an integer value.
                  /*!
                        \return The test results
                  */
                  WeakPointer<DriverType> GetDriver() { return GetContext()->template GetDriver<DriverType>(); }
                  //! A normal member taking two arguments and returning an integer value.
                  /*!
                        \return The test results
                  */
                  WeakPointer<Context> GetContext() { return context; }

            private:
                  //! A private variable.
                  /*!
                        Details.
                  */
                  WeakPointer<Context> context;
    };
}};
