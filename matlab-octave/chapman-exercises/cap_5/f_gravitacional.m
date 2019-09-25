function f_g = f_gravitacional(m, r)

% F_GRAVITACIONAL Calcula a força gravitacional
%     entre dois corpos de massa m(1) e m(2) em 
%     quilogramas, distaciados de r metros.

% Check the number of input arguments
msg = nargchk(2, 2, nargin); % nargchk(numero min de arg, num max de arg, nargin);
                             % nargin é a quant. de arg. inseridas pelo usuário 
error(msg);

global G;
G = 6.672E-11;
% Agora falta chegar se m é mesmo um vetor
if length(m) == 2  
  
  % Agora sim começa o código
  f_g = ( G * m(1) * m(2) ) / r^2;
  
else
  error('numero incorreto de elementos em m!');
end
endfunction
