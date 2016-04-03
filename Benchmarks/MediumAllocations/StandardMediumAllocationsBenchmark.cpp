// Created by Ian Copland on 2016-04-03
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

#include "StandardMediumAllocationsBenchmark.h"

namespace ICMemoryBenchmark
{
    namespace
    {
        constexpr std::int32_t k_numIterations = 500'000;
        constexpr std::int32_t k_allocationSize = 10'000;
    }

    //------------------------------------------------------------------------------
    StandardMediumAllocationsBenchmark::StandardMediumAllocationsBenchmark(IC::BenchmarkSystem& benchmarkSystem)
        : Benchmark(benchmarkSystem)
    {
    }

    //------------------------------------------------------------------------------
    std::string StandardMediumAllocationsBenchmark::GetDescription() const
    {
        return "500,000 medium allocations with the standard allocator";
    }

    //------------------------------------------------------------------------------
    void StandardMediumAllocationsBenchmark::Run()
    {
        for (int i = 0; i < k_numIterations; ++i)
        {
            auto a = std::unique_ptr<std::uint8_t[]>(new uint8_t[k_allocationSize]);
            auto b = std::unique_ptr<std::uint8_t[]>(new uint8_t[k_allocationSize]);
            auto c = std::unique_ptr<std::uint8_t[]>(new uint8_t[k_allocationSize]);
            auto d = std::unique_ptr<std::uint8_t[]>(new uint8_t[k_allocationSize]);
            auto e = std::unique_ptr<std::uint8_t[]>(new uint8_t[k_allocationSize]);
        }

        Complete();
    }
}