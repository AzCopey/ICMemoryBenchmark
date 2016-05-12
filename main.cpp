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

#include "ICBenchmark/ICBenchmark.h"

#include <iostream>

/// Prints a bar of the given lenth to standard out.
///
/// @param length
///        The bar length.
///
void PrintBar(std::size_t length) noexcept
{
    for (std::size_t i = 0; i <length; ++i)
    {
        std::cout << "-";
    }

    std::cout << std::endl;
}

/// Reports the results of the exectuted benchmarks to the output stream.
///
/// @param report
///        A report detailing the results of the benchmark.
///
void ReportResults(IC::BenchmarkReport& report) noexcept
{
    std::cout << "Benchmark Results" << std::endl;
    std::cout << "=================" << std::endl;
    std::cout << std::endl;

    for (const auto& benchmarkGroup : report.GetBenchmarkGroups())
    {
        std::cout << benchmarkGroup.GetName() << std::endl;
        PrintBar(benchmarkGroup.GetName().size());

        for (const auto& benchmark : benchmarkGroup.GetBenchmarks())
        {
            std::cout << benchmark.GetName() << ": " << benchmark.GetTimeTaken() << "ms" << std::endl;
        }

        std::cout << std::endl;
    }
}

/// The entry point to the application.
///
int main() noexcept
{
    auto report = IC::BenchmarkRunner::Run();

    ReportResults(report);

    //Wait for input before ending.
    int x = 0;
    std::cin >> x;

    return 0;
}