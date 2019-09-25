# Exemplo 2.3 - Conversão de Temperatura
# Programa lê temp em ºF e converte para K
# Mostre o resultado

# Fórmula de conversão:
# F - temp em Fahrenheit
# K - temp em Kelvin 

# K = (5/9)*(F - 32) + 273.15

F = input('Enter with the Fahrenheit temperature: ');
K = (5/9)*(F - 32) + 273.15;
fprintf('%g ºF corresponds to %g kelvins\n', F, K);



x = -110:2:212;
y = (5/9).*(x - 32) + 273.15;

plot(x, y,'r-', F, K, 'bo');
title('Conversão de Temperaturas: Fahrenheit para kelvin');
xlabel('ºF');
ylabel('kelvin');
legend('ºF to kelvin', 'ºF',0);
grid on;