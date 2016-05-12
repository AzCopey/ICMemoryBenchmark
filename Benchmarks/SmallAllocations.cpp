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

#include "../ICBenchmark/ICBenchmark.h"
#include "../ICMemory/ICMemory.h"

namespace ICMemoryBenchmark
{
	namespace
	{
		constexpr std::int32_t k_numIterations = 1000000;

		/// A small example struct.
		///
		struct SmallStruct final
		{
			std::uint32_t m_a;
			std::uint64_t m_b;
			std::uint32_t m_c;
			std::uint64_t m_d;
		};
	}

	/// A benchmark for measuring the time taken to perform a large number of small 
	/// allocations with various allocators and pools.
	///
	IC_BENCHMARKGROUP(SmallAllocations)
	{
		/// Performs the benchmark with the standard allocator.
		///
		IC_BENCHMARK(StandardAllocator)
		{
			IC_STARTTIMER();

			for (int i = 0; i < k_numIterations; ++i)
			{
				auto a = std::unique_ptr<std::uint32_t>(new uint32_t);
				auto b = std::unique_ptr<std::uint64_t>(new uint64_t);
				auto c = std::unique_ptr<SmallStruct>(new SmallStruct());
			}

			IC_STOPTIMER();
		}

		/// Performs the benchmark with a BuddyAllocator.
		///
		IC_BENCHMARK(BuddyAllocator)
		{
			constexpr std::size_t k_allocatorSize = 4 * 1024;

			IC::BuddyAllocator allocator(k_allocatorSize);

			IC_STARTTIMER();

			for (int i = 0; i < k_numIterations; ++i)
			{
				auto a = IC::MakeUnique<std::uint32_t>(allocator);
				auto b = IC::MakeUnique<std::uint64_t>(allocator);
				auto c = IC::MakeUnique<SmallStruct>(allocator);
			}

			IC_STOPTIMER();
		}

		/// Performs the benchmark with a LinearAllocator.
		///
		IC_BENCHMARK(LinearAllocator)
		{
			constexpr std::size_t k_allocatorSize = 4 * 1024;

			IC::LinearAllocator allocator(k_allocatorSize);

			IC_STARTTIMER();

			for (int i = 0; i < k_numIterations; ++i)
			{
				{
					auto a = IC::MakeUnique<std::uint32_t>(allocator);
					auto b = IC::MakeUnique<std::uint64_t>(allocator);
					auto c = IC::MakeUnique<SmallStruct>(allocator);
				}

				allocator.Reset();
			}

			IC_STOPTIMER();
		}

		/// Performs the benchmark with a PagedLinearAllocator.
		///
		IC_BENCHMARK(PagedLinearAllocator)
		{
			constexpr std::size_t k_allocatorSize = 4 * 1024;

			IC::PagedLinearAllocator allocator(k_allocatorSize);

			IC_STARTTIMER();

			for (int i = 0; i < k_numIterations; ++i)
			{
				{
					auto a = IC::MakeUnique<std::uint32_t>(allocator);
					auto b = IC::MakeUnique<std::uint64_t>(allocator);
					auto c = IC::MakeUnique<SmallStruct>(allocator);
				}

				allocator.Reset();
			}

			IC_STOPTIMER();
		}

		/// Performs the benchmark with a BlockAllocator
		///
		IC_BENCHMARK(BlockAllocator)
		{
			constexpr std::size_t k_blockSize = 48;
			constexpr std::size_t k_numBlocks = 3;

			IC::BlockAllocator allocator(k_blockSize, k_numBlocks);

			IC_STARTTIMER();

			for (int i = 0; i < k_numIterations; ++i)
			{
				auto a = IC::MakeUnique<std::uint32_t>(allocator);
				auto b = IC::MakeUnique<std::uint64_t>(allocator);
				auto c = IC::MakeUnique<SmallStruct>(allocator);
			}

			IC_STOPTIMER();
		}

		/// Performs the benchmark with a PagedBlockAllocator
		///
		IC_BENCHMARK(PagedBlockAllocator)
		{
			constexpr std::size_t k_blockSize = 48;
			constexpr std::size_t k_numBlocks = 3;

			IC::PagedBlockAllocator allocator(k_blockSize, k_numBlocks);

			IC_STARTTIMER();

			for (int i = 0; i < k_numIterations; ++i)
			{
				auto a = IC::MakeUnique<std::uint32_t>(allocator);
				auto b = IC::MakeUnique<std::uint64_t>(allocator);
				auto c = IC::MakeUnique<SmallStruct>(allocator);
			}

			IC_STOPTIMER();
		}

		/// Performs the benchmark with a SmallObjectAllocator
		///
		IC_BENCHMARK(SmallObjectAllocator)
		{
			constexpr std::size_t k_allocatorSize = 1024;

			IC::SmallObjectAllocator allocator(k_allocatorSize);

			IC_STARTTIMER();

			for (int i = 0; i < k_numIterations; ++i)
			{
				auto a = IC::MakeUnique<std::uint32_t>(allocator);
				auto b = IC::MakeUnique<std::uint64_t>(allocator);
				auto c = IC::MakeUnique<SmallStruct>(allocator);
			}

			IC_STOPTIMER();
		}

		/// Performs the benchmark with ObjectPools
		///
		IC_BENCHMARK(ObjectPool)
		{
			constexpr std::size_t k_poolSize = 16;

			IC::ObjectPool<std::uint32_t> int32Pool(k_poolSize);
			IC::ObjectPool<std::uint64_t> int64Pool(k_poolSize);
			IC::ObjectPool<SmallStruct> smallStructPool(k_poolSize);

			IC_STARTTIMER();

			for (int i = 0; i < k_numIterations; ++i)
			{
				auto a = int32Pool.Create();
				auto b = int64Pool.Create();
				auto e = smallStructPool.Create();
			}

			IC_STOPTIMER();
		}

		/// Performs the benchmark with PagedObjectPools
		///
		IC_BENCHMARK(PagedObjectPool)
		{
			constexpr std::size_t k_poolSize = 16;

			IC::PagedObjectPool<std::uint32_t> int32Pool(k_poolSize);
			IC::PagedObjectPool<std::uint64_t> int64Pool(k_poolSize);
			IC::PagedObjectPool<SmallStruct> smallStructPool(k_poolSize);

			IC_STARTTIMER();

			for (int i = 0; i < k_numIterations; ++i)
			{
				auto a = int32Pool.Create();
				auto b = int64Pool.Create();
				auto e = smallStructPool.Create();
			}

			IC_STOPTIMER();
		}
	}
}