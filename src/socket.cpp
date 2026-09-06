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

    // Get new uuid
    server.Get("/uuid", [](const httplib::Request&, httplib::Response& res) {

        std::cout << "UUID GENERATING\n";
        auto value = generate_uuid();
        std::cout << "UUID GENERATED\n";

        res.set_content(value, "text/plain");
    });

    std::cout << "Cryptography server listening on port 3633...\n";

    // Listen on all local interfaces, port 3633
    if (!server.listen("0.0.0.0", 3633)) {
        std::cerr << "Failed to start server\n";
        return 1;
    }

    return 0;
}
