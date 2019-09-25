function [mag, angle] = polar_value(x, y)
% POLAR_VALUE Converts an input (x, y)  
% value into (r, theta), with theta in degrees
% It illustrates the uses of optional arguments.



# Exemplo 5.3 - Utilizando Argumentos Opcionais
# De coord. retangulares (x, y) para coord. polares


% Define variables:
%     angle      -- Angle in degrees
%     msg        -- Error message
%     mag        -- Magnitude
%     x          -- Input x value
%     y          -- Input y value (optional) 

% Check for a legal number of input arguments.
msg = nargchk(1, 2, nargin);
error(msg);

if nargin < 2     % Se o num de arg de input(in) é < 2 
  y = 0;
end

% Check for (0, 0) input arguments, and print out
% a warning message.

if x == 0 & y == 0
  msg = 'Both x and y are zero: angle is meaningless!';
  warning(msg);
end

% Now calculate the magnitude.
mag = sqrt(x.^2 + y.^2);
% If the second output argument is present, calculate
% angle in degrees

if nargout == 2
  angle = atan2(y,x) * 180/pi;    % Se y~=0 calcula o angle e ele deixa de ser 0
endif

endfunction