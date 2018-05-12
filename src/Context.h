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

#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineCore/EssexEnvironment.h>
#include <EssexEngineCore/IDriver.h>
#include <EssexEngineCore/IDaemon.h>

#include <typeindex>
#include <typeinfo>
#include <unordered_map>

namespace EssexEngine{
    class Context
    {
        public:
            Context() {
                daemonMap = std::unordered_map<std::type_index, WeakPointer<Core::IDaemon>>();
                driverMap = std::unordered_map<std::type_index, WeakPointer<Core::IDriver>>();
            }
            ~Context() {}
            //Drivers
            template<class DriverType> WeakPointer<DriverType> GetDriver() {
                return WeakPointer<DriverType>((DriverType*)driverMap[typeid(DriverType)].Get());
            }
            template<class DriverType> bool HasDriver() {
                std::unordered_map<std::type_index, WeakPointer<Core::IDriver>>::const_iterator got = driverMap.find(typeid(DriverType));
                return !(got == driverMap.end());
            }
            template<class DriverType> void RegisterDriver(WeakPointer<DriverType> driver) {
                driverMap[typeid(DriverType)] = WeakPointer<Core::IDriver>(driver.Get());
                driver->Init();
            }
            //Daemons
            template<class DaemonType> WeakPointer<DaemonType> GetDaemon() {
                return WeakPointer<DaemonType>((DaemonType*)daemonMap[typeid(DaemonType)].Get());
            }
            template<class DaemonType> bool HasDaemon() {
                std::unordered_map<std::type_index, WeakPointer<Core::IDaemon>>::const_iterator got = daemonMap.find(typeid(DaemonType));
                return !(got == daemonMap.end());
            }
            template<class DaemonType> void RegisterDaemon(WeakPointer<DaemonType> daemon) {
                daemonMap[typeid(DaemonType)] = WeakPointer<Core::IDaemon>(daemon.Get());
                daemon->Init();
            }
        private:
            std::unordered_map<std::type_index, WeakPointer<Core::IDaemon>> daemonMap;
            std::unordered_map<std::type_index, WeakPointer<Core::IDriver>> driverMap;
    };
};
