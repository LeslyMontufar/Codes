let clearButton;
let canvas;

let doodleClassifier;
let resultsDiv; // let eh variavel estatica
var res;

let toggleButton;
let video;

function setup() {
    canvas = createCanvas(400, 400);
    clearButton = createButton('clear');
    clearButton.mousePressed(clearCanvas);

    toggleButton = createButton('toggle entry');
    toggleButton.mousePressed(toggleEntry);
    
    toggleButton.value = 1;
    background(225);

    doodleClassifier = ml5.imageClassifier('DoodleNet', modelReady);
    resultsDiv = createDiv('model loading');
    
    video = createCapture(VIDEO);
    video.hide();
}

function modelReady() {
    console.log('model loaded');
    doodleClassifier.classify(canvas, gotResults);
}

function gotResults(error, results) {
    if(error) {
        console.error(error);
        return;
    }
    console.log(results[0].label);
    setTimeout(function(){
        if (results[0].confidence>0.2 && res != results[0].label) {
            res = results[0].label;
            speak(res);
        }
    }, 800);

    let content = `${results[0].label} 
                    ${nf(100*results[0].confidence, 2, 1)}% <br/>
                    ${results[1].label} 
                    ${nf(100*results[1].confidence, 2, 1)}%`;
    // o acento agudo funciona para mandar comando
    resultsDiv.html(content);
    doodleClassifier.classify(canvas, gotResults);
}

function speak(res) {
    if ('speechSynthesis' in window){
        var msg = new SpeechSynthesisUtterance();
        msg.text = res;
        window.speechSynthesis.speak(msg); 
    } else {
        alert('O navegador nao suporta a fala :/');
    }
}

function clearCanvas() {
    background(250);
    toggleButton.value = 1;
}
function toggleEntry() {
    toggleButton.value = !toggleButton.value;
    background(250);
    // console.log(toggleButton.value);
}

function draw() {
    if (toggleButton.value){
        if (mouseIsPressed) {
            strokeWeight(16);
            line(mouseX, mouseY, pmouseX, pmouseY);
        }
    } else {
        image(video, 0, 0, width, height);
    }
}
