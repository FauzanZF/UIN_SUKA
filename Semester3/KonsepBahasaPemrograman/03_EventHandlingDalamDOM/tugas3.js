// Mengambil elemen input dan paragraf
const inputField = document.getElementById('inputField');
const message = document.getElementById('message');

// Menambahkan event keydown ke input field
inputField.addEventListener('keydown', function(event) {
    // Menampilkan karakter terakhir yang ditekan
    message.textContent = `Karakter terakhir yang ditekan: ${event.key}`;
});