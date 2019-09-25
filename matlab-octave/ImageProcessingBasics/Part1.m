  clc;
  close all;
  clear all;
  %% C:\Users\Montufar\Documents\codes\Octave-codes\ImageProcessingBasics
  [filename path] = uigetfile('*jpg', 'Select an Image');
  filename = strcat(path, filename);
  
  im = imread(filename);
  figure(1);
  imshow(im);
  title('Original image');
  
  n = 33;
  im2 = imresize(im, [33 33]);
  figure(2);
  imshow(im2);
  title('Resized image');
  
  % Playing with color channel
  
  figure(3);
  
  subplot(1, 3, 1);
  imRed = im;
  imRed(:,:, 2:3) = 0; % zera os outros canais de G and B
  imshow(imRed);
  title('Red channel Image');
  
  subplot(1, 3, 2);
  imG = im;
  imG(:,:, 1:2:3) = 0; % zera os outros canais de R and B
  imshow(imG);
  title('Green channel Image');
  
  subplot(1, 3, 3);
  imBlue = im;
  imBlue(:,:, 1:2) = 0; % zera os outros canais de R and G
  imshow(imBlue);
  title('Blue channel Image');
  
  %% Color conversion
  
  % using matlab function
  imGrayM = rgb2gray(im); % Agora á uma só matriz
  figure(4);
  imshow(imGrayM);
  title('Gray image');