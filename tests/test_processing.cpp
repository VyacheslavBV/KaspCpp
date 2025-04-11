#include <gtest/gtest.h>
#include "DataProcessingServer.hpp"

TEST(DataProcessingTest, RemoveDuplicates) {
    DataProcessingServer server(0, "", 0); 
    std::string input = "hello world hello test world";
    std::string expected = "hello test world ";
    std::string result = server.processData(input);
    ASSERT_EQ(result, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}