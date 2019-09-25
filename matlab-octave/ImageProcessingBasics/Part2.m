  clc;
  close all;
  clear all;
  %% C:\Users\Montufar\Documents\codes\Octave-codes\ImageProcessingBasics
  [filename path] = uigetfile('*jpg', 'Select an Image');
  filename = strcat(path, filename);
  
  im = imread(filename);
  figure(1);
  subplot(2, 3, 1);
  imshow(im);
  title('Original image');
  
  n = 33;
  
  im2 = imresize(im, [33 33]);
  subplot(2, 3, 2);
  imshow(im2);
  title('Resized image');
  
  %% Histogram of gray image!
  im = rgb2gray(im);
  subplot(2, 3, 3);
  h = imhist(im);
  plot(h);
  title('Coins Histogram');
  
  %% Histogram equalization
  imEq = histeq(im);
  subplot(2, 3, 4);
  imshow(imEq);
  title('Equilized Histogram');
  
  subplot(2, 3, 5);
  imhist(imEq);
  title('hist of equalized image');
  