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

#include "BenchmarkRunner.h"
#include "BenchmarkRegistry.h"
#include "Timer.h"

#include <algorithm>
#include <cassert>
#include <unordered_map>

namespace IC
{
	namespace BenchmarkRunner
	{
		namespace
		{
			/// Executes the given benchmark and returns a report detailing the time taken in milliseconds.
			///
			/// @param benchmark
			///		The benchmark that should be run.
			///
			/// @return A report on the result of the given benchmark.
			///
			BenchmarkReport::Benchmark RunBenchmark(const Benchmark& benchmark)
			{
				Timer timer(false);

				benchmark.GetBenchmarkDelegate()(timer);
				assert(!timer.IsRunning());

				return BenchmarkReport::Benchmark(benchmark.GetBenchmarkName(), timer.GetElapsedTime());
			}

			/// Compiles the given results data into a benchmark report.
			///
			/// @param results
			///		The results data map.
			///
			/// @return The compiled report.
			///
			BenchmarkReport GenerateReport(const std::unordered_map<std::string, std::vector<BenchmarkReport::Benchmark>>& results)
			{
				std::vector<BenchmarkReport::BenchmarkGroup> benchmarkGroupReports;

				for (const auto& result : results)
				{
					auto benchmarks = result.second;

					std::sort(benchmarks.begin(), benchmarks.end(), [](const BenchmarkReport::Benchmark& a, const BenchmarkReport::Benchmark& b)
					{
						return a.GetTimeTaken() < b.GetTimeTaken();
					});

					benchmarkGroupReports.push_back(BenchmarkReport::BenchmarkGroup(result.first, benchmarks));
				}

				return benchmarkGroupReports;
			}
		}

		//------------------------------------------------------------------------------
		BenchmarkReport Run() noexcept
		{
			auto benchmarks = BenchmarkRegistry::Get().GetBenchmarks();

			std::unordered_map<std::string, std::vector<BenchmarkReport::Benchmark>> benchmarkResults;

			for (const auto& benchmark : benchmarks)
			{
				benchmarkResults[benchmark.GetBenchmarkGroupName()].push_back(RunBenchmark(benchmark));
			}

			return GenerateReport(benchmarkResults);
		}
	}
}