% Estilo e Cor

x = 0:1:10;
y = x.^2 - 10.*x + 15;
plot(x, y,  'r--', x, y, 'bo');

title('Red --   and   Blue o');

grid on;