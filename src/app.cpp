#include <iostream>
#include "./httplib.h"

int main() {
    std::cout << "Hi there!";

    // HTTP
    httplib::Server svr;

    svr.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
    res.set_content("Hello World!", "text/plain");
    });

    svr.listen("0.0.0.0", 8080);
}