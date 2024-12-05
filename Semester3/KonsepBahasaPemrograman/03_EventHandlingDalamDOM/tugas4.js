
        // Mengambil elemen input, tombol, dan daftar
        const inputField = document.getElementById('itemInput');
        const addButton = document.getElementById('addItemButton');
        const itemList = document.getElementById('itemList');

        // Menambahkan event click ke tombol
        addButton.addEventListener('click', function() {
            // Mendapatkan nilai dari input field
            const newItemText = inputField.value;

            // Memastikan input tidak kosong
            if (newItemText.trim() !== '') {
                // Membuat elemen li baru
                const newItem = document.createElement('li');
                newItem.textContent = newItemText;

                // Menambahkan elemen li ke ul
                itemList.appendChild(newItem);

                // Mengosongkan input field setelah item ditambahkan
                inputField.value = '';
            } else {
                alert('Masukkan teks untuk item!');
            }
        });