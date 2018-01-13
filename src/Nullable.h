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

#include <utility>

namespace EssexEngine{
    template<class Type> class Nullable 
    {
        public:
            Nullable<Type>() : value(), isSet(false) {}
            Nullable<Type>(Type _value) : value(_value), isSet(true) {} 
            Nullable<Type>(const Nullable& other) : value(other.value), isSet(other.isSet) {}
        
            void swap(Nullable<Type>& other)
            {
                std::swap(isSet, other.isSet);
                std::swap(value, other.value);
            }
        
            Nullable<Type>& operator=(Nullable<Type> other) 
            {
                swap(other);
                return *this;
            }
        
            Type operator=(Type _value) {
                Set(_value);
                return Get();
            }

            bool operator==(Type _value) {
                return HasValue() && value == _value;
            }

            operator Type() const {
                return Get();
            }
        
            Type Get() const 
            {
                if (isSet) {
                    return value;
                } else {
                    return Type();
                }
            }
        
            bool HasValue() const {
                return isSet;
            }
        
            void Reset() {
                isSet = false;
                value = Type();
            }
        protected:
            void Set(Type _value) {
                isSet = true;
                value = _value;
            }
        private:
            Type value;
            bool isSet;
    };
};
