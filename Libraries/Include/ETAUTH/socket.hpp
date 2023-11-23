#pragma once
#include <string>
namespace auth::socket {
	enum authstatus {
		E_AUTH_PENDING = -1,
		E_CONN_FAILED,
		E_DATE_MISMATCH,
		E_CREDENTIALS_INVALID,
		E_BANNED,
		E_HWID_MISMATCH,
		E_NOSUB,
		E_SUCCESS
	};
	void dispatch(const std::string& message);
	void runthread();
	void login(int orgaid);
	authstatus GetStatus();
	std::string getUsername();
	unsigned long long getExpiry();

	//dont use this if you use our loader pipe
	void setUserData(std::string username, std::string password, std::string hwid, int product);
}