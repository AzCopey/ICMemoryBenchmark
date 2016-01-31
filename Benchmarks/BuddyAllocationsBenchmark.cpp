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

#include "BuddyAllocationsBenchmark.h"

namespace
{
    const std::int32_t k_numAllocations = 100000;
    const std::int32_t k_allocationSize = 100000;
    const std::int32_t k_allocatorSize = 1024 * 1024;
    const std::int32_t k_allocatorMinBlockSize = 128;
}

//------------------------------------------------------------------------------
BuddyAllocationsBenchmark::BuddyAllocationsBenchmark(IC::BenchmarkSystem& in_benchmarkSystem)
    : Benchmark(in_benchmarkSystem), m_allocator(k_allocatorSize, k_allocatorMinBlockSize)
{
}

//------------------------------------------------------------------------------
std::string BuddyAllocationsBenchmark::getName() const
{
    return "BuddyAllocator - Basic Allocations";
}

//------------------------------------------------------------------------------
void BuddyAllocationsBenchmark::run()
{
    for (int i = 0; i < k_numAllocations; ++i)
    {
        auto d = IC::makeUniqueArray<std::uint8_t>(m_allocator, k_allocationSize);
    }

    complete();
}
