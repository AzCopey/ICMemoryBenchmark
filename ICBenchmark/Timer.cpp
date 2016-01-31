// Created by Ian Copland on 2015-09-17
//
// The MIT License(MIT)
// 
// Copyright(c) 2015 Ian Copland
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "Timer.h"

#include <cassert>

namespace IC
{
    //-----------------------------------------------------------------------------
    Timer::Timer(bool in_startImmediately) noexcept
    {
        if (in_startImmediately == true)
        {
            start();
        }
    }

    //-----------------------------------------------------------------------------
    void Timer::start(bool in_reset) noexcept
    {
        assert(!m_running);

        m_running = true;

        if (in_reset == true)
        {
            m_start = std::chrono::high_resolution_clock::now();
        }
    }

    //-----------------------------------------------------------------------------
    void Timer::stop() noexcept
    {
        assert(m_running);

        std::chrono::milliseconds elapsedTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_start);
        m_elapsedTime = static_cast<std::uint32_t>(elapsedTimeMs.count());

        m_running = false;
    }

    //-----------------------------------------------------------------------------
    std::uint32_t Timer::getElapsedTime() const noexcept
    {
        return m_elapsedTime;
    }
}