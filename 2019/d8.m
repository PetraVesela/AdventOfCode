clearvars; close all; clc

% TODO: learn to reshape 3-dim arrays without messing up the order,
% permute vs. shiftdim

% retrieve the individual pixels:
file = fopen('inputs/8.txt');
pictureData = fgetl(file);
commas = char(ones(1,numel(pictureData))*',');
pixels = [pictureData; commas];
pixels = str2num( pixels(:).');
clear commas

% form individual layers - 1 layer per row
pictureSize = [6,25];
numLayers = numel(pictureData)/prod(pictureSize);
pixels = reshape(pixels,[prod(pictureSize),numLayers]).';

%% PART 1: just get a checksum:
counter = zeros(1,numLayers);

for layer = 1: numLayers
    counter(layer) = nnz(~pixels(layer,:));    
end

[~, ind] = min(counter);
layer = pixels(ind,:);
howManyOnes = numel( find(layer == 1));
howManyTwos = numel( find(layer == 2));
howManyOnes * howManyTwos

%% PART 2:
% reshape row-like layers to the pictures stacked on top of each other
picture = permute( reshape(pixels, [numLayers, fliplr(pictureSize)]),[3,2,1]);

finalPicture = zeros(fliplr(pictureSize));

for ii = 1: pictureSize(2)
    for jj = 1:pictureSize(1)
        
        pixel = squeeze( picture(jj,ii,:));
        idx = find(pixel~=2, 1, 'first');
        finalPicture(ii,jj) = pixel(idx);
    end
end

imshow(finalPicture.')
fclose(file);