# Fun��o figure
# A fun��o gcf retorna o n�mero da figura corrente
# gcf = get current figure

figure(1)
x = 0:0.05:2;
y1 = exp(x);
plot(x, y1);

figure(2);
y2 = exp(-x);
plot(x, y2);