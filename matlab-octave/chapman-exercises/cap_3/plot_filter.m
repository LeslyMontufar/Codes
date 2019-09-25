# Exemplo 3.6 - Eng. El.: Resposta de Freq. de um 
# Filtro de Passagem Baixa

# Voltagem de saída - V_0
# Voltagem de entrada - V_i

# j = sqrt(-1);

# resposta da amplitude do filtro = V_0 / V_i
# V_0 / V_i = 1 / (1 + j* 2* pi* freq* R* C);

R = 16.0E3% k omhs
C = 1.0E-6 % micro Farads

# Desenhe a amplitude e a resposta de freq. desse filtro.

% Solução:

% Create array of input frequencies
freq = 1:2:1000;

% Calculate response (V_0 / V_i)
res = 1 ./ (1 + j* 2* pi* freq* R* C);

% Calculate amplitude response
amp = abs(res);

% Calculate phase response
phase = angle(res);

% Create plots
subplot(2,1,1);
loglog(freq, amp);
title('Amplitude Response');
xlabel('Frequency (Hz)');
ylabel('Output/Input Ratio');
grid on;

subplot(2,1,2);
semilogx ( freq, phase );
title('Phase Response');
xlabel('Frequency (Hz)');
ylabel('Output/Input Phase (rad)');
grid on;