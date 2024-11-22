// Tangkap elemen form
const form = document.getElementById("registrationForm");

// Tambahkan event listener untuk menangani pengiriman form
form.addEventListener("submit", function(event) {
    event.preventDefault(); // Mencegah pengiriman form secara default
    alert("Formulir dikirimkan!");
    form.reset(); // Mengosongkan form setelah alert
});
