# Exemplo 2.4 - Transfer�ncia de Carga M�xima
# Dados:

% Fonte de voltagem 
V = 120; %V

% Resist�ncia interna Rs
Rs = 50 % ohms

% Suprindo uma carga de resist�ncia R_L

# Encontre o valor de R_L que resultar� na pot�ncia 
# m�xima (P_L) poss�vel fornecida pela fonte para a
# carga

% Da teoria:
% P_L = I^2 * R_L;
% onde I = V/(R_tot) = V/(Rs + R_L);

R_L = 1:1:100; % Passo 1
I = V./(Rs + R_L); % Passo 2 ./
P_L = (I.^2) .* R_L; % Passo 3

% Passo 4
plot(R_L, P_L);
title('Plot of power versus load resistance');
xlabel('Load resistance (ohms)');
ylabel('Power (watts)');
grid on;


[maxP_L, index_maxP_L] = max(P_L);
resR_L = index_maxP_L;

fprintf('M�x P_L = %g\nValor de R_L = %g\n', maxP_L ...
, resR_L);

# plot e fprintf n�o pode ao mesmo tempo?