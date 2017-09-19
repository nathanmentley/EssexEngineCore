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
 
#include <memory>
 
#include <EssexEngineCore/SmartPointer.h>
#include <EssexEngineCore/WeakPointer.h>
  
namespace EssexEngine{
    template<class Type> class UniquePointer: public SmartPointer<Type>
    {
        public:
            UniquePointer(Type* _data): SmartPointer<Type>(_data) {
                ptr = std::unique_ptr<Type>(_data);
            }
            UniquePointer(): SmartPointer<Type>() {}
 
            Type* operator->() {
                return ptr.get();
            }

            WeakPointer<Type> GetWeakPointer() {
                return WeakPointer<Type>(ptr.get());
            }
        private:
            std::unique_ptr<Type> ptr;
    };
};