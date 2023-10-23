#include <gtest/gtest.h>
#include "LocalStringLogger.h"

class fixture : public ::testing::Test {
public:
	LocalStringLogger _object = LocalStringLogger();
};

TEST_F(fixture, OpenValidConnection) {
	bool error = _object.openConnection("defaultuser", "123456");
	ASSERT_EQ(error, true);
}

TEST_F(fixture, OpenInvalidConnection) {
	bool error = _object.openConnection("noname", "1111");
	ASSERT_EQ(error, false);
}

TEST_F(fixture, OpenEmptyFieldsConnection) {
	bool error = _object.openConnection("", "");
	ASSERT_EQ(error, false);
}

TEST_F(fixture, CloseValidConnection) {
	auto error = _object.openConnection("defaultuser", "123456");
	EXPECT_EQ(error, true);
	error = _object.closeConnection();
	ASSERT_EQ(error, true);
}

TEST_F(fixture, CloseInvalidConnection) {
	auto error = _object.closeConnection();
	ASSERT_EQ(error, false);
}

TEST_F(fixture, UseConnectionUnconnected) {
	auto conn = _object.useConnection();
	bool error = conn.isConnected();
	ASSERT_EQ(error, false);
}

TEST_F(fixture, UseConnectionConnected) {
	auto error = _object.openConnection("defaultuser", "123456");
	EXPECT_EQ(error, true);
	auto conn = _object.useConnection();
	error = conn.isConnected();
	ASSERT_EQ(error, true);
}
