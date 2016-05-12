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

#ifndef _ICBENCHMARK_TIMER_H_
#define _ICBENCHMARK_TIMER_H_

#include <chrono>
#include <cstdint>

namespace IC
{
    /// A simple timer for tracking elapsed time in milliseconds. By default a
    /// timer starts running when it is created. This can be disabled by passing
    /// false to the constructor.
    ///
    /// This is not thread-safe, and therefore each Timer instance should only be
    /// used on one thread at a time.
    ///
    class Timer final
    {
    public:
        /// Creates a new timer. The timer will start running immediately unless
        /// false is passed to the contructor.
        ///
        /// @param startImmediately
        ///        Whether or not the timer should be started immediately. Defaults to
        ///        True.
        ///
        Timer(bool startImmediately = true) noexcept;

        /// @return Wehther or not the timer is currently running.
        ///
        bool IsRunning() const noexcept { return m_running; }

        /// Starts the timer running. This is only needed if re-starting the timer
        /// or false was passed during construction. By default the timer will be
        /// reset when restarting, if resuming the timer is desired false can be
        /// passed in. This will assert if the Timer is already running when called.
        ///
        /// @param reset
        ///        Whether or not the timer should be reset. Defaults to true.
        ///
        void Start(bool reset = true) noexcept;

        /// Stops the timer running. This will assert if the timer is not running
        /// when called.
        ///
        void Stop() noexcept;

        /// @return The elapsed time in milliseconds, recorded the last time stop()
        /// was called.
        ///
        std::uint32_t GetElapsedTime() const noexcept;

    private:
        bool m_running = false;
        std::chrono::high_resolution_clock::time_point m_start;
        std::uint32_t m_elapsedTime = 0;
    };
}

#endif