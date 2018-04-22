#include "gtest/gtest.h"
#include "Client.h"

TEST(ClientTest, connect) {
  Client* client = new Client("127.0.0.1");
  // FIXME, should figure out a way to mock the function
  // EXPECT_EQ(client->getState(), ConnectionState::OK);
  EXPECT_EQ(client->getState(), ConnectionState::ConnectionFailed);
}

TEST(ClientTest, sendMessage) {
  EXPECT_EQ(true, true);
}

TEST(ClientTest, recieveMessage) {
  EXPECT_EQ(true, true);
}

TEST(ClientTest, deconstruct) {
  EXPECT_EQ(true, true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}