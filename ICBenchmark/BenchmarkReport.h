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

#ifndef _ICBENCHMARK_BENCHMARKREPORT_H_
#define _ICBENCHMARK_BENCHMARKREPORT_H_

#include "ForwardDeclarations.h"

#include <string>
#include <vector>

namespace IC
{
	/// A container for all information pertaining the results of a series of
	/// benchmarks. Benchmarks are compiled into a series of groups for ease
	/// of reporting.
	///
	/// This is immutable and therefore thread-safe.
	///
	class BenchmarkReport final
	{
	public:
		/// Contains report data pertaining to a single benchmark.
		///
		/// This is immutable and therefore thread-safe.
		///
		class Benchmark final
		{
		public:
			/// Creates a new instance with the given name and time taken.
			///
			/// @param name
			///		The name of the benchmark.
			/// @param timeTimen
			///		The time in seconds that the benchmark took to complete.
			///
			Benchmark(const std::string& name, float timeTaken) noexcept;

			/// @return The name of the benchmark.
			///
			const std::string& GetName() const noexcept { return m_name; }

			/// @return The time in seconds that the benchmark took to complete.
			///
			float GetTimeTaken() const noexcept { return m_timeTaken; }

		private:
			std::string m_name;
			float m_timeTaken = 0.0f;
		};

		/// Contains report data pertaining to a benchmark group.
		///
		/// This is immutable and therefore thread-safe.
		///
		class BenchmarkGroup final
		{
		public:
			/// Creates a new instance with the given name and benchmark list.
			///
			/// @param name
			///		The name of the benchmark group.
			/// @param benchmarks
			///		A list containing data on the benchmarks that make up this group.
			/// 
			BenchmarkGroup(const std::string& name, const std::vector<Benchmark>& benchmarks) noexcept;

			/// @return The name of the benchmark group.
			///
			const std::string& GetName() const noexcept { return m_name; }

			/// @return A list containing data on the benchmarks that make up this group. 
			///
			const std::vector<Benchmark>& GetBenchmarks() const noexcept { return m_benchmarks; }

		private:
			std::string m_name;
			std::vector<Benchmark> m_benchmarks;
		};

		/// Creates a new instance with the given list of benchmark groups.
		///
		/// @param benchmarkGroups
		///		A list containing data on the benchmark groups.
		///
		BenchmarkReport(const std::vector<BenchmarkGroup>& benchmarkGroups) noexcept;

		/// @return A list containing data on the benchmark groups.
		///
		const std::vector<BenchmarkGroup>& GetBenchmarkGroups() const noexcept { return m_benchmarkGroups; }

	private:
		std::vector<BenchmarkGroup> m_benchmarkGroups;
	};
}

#endif