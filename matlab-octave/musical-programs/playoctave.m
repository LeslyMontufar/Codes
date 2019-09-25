%y = 0.25 * randn (2, 44100);

x = [523 ]
y = 0.25 .* x;

player = audioplayer (y, 44100, 10);
play (player);