#pragma once
#include <string>
#include <errno.h>

#ifndef EOK
#define EOK 0
#endif

class DBConnection {
public:
	// password не стоит передавать как строку, лучше передавать хэш пароля,
	// но в данном примере для простоты используется строка
	int open(std::string const& addr, std::string const& username, std::string const& password) {
		if (addr.empty()) return EFAULT;
		if (username.empty()) return EINVAL;
		// имитация соединения с сервером
		if (username == "defaultuser" && password == "123456") {
			fd = 1; // имитация того, что соединение установлено, получили дескриптор для обращения к серверу
			return EOK;
		}
		return ECONNREFUSED;
	}

	int close() {
		if (fd == 0) return EPERM; // соедиенение ранее не было установлено, поэтому закрыть невозможно
		fd = 0;
		return EOK;
	}

	int execQuery(std::string const& query) {
		if (fd == 0) return EPERM; // соединение не было ранее устновлено поэтому невозможно выполнить запрос
		// если соединение установлено, то пытаемся выполнить запрос
		// в качестве примера валидным запросом считается только select
		if (query.find("select") != std::string::npos) return EOK;
		else return EPERM;
	}

	bool isConnected() const {
		return fd != 0;
	}
	
private:
	int fd = 0;

};
