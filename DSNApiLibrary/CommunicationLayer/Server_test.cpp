#include "gtest/gtest.h"
#include "Client.h"


TEST(ServerTest, accept) {
  EXPECT_EQ(true, true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}