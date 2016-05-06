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

#include <array>
#include <thread>

namespace ICMemoryBenchmark
{
	namespace
	{
		constexpr std::int32_t k_numThreads = 8;
		constexpr std::int32_t k_numIterationsPerThread = 1000000;
		constexpr std::int32_t k_allocationSize = 10 * 1024;

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

	/// A benchmark for measuring the time taken to perform a large number of
	/// allocations concurrently.
	///
	IC_BENCHMARKGROUP(ConcurrentAllocations)
	{
		/// Performs the benchmark with the standard allocator.
		///
		IC_BENCHMARK(StandardAllocator)
		{
			std::vector<std::thread> threads;

			IC_STARTTIMER();

			for (int i = 0; i < k_numThreads; ++i)
			{
				threads.push_back(std::thread([]()
				{
					for (int j = 0; j < k_numIterationsPerThread; ++j)
					{
						auto a = std::unique_ptr<std::uint32_t>(new uint32_t);
						auto b = std::unique_ptr<std::uint64_t>(new uint64_t);
						auto e = std::unique_ptr<SmallStruct>(new SmallStruct());
					}
				}));
			}

			for (auto& thread : threads)
			{
				thread.join();
			}

			IC_STOPTIMER();
		}

		/// Performs the benchmark with a BuddyAllocator.
		///
		IC_BENCHMARK(BuddyAllocator)
		{
			constexpr std::size_t k_allocatorSize = 4096;

			IC::BuddyAllocator allocator(k_allocatorSize);

			std::vector<std::thread> threads;

			IC_STARTTIMER();

			for (int i = 0; i < k_numThreads; ++i)
			{
				threads.push_back(std::thread([&allocator]()
				{
					for (int j = 0; j < k_numIterationsPerThread; ++j)
					{
						auto a = IC::MakeUnique<std::uint32_t>(allocator);
						auto b = IC::MakeUnique<std::uint64_t>(allocator);
						auto e = IC::MakeUnique<SmallStruct>(allocator);
					}
				}));
			}

			for (auto& thread : threads)
			{
				thread.join();
			}

			IC_STOPTIMER();
		}

		/// Performs the benchmark with a LinearAllocator.
		///
		IC_BENCHMARK(LinearAllocator)
		{
			constexpr std::size_t k_resetFrequency = 10; //Note: This should divide into k_numIterations with no remainder.
			constexpr std::size_t k_numResetsPerThread = k_numIterationsPerThread / k_resetFrequency;

			std::vector<std::unique_ptr<IC::LinearAllocator>> allocators;
			for (std::int32_t i = 0; i < k_numThreads; i++)
			{
				allocators.push_back(std::unique_ptr<IC::LinearAllocator>(new IC::LinearAllocator()));
			}

			std::vector<std::thread> threads;

			IC_STARTTIMER();

			for (int i = 0; i < k_numThreads; ++i)
			{
				threads.push_back(std::thread([=, &allocators]()
				{
					auto& linearAllocator = *allocators[i];

					for (int j = 0; j < k_numResetsPerThread; ++j)
					{
						for (int k = 0; k < k_resetFrequency; ++k)
						{
							auto a = IC::MakeUnique<std::uint32_t>(linearAllocator);
							auto b = IC::MakeUnique<std::uint64_t>(linearAllocator);
							auto c = IC::MakeUnique<SmallStruct>(linearAllocator);
						}

						linearAllocator.Reset();
					}
				}));
			}

			for (auto& thread : threads)
			{
				thread.join();
			}


			IC_STOPTIMER();
		}

		/// Performs the benchmark with a LinearAllocator backed by a BuddyAllocator
		///
		IC_BENCHMARK(LinearAllocatorBackedByBuddyAllocator)
		{
			constexpr std::size_t k_buddyAllocatorSize = 1024 * 1024;
			constexpr std::size_t k_resetFrequency = 10; //Note: This should divide into k_numIterations with no remainder.
			constexpr std::size_t k_numResetsPerThread = k_numIterationsPerThread / k_resetFrequency;
			
			IC::BuddyAllocator buddyAllocator(k_buddyAllocatorSize);

			std::vector<std::unique_ptr<IC::LinearAllocator>> linearAllocators;
			for (std::int32_t i = 0; i < k_numThreads; i++)
			{
				linearAllocators.push_back(std::unique_ptr<IC::LinearAllocator>(new IC::LinearAllocator(buddyAllocator)));
			}

			std::vector<std::thread> threads;

			IC_STARTTIMER();

			for (int i = 0; i < k_numThreads; ++i)
			{
				threads.push_back(std::thread([=, &linearAllocators]()
				{
					auto& linearAllocator = *linearAllocators[i];

					for (int j = 0; j < k_numResetsPerThread; ++j)
					{
						for (int k = 0; k < k_resetFrequency; ++k)
						{
							auto a = IC::MakeUnique<std::uint32_t>(linearAllocator);
							auto b = IC::MakeUnique<std::uint64_t>(linearAllocator);
							auto c = IC::MakeUnique<SmallStruct>(linearAllocator);
						}

						linearAllocator.Reset();
					}
				}));
			}

			for (auto& thread : threads)
			{
				thread.join();
			}


			IC_STOPTIMER();
		}
	}
}