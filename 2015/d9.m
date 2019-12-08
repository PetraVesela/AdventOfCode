clearvars; close all ; clc

% open the file and read all words
input = fopen('inputs/9.txt', 'r');
data = strsplit(fgetl(input));

for i = 1:27
    temp2 = strsplit(fgetl(input));
    data = cat(1,data, temp2);
end

% only keep the important info
data(:,2) = [];
data(:,3) = [];

names = unique(cat(1, data(:,1), data(:,2)));

% run the genetic "optimization"
gmax = 10000;

population = cell(gmax,2);
critVec = zeros(gmax, 1);
for ii = 1:gmax
    population{ii,1} = randperm(8);
    %population{ii,2} = getFitness(population{ii,1}, data, names);
    critVec(ii) = getFitness(population{ii,1}, data, names);
end

shortest = min(critVec)
longest = max(critVec)


function fitness = getFitness( inds, data, names)

    sortedNames = names(inds);
    fitness = 0; 
    for ii = 1:7
        %get the distance between two successive cities:
        firstName = mod(find(contains(data, sortedNames{ii})), length(data));
        secondName = mod(find(contains(data, sortedNames{ii+1})), length(data));
        
        firstName(firstName==0) = 28;
        secondName(secondName==0) = 28;
        ind = intersect(firstName, secondName);
        
        fitness = fitness + str2double(data{ind,3});
    end
end



