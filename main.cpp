#include <iostream>
#include <string>
#include <cstdio>
#include "httplib.h"
#include "json.h"

//#define RES [&](const httplib::Request &req, httplib::Response &res)
#define REQ [&](const httplib::Request &req, httplib::Response &)
#define CPPHTTPLIB_OPENSSL_SUPPORT

using httplib::Server;
using nlohmann::json;
using namespace std::chrono;

auto readJSON() {
    // Reading Json file
    std::cout << "Preparing to read JSON file..." << std::endl;
    std::ifstream o(R"(C:\Users\justi\OneDrive\Desktop\Grade 12 Computer Science\christianslogin\users.json)");
    json data = json::parse(o);
    std::cout << "Finished reading JSON file..." << std::endl;
    return data;
}

void closeJSON(json data) {
    // Writing to json file
    std::cout << "Preparing to parse JSON file..." << std::endl;
    std::ofstream w(R"(C:\Users\justi\OneDrive\Desktop\Grade 12 Computer Science\christianslogin\users.json)");
    w << std::setw(4) << data << std::endl;
    w.flush();
    std::cout << "Finished parsing JSON file..." << std::endl;

}


int main() {

    std::cout << "Running" << std::endl;
    httplib::Server svr;

    svr.Get("/signup", [](const httplib::Request &req, httplib::Response &res) {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "SignUp API Request Starting..." << std::endl;
        res.set_header("Access-Control-Allow-Origin", "http://127.0.0.1:5500");

        // Extract the two string arguments from the query string
        std::string username = req.get_param_value("arg1");
        std::string password = req.get_param_value("arg2");


        json data = readJSON();

        bool isValidSignUp = true;
        std::string message;

        // Checking username is already in use
        for (int i = 0; i < data.size(); i++) {
            if (data[i]["username"] == username) {
                std::cout << "SignUp API: Error Checking..." << std::endl;


                // If valid gets all the information
                username = data[i]["username"];
                // password = data[i]["password"];
                isValidSignUp = false;

                std::cout << "SignUp API: " << username << ": Access Granted" << std::endl;
            }
        }

        if (isValidSignUp) {
            std::cout << "SignUp API: Adding Data..." << std::endl;
            // Adding data
            data[data.size()] = {{"username", username},
                                     {"password", password}};

            closeJSON(data);

            message = "SignUp Successful";
            std::cout << "SignUp API: " << "Successful" << std::endl;

        } else {
            message = "SignUp Unsuccessful";
            std::cout << "SignUp API: " << "Unsuccessful" << std::endl;

        }


        res.set_content(message, "text/plain");
        std::cout << "SignUp API: Request Ending." << std::endl;
    });

    svr.Get("/login", [](const httplib::Request &req, httplib::Response &res) {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Login API Request Starting..." << std::endl;
        res.set_header("Access-Control-Allow-Origin", "http://127.0.0.1:5500");

        // Extract the two string arguments from the query string
        std::string username = req.get_param_value("arg1");
        std::string password = req.get_param_value("arg2");
        
        // Init variable
        bool isLoggedIn = false;


        json data = readJSON();

        // Checking if valid login information
        for (int i = 0; i < data.size(); i++) {
            std::cout << "SignUp API: Error Checking..." << std::endl;
            if (data[i]["username"] == username &&
                data[i]["password"] == password) {

                // If valid gets all the information
                username = data[i]["username"];
               // password = data[i]["password"];
                isLoggedIn = true;

                std::cout << "Login API: " << username << ": Access Granted" << std::endl;
            }
        }

        // Use the arguments to construct the response message

        std::string message;
        if (!isLoggedIn)
            message = "Login Denied";
        else
            message = "Login Successful";


        res.set_content(message, "text/plain");
        std::cout << "Login API: Request Ending." << std::endl;
    });

    svr.listen("0.0.0.0", 8081);




    return 0;
}
