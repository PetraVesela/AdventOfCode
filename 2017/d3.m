 clear ; close all ; clc

 input = 347991;

 vec = zeros(1,20);
 vec(1) = 1;
 incr = 2;
 dist = zeros(1,20);
 dist(1) = 0;
 
 for ii = 1:4:1180
    for j = 1:4
        vec(ii+j) = vec(ii+j-1) + incr;
        dist(ii+j) = incr;
    end
    incr = incr+2;
 end    
 
 nearestCorner = vec(end-3)
 cornerDistance = dist(end-3)
% 590-110 = 480;
 %armSize = 0.25*( (vec(end)) - (vec(end-4)));

