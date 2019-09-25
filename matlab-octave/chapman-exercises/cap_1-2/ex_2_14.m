# Exemplo 2.14 - Energia armazenada em uma Mola
# F = k*x;
# E = (1/2) * k * x^2;

molas = [20, 500; 24, 600; 22, 700; 20, 800];
F = molas(: , 1);
k = molas(:, 2);

x = F./k;
E = (1/2) .* k .*x.^2;

[maxE, num_mola] = max(E); 

fprintf('A mola %i possui mais energia pot armazenada\nde %g Joules\n',...
num_mola, maxE);