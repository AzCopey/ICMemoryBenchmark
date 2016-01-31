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

#include "BenchmarkSystem.h"

#include <iostream>

namespace IC
{
    //------------------------------------------------------------------------------
    BenchmarkSystem::BenchmarkSystem()
        : m_timer(false)
    {
    }

    //------------------------------------------------------------------------------
    void BenchmarkSystem::runBenchmarks()
    {
        assert(!m_running);
        assert(m_benchmarks.size() > 0);

        std::unique_lock<std::mutex> lock(m_mutex);
        m_running = true;

        while (m_benchmarks.size() > 0)
        {
            m_currentBenchmark = m_benchmarks.front().get();
            m_timer.start(true);

            lock.unlock();
            m_currentBenchmark->run();
            lock.lock();

            while (m_currentBenchmark)
            {
                m_completeCondition.wait(lock);
            }

            m_benchmarks.pop();
        }

        printReport();
        m_report.clear();

        m_running = false;
    }

    //------------------------------------------------------------------------------
    void BenchmarkSystem::complete(Benchmark* in_benchmark)
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        assert(in_benchmark == m_currentBenchmark);

        m_timer.stop();
        
        BenchmarkReport benchmarkReport;
        benchmarkReport.m_name = m_currentBenchmark->getName();
        benchmarkReport.m_timeTaken = m_timer.getElapsedTime();
        m_report.push_back(benchmarkReport);

        m_currentBenchmark = nullptr;
        m_completeCondition.notify_one();
    }

    //------------------------------------------------------------------------------
    void BenchmarkSystem::printReport() const
    {
        std::cout << "Benchmark Results" << std::endl;
        std::cout << "=================" << std::endl;
        std::cout << std::endl;

        for (auto report : m_report)
        {
            std::cout << report.m_name << ": " << report.m_timeTaken << "ms." << std::endl;
        }
    }
}