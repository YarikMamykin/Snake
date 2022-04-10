#include <gtest/gtest.h>
#include "commands/synchronous_commands/QueryLock/QueryLock.hpp"
#include <string>
#include <future>


namespace commands_test {

	TEST(QueryLockTest, MakeSynchronousRequestResponseToAnotherThread)
	{

		std::string response_data_holder;
		const std::string expected_response_data { "expected_data" };

		ASSERT_TRUE(response_data_holder.empty());

		{
			commands::QueryLock ql;

			auto response_thread = [&ql, &response_data_holder, &expected_response_data]() mutable noexcept {
				std::mutex m; 
				std::unique_lock<std::mutex> lk(m); 
				std::condition_variable cv; 
				cv.wait_for(lk, std::chrono::milliseconds(20u)); 

				response_data_holder = expected_response_data;

				ql.unlock();
			};

			auto thread_handler = std::async(std::launch::async, response_thread);
		}

		EXPECT_EQ(response_data_holder, expected_response_data);
	}
}
