clear all ; close all ; clc

% Matlab 2013b

input = fopen('input.txt', 'r');
temp = fgetl(input);

for i = 1:153
    data{i} = temp;
    temp = fgetl(input);
end


fclose(input);

cols = 50;
rows = 6; 

map = zeros (rows, cols);

for i = 1:153
    
    instr = regexp(data{i}, '\d+', 'match');
    x = str2double(instr{1});
    y = str2double(instr{2});
    
    if data{i}(2) ==  'e'       %RECT 
       map (1:y,1:x) = ones (1:y, 1:x);
       
        else if data{i}(8) == 'r'   %ROTATE ROW
                map (x+1, :) = circshift(map(x+1, :), [0 y]);
                
            else map (:, x+1) = circshift(map(:, x+1), y); %ROTATE COLUMN
            end
    end
    
   
end

result = nnz(map)
imshow(mat2gray(map, [0,1]));
