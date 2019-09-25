% sin_x.m : Esse arquivo M calcula e desenha a
% função seno(x) para 0 <= x <= 6.
a = input('Enter the value of a: ');
b = input('Enter the value of b: ');
x = a:0.1:b;
y = sin(x);
plot(x, y);
