// Theme Toggle
const themeToggleBtn = document.getElementById('theme-toggle');
const lightStylesheet = document.getElementById('theme-stylesheet');
const darkStylesheet = document.getElementById('dark-theme-stylesheet');

// Pomodoro Timer Variables
const timerDisplay = document.getElementById('timer');
const startBtn = document.getElementById('start-btn');
const pauseBtn = document.getElementById('pause-btn');
const resumeBtn = document.getElementById('resume-btn');
const resetBtn = document.getElementById('reset-btn');
const studyTimeInput = document.getElementById('study-time');
const breakTimeInput = document.getElementById('break-time');

// Todo List Variables
const todoInput = document.getElementById('todo-input');
const addTodoBtn = document.getElementById('add-todo');
const todoList = document.getElementById('todo-list');

// Pomodoro Timer Logic
let timer;
let timeLeft;
let isStudyTime = true;
let isRunning = false;



//sound
const studyEndSound = new Audio('alarm.wav');
const breakEndSound = new Audio('alarm.wav');


// Theme Management
function toggleTheme() {
    if (lightStylesheet.disabled) {
        // Switch to Light Mode
        lightStylesheet.disabled = false;
        darkStylesheet.disabled = true;
        localStorage.setItem('theme', 'light');
    } else {
        // Switch to Dark Mode
        lightStylesheet.disabled = true;
        darkStylesheet.disabled = false;
        localStorage.setItem('theme', 'dark');
    }
}

function loadTheme() {
    const savedTheme = localStorage.getItem('theme');
    if (savedTheme === 'dark') {
        lightStylesheet.disabled = true;
        darkStylesheet.disabled = false;
    } else {
        lightStylesheet.disabled = false;
        darkStylesheet.disabled = true;
    }
}

// Theme Toggle Event Listener
themeToggleBtn.addEventListener('click', toggleTheme);

function startTimer() {
    if (isRunning) return; // Jika timer sudah berjalan, hentikan fungsi
    isRunning = true;

    // Jika waktu belum diatur, gunakan waktu input
    if (timeLeft == null) {
        const studyTime = studyTimeInput.value * 60;
        const breakTime = breakTimeInput.value * 60;
        timeLeft = isStudyTime ? studyTime : breakTime;
    }

    timer = setInterval(() => {
        const minutes = Math.floor(timeLeft / 60);
        const seconds = timeLeft % 60;
        timerDisplay.textContent = `${minutes.toString().padStart(2, '0')}:${seconds.toString().padStart(2, '0')}`;

        if (timeLeft <= 0) {
            clearInterval(timer);
            isRunning = false; // Pastikan status dihentikan sementara
            setTimeout(() => {
                if (isStudyTime) {
                    // Ketika waktu belajar habis
                    studyEndSound.play(); // Putar suara akhir waktu belajar
                    isStudyTime = false; // Beralih ke waktu istirahat
                    timeLeft = breakTimeInput.value * 60; // Atur waktu istirahat
                    startTimer(); // Mulai timer istirahat setelah sedikit delay
                } else {
                    // Ketika waktu istirahat habis
                    breakEndSound.play(); // Putar suara akhir waktu istirahat
                    isStudyTime = true; // Kembali ke waktu belajar
                    timeLeft = null; // Reset waktu
                    timerDisplay.textContent = `${studyTimeInput.value}:00`; // Tampilkan ulang waktu belajar
                }
            }, 200); // Tambahkan delay 200ms
        }

        timeLeft--;
    }, 1000);
}

function resumeTimer() {
    if (!isRunning && timeLeft > 0) {
        isRunning = true;
        timer = setInterval(() => {
            const minutes = Math.floor(timeLeft / 60);
            const seconds = timeLeft % 60;
            timerDisplay.textContent = `${minutes.toString().padStart(2, '0')}:${seconds.toString().padStart(2, '0')}`;

            if (timeLeft <= 0) {
                clearInterval(timer);
                isRunning = false; // Pastikan status dihentikan sementara
                setTimeout(() => {
                    if (isStudyTime) {
                        // Ketika waktu belajar habis
                        studyEndSound.play(); // Putar suara akhir waktu belajar
                        isStudyTime = false; // Beralih ke waktu istirahat
                        timeLeft = breakTimeInput.value * 60; // Atur waktu istirahat
                        startTimer(); // Mulai timer istirahat setelah sedikit delay
                    } else {
                        // Ketika waktu istirahat habis
                        breakEndSound.play(); // Putar suara akhir waktu istirahat
                        isStudyTime = true; // Kembali ke waktu belajar
                        timeLeft = null; // Reset waktu
                        timerDisplay.textContent = `${studyTimeInput.value}:00`; // Tampilkan ulang waktu belajar
                    }
                }, 200); // Tambahkan delay 200ms
            }

            timeLeft--;
        }, 1000);
    }
}


// Tambahkan fungsi pauseTimer
function pauseTimer() {
    if (isRunning) {
        clearInterval(timer);
        isRunning = false; // Timer berhenti sementara
    }
}

function resetTimer() {
    clearInterval(timer);
    isRunning = false;
    isStudyTime = true;
    timeLeft = null;
    timerDisplay.textContent = `${studyTimeInput.value.padStart(2, '0')}:00`; // Reset ke waktu belajar awal
}

// Event Listeners untuk tombol Timer
startBtn.addEventListener('click', startTimer);
pauseBtn.addEventListener('click', pauseTimer);
resumeBtn.addEventListener('click', resumeTimer);
resetBtn.addEventListener('click', resetTimer);

// TODO LIST Updates
function loadTodos() {
    const todos = JSON.parse(localStorage.getItem('todos') || '[]');
    todoList.innerHTML = '';
    todos.forEach((todo, index) => {
        const li = document.createElement('li');
        li.innerHTML = `
            <span class="${todo.completed ? 'completed' : ''}">${todo.text}</span>
            <div class="todo-buttons">
                <button class="complete-btn" data-index="${index}">✓</button>
                <button class="delete-btn" data-index="${index}">✗</button>
            </div>
        `;
        todoList.appendChild(li);
    });
    attachTodoListeners();
}

function attachTodoListeners() {
    // Complete Todo
    document.querySelectorAll('.complete-btn').forEach((btn) => {
        btn.addEventListener('click', () => {
            const index = btn.getAttribute('data-index');
            const todos = JSON.parse(localStorage.getItem('todos') || '[]');
            todos[index].completed = !todos[index].completed;
            saveTodos(todos);
            loadTodos();
        });
    });

    // Delete Todo
    document.querySelectorAll('.delete-btn').forEach((btn) => {
        btn.addEventListener('click', () => {
            const index = btn.getAttribute('data-index');
            const todos = JSON.parse(localStorage.getItem('todos') || '[]');
            todos.splice(index, 1);
            saveTodos(todos);
            loadTodos();
        });
    });
}

function saveTodos(todos) {
    localStorage.setItem('todos', JSON.stringify(todos));
}

addTodoBtn.addEventListener('click', () => {
    const todoText = todoInput.value.trim();
    if (todoText) {
        const todos = JSON.parse(localStorage.getItem('todos') || '[]');
        todos.push({ text: todoText, completed: false });
        saveTodos(todos);
        todoInput.value = '';
        loadTodos();
    }
});

// Load todo items on page load
document.addEventListener('DOMContentLoaded', () => {
    loadTheme(); // Pastikan tema dimuat
    loadSavedSettings(); // Pastikan pengaturan timer dimuat
    loadTodos(); // Pastikan todo list dimuat
});


// -----------sspotify

const spotifyBtn = document.getElementById('spotify-link');

spotifyBtn.addEventListener('click', () => {
    window.open('https://open.spotify.com/', '_blank');
});