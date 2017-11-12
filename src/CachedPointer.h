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
 
#include <EssexEngineCore/Nullable.h>
#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineCore/IResourceCache.h>
  
namespace EssexEngine{
    template<class Type> class CachedPointer: public Nullable<Type*>
    {
        public:
            CachedPointer(std::string _key, Type* _data, Core::Utils::IResourceCache<Type>* _cache): Nullable<Type*>(_data) {
                key = _key;
                ptr = _data;
                cache = _cache;
                moved = false;

                cache->IncrementUsage(key);
            }
            CachedPointer() : Nullable<Type*>() {
                moved = false;
            }
            ~CachedPointer() {
                if(!moved && Nullable<Type*>::HasValue()) {
                    cache->ClearUsage(key);
                }
            }
            CachedPointer<Type>(CachedPointer<Type>&& other) {
                key = other.key;
                ptr = other.ptr;
                cache = other.cache;

                if(other.HasValue()) {
                    Nullable<Type*>::Set(other.Get());
                } else {
                    Nullable<Type*>::Reset();
                }

                other.moved = true;
            }

            Type* operator->() {
                return ptr;
            }

            WeakPointer<Type> ToWeakPointer() {
                return WeakPointer<Type>(ptr);
            }
        private:
            std::string key;
            Type* ptr;
            Core::Utils::IResourceCache<Type>* cache;
            bool moved;
    };
};
