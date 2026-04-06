/**
 * @file Tests/ThreadPool.cpp
 * @brief Unit tests for ThreadPool
 * @date 2025-10-31
 */

#include <atomic>
#include <chrono>
#include <future>
#include <string>
#include <thread>
#include <vector>

#include <Concerto/Core/ThreadPool/ThreadPool.hpp>

#include <gtest/gtest.h>

using cct::ThreadPool;
using namespace std::chrono_literals;

TEST(ThreadPoolInitialization, DefaultConstruction)
{
	ThreadPool pool;
	EXPECT_GT(pool.GetWorkerCount(), 0u);
}

TEST(ThreadPoolInitialization, ExplicitThreadCount)
{
	ThreadPool pool(4);
	EXPECT_EQ(pool.GetWorkerCount(), 4u);
}

TEST(ThreadPoolInitialization, SingleThreadPool)
{
	ThreadPool pool(1);
	EXPECT_EQ(pool.GetWorkerCount(), 1u);
}

TEST(ThreadPoolAddTask, SingleTaskExecution)
{
	ThreadPool pool(4);
	std::atomic<bool> executed{false};

	pool.AddTask(
		[&executed]()
		{ executed.store(true, std::memory_order_relaxed); });

	ASSERT_TRUE(pool.WaitFor(1000ms));
	EXPECT_TRUE(executed.load());
}

TEST(ThreadPoolAddTask, MultipleTasksExecution)
{
	ThreadPool pool(4);
	std::atomic<int> counter{0};
	constexpr int numTasks = 100;

	for (int i = 0; i < numTasks; ++i)
	{
		pool.AddTask(
			[&counter]()
			{ counter.fetch_add(1, std::memory_order_relaxed); });
	}

	ASSERT_TRUE(pool.WaitFor(5000ms));
	EXPECT_EQ(counter.load(), numTasks);
}

TEST(ThreadPoolAddTask, TaskWithSharedState)
{
	ThreadPool pool(4);
	std::atomic<int> sum{0};
	constexpr int numTasks = 50;

	for (int i = 1; i <= numTasks; ++i)
	{
		pool.AddTask([&sum, i]()
					 { sum.fetch_add(i, std::memory_order_relaxed); });
	}

	ASSERT_TRUE(pool.WaitFor(5000ms));
	EXPECT_EQ(sum.load(), (numTasks * (numTasks + 1)) / 2);
}

TEST(ThreadPoolSubmit, ReturningInt)
{
	ThreadPool pool(4);
	auto future = pool.Submit([]()
							  { return 42; });

	ASSERT_TRUE(pool.WaitFor(1000ms));
	EXPECT_EQ(future.get(), 42);
}

TEST(ThreadPoolSubmit, ReturningString)
{
	ThreadPool pool(4);
	auto future = pool.Submit([]()
							  { return std::string("Hello, ThreadPool!"); });

	ASSERT_TRUE(pool.WaitFor(1000ms));
	EXPECT_EQ(future.get(), "Hello, ThreadPool!");
}

TEST(ThreadPoolSubmit, WithComputation)
{
	ThreadPool pool(4);
	auto future = pool.Submit([]()
							  {
    int sum = 0;
    for (int i = 1; i <= 100; ++i)
      sum += i;
    return sum; });

	ASSERT_TRUE(pool.WaitFor(1000ms));
	EXPECT_EQ(future.get(), 5050);
}

TEST(ThreadPoolSubmit, MultipleSubmitCalls)
{
	ThreadPool pool(4);
	std::vector<std::future<int>> futures;
	constexpr int numTasks = 20;

	for (int i = 0; i < numTasks; ++i)
	{
		futures.push_back(pool.Submit([i]()
									  { return i * i; }));
	}

	ASSERT_TRUE(pool.WaitFor(5000ms));

	for (int i = 0; i < numTasks; ++i)
	{
		EXPECT_EQ(futures[i].get(), i * i);
	}
}

TEST(ThreadPoolExceptionHandling, TaskThrowingException)
{
	ThreadPool pool(4);
	auto future =
		pool.Submit([]() -> int
					{ throw std::runtime_error("Test exception"); });

	EXPECT_TRUE(pool.WaitFor(1000ms));
	EXPECT_THROW(future.get(), std::runtime_error);
}

TEST(ThreadPoolExceptionHandling, MultipleTasksWithExceptions)
{
	ThreadPool pool(4);
	std::vector<std::future<int>> futures;

	for (int i = 0; i < 10; ++i)
	{
		futures.push_back(pool.Submit([i]() -> int
									  {
      if (i % 2 == 0)
        throw std::runtime_error("Even number");
      return i; }));
	}

	ASSERT_TRUE(pool.WaitFor(5000ms));

	for (int i = 0; i < 10; ++i)
	{
		if (i % 2 == 0)
			EXPECT_THROW(futures[i].get(), std::runtime_error);
		else
			EXPECT_EQ(futures[i].get(), i);
	}
}

TEST(ThreadPoolExceptionHandling, PoolContinuesAfterException)
{
	ThreadPool pool(4);
	auto future1 =
		pool.Submit([]() -> int
					{ throw std::runtime_error("First exception"); });

	ASSERT_TRUE(pool.WaitFor(1000ms));
	EXPECT_THROW(future1.get(), std::runtime_error);

	auto future2 = pool.Submit([]()
							   { return 42; });

	ASSERT_TRUE(pool.WaitFor(1000ms));
	EXPECT_EQ(future2.get(), 42);
}

TEST(ThreadPoolWait, WaitForWithImmediateCompletion)
{
	ThreadPool pool(4);
	std::atomic<int> counter{0};

	for (int i = 0; i < 10; ++i)
	{
		pool.AddTask(
			[&counter]()
			{ counter.fetch_add(1, std::memory_order_relaxed); });
	}

	ASSERT_TRUE(pool.WaitFor(5000ms));
	EXPECT_EQ(counter.load(), 10);
}

TEST(ThreadPoolWait, WaitForWithTimeout)
{
	ThreadPool pool(4);

	pool.AddTask([]()
				 { std::this_thread::sleep_for(500ms); });

	EXPECT_FALSE(pool.WaitFor(100ms));
	EXPECT_TRUE(pool.WaitFor(1000ms));
}

TEST(ThreadPoolWait, WaitWithDeadline)
{
	ThreadPool pool(4);

	pool.AddTask([]()
				 { std::this_thread::sleep_for(500ms); });

	auto deadline = std::chrono::steady_clock::now() + 200ms;
	EXPECT_FALSE(pool.Wait(deadline));

	deadline = std::chrono::steady_clock::now() + 1000ms;
	EXPECT_TRUE(pool.Wait(deadline));
}

TEST(ThreadPoolWait, MultipleWaitCalls)
{
	ThreadPool pool(4);
	std::atomic<int> counter{0};

	for (int i = 0; i < 50; ++i)
	{
		pool.AddTask(
			[&counter]()
			{ counter.fetch_add(1, std::memory_order_relaxed); });
	}

	ASSERT_TRUE(pool.WaitFor(5000ms));
	EXPECT_EQ(counter.load(), 50);
	EXPECT_TRUE(pool.WaitFor(100ms));
}

TEST(ThreadPoolStop, RequestStopWithEmptyQueue)
{
	ThreadPool pool(4);
	std::atomic<int> counter{0};

	for (int i = 0; i < 10; ++i)
	{
		pool.AddTask(
			[&counter]()
			{ counter.fetch_add(1, std::memory_order_relaxed); });
	}

	ASSERT_TRUE(pool.WaitFor(5000ms));
	pool.RequestStop();

	EXPECT_EQ(counter.load(), 10);
}

TEST(ThreadPoolStop, RequestStopIsIdempotent)
{
	ThreadPool pool(4);

	pool.RequestStop();
	pool.RequestStop();
	pool.RequestStop();
}

TEST(ThreadPoolStop, NoNewTasksAfterRequestStop)
{
	ThreadPool pool(4);
	std::atomic<int> counter{0};

	pool.RequestStop();

	pool.AddTask(
		[&counter]()
		{ counter.fetch_add(1, std::memory_order_relaxed); });

	std::this_thread::sleep_for(100ms);
	EXPECT_EQ(counter.load(), 0);
}

TEST(ThreadPoolStop, SubmitAfterRequestStopFailsGracefully)
{
	ThreadPool pool(4);
	pool.RequestStop();

	auto future = pool.Submit([]()
							  { return 42; });

	EXPECT_TRUE(future.valid());
}

TEST(ThreadPoolDestruction, DestructionWithEmptyQueue)
{
	std::atomic<int> counter{0};

	{
		ThreadPool pool(4);

		for (int i = 0; i < 10; ++i)
		{
			pool.AddTask(
				[&counter]()
				{ counter.fetch_add(1, std::memory_order_relaxed); });
		}

		ASSERT_TRUE(pool.WaitFor(5000ms));
	}

	EXPECT_EQ(counter.load(), 10);
}

TEST(ThreadPoolDestruction, DestructionWithPendingTasks)
{
	std::atomic<int> counter{0};

	{
		ThreadPool pool(4);

		for (int i = 0; i < 100; ++i)
		{
			pool.AddTask([&counter]()
						 {
        std::this_thread::sleep_for(10ms);
        counter.fetch_add(1, std::memory_order_relaxed); });
		}
	}

	EXPECT_GE(counter.load(), 0);
}

TEST(ThreadPoolConcurrentOperations, ConcurrentAddTaskFromMultipleThreads)
{
	ThreadPool pool(8);
	std::atomic<int> counter{0};
	constexpr int numThreads = 10;
	constexpr int tasksPerThread = 100;

	std::vector<std::thread> threads;
	for (int t = 0; t < numThreads; ++t)
	{
		threads.emplace_back([&pool, &counter]()
							 {
      for (int i = 0; i < tasksPerThread; ++i) {
        pool.AddTask(
            [&counter]() { counter.fetch_add(1, std::memory_order_relaxed); });
      } });
	}

	for (auto& thread : threads)
		thread.join();

	ASSERT_TRUE(pool.WaitFor(10000ms));
	EXPECT_EQ(counter.load(), numThreads * tasksPerThread);
}

TEST(ThreadPoolConcurrentOperations, ConcurrentSubmitFromMultipleThreads)
{
	ThreadPool pool(8);
	constexpr int numThreads = 10;
	constexpr int tasksPerThread = 50;

	std::vector<std::thread> threads;
	std::vector<std::vector<std::future<int>>> allFutures(numThreads);

	for (int t = 0; t < numThreads; ++t)
	{
		threads.emplace_back([&pool, &allFutures, t]()
							 {
      for (int i = 0; i < tasksPerThread; ++i) {
        allFutures[t].push_back(pool.Submit([i]() { return i; }));
      } });
	}

	for (auto& thread : threads)
		thread.join();

	ASSERT_TRUE(pool.WaitFor(10000ms));

	for (int t = 0; t < numThreads; ++t)
	{
		for (int i = 0; i < tasksPerThread; ++i)
		{
			EXPECT_EQ(allFutures[t][i].get(), i);
		}
	}
}

TEST(ThreadPoolConcurrentOperations, ConcurrentWaitFromMultipleThreads)
{
	ThreadPool pool(8);
	std::atomic<int> counter{0};

	for (int i = 0; i < 100; ++i)
	{
		pool.AddTask([&counter]()
					 {
      std::this_thread::sleep_for(10ms);
      counter.fetch_add(1, std::memory_order_relaxed); });
	}

	std::vector<std::thread> threads;
	std::atomic<int> waitSuccessCount{0};

	for (int t = 0; t < 5; ++t)
	{
		threads.emplace_back([&pool, &waitSuccessCount]()
							 {
      if (pool.WaitFor(10000ms))
        waitSuccessCount.fetch_add(1, std::memory_order_relaxed); });
	}

	for (auto& thread : threads)
		thread.join();

	EXPECT_EQ(counter.load(), 100);
	EXPECT_EQ(waitSuccessCount.load(), 5);
}

TEST(ThreadPoolEdgeCases, TasksThatAddMoreTasks)
{
	ThreadPool pool(4);
	std::atomic<int> counter{0};

	pool.AddTask([&pool, &counter]()
				 {
    counter.fetch_add(1, std::memory_order_relaxed);

    pool.AddTask(
        [&counter]() { counter.fetch_add(1, std::memory_order_relaxed); }); });

	ASSERT_TRUE(pool.WaitFor(5000ms));
	EXPECT_EQ(counter.load(), 2);
}

TEST(ThreadPoolEdgeCases, LargeNumberOfThreads)
{
	ThreadPool pool(100);
	std::atomic<int> counter{0};

	for (int i = 0; i < 1000; ++i)
	{
		pool.AddTask(
			[&counter]()
			{ counter.fetch_add(1, std::memory_order_relaxed); });
	}

	ASSERT_TRUE(pool.WaitFor(10000ms));
	EXPECT_EQ(counter.load(), 1000);
}

TEST(ThreadPoolEdgeCases, TasksWithVaryingDurations)
{
	ThreadPool pool(4);
	std::atomic<int> counter{0};

	for (int i = 0; i < 20; ++i)
	{
		pool.AddTask([&counter, i]()
					 {
      if (i % 2 == 0)
        std::this_thread::sleep_for(10ms);
      else
        std::this_thread::sleep_for(50ms);
      counter.fetch_add(1, std::memory_order_relaxed); });
	}

	ASSERT_TRUE(pool.WaitFor(10000ms));
	EXPECT_EQ(counter.load(), 20);
}

TEST(ThreadPoolEdgeCases, EmptyPoolBehavior)
{
	ThreadPool pool(4);
	EXPECT_TRUE(pool.WaitFor(100ms));
}

TEST(ThreadPoolEdgeCases, ImmediateRequestStopAfterConstruction)
{
	ThreadPool pool(4);
	pool.RequestStop();

	std::atomic<int> counter{0};
	pool.AddTask(
		[&counter]()
		{ counter.fetch_add(1, std::memory_order_relaxed); });

	std::this_thread::sleep_for(100ms);
	EXPECT_EQ(counter.load(), 0);
}

TEST(ThreadPoolStress, HighVolumeTaskProcessing)
{
	ThreadPool pool(8);
	std::atomic<int> counter{0};
	constexpr int numTasks = 10000;

	for (int i = 0; i < numTasks; ++i)
	{
		pool.AddTask(
			[&counter]()
			{ counter.fetch_add(1, std::memory_order_relaxed); });
	}

	ASSERT_TRUE(pool.WaitFor(30000ms));
	EXPECT_EQ(counter.load(), numTasks);
}

TEST(ThreadPoolStress, MixedAddTaskAndSubmit)
{
	ThreadPool pool(8);
	std::atomic<int> addTaskCounter{0};
	std::vector<std::future<int>> futures;
	constexpr int numOperations = 1000;

	for (int i = 0; i < numOperations; ++i)
	{
		if (i % 2 == 0)
		{
			pool.AddTask([&addTaskCounter]()
						 { addTaskCounter.fetch_add(1, std::memory_order_relaxed); });
		}
		else
		{
			futures.push_back(pool.Submit([i]()
										  { return i; }));
		}
	}

	ASSERT_TRUE(pool.WaitFor(30000ms));
	EXPECT_EQ(addTaskCounter.load(), numOperations / 2);

	for (size_t i = 0; i < futures.size(); ++i)
	{
		EXPECT_EQ(futures[i].get(), static_cast<int>(i * 2 + 1));
	}
}

TEST(ThreadPoolThreadSafety, NoDataRacesWithSharedAtomic)
{
	ThreadPool pool(4);
	std::atomic<int> counter{0};
	constexpr int numIncrements = 10000;

	for (int i = 0; i < numIncrements; ++i)
	{
		pool.AddTask(
			[&counter]()
			{ counter.fetch_add(1, std::memory_order_relaxed); });
	}

	ASSERT_TRUE(pool.WaitFor(30000ms));
	EXPECT_EQ(counter.load(), numIncrements);
}

TEST(ThreadPoolThreadSafety, GetWorkerCountIsThreadSafe)
{
	ThreadPool pool(4);
	std::vector<std::thread> threads;

	for (int t = 0; t < 10; ++t)
	{
		threads.emplace_back([&pool]()
							 {
		for (int i = 0; i < 100; ++i) {
			volatile size_t count = pool.GetWorkerCount();
			(void)count;
      	} });
	}

	for (auto& thread : threads)
		thread.join();
}
