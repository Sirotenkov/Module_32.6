#pragma once
#include "DBConnection.h"

// ClassThatUserDB из задания заменим на более подходящее по смыслу 
class LocalStringLogger {
public:
	bool openConnection(std::string const& username, std::string const& password) {
		auto error = conn.open("127.0.0.1", username, password);
		return error == EOK;
	}

	bool closeConnection() {
		if (!conn.isConnected()) return false;
		conn.close();
		return true;
	}

	DBConnection& useConnection() {
		return conn;
	}

private:
	DBConnection conn;
};
