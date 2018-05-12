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

#include <EssexEngineCore/Nullable.h>
#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineCore/IResourceCache.h>
  
namespace EssexEngine{
    template<class KeyType, class ValueType> class CachedPointer: public Nullable<ValueType*>
    {
        public:
            CachedPointer(KeyType _key, ValueType* _data, Core::Utils::IResourceCache<KeyType, ValueType>* _cache): Nullable<ValueType*>(_data) {
                key = _key;
                ptr = _data;
                cache = _cache;
                moved = false;

                cache->IncrementUsage(key);
            }
            CachedPointer() : Nullable<ValueType*>() {
                moved = false;
            }
            ~CachedPointer() {
                if(!moved && Nullable<ValueType*>::HasValue()) {
                    cache->ClearUsage(key);
                }
            }
            CachedPointer<KeyType, ValueType>(CachedPointer<KeyType, ValueType>&& other) {
                key = other.key;
                ptr = other.ptr;
                cache = other.cache;

                if(other.HasValue()) {
                    Nullable<ValueType*>::Set(other.Get());
                } else {
                    Nullable<ValueType*>::Reset();
                }

                other.moved = true;
            }

            ValueType* operator->() {
                return ptr;
            }

            WeakPointer<ValueType> ToWeakPointer() {
                return WeakPointer<ValueType>(ptr);
            }
        private:
            KeyType key;
            ValueType* ptr;
            Core::Utils::IResourceCache<KeyType, ValueType>* cache;
            bool moved;
    };
};
