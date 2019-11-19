x = -20:0.1:20;
f = 4 - 2*x - x.^2./(sqrt(x.^2-x-2));
plot(x, f);
hold on;

