// Created by Ian Copland on 2016-01-31
//
// The MIT License(MIT)
// 
// Copyright(c) 2016 Ian Copland
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

#ifndef _ICBENCHMARK_BENCHMARK_H_
#define _ICBENCHMARK_BENCHMARK_H_

#include "ForwardDeclarations.h"

#include <memory>
#include <queue>
#include <string>

namespace IC
{
    /// A single performance benchmark. The test() method should be overriden to
    /// include performance critical code. Once this code has finished, the complete()
    /// method should be called. The time taken between test() and complete() being
    /// called will be stored and compared to other tests.
    ///
    /// Note that construction and destruction will not be included in the output time,
    /// so any setup/cleanup should be performed in the constructor/destructor.
    ///
    /// This is thread-safe.
    ///
    class Benchmark
    {
    public:
        /// Constructs a new benchmark with the given reference to the benchmark system.
        ///
        Benchmark(BenchmarkSystem& in_benchmarkSystem);

        /// This must be thread-safe.
        ///
        /// @return a name for the benchmark.
        ///
        virtual std::string getName() const = 0;

        virtual ~Benchmark() { };

    protected:
        friend class BenchmarkSystem;

        /// Runs a benchmark test. This should be overridden to include performance
        /// critical code. Once the code has finished executing, complete() should
        /// be called. The test can be multi-threaded, in which case complete() will
        /// be called after the the test() method has finished running().
        ///
        virtual void run() = 0;

        /// Completes the current test. This is thread-safe, but should only be called
        /// while a benchmark test is active.
        ///
        void complete();

    private:
        BenchmarkSystem& m_benchmarkSystem;
    };
}

#endif