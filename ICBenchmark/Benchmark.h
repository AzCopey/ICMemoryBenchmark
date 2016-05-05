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

#ifndef _ICBENCHMARK_BENCHMARK_H_
#define _ICBENCHMARK_BENCHMARK_H_

#include "ForwardDeclarations.h"

#include <functional>
#include <string>

namespace IC
{
	/// An immutable description of a single Benchmark, including the name of
	/// the benchmark and benchmark group, and the function that should be
	/// called to execute the benchmark.
	///
	/// Benchmarks should be created using the macros defined in BenchmarkGroup.h
	///
	/// This is thread-safe.
	///
	class Benchmark final
	{
	public:
		/// The function that should be called to perform the benchmark.
		///
		/// @param timer
		///		The timer which should be used to time the benchmark.
		///
		using BenchmarkDelegate = std::function<void(Timer& timer) noexcept>;

		/// Creates a new instance of the benchmark.
		///
		/// @param benchmarkGroupName
		///		The name of the group this benchmark belongs to.
		/// @param benchmarkName
		///		The name of this benchmark.
		/// @param benchmarkDelegate
		///		The function which will be executed to perform the benchmark.
		///
		Benchmark(const std::string& benchmarkGroupName, const std::string& benchmarkName, const BenchmarkDelegate& benchmarkDelegate) noexcept;

		/// @return The name of the benchmark group.
		///
		const std::string& GetBenchmarkGroupName() const noexcept { return m_benchmarkGroupName; }

		/// @return The name of the benchmark.
		///
		const std::string& GetBenchmarkName() const noexcept { return m_benchmarkName; }

		/// @return The function which should be executed to perform the benchmark.
		///
		const BenchmarkDelegate& GetBenchmarkDelegate() const noexcept { return m_benchmarkDelegate; }

	private:
		std::string m_benchmarkGroupName;
		std::string m_benchmarkName;
		BenchmarkDelegate m_benchmarkDelegate;
	};
}

#endif