clear ; close all ; clc

input = fopen('input.txt', 'r');

%% Part 1 
% valid = 0;
% for ind = 1:512
%     data = fgetl(input);
%     data = strsplit(data);
%     len_before = length(data);
%     data = unique(data);
%     len_after = length(data);
%     
%     if len_before == len_after
%         valid = valid+1;
%     end
% end

%% Part 2 
valid = 0;

for ind = 1:512
    data = fgetl(input);
    data = strsplit(data);
    
    permutations = cell(length(data),1);
    for ii = 1:numel(data)
        permutations{ii} = string(unique(perms(data{ii}), 'rows'));
    end

   b = cat(1,permutations{1:end});
   a = unique(b);
   if length(a) == length(b)
       valid = valid+1;
   end
    
end