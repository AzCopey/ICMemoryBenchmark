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

	/// TODO
	///
	IC_BENCHMARKGROUP(SmallAllocations)
	{
		/// TODO
		///
		IC_BENCHMARK(StandardAllocator)
		{
			IC_STARTTIMER();

			for (int i = 0; i < k_numIterations; ++i)
			{
				auto a = std::unique_ptr<std::uint32_t>(new uint32_t);
				auto b = std::unique_ptr<std::uint64_t>(new uint64_t);
				auto e = std::unique_ptr<SmallStruct>(new SmallStruct());
			}

			IC_STOPTIMER();
		}

		/// TODO
		///
		IC_BENCHMARK(BuddyAllocator)
		{
			constexpr std::size_t k_allocatorSize = 4096;

			IC::BuddyAllocator allocator(k_allocatorSize);

			IC_STARTTIMER();

			for (int i = 0; i < k_numIterations; ++i)
			{
				auto a = IC::MakeUnique<std::uint32_t>(allocator);
				auto b = IC::MakeUnique<std::uint64_t>(allocator);
				auto e = IC::MakeUnique<SmallStruct>(allocator);
			}

			IC_STOPTIMER();
		}

		/// TODO
		///
		IC_BENCHMARK(LinearAllocator)
		{
			constexpr std::size_t k_resetFrequency = 10;

			IC::LinearAllocator allocator;

			IC_STARTTIMER();

			for (int i = 0; i < k_numIterations; ++i)
			{
				auto a = IC::MakeUnique<std::uint32_t>(allocator);
				auto b = IC::MakeUnique<std::uint64_t>(allocator);
				auto e = IC::MakeUnique<SmallStruct>(allocator);

				//TODO: This can probably be written more efficiently.
				if (i % k_resetFrequency == 0)
				{
					allocator.Reset();
				}
			}

			IC_STOPTIMER();
		}
	}
}