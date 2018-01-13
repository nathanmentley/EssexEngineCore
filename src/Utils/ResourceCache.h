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
#include <utility>

#include <EssexEngineCore/IResourceCache.h>
#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineCore/CachedPointer.h>

#include <EssexEngineCore/LogDaemon.h>

namespace EssexEngine{
namespace Core{
namespace Utils{
    template<class KeyType, class ValueType> class ResourceCache: public IResourceCache<KeyType, ValueType>
	{
		public:
			ResourceCache(WeakPointer<Logging::LogDaemon> _log) {
                log = _log;

			    data = std::map<KeyType, WeakPointer<ValueType>>();
                usage = std::map<KeyType, uint32_t>();
			}
			~ResourceCache() {}

			bool HasKey(KeyType key) {
				return (data.find(key) != data.end());
			}

			CachedPointer<KeyType, ValueType> Get(KeyType key) {
                return std::move(CachedPointer<KeyType, ValueType>(key, data[key].Get(), this));
            }

			void Cache(KeyType key, WeakPointer<ValueType> value) {
                data.emplace(key, value);
                usage.emplace(key, 0);
            }
        
            void IncrementUsage(KeyType key) {
                usage[key]++;
            }

            void ClearUsage(KeyType key) {
                usage[key]--;

                if(usage[key] == 0) {
                    Clear(key);
                }
            }
        protected:
            void Clear(KeyType key) {
                if(HasKey(key)) {
                    delete data[key].Get();

                    data.erase(key);
                    usage.erase(key);
                }
            }
        private:
            WeakPointer<Logging::LogDaemon> log;

            std::map<KeyType, WeakPointer<ValueType>> data;
            std::map<KeyType, uint32_t> usage;
	};
}}};
