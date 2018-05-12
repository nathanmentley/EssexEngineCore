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

#include <utility>
#include <functional>
 
#include <EssexEngineCore/Nullable.h>
#include <EssexEngineCore/ISmartPointer.h>
#include <EssexEngineCore/WeakPointer.h>
  
namespace EssexEngine{
    template<class Type> class BaseUniquePointer: public Nullable<Type*>, public ISmartPointer<Type>
    {
        public:
            BaseUniquePointer(Type* _data, std::function<void(Type*)> _logic): Nullable<Type*>(_data) {
                ptr = _data;
                moved = false;
                logic = _logic;
            }
            
            BaseUniquePointer(const std::function<void(Type*)> _logic) : Nullable<Type*>() {
                moved = false;
                logic = _logic;
            }
            
            ~BaseUniquePointer() {
                if(!moved && Nullable<Type*>::HasValue()) {
                    if(logic) {
                        logic(Get());
                    }
                }
            }

            BaseUniquePointer<Type>(BaseUniquePointer<Type>&& other) {
                ptr = other.ptr;

                if(other.HasValue()) {
                    Nullable<Type*>::Set(other.Get());
                } else {
                    Nullable<Type*>::Reset();
                }

                other.moved = true;
                other.logic = logic;
            }
 
            void swap(BaseUniquePointer<Type>& other)
            {
                std::swap(ptr, other.ptr);
                std::swap(moved, other.moved);
                logic.swap(other.logic);
                Nullable<Type*>::swap(other);
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

            void Replace(Type* _data) {
                Reset();
                
                ptr = _data;
                Nullable<Type*>::Set(_data);
            }

            //Nullable Overrides
            void Reset() {
                if(!moved && Nullable<Type*>::HasValue()) {
                    Nullable<Type*>::Reset();
                    if(logic) {
                        logic(Get());
                    }
                } 
            }
        private:
            std::function<void(Type*)> logic;
            Type* ptr;
            bool moved;
    };
};
