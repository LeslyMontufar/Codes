clc;
clear;

% Binariza e troca de cor
color = struct('red', 50, 'green', 80, 'blue', 160);
[filename, pathname] = uigetfile({'*.png';'*.ico';'*.jpg'},'Select an image');
path = strcat(pathname, filename);
im = imread(path);

im_gray = rgb2gray(im);
new_im = zeros(size(im_gray, 1), size(im_gray, 2), 'uint8');
tickness = 0;
for i = 1:size(im_gray, 1)
    for j = 1:size(im_gray, 2)
        if im_gray(i,j)~= 255
            new_im(i,j-tickness:j,1) = color.red;
            new_im(i,j-tickness:j,2) = color.green;
            new_im(i,j-tickness:j,3) = color.blue;
        else
            new_im(i,j,1:3) = 255;
        end
    end
end

figure();
subplot(131); imshow(im);
subplot(132); imshow(im_gray);
subplot(133); imshow(new_im);

name = input('Image name: ');
imwrite(new_im, [name '.png']);
