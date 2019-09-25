# Exemplo try-catch

% Inicia a matriz
a = [ 1 -3 2 5 ];
try
  % Tenta exibir um elemento
  index = input('Forneça o índice a ser exibido: ');
  disp(['a(' int2str(index) ')= ' num2str(a(index))]);
  % Não precisa do + igual em Java
  
catch
  % Se chegarmos aqui, ocorreu um erro
  disp(['Índice ilegal: ' int2str(index)]);
  
end
