document.addEventListener('DOMContentLoaded', () => {
    const roomContainer = document.getElementById('rooms');
    const bookingForm = document.getElementById('booking-form');

    // Fetch available rooms
    async function fetchRooms() {
        const response = await fetch('http://localhost:3000/rooms');
        const rooms = await response.json();
        roomContainer.innerHTML = rooms.map(room => `
            <div>
                <p>Room ${room.room_number}</p>
                <p>Type: ${room.type}</p>
                <p>Price: $${room.price_per_night}</p>
                <p>Status: ${room.is_available ? 'Available' : 'Booked'}</p>
            </div>
        `).join('');
    }

    // Handle room booking
    bookingForm.addEventListener('submit', async (event) => {
        event.preventDefault();
        const name = document.getElementById('name').value;
        const email = document.getElementById('email').value;
        const roomNumber = document.getElementById('room-number').value;

        const response = await fetch('http://localhost:3000/book-room', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ name, email, room_number: roomNumber }),
        });

        alert(await response.text());
        fetchRooms(); // Refresh rooms
    });

    fetchRooms(); // Initial call
});
