#include "room.h"
#include "customer.h"
#include "booking.h"
#include <httplib.h>
#include <iostream>
using namespace httplib;

int main() {
    // Initialize the database connection
    Database db("tcp://127.0.0.1:3306", "root", "password", "hotel_management");

    // Initialize the HTTP server
    Server server;

    // Get available rooms
    server.Get("/rooms", [&db](const Request &, Response &res) {
        std::string rooms_json = db.getAvailableRooms();
        res.set_content(rooms_json, "application/json");
    });

    // Book a room
    server.Post("/book-room", [&db](const Request &req, Response &res) {
        // Parse request body for booking data
        auto json = parseJson(req.body);
        std::string name = json["name"].asString();
        std::string email = json["email"].asString();
        int room_number = json["room_number"].asInt();

        std::string message = db.bookRoom(name, email, room_number);
        res.set_content(message, "text/plain");
    });

    std::cout << "Server running on http://localhost:3000 ..." << std::endl;
    server.listen("localhost", 3000);

    return 0;
}
