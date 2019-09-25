n = 0:size(data, 1)-1;
tempo = 1./data(:, 1);

figure(1);
ti = 5e5;
tf = 6e5;

plot(n(ti:tf), data(ti:tf, 1));