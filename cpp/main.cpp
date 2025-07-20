#include "crow.h"
#include <fstream>
#include <sodium.h>
#include <string>
#include "include/UserManager.h"
using namespace std;

string fileToString(const string& path) {
	ifstream file(path);
	if (!file) return "File not found";

	stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

string hashPassword(const string& password) {
	if (sodium_init()  < 0){
		throw runtime_error("Failed to initialize libsodium");
	}

	char hashed[crypto_pwhash_STRBYTES];

	if (crypto_pwhash_str(hashed, password.c_str(), password.size(), crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE)) {
		throw runtime_error("Hashing failed -- not enough memory");
	}

	return string(hashed);
}

int main() {
	crow::SimpleApp app;
	UserManager userManager;

	CROW_ROUTE(app, "/")([](){
		string html = fileToString("../public/home.html");
		crow::response res;
		res.code = 200;
		res.set_header("Content-Type", "text/html");
		res.body = html;
		return res;
	});

	CROW_ROUTE(app, "/register").methods("POST"_method)([&](const crow::request& req){
		//recieving credentials and hashing password
		auto body = crow::json::load(req.body);
		if (!body) {
			return crow::response(400, "Invalid JSON");
		}

		string username=body["username"].s();
		string password=body["password"].s();
		string password_hashed = hashPassword(password);

		if (!userManager.checkExistence(username)) {
			userManager.registerUser(username, password_hashed);
		} else {
			return crow::response(400, "Username already in use.");
		}

		return crow::response(200,password_hashed);
	});

	// CROW_ROUTE(app, "/login").methods("POST"_method)([](const crow::request& req){
	// 	auto body = crow::json::load(req.body);

	// 	string username=body["username"].s();
	// 	string password=body["password"].s();

	// 	crow::json::wvalue users_json = load_users(user_db);
	// 	auto& users = users_json["users"];
	// 	string hashedPassword;

	// 	for (size_t i=0; i < users.size(); ++i) {
	// 		string current = crow::json::load(users[i]["username"].dump()).s();
	// 		if (current == username) {
	// 			hashedPassword = crow::json::load(users[i]["password"].dump()).s();
	// 			break;
	// 		}
	// 	}

	// 	if (crypto_pwhash_str_verify(hashedPassword.c_str(), password.c_str(), password.length()) == 0 ) {
	// 		return crow::response(200, "Logged in!");
	// 	} else {
	// 		return crow::response(400, "Invalid login");
	// 	}
	// });

	app.port(8080).multithreaded().run();

	return 0;
}
