##  dados = zeros(2,5);
  
##  for i=1:5
##    dados(1,i) = input('corrente i: ')*10^(-3);
##    dados(2,i) = input('angulo: ');
##  end
  dados(1:5, 1) = [0.024000   0.048000   0.072000   0.096000   0.120000];
  dados(:, 2) = [40   50   60   80   82];
  
  for i=1:5
    fprintf('%.4f\n', y(i)=tand(dados(i,2)));
  end
  x = dados(:, 1);
  %scatter (x, y);
  plot(x,y,'ro','MarkerSize',8);
  xlabel('tg \theta'); % Set the x-axis label
  ylabel('corrente i'); % Set the y-axis label
  title('Gráfico 1');
  
  
  m = length(x);
% Add a column of all ones (intercept term) to x
  X = [ones(m, 1) x];
  theta = (pinv(X'*X))*X'*y ;
 
 hold on; % this keeps our previous plot of the training data visible
plot(X(:,2), X*theta, '-')
legend('Dados', 'Reta de regressão linear')
hold off % Don't put any more plots on this figure
##  comet(x,y,1);