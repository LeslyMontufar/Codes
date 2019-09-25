# Exemplo 3.12 - A espiral de Arquimedes

# r = k* theta;

theta = 0:pi/20:6*pi;
k = 0.5;

r = k.* theta;
polar(theta, r, 'b-');

title('\bfEspiral de Arquimedes');
legend('r');