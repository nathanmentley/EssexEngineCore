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

#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineCore/SmartPointer.h>
 
namespace EssexEngine{
    template<class Type> class SharedPointer: public SmartPointer<Type>
    {
        public:
            SharedPointer(Type* _data): SmartPointer<Type>(_data) {
                ptr = std::shared_ptr<Type>(_data);
            }
            SharedPointer(): SmartPointer<Type>() {}

            Type* operator->() {
                return ptr.get();
            }
            
            WeakPointer<Type> GetWeakPointer() {
                return WeakPointer<Type>(ptr.get());
            }

            SharedPointer<Type> Clone() {
                return SharedPointer<Type>(ptr);
            }
        protected:
            SharedPointer(std::shared_ptr<Type> _ptr) {
                ptr = _ptr;
            }
        private:
            std::shared_ptr<Type> ptr;
    };
};