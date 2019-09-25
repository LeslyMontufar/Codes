# Exemplo 2.3 - Convers�o de Temperatura
# Programa l� temp em �F e converte para K
# Mostre o resultado

# F�rmula de convers�o:
# F - temp em Fahrenheit
# K - temp em Kelvin 

# K = (5/9)*(F - 32) + 273.15

F = input('Enter with the Fahrenheit temperature: ');
K = (5/9)*(F - 32) + 273.15;
fprintf('%g �F corresponds to %g kelvins\n', F, K);



x = -110:2:212;
y = (5/9).*(x - 32) + 273.15;

plot(x, y,'r-', F, K, 'bo');
title('Convers�o de Temperaturas: Fahrenheit para kelvin');
xlabel('�F');
ylabel('kelvin');
legend('�F to kelvin', '�F',0);
grid on;