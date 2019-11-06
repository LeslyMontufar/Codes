clc;
clear all;
close all;

%% Aprendendo Circuitos
if ask('configuracao padrao? (1/0) ')
    f = 60;
    ini_time = 0;
    end_time = 50e-3;
else
    f = input('freq: ');
    ini_time = input('inicial time: ');
    end_time = input('end time: ');
end

T = 1/f;
t = ini_time:end_time/1e3:end_time;
alpha = -cosd(60)+ j*sind(60); %1 fasor de 120
omega = 2*pi*f;
if ask('Delta=1 ou estrela=0? ')
    %% Delta
    fprintf('\t Configura��o em delta;\n');
    VL_rms = input('VL_rms: ');
    VAB = VL_rms*sqrt(2)* sin(omega*t);
%     VBC = VAB * alpha^2;
%     VCA = VAB * alpha;
else
    %% Estrela
   disp('Configuracao em estrela') 
end

fprintf('O sistema operando numa frequ�ncia de %g, logo com per�odo de %g s\n', f, T);

%% Dados gr�ficos obtidos
%% No tempo
figure('Name', 'Tens�es de linha')
plot(t, VAB);
hold on;
grid on;
% plot(t, VBC);
% plot(t, VCA);
legend('VAB')

%% Fasores
figure('Name', 'Tens�es - Fasores')
fasor = 0: 0.1: VL_rms;
polarplot(0, fasor, '*');
hold on;
polarplot(angle(alpha), fasor, '*');
polarplot(angle(alpha^2), fasor, '*');

%% Funcoes uteis
function bool = ask(question)
    if input(question)==1
        bool = 1;
    else 
        bool = 0;
    end
end

function ponto(tipo)
    if tipo == 'cartesiana'
        
    else if tipo == 'polar'
    end
end