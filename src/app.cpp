#include <iostream>
#include "./httplib.h"
#include <math.h>

int main() {
    std::cout << "Hi there!";

    // HTTP
    httplib::Server svr;

    svr.Get("/", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    svr.Get("/plus/:first/:second", [](const httplib::Request& req, httplib::Response &res) {
        try {
            double first_argument = std::stod( req.path_params.at("first") );
            double second_argument = std::stod( req.path_params.at("second") );
            auto answer = std::to_string( first_argument + second_argument );
            res.set_content(req.path_params.at("first") + " + " + req.path_params.at("second")  + " = " + answer, "text/plain");
        } catch (std::exception& ex) {
            std::cout << ex.what() << std::endl;
            res.set_content("Invalid... Please check server logs.", "text/plain");
        }
    });

    svr.Get("/divide/:first/:second", [](const httplib::Request& req, httplib::Response &res) {
        try {
            double first_argument = std::stod( req.path_params.at("first") );
            double second_argument = std::stod( req.path_params.at("second") );
            auto answer = std::to_string( first_argument / second_argument );
            res.set_content(req.path_params.at("first") + " / " + req.path_params.at("second")  + " = " + answer, "text/plain");
        } catch (std::exception& ex) {
            std::cout << ex.what() << std::endl;
            res.set_content("Invalid... Please check server logs.", "text/plain");
        }
    });

    svr.Get("/minus/:first/:second", [](const httplib::Request& req, httplib::Response &res) {
        try {
            double first_argument = std::stod( req.path_params.at("first") );
            double second_argument = std::stod( req.path_params.at("second") );
            auto answer = std::to_string( first_argument - second_argument );
            res.set_content(req.path_params.at("first") + " - " + req.path_params.at("second")  + " = " + answer, "text/plain");
        } catch (std::exception& ex) {
            std::cout << ex.what() << std::endl;
            res.set_content("Invalid... Please check server logs.", "text/plain");
        }
    });

    svr.Get("/multiply/:first/:second", [](const httplib::Request& req, httplib::Response &res) {
        try {
            double first_argument = std::stod( req.path_params.at("first") );
            double second_argument = std::stod( req.path_params.at("second") );
            auto answer = std::to_string( first_argument * second_argument );
            res.set_content(req.path_params.at("first") + " x " + req.path_params.at("second")  + " = " + answer, "text/plain");
        } catch (std::exception& ex) {
            std::cout << ex.what() << std::endl;
            res.set_content("Invalid... Please check server logs.", "text/plain");
        }
    });

    svr.Get("/exponent/:first/:second", [](const httplib::Request& req, httplib::Response &res) {
        try {
            double first_argument = std::stod( req.path_params.at("first") );
            double second_argument = std::stod( req.path_params.at("second") );
            if (first_argument > 50) {
                res.set_content("Please select a number less than 50", "text/plain");
            }
            else if (second_argument > 50) {
                res.set_content("Please select a number less than 50", "text/plain");
            } else {
                auto answer = std::to_string( pow(first_argument, second_argument) );
                res.set_content(req.path_params.at("first") + " ** " + req.path_params.at("second")  + " = " + answer, "text/plain");
            }
        } catch (std::exception& ex) {
            std::cout << ex.what() << std::endl;
            res.set_content("Invalid... Please check server logs.", "text/plain");
        }
    });

    svr.listen("0.0.0.0", 8080);
}