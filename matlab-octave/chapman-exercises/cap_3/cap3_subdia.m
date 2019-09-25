# Subdiagramas

figure(1);

% current 1
subplot(2, 1, 1); % 2 linhas e 1 coluna
x = -pi:pi/20:pi;
y = sin(x);
plot(x, y);
title('Subdiagrama 1: sen(x)');

% current 2
subplot(2, 1, 2); % 2 linhas e 1 coluna
x = -pi:pi/20:pi;
y = cos(x);
plot(x, y);
title('Subdiagrama 2: cos(x)');