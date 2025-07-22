#pragma once

#include <string>
#include <unordered_map>
#include <random>
#include <sstream>
#include <functional>
#include <sodium.h>
using namespace std;

class AuthService {
public:
	static string hashPassword(const string& password) {
		if (sodium_init()  < 0){
			throw runtime_error("Failed to initialize libsodium");
		}
	
		char hashed[crypto_pwhash_STRBYTES];
	
		if (crypto_pwhash_str(hashed, password.c_str(), password.size(), crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE)) {
			throw runtime_error("Hashing failed -- not enough memory");
		}
	
		return string(hashed);
	}

	static bool verify(const std::string& storedHash, const std::string& password) {
		return crypto_pwhash_str_verify(storedHash.c_str(), password.c_str(), password.length()) == 0;
	}

    static std::string createSession(string username) {
        std::stringstream ss;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 255);

        for (int i = 0; i < 32; ++i) {
            ss << std::hex << distrib(gen);
        }
        std::string token = ss.str();

	sessions[token] = username;
        return token;
    }

    static string getUsernameFromToken(const std::string& token) {
        if (sessions.count(token)) {
            return sessions.at(token);
        }
        return "";
    }

private:
    static std::unordered_map<std::string, string> sessions;
};

std::unordered_map<std::string, string> AuthService::sessions;
