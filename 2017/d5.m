clear ; close ; clc

%% Reading the data
input = fopen('inputs/5.txt', 'r');
data = fscanf(input, '%d');
fclose(input);

orig = data;
%% 1st part
steps = 0;
position = 1;

while position <= length(data) && position > 0
    data(position) = data(position)+1;
    position = position + data(position)-1;
    steps = steps+1;
end

steps

%% 2nd part

data = orig;
steps = 0;
position = 1;

while position <= length(data) && position > 0
    
    if data(position)  < 3
        data(position) = data(position)+1;
        position = position + data(position)-1;
    else
        data(position) = data(position)-1;
        position = position + data(position)+1; 
    end
    steps = steps+1;
end

steps

