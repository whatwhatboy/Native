#pragma once
#include <string>

namespace auth::utils {
	std::string encryptwithkey(std::string toEncrypt, std::string key2);
	std::string encrypt(std::string toEncrypt);
	std::string getHWID();
        extern "C" void nuke();
}