#pragma once

#include <string>
#include <unordered_map>
#include <random>
#include <sstream>
#include <functional>
using namespace std;

class AuthService {
public:
    // static std::string hashPassword(const std::string& password) {
    // }

    // static bool verifyPassword(const string& password, const string& hash) {
    // }

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
