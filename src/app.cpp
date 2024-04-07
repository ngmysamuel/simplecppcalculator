#include <iostream>
#include "./httplib.h"

int main() {
    std::cout << "Hi there!";

    // HTTP
    httplib::Server svr;

    svr.Get("/", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    svr.Get("/plus/:first/:second", [](const httplib::Request& req, httplib::Response &res) {
        auto first_argument = req.path_params.at("first");
        auto second_argument = req.path_params.at("second");
        auto answer = first_argument + second_argument;
        res.set_content(answer, "text/plain");
    });

    svr.listen("0.0.0.0", 8080);
}