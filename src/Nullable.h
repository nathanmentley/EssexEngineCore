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
  
namespace EssexEngine{
    template<class Type> class Nullable 
    {
        public:
            Nullable() : value(), isSet(false) {}
            Nullable(Type _value) : value(_value), isSet(true) {} 
            Nullable(const Nullable& other) : value(other.value), isSet(other.isSet) {}
        
            friend void swap(Nullable& a, Nullable& b)
            {
                std::swap(a.isSet, b.isSet);
                std::swap(a.value, b.value);
            }
        
            Nullable& operator=(Nullable other) 
            {
                swap(*this, other);
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
        private:
            void Set(Type _value) {
                value = _value;
                isSet = true;
            }
            Type value;
            bool isSet;
    };
};