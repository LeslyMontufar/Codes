clc;
clear;
close;
function matrizImagem = substituirPixel(imagem,vI,vF)
    [rows col] = size(imagem);
    
    matrizImagem = imagem;
    for ii=1:rows
      for jj=1:col
        if imagem(ii, jj) >= vI
          matrizImagem(ii, jj)=vF;
        end
      end        
    end
    
end

cd desktop;
%230 245 
[fileName path]=uigetfile("*.png, *.jpg", "Select Image");

fileName = [path fileName];
imagem = imread(fileName);

figure(1);
imshow(imagem);

matriz = substituirPixel(imagem, 230,255);

figure(2);
imwrite(matriz, "oi.jpg");
imshow(matriz);
