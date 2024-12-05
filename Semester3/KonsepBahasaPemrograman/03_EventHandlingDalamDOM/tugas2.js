
// Mengambil elemen tombol dan paragraf
        const button = document.getElementById('hoverButton');
        const message = document.getElementById('message');

// Menambahkan event mouseover ke tombol
        button.addEventListener('mouseover', function() {
            // Menampilkan pesan pada paragraf
            message.textContent = 'Mouse is over the button!';
        });