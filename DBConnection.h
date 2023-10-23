#pragma once
#include <string>
#include <errno.h>

#ifndef EOK
#define EOK 0
#endif

class DBConnection {
public:
	// password �� ����� ���������� ��� ������, ����� ���������� ��� ������,
	// �� � ������ ������� ��� �������� ������������ ������
	int open(std::string const& addr, std::string const& username, std::string const& password) {
		if (addr.empty()) return EFAULT;
		if (username.empty()) return EINVAL;
		// �������� ���������� � ��������
		if (username == "defaultuser" && password == "123456") {
			fd = 1; // �������� ����, ��� ���������� �����������, �������� ���������� ��� ��������� � �������
			return EOK;
		}
		return ECONNREFUSED;
	}

	int close() {
		if (fd == 0) return EPERM; // ����������� ����� �� ���� �����������, ������� ������� ����������
		fd = 0;
		return EOK;
	}

	int execQuery(std::string const& query) {
		if (fd == 0) return EPERM; // ���������� �� ���� ����� ���������� ������� ���������� ��������� ������
		// ���� ���������� �����������, �� �������� ��������� ������
		// � �������� ������� �������� �������� ��������� ������ select
		if (query.find("select") != std::string::npos) return EOK;
		else return EPERM;
	}

	bool isConnected() const {
		return fd != 0;
	}
	
private:
	int fd = 0;

};
