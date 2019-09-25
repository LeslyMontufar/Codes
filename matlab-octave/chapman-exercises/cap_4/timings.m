# Exemplo 4.5 - Comparando Laços e Vetorização
# A contagem de tempo pode ser efetuada pelas funções tic
# toc do MATLAB.

% Define variables: 
%   ii, jj      -- Loop index (i e j são complexos!)

% Será medido várias vezes o tempo para cada processo
% e grvado nessas variáveis o tempo MÉDIO do processo
%   average1    -- Average time for calculation 1
%   average2    -- Average time for calculation 2
%   average3    -- Average time for calculation 3

%   n_repetitions    -- Number of times to loop calculation
%   square      -- Array of squares
   

# 1. Perform calculation with an uninitialized array
# " square "

n_repetitions = 1; % beacuse this process is too slow
tic; % start timer
for jj = 1:n_repetitions
  clear square
  for ii = 1:10000
    square(ii) = ii^2;
  endfor
endfor

average1 = (toc) / n_repetitions;

# 2. Perform calculation with a pre-allocated array
# " square "
n_repetitions = 10;
tic; % start timer
for jj = 1:n_repetitions
  clear square
  square = zeros(1, 1000); % Pré inicializa a matriz unidimensional
  for ii = 1:10000
    square(ii) = ii^2;
  endfor
endfor

average2 = (toc) / n_repetitions;

# 3. Perform calculation with vectors.
# " square "
n_repetitions = 100;
tic; % start timer
for jj = 1:n_repetitions
  clear square
  ii = 1:10000; % Set up vector
  square(ii) = ii.^2;
endfor

average3 = (toc) / n_repetitions;


% Display results
fprintf('Loop / uninitialized array = %8.4f\n', ...
        average1);
fprintf('Loop / initialized array   = %8.4f\n', ...
        average2);
fprintf('Vectorized                 = %8.4f\n', ...
        average3);