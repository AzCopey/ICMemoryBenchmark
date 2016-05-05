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

#ifndef _ICBENCHMARK_BENCHMARKGROUP_H_
#define _ICBENCHMARK_BENCHMARKGROUP_H_

#include "AutoRegisterBenchmark.h"
#include "Benchmark.h"
#include "Timer.h"

/// Declares a new benchmark group.
///
/// @param benchmarkGroupName
///		The name of the benchmark group.
///
#define IC_BENCHMARKGROUP(benchmarkGroupName) \
	namespace benchmarkGroupName##BenchmarkGroup_ \
	{ \
		const std::string k_benchmarkGroupName_ = #benchmarkGroupName; \
	} \
	namespace benchmarkGroupName##BenchmarkGroup_

/// Declares a new benchmark within a benchmark group.
///
/// @param benchmarkName
///		The name of the benchmark.
///
#define IC_BENCHMARK(benchmarkName) \
	void benchmarkName##Benchmark_(IC::Timer& timer_) noexcept; \
	namespace \
	{ \
		const IC::AutoRegisterBenchmark benchmarkName##AutoReg(IC::Benchmark(k_benchmarkGroupName_, #benchmarkName, benchmarkName##Benchmark_)); \
	} \
	void benchmarkName##Benchmark_(IC::Timer& timer_) noexcept

/// Starts the timer within a benchmark.
///
#define IC_STARTTIMER() \
	timer_.Start();

/// Stops the timer within a benchmark. This is optional as the timer will be
/// automatically stopped when the benchmark returns. Usually this is used when
/// shutdown code should be  excluded from the benchmark time.
///
#define IC_STOPTIMER() \
	timer_.Stop();

#endif