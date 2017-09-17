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
  
namespace EssexEngine{
    template<class Type> class WeakPointer: public SmartPointer<Type>
    {
        public:
            WeakPointer(Type* _data): SmartPointer<Type>(_data) {
                ptr = _data;
            }
            WeakPointer(): SmartPointer<Type>() {}
 
            Type* operator->() {
                return ptr;
            }

            template<class ToType> WeakPointer<ToType> Cast() {
                return WeakPointer<ToType>((ToType*)ptr);
            }
        private:
            Type* ptr;
    };
};