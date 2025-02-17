<div class="container mt-5">
  <h3>Form Pendaftaran</h3>
  <form id="registrationForm">
    <h5 class="mt-4">Data Pendaftaran</h5>
    <div class="mb-3">
      <label for="program_studi" class="form-label"
        >Pilihan Program Studi</label
      >
      <select
        id="program_studi"
        name="program_studi"
        class="form-select"
        required
      >
        <option value="">-- Pilih Program Studi --</option>
        <option value="S1 - Teknologi Informatika">
          S1 - Teknologi Informatika
        </option>
        <option value="S1 - Sistem Informasi">S1 - Sistem Informasi</option>
        <option value="D3 - Manajemen Informatika">
          D3 - Manajemen Informatika
        </option>
      </select>
    </div>

    <div id="selected_program" class="alert alert-info">
      Pilihan Program Studi:
      <span id="program_value">[Belum ada pilihan]</span>
    </div>

    <div class="mb-3">
      <label for="kelas" class="form-label">Pilihan Kelas</label>
      <select id="kelas" name="kelas" class="form-select" required>
        <option value="">-- Pilih Kelas --</option>
        <option value="Pagi">Pagi</option>
        <option value="Malam">Malam</option>
      </select>
    </div>

    <div id="selected_kelas" class="alert alert-warning">
      Pilihan Kelas: <span id="kelas_value">[Belum ada pilihan]</span>
    </div>

    <h5 class="mt-4">Data Pribadi</h5>
    <div class="mb-3">
      <label for="nama_lengkap" class="form-label">Nama Lengkap</label>
      <input
        type="text"
        id="nama_lengkap"
        name="nama_lengkap"
        class="form-control"
        required
      />
    </div>
    <div class="mb-3">
      <label for="nik" class="form-label">NIK</label>
      <input
        type="text"
        id="nik"
        name="nik"
        class="form-control"
        maxlength="16"
        required
      />
    </div>
    <div class="mb-3">
      <label for="tempat_lahir" class="form-label">Tempat Lahir</label>
      <input
        type="text"
        id="tempat_lahir"
        name="tempat_lahir"
        class="form-control"
        required
      />
    </div>
    <div class="mb-3">
      <label for="tanggal_lahir" class="form-label">Tanggal Lahir</label>
      <input
        type="date"
        id="tanggal_lahir"
        name="tanggal_lahir"
        class="form-control"
        required
      />
    </div>
    <div class="mb-3">
      <label for="gender" class="form-label">Gender</label>
      <input
        type="text"
        id="gender"
        name="gender"
        class="form-control"
        readonly
      />
    </div>
    <div class="mb-3">
      <label for="email" class="form-label">Email</label>
      <input
        type="email"
        id="email"
        name="email"
        class="form-control"
        required
      />
    </div>
    <div class="mb-3">
      <label for="alamat" class="form-label">Alamat</label>
      <textarea
        id="alamat"
        name="alamat"
        class="form-control"
        rows="3"
        required
      ></textarea>
    </div>

    <h5 class="mt-4">Sumber Informasi</h5>
    <div class="mb-3">
      <div class="form-check">
        <input
          type="radio"
          id="internet"
          name="sumber_informasi"
          value="Internet"
          class="form-check-input"
          required
        />
        <label for="internet" class="form-check-label">Internet/Website</label>
      </div>
      <div class="form-check">
        <input
          type="radio"
          id="brosur"
          name="sumber_informasi"
          value="Brosur"
          class="form-check-input"
          required
        />
        <label for="brosur" class="form-check-label">Brosur</label>
      </div>
      <div class="form-check">
        <input
          type="radio"
          id="spanduk"
          name="sumber_informasi"
          value="Spanduk"
          class="form-check-input"
          required
        />
        <label for="spanduk" class="form-check-label">Spanduk</label>
      </div>
      <div class="form-check">
        <input
          type="radio"
          id="media_cetak"
          name="sumber_informasi"
          value="Media_cetak"
          class="form-check-input"
          required
        />
        <label for="media_cetak" class="form-check-label"
          >Media Cetak (Koran, Majalah)</label
        >
      </div>
      <div class="form-check">
        <input
          type="radio"
          id="teman"
          name="sumber_informasi"
          value="Teman"
          class="form-check-input"
          required
        />
        <label for="teman" class="form-check-label">Teman</label>
      </div>
      <div class="form-check">
        <input
          type="radio"
          id="keluarga"
          name="sumber_informasi"
          value="Keluarga"
          class="form-check-input"
          required
        />
        <label for="keluarga" class="form-check-label">Keluarga</label>
      </div>
    </div>

    <div class="mt-3 mb-3">
      <button type="submit" class="btn btn-primary">Submit</button>
    </div>
  </form>

  <div id="submitAlert" class="alert alert-success">
    <strong>Form Berhasil Disubmit!</strong>
    <div>Program Studi: {{ $program_studi }}</div>
    <div>Kelas: {{ $kelas }}</div>
    <div>Nama Lengkap: {{ $nama_lengkap }}</div>
    <div>NIK: {{ $nik }}</div>
    <div>Tempat Lahir: {{ $tempat_lahir }}</div>
    <div>Tanggal Lahir: {{ $tanggal_lahir }}</div>
    <div>Email: {{ $email }}</div>
    <div>Alamat: {{ $alamat }}</div>
    <div>Sumber Informasi: {{ $sumber_informasi }}</div>
  </div>
</div>