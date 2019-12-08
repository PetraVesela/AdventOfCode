clear ; close ; clc;

input = fopen('inputs/6.txt', 'r');
data = fscanf(input, '%d');
fclose(input);

cycles = 0;
memory(1,:) = data;

while length(memory) == length(unique(memory, 'rows')) 
    
    [dose, position] = max(data);
    % solving the tie
    if length(dose) ~= 1
        position = position(1);
        dose = data(position);
    end
    
    % redistribution:
    data(position) = 0;
     for ind = 1:dose
         position = position+1;
         if position == 17  
             position = 1;
         end
        data(position) = data(position)+1;
     end
    cycles = cycles+1;
    memory(cycles+1,:) = data;
    
end

cycles

[~,a,b] = intersect(data', memory, 'rows');
difference = cycles - b + 1