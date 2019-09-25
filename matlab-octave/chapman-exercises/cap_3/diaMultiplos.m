% Diagramas M�ltiplos
% f(x) e sua derivada

x = 0:pi/100:2*pi;
y1 = sin(2*x);
y2 = 2 * cos(2*x);
plot(x, y1, x, y2);
title('Diagrama M�ltiplo');
xlabel('x');
ylabel('y');

grid on; % grade ligada