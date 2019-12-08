clear ; close all ; clc


input = fopen('input.txt', 'r');
data = fscanf(input, '%s');
fclose(input);

field  = reshape(data, [8,572]);

result1 = '00000000';

for ind = 1:8
    result1(ind) = char(mode(double(field(ind,:))));
end

disp(['First result is: ', result1]);

%% second part


for ind = 1:8

    a = histcounts(double(field(ind,:)));
    [~, result2(ind)] = min(a);
    result2(ind) = result2(ind)+96;
    
end

disp(['Second result is: ', char(result2)]);


