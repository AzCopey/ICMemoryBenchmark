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

#ifndef _ICMEMORYBENCHMARK_BENCHMARKS_LARGEALLOCATIONS_STANDARDLARGEALLOCATIONSBENCHMARK_H_
#define _ICMEMORYBENCHMARK_BENCHMARKS_LARGEALLOCATIONS_STANDARDLARGEALLOCATIONSBENCHMARK_H_

#include "../../ICBenchmark/ICBenchmark.h"

namespace ICMemoryBenchmark
{
    /// A benchmark for testing allocation time with new/delete.
    ///
    class StandardLargeAllocationsBenchmark final : public IC::Benchmark
    {
    public:
        /// Initialises the benchmark.
        ///
        /// @param benchmarkSystem
        ///     The benchmark system.
        ///
        StandardLargeAllocationsBenchmark(IC::BenchmarkSystem& benchmarkSystem);

        /// @return The description of the benchmark.
        ///
        std::string GetDescription() const override;
    private:

        /// Performs the test.
        ///
        void Run() override;
    };
}

#endif