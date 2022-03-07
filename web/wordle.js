let table = document.getElementById("wordletable");
let currentRow = 0;
const json = JSON.parse('{"ROATE:{}}');
let currentWord = json;

for (let row = 0; row < 6; row++) {
    
    table.rows[row].cells[5].onclick = function() {
        nextRow(this);
    };
    
    for (let cell = 0; cell < 5; cell++) {
        table.rows[row].cells[cell].onclick = function() {
            cycleColor(this);
        };
        
    }
}

function cycleColor(cell) {
    if (cell.parentNode.rowIndex == currentRow) {
        if (cell.classList.contains("gray")) {
            cell.classList.replace("gray", "yellow");
        } else if (cell.classList.contains("yellow")) {
            cell.classList.replace("yellow", "green");
        } else if (cell.classList.contains("green")) {
            cell.classList.replace("green", "gray");
        }
    }
}

function nextRow(cell) {
    if (cell.hasAttribute("hidden") == false) {
        let row = cell.parentNode.rowIndex + 1;
        let res = getResult(row - 1);
        
        if(res == "22222") {
            cell.setAttribute("hidden", "");
            return;
        }
        
        currentWord = currentWord[Object.keys(currentWord)[0]];
        
        if (!currentWord.hasOwnProperty(res)) {
            alert("Invalid input");
            return;
        }
        currentWord = currentWord[res];
        
        cell.setAttribute("hidden", "");
        
        if (row < 5) {
            table.rows[row].cells[5].removeAttribute("hidden");
            currentRow = row;
        } else {
            currentRow = 6;
        }
        
        for (let i = 0; i < 5; i++) {
            table.rows[row].cells[i].classList.replace("empty", "gray");
        }
        
        nextWord(row - 1, res);
    }
}

function writeWord(word, row) {
    for (let i = 0; i < 5; i++) {
        table.rows[row].cells[i].innerHTML = word[i];
    }
}

function nextWord(row, res) {
    if (typeof(currentWord) == "string") {
        writeWord(currentWord, row + 1);
        
        for (let i = 0; i < 5; i++) {
            table.rows[row + 1].cells[i].classList.replace("gray", "green");
        }
        
        currentRow = 6;
        
        table.rows[row + 1].cells[5].setAttribute("hidden", "");
    } else {
        writeWord(Object.keys(currentWord)[0], row + 1);
    }
}

function getResult(row) {
    let res = "";
    
    for (let i = 0; i < 5; i++) {
        let classes = table.rows[row].cells[i].classList;
        
        if (classes.contains("gray")) {
            res += "0";
        } else if (classes.contains("yellow")) {
            res += "1";
        } else if (classes.contains("green")) {
            res += "2";
        }
    }
    
    return res;
}
