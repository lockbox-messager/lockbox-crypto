#include <iostream>
#include <random>
#include <sstream>
#include <iomanip>
#include <string>

std::string generate_uuid() {
    // Use thread_local to avoid recreating the engine on every call
    static thread_local std::random_device rd;
    static thread_local std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 15);
    std::uniform_int_distribution<int> dis2(8, 11);

    std::stringstream ss;
    ss << std::hex << std::setfill('0');

    // Section 1: 8 hex digits
    for (int i = 0; i < 8; ++i) ss << dis(gen);
    ss << "-";

    // Section 2: 4 hex digits
    for (int i = 0; i < 4; ++i) ss << dis(gen);
    ss << "-";

    // Section 3: 4 hex digits (starts with a '4' for Version 4 UUID)
    ss << "4";
    for (int i = 0; i < 3; ++i) ss << dis(gen);
    ss << "-";

    // Section 4: 4 hex digits (starts with 8, 9, a, or b for variant 1)
    ss << dis2(gen);
    for (int i = 0; i < 3; ++i) ss << dis(gen);
    ss << "-";

    // Section 5: 12 hex digits
    for (int i = 0; i < 12; ++i) ss << dis(gen);

    return ss.str();
}