// Created by Ian Copland on 2016-05-05
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

#ifndef _ICBENCHMARK_BENCHMARKREGISTERY_H_
#define _ICBENCHMARK_BENCHMARKREGISTERY_H_

#include "Benchmark.h"

#include <vector>

namespace IC
{
    /// A singleton which contains a list of all registered benchmarks. Typically
    /// all tests are registered during static initialisation time via the macros
    /// declared in BenchmarkGroup.h.
    ///
    /// This is not thread-safe.
    ///
    class BenchmarkRegistry final
    {
    public:
        /// @return The singleton instance of the BenchmarkRegistry.
        ///
        static BenchmarkRegistry& Get() noexcept;

        /// Adds a new benchmark to the registry.
        ///
        /// @param benchmark
        ///        The benchmark which should be added to the registry.
        ///
        void RegisterBenchmark(const Benchmark& benchmark) noexcept;

        /// @return The list of all currently registered benchmarks.
        ///
        const std::vector<Benchmark>& GetBenchmarks() const noexcept { return m_benchmarks; }

    private:
        BenchmarkRegistry() = default;
        BenchmarkRegistry(const BenchmarkRegistry&) = delete;
        BenchmarkRegistry& operator=(const BenchmarkRegistry&) = delete;
        BenchmarkRegistry(BenchmarkRegistry&&) = delete;
        BenchmarkRegistry& operator=(BenchmarkRegistry&&) = delete;

        std::vector<Benchmark> m_benchmarks;
    };
}

#endif