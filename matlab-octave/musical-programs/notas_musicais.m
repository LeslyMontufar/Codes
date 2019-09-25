  # Notas musicais: a escala justa musical

  # do re mi fa sol la si do

  clear all;
  close all;

  %clf; % clear current figure window
  %subplot(1, 1, 1);
  amostra = 11025;
  
  frequencias = 11.*[24 27 30 32 36 40 45 48];
  div = amostra ./ frequencias;
  nota = zeros(9, amostra);
  
  for ii = 1: amostra
    for iinota = 1 : 7
      nota(iinota, ii) = sin(2*pi*ii / div(iinota));
    endfor
    nota(8, ii) = sin(2*2*pi*ii/div(1));
    
    for iinota = 1: 8
      nota(9, ii) = nota(iinota, ii);
    end
    
  endfor
  
  clear ii;
  iinota = 1;
  
  t = 1:300;
  figure(1);
  subplot(2, 2, 1), plot(t, nota(iinota, t), 'b', t, nota(iinota+1, t), 'r', 'LineWidth', 2);
  xlabel('DO(azul) RE(vermelho)');
  title('NOTAS MUSICAIS');
  
  iinota = iinota + 2;
  subplot(2, 2, 2), plot(t, nota(iinota, t), 'b', t, nota(iinota+1, t), 'r', 'LineWidth', 2);
  xlabel('MI(azul) FA(vermelho)');
  title('NOTAS MUSICAIS');
  
  iinota = iinota + 2;
  subplot(2, 2, 3), plot(t, nota(iinota, t), 'b', t, nota(iinota+1, t), 'r', 'LineWidth', 2);
  xlabel('SOL(azul) LA(vermelho)');
  title('NOTAS MUSICAIS');
  
  iinota = iinota + 2;
  subplot(2, 2, 4), plot(t, nota(iinota, t), 'b', t, nota(iinota+1, t), 'r', 'LineWidth', 2);
  xlabel('SI(azul) DO oitava a cima(vermelho)');
  title('NOTAS MUSICAIS');
  
  % fft - fast fourier transform
  %  Thus if X is a matrix, 'fft (X)' computes the FFT for
  %  each *'column'* of X.
  
  nota9(:, 1) = nota(9, :);
  pause; % causes M-files to stop and wait for you to press any key before continuing.
  
  F1 = abs(fft(nota9)); % gráfico não é conforme com o vetor !!!!
  
  F1(1:600) = F1(2:601); % desloca a função 1 para a esquerda, duplicando 661 para 660
  
  t = 1:600;
  figure(2);
  plot(t, F1(t), 'b', 'LineWidth', 2); % LineWidth deixa a linha mais grossa
  xlabel('Harmonicas DO3+RE+MI+FA+SOL+LA+SI+DO4');
  title('Frequencias das notas musicais');
  