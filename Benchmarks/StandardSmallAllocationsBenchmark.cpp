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

#include "StandardSmallAllocationsBenchmark.h"

namespace
{
    const std::int32_t k_numIterations = 1000000;
}

//------------------------------------------------------------------------------
StandardSmallAllocationsBenchmark::StandardSmallAllocationsBenchmark(IC::BenchmarkSystem& in_benchmarkSystem)
    : Benchmark(in_benchmarkSystem)
{
}

//------------------------------------------------------------------------------
std::string StandardSmallAllocationsBenchmark::getDescription() const
{
    return "1,000,000 small allocations with the standard allocator";
}

//------------------------------------------------------------------------------
void StandardSmallAllocationsBenchmark::run()
{
    for (int i = 0; i < k_numIterations; ++i)
    {
        auto a = std::unique_ptr<std::uint32_t>(new uint32_t);
        auto b = std::unique_ptr<std::uint32_t>(new uint32_t);
        auto c = std::unique_ptr<std::uint32_t>(new uint32_t);
        auto d = std::unique_ptr<std::uint32_t>(new uint32_t);
        auto e = std::unique_ptr<std::uint32_t>(new uint32_t);
    }

    complete();
}
