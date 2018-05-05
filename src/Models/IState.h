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
namespace Core{
namespace Models{
    class IState
    {
    public:
        virtual ~IState() {};

        virtual void Setup() = 0;
        
        virtual void Logic() = 0;
        virtual void Render() = 0;
        
        virtual bool PauseUnder() = 0;
        
        bool completed;
    };
}}};
