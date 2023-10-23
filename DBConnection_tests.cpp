#include <gtest/gtest.h>
#include "DBConnection.h"

class fixture : public ::testing::Test {
public:
	DBConnection _object = DBConnection();
};

TEST_F(fixture, OpenWithEmptyAddress) {
	auto error = _object.open("", "", "");
	ASSERT_EQ(error, EFAULT);
}

TEST_F(fixture, OpenWithEmptyUsername) {
	auto error = _object.open("127.0.0.1:8000", "", "");
	ASSERT_EQ(error, EINVAL);
}

TEST_F(fixture, OpenValidUser) {
	auto error = _object.open("127.0.0.1:8000", "defaultuser", "123456");
	ASSERT_EQ(error, EOK);
}

TEST_F(fixture, OpenInvalidUser) {
	auto error = _object.open("127.0.0.1:8000", "noname", "1111");
	ASSERT_EQ(error, ECONNREFUSED);
}

TEST_F(fixture, CloseConnected) {
	auto error = _object.open("127.0.0.1:8000", "defaultuser", "123456");
	EXPECT_EQ(error, EOK);
	error = _object.close();
	ASSERT_EQ(error, EOK);
}

TEST_F(fixture, CloseUnconnected) {
	auto error = _object.close();
	ASSERT_EQ(error, EPERM);
}

TEST_F(fixture, ValidQueryWhenConnected) {
	auto error = _object.open("127.0.0.1:8000", "defaultuser", "123456");
	EXPECT_EQ(error, EOK);
	error = _object.execQuery("select *");
	ASSERT_EQ(error, EOK);
}

TEST_F(fixture, InvalidQueryWhenConnected) {
	auto error = _object.open("127.0.0.1:8000", "defaultuser", "123456");
	EXPECT_EQ(error, EOK);
	error = _object.execQuery("drop");
	ASSERT_EQ(error, EPERM);
}

TEST_F(fixture, ValidQueryWhenUnconnected) {
	auto error = _object.execQuery("select *");
	ASSERT_EQ(error, EPERM);
}
