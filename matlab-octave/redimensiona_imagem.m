clear all;

function ans = ask(question)
  fprintf('\t');
  opcao = input(question, 's');
  if opcao == 'n' ans = 0; else ans = 1; end
end


[im.filename im.path] = uigetfile('*jpg; *png', 'Select an Image', 'MultiSelect', 'on');
im.path = strcat(im.path, im.filename);

% folder_name = input('Nome da pasta para salvar imagens: ', 's');
folder_name = 'imr';
cd qrcode;
if !exist(folder_name,'dir')
  mkdir(folder_name);
end
cd(folder_name); % precisa para considerar str

for ii = 1 : size(im.filename,2)
  fprintf('Image: %s\n', im.filename{1, ii});
  im.original = imread(im.path{1, ii});
  [row col e] = size(im.original);
  fprintf('original: %g %g %g\n', row, col, e);
  x = 640/((row*col)^(1/2));
  im.new = imresize(im.original, [floor(row*x) floor(col*x)], 'nearest');
  [rn cn en] = size(im.new);
  fprintf('new: %g %g %g\n', rn, cn, en);
  
  %fig = figure('Name', 'Compara imagens', 'NumberTitle', 'off');
  %subplot(121); imshow(im.original);
  %subplot(122); imshow(im.new);
  %if ask('salvar imagem? (s/n) ') saveimage(fig, im.filename{1,ii}, '-dpng'); end
  name = im.filename{1,ii};
  name = name(1:end-4);
  imwrite(im.new, [name '-r.png']);
  fprintf('renamed to: %s\n', [name '-r.png']);
  
end
