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

#include <map>
#include <memory>
#include <string>
#include <utility>

#include <EssexEngineCore/IResourceCache.h>
#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineCore/CachedPointer.h>

#include <EssexEngineCore/LogDaemon.h>

namespace EssexEngine{
namespace Core{
namespace Utils{
    template<class Type> class ResourceCache: public IResourceCache<Type>
	{
		public:
			ResourceCache(WeakPointer<Logging::LogDaemon> _log) {
                log = _log;

			    data = std::map<std::string, WeakPointer<Type>>();
                usage = std::map<std::string, uint32_t>();
			}
			~ResourceCache() {}

			bool HasKey(std::string key) {
				return (data.find(key) != data.end());
			}

			CachedPointer<Type> Get(std::string key) {
                return std::move(CachedPointer<Type>(key, data[key].Get(), this));
            }

			void Cache(std::string key, WeakPointer<Type> value) {
                data.emplace(key, value);
                usage.emplace(key, 0);
                
                //log->DebugLine("caching resource: [%s]", key.c_str());
            }
        
            void IncrementUsage(std::string key) {
                usage[key]++;
                //log->DebugLine("provisioning resource: %d [%s]", usage[key], key.c_str());
            }

            void ClearUsage(std::string key) {
                usage[key]--;
                //log->DebugLine("deprovisioning resource: %d [%s]", usage[key], key.c_str());

                if(usage[key] == 0) {
                    Clear(key);
                }
            }
        protected:
            void Clear(std::string key) {
                //log->DebugLine("deleting resource: [%s]", key.c_str());

                delete Get(key).Get();

                data.erase(key);
                usage.erase(key);
            }
        private:
            WeakPointer<Logging::LogDaemon> log;

            std::map<std::string, WeakPointer<Type>> data;
            std::map<std::string, uint32_t> usage;
	};
}}};
