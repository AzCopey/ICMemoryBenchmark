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

#ifndef _ICBENCHMARK_BENCHMARKSYSTEM_H_
#define _ICBENCHMARK_BENCHMARKSYSTEM_H_

#include "ForwardDeclarations.h"
#include "Benchmark.h"
#include "Timer.h"

#include <cassert>
#include <memory>
#include <mutex>
#include <queue>

namespace IC
{
    /// A system for running and managing benchmark tests. This allows multiple
    /// benchmarks to be provided, each of which will be run one after another.
    /// Once all are complete, results will be displayed on screen.
    ///
    /// Multi-threaded benchmarks are supported, but the BenchmarkSystem itself 
    /// is not thread-safe. It should only be used from one thread.
    ///
    class BenchmarkSystem final
    {
    public:
        BenchmarkSystem();

        /// Adds a new test of the given type to the benchmark system.
        ///
        template <typename TType> void createBenchmark();

        /// Runs all benchmarks until complete. Benchmarks may be multi-threaded
        /// so this will block until the tests are complete.
        ///
        void runBenchmarks();

    private:
        friend class Benchmark;

        /// A container for information on the result of a benchmark.
        struct BenchmarkReport
        {
            std::string m_description;
            std::uint32_t m_timeTaken;
        };

        /// Completes the given benchmark tests. This must be the currently running
        /// test.
        ///
        /// @param The test to complete.
        ///
        void complete(Benchmark* in_benchmark);

        /// Prints the results of the benchmarks. This is not thread-safe and must
        /// be run while the mutex is held.
        ///
        void printReport() const;

        bool m_running = false;
        Benchmark* m_currentBenchmark = nullptr;
        Timer m_timer;
        std::queue<std::unique_ptr<Benchmark>> m_benchmarks;
        std::vector<BenchmarkReport> m_report;
        std::condition_variable m_completeCondition;
        std::mutex m_mutex;
    };

    //------------------------------------------------------------------------------
    template <typename TType> void BenchmarkSystem::createBenchmark()
    {
        assert(!m_running);

        std::unique_ptr<Benchmark> benchmark = std::unique_ptr<TType>(new TType(*this));
        m_benchmarks.push(std::move(benchmark));
    }
}

#endif