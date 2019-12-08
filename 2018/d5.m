clearvars ; clc

% open the file
input = fopen('inputs/5.txt', 'r');
orig = fgetl(input);
a = orig;
results = [];

MODIF = 'A':'Z';
modif = 'a':'z';
m = [modif, MODIF; MODIF, modif;].';

for ii = 1:52
    C{ii} = m(ii, :);
end

while true
    n = numel(a);
    a = regexprep(a, C, '');

    if numel(a) == n
        FirstPart = numel(a)
        break
    end
end

for ii = 1:26
    b = orig;
    b(b == modif(ii)) = [];
    b(b == MODIF(ii)) = [];
    
    while true
        n = numel(b);
        b = regexprep(b, C, '');
        
        if numel(b) == n
            numel(b);
            break
        end
    end
    results = [results; numel(b)];
end
min(results)
