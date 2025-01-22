#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class Database {
private:
    sql::Driver *driver;
    sql::Connection *connection;

public:
    Database(const std::string &host, const std::string &user, const std::string &password, const std::string &db_name);
    ~Database();

    std::string getAvailableRooms();
    std::string bookRoom(const std::string &name, const std::string &email, int room_number);
};

#endif
