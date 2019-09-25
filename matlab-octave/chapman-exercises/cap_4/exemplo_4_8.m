# Exemplo 4.8 - O Vôo de uma Bola
# Resolução do livro. Misturado com mudanças minhas!

# t_voo = (2 * v_y0) / g;
g = 9.81; % m/s^2

# 3. Projete o algoritmo

#     Calcule a distância percorrida pela bola para 
#     \theta variando entre 0 e 90º
#     
#     Escreva uma tabela de distâncias percorridas
#     Determine a dist percorrida máxima e a apresente
#     
#     Desenhe as trajetórias para \theta variando entre
#     5 e 85º (de 10 em 10º)
#     Desenhe a trajetória de percurso máximo

# 4. Programe!

# Dados:
v0 = 20;

#     Calcule a distância percorrida pela bola para 
#     \theta variando entre 0 e 90º
percurso = zeros(1, 91);            % Para reduzir o tempo de compilação
for index = 1:91
  theta = index - 1;
  v_x0 = v0 * cosd(theta);
  v_y0 = v0 * sind(theta);
  max_t = (2 * v_y0) / g;
  percurso(index) = v_x0 * max_t;   % Mov Unifome para o eixo x
end
   
%     Escreva uma tabela de distâncias percorridas
fprintf('Tabela de distancias percorridas:\ntheta\t\tdistancia\n');
% \theta so funciona no title dos figure

for index = 1:91
  theta = index - 1;
  fprintf('%d\t\t%.4f\n', theta, percurso(index));
end

%     Determine a dist percorrida máxima e a apresente
[max_dist angle] = max(percurso);
fprintf('\n\nDistancia maxima: %.4f\nAngulo: %i degres\n\n', ...
        max_dist, angle = angle-1);

#     Desenhe as trajetórias para \theta variando entre
#     5 e 85º (de 10 em 10º)

for ii = 5:10:85
  theta = ii; 
  v_x0 = v0 * cosd(theta);
  v_y0 = v0 * sind(theta);
  max_t = 2* v_y0 / g;

  x = zeros(1, 21);
  y = zeros(1, 21);
  
  for jj = 1:21
    time = (jj-1) * max_t/20;
    
    x(jj) = v_x0 * time; % M.U.
    y(jj) = v_y0 * time - 0.5 * g * time^2; % M.U.
  end
  plot(x, y, 'b');
  
  if ii == 5
    hold on; % Para múltiplos gráficos se aplica o hold on depois da 1ºfigure
  end
  
end

% Add titles and axis labels
title('\bfTrajectory of Ball vs Initial Angle \theta');
xlabel('\bf\itx \rm\bf(meters)');
ylabel('\bf\ity \rm\bf(meters)');
axis ([ 0 45 0 25]);
grid on;

#     Desenhe a trajetória de percurso máximo
v_x0 = v0 * cosd(angle); % essa é a vel. para esse angle
v_y0 = v0 * sind(angle); % essa é a vel. para esse angle
max_t = 2 * v_y0 / g; % estou considerando a g positiva

% Calculate the (x, y) positions
x = zeros(1, 21);
y = zeros(1, 21);
for jj = 1:21
  time = (jj-1) * max_t/20;
  x(jj) = v_x0 * time;
  y(jj) = v_y0 * time - 0.5 * g * time^2; % estou considerando a g positiva
endfor

plot(x, y, 'r', 'LineWidth', 3.0);
hold off