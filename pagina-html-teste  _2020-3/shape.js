/// <reference path="node_modules/@types/p5/global.d.ts" />
// let r,x,y;

function setup() {
    createCanvas(400, 400);
    // background(255);
}

function draw() {
    background(225);
    saveFrames('out', 'png', 1, 25, data => {
        print(data);
      });
    // strokeWeight(4);
    // r = random(24, 64);
    // x = random(width-r);
    // y = random(height-r);
    // stroke(random(100), random(100), random(100));
    // circle(x, y, r*2);
    // saveFrame("data/circle####.png");
}