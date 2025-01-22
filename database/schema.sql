CREATE DATABASE hotel_management;

USE hotel_management;

CREATE TABLE rooms (
    id INT AUTO_INCREMENT PRIMARY KEY,
    room_number INT NOT NULL,
    type VARCHAR(50),
    price_per_night FLOAT,
    is_available BOOLEAN DEFAULT TRUE
);

CREATE TABLE customers (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100),
    email VARCHAR(100),
    phone VARCHAR(20)
);

CREATE TABLE bookings (
    id INT AUTO_INCREMENT PRIMARY KEY,
    customer_id INT,
    room_id INT,
    FOREIGN KEY (customer_id) REFERENCES customers(id),
    FOREIGN KEY (room_id) REFERENCES rooms(id)
);
