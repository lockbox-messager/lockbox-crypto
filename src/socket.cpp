#include <iostream>
#include "external/httplib.h"
#include "uuid.hpp"

int socket_main() {
    httplib::Server server;

    server.Get("/ping", [](const httplib::Request&, httplib::Response& res) {
        res.set_content(
            R"({"success":true,"message":"pong"})",
            "application/json"
        );
    });

    server.Get("/room-id", [](const httplib::Request&, httplib::Response& res) {

        auto value = generate_uuid();

        res.set_content("room-" + value, "text/plain");
    });

    server.Get("/user-id", [](const httplib::Request&, httplib::Response& res) {

        auto value = generate_uuid();

        res.set_content("user-" + value, "text/plain");
    });

    std::cout << "Cryptography server listening on port 3633...\n";

    // Listen on all local interfaces, port 3633
    if (!server.listen("0.0.0.0", 3633)) {
        std::cerr << "Failed to start server\n";
        return 1;
    }

    return 0;
}
