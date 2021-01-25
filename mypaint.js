# Using library P5 - see the coding train canal!

var x = false;
function setup() {
  createCanvas(400, 400);
  background(0);
}

function draw() {
  noStroke();
  if(x==true){
    fill(250, 200, 250);
    ellipse(mouseX, mouseY, 25, 25);
  }
}

function mousePressed(){ //evento
  x= !x;
}
