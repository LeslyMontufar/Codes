clc;
clear all;
close all;
f=60;
w =2*pi*60;

table = readtable('table.txt', 'Format', '%f\t%f');
array = table2array(table);

T = 1;
t = 0:0.0001:T*1/f;
for ii=1:size(array, 2)
   figure(ii);
   plot(t, array(1,ii)*sin(w*t), t, array(2,ii)*sin(w*t-120*(pi/180)), t, array(3,ii)*sin(w*t+120*(pi/180)));
   xlabel('Tempo (s)');
   ylabel(table.Properties.VariableNames{1, ii});
end

% Potencia % precisa da defasagem tensao corrente