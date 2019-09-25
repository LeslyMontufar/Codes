# Exemplo 4.8 - O V�o de uma Bola
# Resolu��o do livro. Misturado com mudan�as minhas!

# t_voo = (2 * v_y0) / g;
g = 9.81; % m/s^2

# 3. Projete o algoritmo

#     Calcule a dist�ncia percorrida pela bola para 
#     \theta variando entre 0 e 90�
#     
#     Escreva uma tabela de dist�ncias percorridas
#     Determine a dist percorrida m�xima e a apresente
#     
#     Desenhe as trajet�rias para \theta variando entre
#     5 e 85� (de 10 em 10�)
#     Desenhe a trajet�ria de percurso m�ximo

# 4. Programe!

# Dados:
v0 = 20;

#     Calcule a dist�ncia percorrida pela bola para 
#     \theta variando entre 0 e 90�
percurso = zeros(1, 91);            % Para reduzir o tempo de compila��o
for index = 1:91
  theta = index - 1;
  v_x0 = v0 * cosd(theta);
  v_y0 = v0 * sind(theta);
  max_t = (2 * v_y0) / g;
  percurso(index) = v_x0 * max_t;   % Mov Unifome para o eixo x
end
   
%     Escreva uma tabela de dist�ncias percorridas
fprintf('Tabela de distancias percorridas:\ntheta\t\tdistancia\n');
% \theta so funciona no title dos figure

for index = 1:91
  theta = index - 1;
  fprintf('%d\t\t%.4f\n', theta, percurso(index));
end

%     Determine a dist percorrida m�xima e a apresente
[max_dist angle] = max(percurso);
fprintf('\n\nDistancia maxima: %.4f\nAngulo: %i degres\n\n', ...
        max_dist, angle = angle-1);

#     Desenhe as trajet�rias para \theta variando entre
#     5 e 85� (de 10 em 10�)

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
    hold on; % Para m�ltiplos gr�ficos se aplica o hold on depois da 1�figure
  end
  
end

% Add titles and axis labels
title('\bfTrajectory of Ball vs Initial Angle \theta');
xlabel('\bf\itx \rm\bf(meters)');
ylabel('\bf\ity \rm\bf(meters)');
axis ([ 0 45 0 25]);
grid on;

#     Desenhe a trajet�ria de percurso m�ximo
v_x0 = v0 * cosd(angle); % essa � a vel. para esse angle
v_y0 = v0 * sind(angle); % essa � a vel. para esse angle
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