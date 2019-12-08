clearvars; clc

% open the file
input = fopen('2.txt', 'r');
exactlyTwo = 0;
exactlyThree = 0;

for ii = 1:250
    
   data = fgetl(input);
   if ii == 1
        m = data;
   else 
       m = [m;data];
   end
   data = sort(data);
 
   [u, ~, ind] = unique(data); % to get a vector of numbers
   h = histcounts(ind);
   
   if sum( ismember(h,2))
       exactlyTwo = exactlyTwo+1;
   end
   
   if sum( ismember(h,3))
       exactlyThree = exactlyThree+1;
   end
   
end
fclose(input);
firstPart = exactlyTwo*exactlyThree

for ii = 1:250
    for jj = 1:250
       if sum(m(ii,:) ~= m(jj,:)) == 1
          secondPart = m(ii,:);
          secondPart(  m(ii,:) == m(jj,:))
          return
       end
    end
end


