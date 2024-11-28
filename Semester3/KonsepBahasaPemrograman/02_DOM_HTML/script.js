// const header1 = document.getElementById("h1")
// const p = document.getElementsByTagName("p")
// const list = document.querySelectorAll("li")

// header1.style.backgroundColor = "Aqua"
// p[0].style.backgroundColor = "tomato"
// list[0].style.color = "brown"

//---------------------------

const SebuahNode = document.getElementById("h1")
SebuahNode.innerHTML = "<em>Javascript</em>"

//---------------------------

// const nodeSection = document.getElementById("a")
// const nodeP = nodeSection.querySelector("p")
// const list = "<ol><li>ayam goreng</li><li>ayam rebus</li></ol>"
// nodeP.innerHTML = list

//----------------------------

// const nodeH1 = document.getElementById("h1")
// nodeH1.style.fontFamily = "consolas"
// nodeH1.style.backgroundColor = "gold"
// nodeH1.style.textShadow = "10px 10px 10px "

//----------------------------

// const nodeH1 = document.getElementById("h1")
// nodeH1.getAttribute("id")

// const nodeSection =document.getElementById("a")
// const nodeP1 = nodeSection.querySelector("P")
// nodeP1.setAttribute("id", "P1")

// const nodeDiv2 = document.getElementById("container2")
// const nodeUl = nodeDiv2.querySelector("ul")
// nodeUl.removeAttribute("id")

//------------------------------
document.getElementById("container1").style.backgroundColor = "#c0c0c033";
document.getElementById("container1").style.color = "#4169ff";
document.getElementById("container2").style.backgroundColor = "#000000cc ";
document.getElementById("container2").style.color = "#ffd700";



// Mengubah atribut href pada semua <a> menjadi "https://www.google.com"
const links = document.querySelectorAll("a");
links.forEach((link) => {
  link.setAttribute("href", "https://www.google.com");
});

// Pilih semua elemen yang ingin diubah
const elements = document.querySelectorAll("h1, p, a, li");

// Daftar font dan ukuran
const fonts = ["Arial", "Verdana", "Tahoma", "Georgia", "Courier New"];
const sizes = ["16px", "18px", "20px", "22px", "24px"];

// Loop melalui elemen-elemen tersebut
elements.forEach((element, index) => {
    // Gunakan font dan ukuran secara dinamis berdasarkan indeks
    const font = fonts[index % fonts.length];
    const size = sizes[index % sizes.length];

    // Terapkan gaya ke elemen
    element.style.fontFamily = font;
    element.style.fontSize = size;
});
