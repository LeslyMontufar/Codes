function quickplot(fun, xlim)   % Não há retorno!
%QUICKPLOT Generate quick plot of a function 
% Function QUICKPLOT generates a quick plot
% of a function contained in an external M-file,
% between user-specified x limits.
% 
% 
% Define variables:
%     fun         -- Function to plot
%     msg         -- Error message
%     n_steps     -- Number of steps to plot
%     steps_size  -- Step size
%     x           -- X-values to plot
%     y           -- Y-values to plot
%     xlim        -- Plot x limits


% Check for a legal number of input arguments.
msg = nargchk(2, 2, nargin);
error(msg);

% Check the second argument to see if it has two
% elements. Note that this double test allows the
% argument to be either:
% a row or a column vector
if ( size(xlim, 1) == 1 & size(xlim, 2) == 2 ) | ...
   ( size(xlim, 1) == 2 & size(xlim, 2) == 1 )
   % Melhor seria usar:
   % if length(xlim) == 2 , pois já vê número de elementos
   % seja um array linha ou coluna!
   % Ok--continue processing.
   n_steps = 100;
   steps_size = (xlim(2) - xlim(1)) / n_steps;    % x é um vetor que tem o valor inicial e final
   
   x = xlim(1): steps_size: xlim(2);
   y = feval(fun, x);                 % Transforma o texto fun em função matematica evaluada em x
   
   plot(x, y);
   title(['\bfPlot of function ' fun '(x)']); % fun é texto e y = feval(fun, x); vector
   xlabel('\bfx');
   ylabel(['\bf' fun '(x)']);
else 
   % Em caso de numeros de elementos em xlim errado
   error('Incorrect number of elements in xlim.');
end
endfunction
