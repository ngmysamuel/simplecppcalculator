#include <iostream>
#include "./httplib.h"
#include <math.h>

std::string formatJson(std::string ans, std::string op, std::string arg1, std::string arg2) {
    return "{\"answer\": \"" + ans + "\", \"statement\": \"" + arg1 + " " + op + " " + arg2 + " = " + ans + "\" }";
}

std::string operate(std::string arg1, std::string arg2, std::string op) {
    double first_argument = std::stod( arg1 );
    double second_argument = std::stod( arg2 );
    if (op == "plus") {
        auto answer = std::to_string( first_argument + second_argument );
        return formatJson(answer, "+", arg1, arg2);
    } else if (op == "minus") {
        auto answer = std::to_string( first_argument - second_argument );
        return formatJson(answer, "-", arg1, arg2);
    } else if (op == "multiply") {
        auto answer = std::to_string( first_argument * second_argument );
        return formatJson(answer, "*", arg1, arg2);
    } else if (op == "divide") {
        auto answer = std::to_string( first_argument / second_argument );
        return formatJson(answer, "/", arg1, arg2);
    }
    throw std::invalid_argument( "No such operator" );
}

void handleException(std::exception& ex, httplib::Response &res) {
    std::cout << "\nInvalid... Exception: " << ex.what() << std::endl;
    res.set_content("{\"isError\": \"true\", \"message\": \"Invalid... Please check server logs.\"}", "application/json");
    res.status = httplib::StatusCode::InternalServerError_500;
}

int main() {
    std::cout << "Server started!";

    // HTTP
    httplib::Server svr;

    svr.Get("/", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    svr.Get("/plus/:first/:second", [](const httplib::Request& req, httplib::Response &res) {
        try {
            res.set_content(
                    operate(req.path_params.at("first"), req.path_params.at("second"), "plus"),
                    "application/json"
                );
        } catch (std::exception& ex) {
            handleException(ex, res);
        }
    });

    svr.Get("/divide/:first/:second", [](const httplib::Request& req, httplib::Response &res) {
        try {
            res.set_content(
                    operate(req.path_params.at("first"), req.path_params.at("second"), "divide"),
                    "application/json"
                );
        } catch (std::exception& ex) {
            handleException(ex, res);
        }
    });

    svr.Get("/minus/:first/:second", [](const httplib::Request& req, httplib::Response &res) {
        try {
            res.set_content(
                    operate(req.path_params.at("first"), req.path_params.at("second"), "minus"),
                    "application/json"
                );
        } catch (std::exception& ex) {
            handleException(ex, res);
        }
    });

    svr.Get("/multiply/:first/:second", [](const httplib::Request& req, httplib::Response &res) {
        try {
            res.set_content(
                    operate(req.path_params.at("first"), req.path_params.at("second"), "multiply"),
                    "application/json"
                );
        } catch (std::exception& ex) {
            handleException(ex, res);
        }
    });

    svr.Get("/exponent/:first/:second", [](const httplib::Request& req, httplib::Response &res) {
        try {
            double first_argument = std::stod( req.path_params.at("first") );
            double second_argument = std::stod( req.path_params.at("second") );
            if (first_argument > 50) {
                res.set_content("{\"isError\": \"true\", \"message\": \"Invalid... Please select a number less than 50\"}", "application/json");
                res.status = httplib::StatusCode::InternalServerError_500;
            }
            else if (second_argument > 50) {
                res.set_content("{\"isError\": \"true\", \"message\": \"Invalid... Please select a number less than 50\"}", "application/json");
                res.status = httplib::StatusCode::InternalServerError_500;
            } else {
                auto answer = std::to_string( pow(first_argument, second_argument) );
                res.set_content(formatJson(answer, "**", req.path_params.at("first"), req.path_params.at("second")), "application/json");
            }
        } catch (std::exception& ex) {
            handleException(ex, res);
        }
    });

    svr.listen("0.0.0.0", 8080);
}