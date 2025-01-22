#include "room.h"
#include <json/json.h>
#include <stdexcept>

// Constructor to initialize database connection
Database::Database(const std::string &host, const std::string &user, const std::string &password, const std::string &db_name) {
    driver = get_driver_instance();
    connection = driver->connect(host, user, password);
    connection->setSchema(db_name);
}

// Destructor to clean up the connection
Database::~Database() {
    delete connection;
}

// Get all available rooms
std::string Database::getAvailableRooms() {
    sql::Statement *stmt = connection->createStatement();
    sql::ResultSet *res = stmt->executeQuery("SELECT * FROM rooms WHERE is_available = true");

    Json::Value rooms(Json::arrayValue);
    while (res->next()) {
        Json::Value room;
        room["room_number"] = res->getInt("room_number");
        room["type"] = res->getString("type");
        room["price_per_night"] = res->getDouble("price_per_night");
        room["is_available"] = res->getBoolean("is_available");
        rooms.append(room);
    }

    delete res;
    delete stmt;

    Json::StreamWriterBuilder writer;
    return Json::writeString(writer, rooms);
}

// Book a room
std::string Database::bookRoom(const std::string &name, const std::string &email, int room_number) {
    try {
        // Check room availability
        sql::PreparedStatement *check_stmt = connection->prepareStatement(
            "SELECT * FROM rooms WHERE room_number = ? AND is_available = true");
        check_stmt->setInt(1, room_number);
        sql::ResultSet *res = check_stmt->executeQuery();

        if (!res->next()) {
            delete res;
            delete check_stmt;
            return "Room is not available!";
        }

        int room_id = res->getInt("id");

        // Add customer
        sql::PreparedStatement *add_customer = connection->prepareStatement(
            "INSERT INTO customers (name, email) VALUES (?, ?)");
        add_customer->setString(1, name);
        add_customer->setString(2, email);
        add_customer->execute();
        delete add_customer;

        // Mark room as booked
        sql::PreparedStatement *update_room = connection->prepareStatement(
            "UPDATE rooms SET is_available = false WHERE id = ?");
        update_room->setInt(1, room_id);
        update_room->execute();
        delete update_room;

        return "Room booked successfully!";
    } catch (sql::SQLException &e) {
        return std::string("Error during booking: ") + e.what();
    }
}
