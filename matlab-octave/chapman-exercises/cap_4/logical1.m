# Exemplo 4.6 - Utilizando Matrizes Lógicas 
# como Máscaras de Operações

# Proposta:
#   Calcular o tempo requerido para calcular a
#   raíz quadrada de todos os valores de um array 
#   com 10.000 elementos (1, 2, ..., 10.000).
#   
#   1. Usando for e if
#   2. Usando um array lógico

#   average1
#   average2
#   n_rep
#   
#   a
#   b_logical
#   ii, jj

#   1. Usando for e if

n_rep = 1;
tic;
for jj = 1:n_rep;
  
  a = 1:10000;
  for ii = 1:1000
    if a(ii) > 5000
      a(ii) = sqrt( a(ii) );
    end
  end
  
end
average1 = (toc)/n_rep;

#   2. Usando um array lógico

n_rep = 10;
tic;
for jj = 1:n_rep;
  a = 1:10000;
  b_logical = a > 5000;       % Create mask
  
  a(b_logical) = sqrt( a(b_logical) );        % Take square root
  
end
average2 = (toc)/n_rep;

# Display results
fprintf('Loop / if approach =       %8.4f\n', ...
        average1);
fprintf('Logical array approach =   %8.4f\n', ...
        average2);