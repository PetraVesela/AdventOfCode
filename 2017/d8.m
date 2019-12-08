clear all ; close all ; clc

input = fopen('inputs/8.txt', 'r');

for ii = 1:2:2000
    % pre-processing
    data = strsplit( fgetl(input));
    regs{ii} = data{1};
    regs{ii+1} = data{5};
    
end
regs = unique(regs);
fclose(input);

% perform the instructions
input = fopen('input.txt', 'r');
values = zeros(size(regs));

absMax = 0;
for ii = 1:1000

    data = strsplit( fgetl(input));
    where = find(strcmp(data{5}, regs)==1);
    
    valid = 0;
    
    instruction = [num2str( values(where)) , data{6:7}];
    instruction = strrep(instruction, '!', '~');
    valid = eval(instruction);
    
    if valid == true
        which = find(strcmp(data{1}, regs)==1);
         if data{2}(1) == 'i'
             values(which) = values(which) + str2num( data{3});
         else
             values(which) = values(which) - str2num( data{3});
        end
    end
   if max(values) > absMax
       absMax = max(values);
   end
end

max(values)
absMax