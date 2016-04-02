// Created by Ian Copland on 2016-04-02
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

#include "LinearLargeAllocationsBenchmark.h"

namespace
{
    const std::int32_t k_numIterations = 10000;
    const std::int32_t k_allocationSize = 10'000'000;
    const std::int32_t k_buddyAllocatorSize = 128 * 1024 * 1024;
    const std::int32_t k_buddyAllocatorMinBlockSize = 1024;
    const std::int32_t k_linearAllocatorPageSize = 64 * 1024 * 1024;
}

//------------------------------------------------------------------------------
LinearLargeAllocationsBenchmark::LinearLargeAllocationsBenchmark(IC::BenchmarkSystem& benchmarkSystem)
    : Benchmark(benchmarkSystem), m_buddyAllocator(k_buddyAllocatorSize, k_buddyAllocatorMinBlockSize), m_linearAllocator(m_buddyAllocator, k_linearAllocatorPageSize)
{
}

//------------------------------------------------------------------------------
std::string LinearLargeAllocationsBenchmark::GetDescription() const
{
    return "10,000 large allocations with the Buddy Allocator";
}

//------------------------------------------------------------------------------
void LinearLargeAllocationsBenchmark::Run()
{
    for (int i = 0; i < k_numIterations; ++i)
    {
        auto a = IC::MakeUniqueArray<std::uint8_t>(m_linearAllocator, k_allocationSize);
        auto b = IC::MakeUniqueArray<std::uint8_t>(m_linearAllocator, k_allocationSize);
        auto c = IC::MakeUniqueArray<std::uint8_t>(m_linearAllocator, k_allocationSize);
        auto d = IC::MakeUniqueArray<std::uint8_t>(m_linearAllocator, k_allocationSize);
        auto e = IC::MakeUniqueArray<std::uint8_t>(m_linearAllocator, k_allocationSize);

        m_linearAllocator.Reset();
    }

    Complete();
}
