# Exemplo try-catch

% Inicia a matriz
a = [ 1 -3 2 5 ];
try
  % Tenta exibir um elemento
  index = input('Forne�a o �ndice a ser exibido: ');
  disp(['a(' int2str(index) ')= ' num2str(a(index))]);
  % N�o precisa do + igual em Java
  
catch
  % Se chegarmos aqui, ocorreu um erro
  disp(['�ndice ilegal: ' int2str(index)]);
  
end
