# Gera histogramas

clear all;
close all;

[im.filename im.path] = uigetfile('*jpg; *png', 'Select an Image', 'MultiSelect', 'on');
im.path = strcat(im.path, im.filename);

folder_name = 'hist';
cd qrcode;
if !exist(folder_name,'dir')
  mkdir(folder_name);
end
cd(folder_name);

for ii = 1 : size(im.filename,2)
  fprintf('Image: %s\n', im.filename{1, ii});
  im.gray = imread(im.path{1, ii});
  if length(unique(im.gray)) > 255 im.gray = rgb2gray(im.gray); end
  im.hist = imhist(im.gray);
  name = im.filename{1,ii};
  name = name(1:end-4);
  
  figure;
  plot(im.hist);
  grid on;
  %xlim([0 260]);
  print([name '-hist'], '-dpng');
  fprintf('hist: %s\n', [name '-hist.png']);

end
