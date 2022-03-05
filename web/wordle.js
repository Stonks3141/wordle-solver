let table = document.getElementById("wordletable");
let currentRow = 0;
const json = JSON.parse('{"SALET":{"00000":{"COURD":{"00000":{"NYMPH":{"10100":"MINIM","11000":"KINKY","11001":"WHINY","11010":"PINKY","12000":"VYING","21000":"NINNY","00001":"WHIFF","01000":{"FIZZY":{"12002":"JIFFY"}},"01010":"PIGGY","01021":"HIPPY","01220":"WIMPY","02110":"PYGMY"}},"00001":{"DINGY":{"12002":"BIDDY","12012":"GIDDY","12202":"WINDY","21111":"DYING","22002":"DIZZY"}},"00002":"VIVID","00010":{"BEIGY":{"20200":"BRINK","20202":"BRINY","20210":"BRING","00202":"PRIVY","00210":"WRING","00212":"GRIMY"}},"00011":"DRINK","00012":{"GRIND":{"11102":"RIGID"}},"00020":"MYRRH","00100":{"GIMPY":{"10002":"BUGGY","11000":"FUNGI","20022":"GUPPY","20202":"GUMMY","00002":{"FUNKY":{"22002":"FUZZY","22202":"FUNNY","02202":"BUNNY","02222":"HUNKY"}},"00012":"PUFFY","00022":"PUPPY","00202":"MUMMY","00220":"HUMPH","00222":"JUMPY","00102":"UNIFY","01010":"UNZIP"}},"00101":{"DUMPY":{"12002":"BUDDY","12012":"PUDGY","12102":"MUDDY","22202":"DUMMY"}},"00102":{"HUMID":{"01022":"UNDID"}},"00110":{"MURKY":{"02102":"RUGBY"}},"00111":"RUDDY","02220":"MOURN"}},"01010":{"BEARD":{"01102":{"AHEAD":{"00222":"KNEAD","20202":"AMEND"}}}}}}');
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
