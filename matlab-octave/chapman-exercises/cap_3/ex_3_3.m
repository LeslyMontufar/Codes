# Exemplo 3.3 - Avaliar uma Função de Duas Variáveis

# 1. Estabeleça o prolema
% Jogar os valores na função f(x, y)

# 2. Defina as entradas e saídas
% Entrada: x e y
% Saída: f(x, y)

# 3. Projete o algoritmo
% Ler x e y
% Calcule f(x,y)
% Mostre f(x,y)

# 4. Transforme o algoritmo em declarações MATLAB

% Ler x e y
x = input('Enter the x value: ');
y = input('Enter the y value: ');

% Calcule f(x,y)
if x>=0 & y>=0
  fxy = x + y;
elseif x>=0 & y<0
  fxy = x + y^2;
elseif x<0 & y>=0
  fxy = x^2 + y;
else
  fxy = x^2 + y^2;
end

% Mostre f(x,y)
fprintf('f(%g, %g) = %g\n', x, y, fxy);

# 5. Teste o programa