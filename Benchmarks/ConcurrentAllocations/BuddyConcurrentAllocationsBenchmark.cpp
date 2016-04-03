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

#include "BuddyConcurrentAllocationsBenchmark.h"

namespace ICMemoryBenchmark
{
    namespace
    {
        constexpr std::int32_t k_numIterations = 10'000'000;
        constexpr std::int32_t k_numThreads = 10;
        constexpr std::int32_t k_allocatorSize = 1024;
        constexpr std::int32_t k_allocatorMinBlockSize = 16;

        constexpr std::int32_t k_numIterationsPerThread = k_numIterations / k_numThreads;

        /// A small example struct.
        ///
        struct ConcurrentStruct final
        {
            std::uint32_t m_a;
            std::uint64_t m_b;
            std::uint32_t m_c;
            std::uint64_t m_d;
        };
    }

    //------------------------------------------------------------------------------
    BuddyConcurrentAllocationsBenchmark::BuddyConcurrentAllocationsBenchmark(IC::BenchmarkSystem& benchmarkSystem)
        : Benchmark(benchmarkSystem), m_allocator(k_allocatorSize, k_allocatorMinBlockSize)
    {
    }

    //------------------------------------------------------------------------------
    std::string BuddyConcurrentAllocationsBenchmark::GetDescription() const
    {
        return "1,000,000 concurrent allocations with the Buddy Allocator";
    }

    //------------------------------------------------------------------------------
    void BuddyConcurrentAllocationsBenchmark::Run()
    {
        std::vector<std::thread> threads;

        for (int i = 0; i < k_numThreads; ++i)
        {
            threads.push_back(std::thread([=]()
            {
                for (int j = 0; j < k_numIterationsPerThread; ++j)
                {
                    auto a = IC::MakeUnique<std::uint32_t>(m_allocator);
                    auto b = IC::MakeUnique<std::uint64_t>(m_allocator);
                    auto e = IC::MakeUnique<ConcurrentStruct>(m_allocator);
                }
            }));
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        Complete();
    }
}
