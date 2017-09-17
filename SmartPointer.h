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

#include <EssexEngineCore/Nullable.h>
 
namespace EssexEngine{
    template<class Type> class SmartPointer: public Nullable<Type*>
    {
        public:
            SmartPointer(Type* _data): Nullable<Type*>(_data) { weakPointer = _data; }
            SmartPointer(): Nullable<Type*>() {}

            Type* operator->() { return weakPointer; };
            Type* Get() { return weakPointer; }
/*
            bool operator== (const SmartPointer<Type> &other)
            {
                return (Get() == other.Get());
            }
             
            bool operator!= (const SmartPointer<Type> &other)
            {
                return !(Get() == other.Get());
            }*/
        private:
            Type* weakPointer;
    };
};