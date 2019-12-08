clear  ; close ; clc

%% Part1

checksum1 = 0;
checksum2 = 0;

input = fopen('inputs/2.txt', 'r');
for ind = 1:16
    data = fgetl(input);
    data = str2num(data);
    checksum1 = checksum1 + (max(data) - min(data));
end

fclose(input);

%% Part2
input = fopen('input.txt', 'r');
for ind = 1:16
    data = fgetl(input);
    data = str2num(data);
    
    Data = nchoosek(data,2);
    temp = fliplr(Data);
    Data = [Data; temp];
    remain = 1;
    ind2 = 1; 
        while remain ~= 0
            remain = rem(Data(ind2, 1), Data(ind2, 2));
            ind2 = ind2+1;
        end
        addition = Data(ind2-1, 1)/Data(ind2-1, 2);
    if addition < 1
        addition = 1/addition;
    end
    checksum2 = checksum2 + addition;
end

fclose(input);
