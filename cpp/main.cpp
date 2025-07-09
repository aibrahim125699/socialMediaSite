#include "crow.h"
#include <fstream>
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

	CROW_ROUTE(app, "/register").methods("POST"_method)([](const crow::request& req){
		auto body = crow::json::load(req.body);
		if (!body) {
			return crow::response(400, "Invalid JSON");
		}

		string username=body["username"].s();
		string password=body["password"].s();

		// ADD SAVING TO CREDENTIALS FEATURE later

		return crow::response(200,username);
		// login functionality for later
		// if (username == USERNAME && password == PASSWORD) {
		// 	return crow::response(200, "Login successful");
		// } else {
		// 	return crow::response(401, "Unauthorized");
		// }
	});

	app.port(8080).multithreaded().run();

	return 0;
}
