#include "crow.h"
#include <fstream>
#include <sodium.h>
#include <string>
#include "include/UserManager.h"
#include "include/AuthService.h"
using namespace std;

string fileToString(const string& path) {
	ifstream file(path);
	if (!file) return "File not found";

	stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}


int main() {
	crow::SimpleApp app;

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

		if (!UserManager::userExists(username)) {
			UserManager::registerUser(username, password);
		} else {
			return crow::response(400, "Username already in use.");
		}

		return crow::response(200,password);
	});

	CROW_ROUTE(app, "/login").methods("POST"_method)([&](const crow::request& req){

		auto body = crow::json::load(req.body);

		string username=body["username"].s();
		string password=body["password"].s();
		User* user = UserManager::getUser(username);
		
		if (user && AuthService::verify(user->getPassword(), password)) {
			std::string token = AuthService::createSession(user->getUsername());
			crow::json::wvalue response_json;
			response_json["token"] = token;
			response_json["username"] = user->getUsername();
			return crow::response(200, response_json);
		} else {
            		return crow::response(401, "{\"error\": \"Invalid credentials\"}");
		}
	
	});

	app.port(8080).multithreaded().run();

	return 0;
}
