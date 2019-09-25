# Exemplo 2.4 - Transferência de Carga Máxima
# Dados:

% Fonte de voltagem 
V = 120; %V

% Resistência interna Rs
Rs = 50 % ohms

% Suprindo uma carga de resistência R_L

# Encontre o valor de R_L que resultará na potência 
# máxima (P_L) possível fornecida pela fonte para a
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

fprintf('Máx P_L = %g\nValor de R_L = %g\n', maxP_L ...
, resR_L);

# plot e fprintf não pode ao mesmo tempo?