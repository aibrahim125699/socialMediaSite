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

	app.port(8080).multithreaded().run();

	return 0;
}
