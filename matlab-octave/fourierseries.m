% Series de Fourier
clearvars -except nro;
close all;
clc;
global nro;

function ans = ask(question)
  fprintf('\t');
  opcao = input(question, 's');
  if opcao == 'n' ans = 0; else ans = 1; end
end
function grafico(f, L)
  x = -L:0.1:L;
  y = f(x);
  xlim([-L L]);
  plot(x, y);
  grid on;
endfunction
function y = u(x) y = (x>=0); end 
function y = p(n) y = (-1).^n; end 
function f = get_f(str, var)
  str = strrep(str,'^','.^');
  str = strrep(str,'*','.*');
  str = strrep(str,'/','./');
  str = strrep(str,'sen','sin');
  str = strrep(str,'..','.');
  f = str2func(['@(' var ')' str]);
end
function flag = contains(vetor, line, n)
  flag = 0;
  if !isempty(vetor)
    for i = 1:length(vetor(line, :))
      if vetor(line, i) == n
        flag = 1;
      end
    end
  end
end
function f = get_f_fourier(a0, an, bn, n_max, L, aPart, bPart)
  str = ['@(x)' num2str(a0/2)]; % a0 é número
  % Adding even part solution
  for n = 1:n_max
    if !contains(aPart, 1, n)
      str = [str '+' num2str(an(n)) '*cos(' num2str(n*pi/L) '*x)'];
    end
  end
  for i = 1:size(aPart, 2)
    str = [str '+' num2str(aPart(2,i)) '*cos(' num2str(aPart(1,i)*pi/L) '*x)'];
  end
  # Adding odd part solution
  for n = 1:n_max
    if !contains(bPart, 1, n)
      str = [str '+' num2str(bn(n)) '*sin(' num2str(n*pi/L) '*x)'];
    end
  end
  for i = 1:size(bPart, 2)
    str = [str '+' num2str(bPart(2,i)) '*sin(' num2str(bPart(1,i)*pi/L) '*x)'];
  end
  f = str2func(str);
end
function saveimage(fig, n_max, format)
  global nro;
  print(fig, sprintf('Grafico%03d-n_max-%d', nro, n_max), format); % '-r1000' nao faz diferença
end
function [ffourier n_max] = desenvolveFourier(f, a0, an, bn, L, aPart, bPart) % só uma o f para comparar graficos
  while 1
    n_max = input('n_max = ');
    ffourier = get_f_fourier(a0, an, bn, n_max, L, aPart, bPart);
    fig = figure('Name', 'Gráfico da função', 'NumberTitle', 'off');
    grafico(f, L);
    hold on;
    grafico(ffourier, L);
    if ask('salvar imagem? (s/n) ') saveimage(fig, n_max, '-dpng'); end % nao precisava especificar o fig
    if !ask('alterar o valor de n_max? (s/n) ') break; end
  end
end
  
if isempty(nro) | isempty(dir('*.png'))
  nro = 0;
elseif ask('deletar imagens anteriores? (s/n) ') % elseif tudo junto
  try % prefiro um warning só
    delete *.png;
    fprintf('\n');
  end
  nro = 0;
else ask('reiniciar contagem das imagens? (s/n) ')
  nro = 0;
end
fprintf('\tInformacoes:\n\n');
fprintf('\tu(x) - degrau unitario\n');
fprintf('\tp(n) - (-1)^n\n\n');
fprintf('\t1 - Comparar resposta\n\t2 - Calcular Serie de Fourier\n\t0 - Sair\n\n');
while 1
  nro = nro + 1;
  fflush (stdout);
  f = get_f(input('f(x) = ', 's'), 'x');
  L = input('L = ');
  fprintf('\n\t');
  opcao = input('Opcao: ');
  switch opcao
    case 1
      aPart = []; bPart = [];
      a0 = input('a0 = ');
      an = get_f(input('an = ', 's'), 'n');
      if ask('an particular? (s/n) ')
        while 1
          aN = input('n (press 0 to stop)= ');
          if aN==0 break; end
          aNro = input('a(n) = ');
          aPart = [aPart [aN; aNro]];
        end
      end
      bn = get_f(input('bn = ', 's'), 'n');
      if ask('bn particular? (s/n) ')
        while 1
          bN = input('n (press 0 to stop)= ');
          if bN==0 break; end
          bNro = input('b(n) = ');
          bPart = [bPart [bN; bNro]];
        end
      end
      [ffourier n_max] = desenvolveFourier(f, a0, an, bn, L, aPart, bPart);
    case 2
      a0 = (1/L)*integral(f, -L, L);
      fan = get_f([func2str(f)(5:end) '.*cos(n*' num2str(pi/L) '*x)'], 'x, n'); 
      fbn = get_f([func2str(f)(5:end) '.*sin(n*' num2str(pi/L) '*x)'], 'x, n'); 
      an = (1/L)*int(str2func([func2str(f) '.*cos(n*' num2str(pi/L) '*x)']), -L, L);
      bn = (1/L)*int(str2func([func2str(f) '.*sin(n*' num2str(pi/L) '*x)']), -L, L);
      aPart = []; bPart = [];
      fprintf('a0 = %g\n', a0);
      fprintf('an = ');
      [ffourier n_max] = desenvolveFourier(f, a0, an, bn, L, aPart, bPart);
    otherwise
      break;
  end
  if !ask('reiniciar programa? (s/n) ') break; end
end
