// Created by Ian Copland on 2016-05-06
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

#include "../ICBenchmark/ICBenchmark.h"
#include "../ICMemory/ICMemory.h"

namespace ICMemoryBenchmark
{
	namespace
	{
		constexpr std::int32_t k_numIterations = 10000;
		constexpr std::int32_t k_allocationSize = 10 * 1024 * 1024;
	}

	/// A benchmark for measuring the time taken to perform a large number of large 
	/// allocations with various allocators and pools.
	///
	IC_BENCHMARKGROUP(LargeAllocations)
	{
		/// Performs the benchmark with the standard allocator.
		///
		IC_BENCHMARK(StandardAllocator)
		{
			IC_STARTTIMER();

			for (int i = 0; i < k_numIterations; ++i)
			{
				auto a = std::unique_ptr<std::uint8_t[]>(new uint8_t[k_allocationSize]);
				auto b = std::unique_ptr<std::uint8_t[]>(new uint8_t[k_allocationSize]);
				auto c = std::unique_ptr<std::uint8_t[]>(new uint8_t[k_allocationSize]);
				auto d = std::unique_ptr<std::uint8_t[]>(new uint8_t[k_allocationSize]);
				auto e = std::unique_ptr<std::uint8_t[]>(new uint8_t[k_allocationSize]);
			}

			IC_STOPTIMER();
		}

		/// Performs the benchmark with a BuddyAllocator.
		///
		IC_BENCHMARK(BuddyAllocator)
		{
			constexpr std::int32_t k_allocatorSize = 128 * 1024 * 1024;
			constexpr std::int32_t k_allocatorMinBlockSize = 1024;

			IC::BuddyAllocator allocator(k_allocatorSize, k_allocatorMinBlockSize);

			IC_STARTTIMER();

			for (int i = 0; i < k_numIterations; ++i)
			{
				auto a = IC::MakeUniqueArray<std::uint8_t>(allocator, k_allocationSize);
				auto b = IC::MakeUniqueArray<std::uint8_t>(allocator, k_allocationSize);
				auto c = IC::MakeUniqueArray<std::uint8_t>(allocator, k_allocationSize);
				auto d = IC::MakeUniqueArray<std::uint8_t>(allocator, k_allocationSize);
				auto e = IC::MakeUniqueArray<std::uint8_t>(allocator, k_allocationSize);
			}

			IC_STOPTIMER();
		}

		/// Performs the benchmark with a LinearAllocator.
		///
		IC_BENCHMARK(LinearAllocator)
		{
			constexpr std::int32_t k_pageSize = 64 * 1024 * 1024;

			IC::LinearAllocator allocator(k_pageSize);

			IC_STARTTIMER();

			for (int i = 0; i < k_numIterations; ++i)
			{
				auto a = IC::MakeUniqueArray<std::uint8_t>(allocator, k_allocationSize);
				auto b = IC::MakeUniqueArray<std::uint8_t>(allocator, k_allocationSize);
				auto c = IC::MakeUniqueArray<std::uint8_t>(allocator, k_allocationSize);
				auto d = IC::MakeUniqueArray<std::uint8_t>(allocator, k_allocationSize);
				auto e = IC::MakeUniqueArray<std::uint8_t>(allocator, k_allocationSize);

				allocator.Reset();
			}

			IC_STOPTIMER();
		}

		/// Performs the benchmark with a LinearAllocator backed by a BuddyAllocator
		///
		IC_BENCHMARK(LinearAllocatorBackedByBuddyAllocator)
		{
			constexpr std::int32_t k_buddyAllocatorSize = 128 * 1024 * 1024;
			constexpr std::int32_t k_buddyAllocatorMinBlockSize = 64 * 1024 * 1024;
			constexpr std::int32_t k_linearAllocatorPageSize = 64 * 1024 * 1024;

			IC::BuddyAllocator buddyAllocator(k_buddyAllocatorSize, k_buddyAllocatorMinBlockSize);
			IC::LinearAllocator linearAllocator(buddyAllocator, k_linearAllocatorPageSize);

			IC_STARTTIMER();

			for (int i = 0; i < k_numIterations; ++i)
			{
				auto a = IC::MakeUniqueArray<std::uint8_t>(linearAllocator, k_allocationSize);
				auto b = IC::MakeUniqueArray<std::uint8_t>(linearAllocator, k_allocationSize);
				auto c = IC::MakeUniqueArray<std::uint8_t>(linearAllocator, k_allocationSize);
				auto d = IC::MakeUniqueArray<std::uint8_t>(linearAllocator, k_allocationSize);
				auto e = IC::MakeUniqueArray<std::uint8_t>(linearAllocator, k_allocationSize);

				linearAllocator.Reset();
			}

			IC_STOPTIMER();
		}
	}
}