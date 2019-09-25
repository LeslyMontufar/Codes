# Exemplo 4.2 - A Função Fatorial

n = input('Enter with the value of n: ');

fat = 1;
for i=1 :1:n
  fat = fat * i; 
endfor

disp([num2str(n) '! = ' num2str(fat)]);
