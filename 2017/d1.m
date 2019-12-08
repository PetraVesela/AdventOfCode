clear  ; close ; clc

%% Reading the data
input = fopen('inputs/1.txt', 'r');
data = fscanf(input, '%s')
fclose(input);

%% Processing the Captcha
sum_part1 = 0;


for ind = 1:numel(data)-1
    
    if str2double( data(ind)) == str2double( data(ind+1))
        sum_part1 = sum_part1 + str2double( data(ind));
    end
    
end

if str2double( data(1)) == str2double( data(end))
    sum_part1 = sum_part1 + str2double( data(1));
end

%% second part
sum_part2 = 0;

% replicate the buffer once:
len = length(data);
data = [data, data];

for ind = len-1 : 2*len
     if str2double( data(ind)) == str2double( data(ind - len/2))
        sum_part2 = sum_part2 + str2double( data(ind - len/2));
    end
end

sum_part1
sum_part2
