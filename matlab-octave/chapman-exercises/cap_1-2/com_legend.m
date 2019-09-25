% Comando legend
% f(x) e sua derivada

x = 0:pi/100:2*pi;
y1 = sin(2*x);
y2 = 2 * cos(2*x);
plot(x, y1, x, y2);
title('Plot of f(x) = sin(2x) and its derivative');
xlabel('x');
ylabel('y');
legend('f(x)', 'd/dx f(x)', 0)

grid on; % grade ligada