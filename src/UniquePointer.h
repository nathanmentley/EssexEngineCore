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
 
#include <EssexEngineCore/Nullable.h>
#include <EssexEngineCore/ISmartPointer.h>
#include <EssexEngineCore/WeakPointer.h>
  
namespace EssexEngine{
    template<class Type> class UniquePointer: public Nullable<Type*>, public ISmartPointer<Type>
    {
        public:
            UniquePointer(Type* _data): Nullable<Type*>(_data) {
                ptr = _data;
                moved = false;
            }
            UniquePointer() : Nullable<Type*>() {}
            ~UniquePointer() {
                if(!moved && Nullable<Type*>::HasValue()) {
                    delete Get();
                }
            }
            UniquePointer<Type>(UniquePointer<Type>&& other) {
                ptr = other.ptr;

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

            Type* Get() {
                return ptr;
            }

            WeakPointer<Type> ToWeakPointer() {
                return WeakPointer<Type>(ptr);
            }
        private:
            Type* ptr;
            bool moved;
    };
};
