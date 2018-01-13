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
 
#include <EssexEngineCore/Nullable.h>  
#include <EssexEngineCore/ISmartPointer.h>
#include <EssexEngineCore/WeakPointer.h>

namespace EssexEngine{
    template<class Type> class SharedPointer: public Nullable<Type*>, public ISmartPointer<Type>
    {
        public:
            SharedPointer(Type* _data): Nullable<Type*>(_data) {
                ptr = _data;
                moved = false;

                //TODO: reference counting inc
            }
            SharedPointer() : Nullable<Type*>() {
                moved = false;
            }
            ~SharedPointer() {
                //TODO: check reference count
                if(!moved && Nullable<Type*>::HasValue()) {
                    delete Get();
                }
            }
            SharedPointer<Type>(SharedPointer<Type>&& other) {
                ptr = other.ptr;

                if(other.HasValue()) {
                    Nullable<Type*>::Set(other.Get());
                } else {
                    Nullable<Type*>::Reset();
                }

                other.moved = true;

                //TODO: Ensure counting inc doesn't happen.
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
