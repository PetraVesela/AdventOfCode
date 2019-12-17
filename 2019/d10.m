clearvars; close all; clc

% NOTE: workaround - I'm working on a fliped map!
%% retrieve the input:
file = fopen('inputs/10.txt');
asteroidMap = zeros(10);
playGroundSize = size(asteroidMap,1);

for ii = 1:playGroundSize
    asteroidMap(ii, :) = fgetl(file);
end
fclose(file);   

% make it look nicer:
asteroidMap(asteroidMap == 46) = 0;
asteroidMap(asteroidMap == 35) = 1;

%plotMap(asteroidMap)
%% PART 1

numAsteroids = sum( sum( asteroidMap));
aCoords = zeros(2,numAsteroids);
[aCoords(2,:), aCoords(1,:)] = find(flipud(asteroidMap));
[emptyCoords(2,:), emptyCoords(1,:)] = find(flipud(~asteroidMap));

allCoords = [aCoords, emptyCoords] - 0.5;
aCoords = aCoords - 0.5;
canSee = zeros(1,numAsteroids);

% shoot a ray at all other asteroids and get its slope
ind = 0;

for pt1 = aCoords % for every Asteroid
    ind = ind+1;
    tryToDetect = aCoords;
    tryToDetect(:,ind) = [];
    
    x1 = pt1(1); % starting point
    y1 = pt1(2);

    for pt2 = tryToDetect 
        x2 = pt2(1);
        y2 = pt2(2);
%         plot([x1, x2], [y1, y2],'r');
%         pause(0.2)

        slope = (y1 - y2)/(x1 - x2);
        if x1<x2
            slope = slope + 1i; %random workaround
        else
            slope = slope -1i;
        end

        % get thisAsteroid -> otherAsteroids slopes   
        slopes = (y1 - tryToDetect(2,:))./ (x1 - tryToDetect(1,:));
        
        % distinguish +/- direction of the ray
        for ii = 1: size(slopes,2)
            if x1 < tryToDetect(1,ii) 
                slopes(ii) = slopes(ii)+1i;
            else 
                slopes(ii) = slopes(ii)-1i;
            end
            
        end     
        % check     
        if sum( slopes == slope) % if there is something left visible
            canSee(ind) = canSee(ind)+1;
            tryToDetect(:,slopes == slope) = [];
        end        
         
    end
  
end

[M, I] = max( canSee);

base = aCoords(:,I);
%% start the vaporization from this point:

shot = 0;

% It's enough to point at the outermost points of grid:
% targets = getTargets(playGroundSize);
% 
% [~, whereToBegin] = find(targets(1,:) == base(1) & ...
%                       targets(2,:) == playGroundSize-0.5);
% targets = circshift(targets, -whereToBegin+1,2);

%currentDirection = Inf;
plotMap(asteroidMap);
x1 = base(1);
y1 = base(2);
slopes = (y1 - aCoords(2,:))./ (x1 - aCoords(1,:));
[sl, I_slopes] = sort(slopes);
distances = getDistance(base, aCoords);
aCoords(:,I) = []; % don't try to shoot yourself


for target = aCoords
    plot([base(1), target(1)],[base(2), target(2)], 'g' )
    x2 = target(1);
    y2 = target(2);
    slope = (y1 - y2)/(x1 - x2);
    if x1<x2
        slope = slope + 1i;
    else
        slope = slope -1i;
    end

    % get thisAsteroid -> otherAsteroids slopes   
    slopes = (y1 - aCoords(2,:))./ (x1 - aCoords(1,:));
       
    % distinguish +/- direction of the ray
    for ii = 1: size(slopes,2)
        if x1 < aCoords(1,ii) 
            slopes(ii) = slopes(ii)+1i;
        else 
            slopes(ii) = slopes(ii)-1i;
        end
    end     
    if sum( slopes == slope) % if there is something left visible
        strike = find(slopes == slope);
        if numel(strike)>1
           distances = getDistance(base, aCoords(:, strike));
           [~, closest] = min(distances);
           strike = strike(closest);
        end
        plot(aCoords(1,strike), aCoords(2, strike), 'r*');
        pause(0.2);
        aCoords(:,strike) = [];
        shot = shot+1;
    end



%plotMap(asteroidMap)
end


[X,Y] = getCoordinates(base(1), base(2), size(asteroidMap, 1));
%plotMap(asteroidMap)

function dist = getDistance(pt1, pt2)
    dist = sqrt((pt1(1)-pt2(1,:)).^2 + (pt1(2) - pt2(2,:)).^2);
end
% 
% function targets = getTargets(playGroundSize)
%     cte = playGroundSize - 0.5;
%     ii = 0.5 : playGroundSize - 0.5;
%     targets1 = [ii(1:end-1), cte*ones( size( ii)); ...
%                cte*ones( size( ii(1:end-1))), fliplr(ii)];
%     targets2 = [fliplr(ii(1:end-2)), 0.5*ones( size(ii(1:end-1))); ...
%                 0.5*ones( size( ii(1:end-2))), ii(1:end-1)];
%             
%     targets = [targets1, targets2];
% 
% end

function [X, Y] = getCoordinates(x, y, sz)
    X = x - 0.5;
    Y = (sz - 0.5)  - y;
end
function plotMap(asteroidMap)
    asteroidMap = flipud(asteroidMap);
    playGroundSize = size(asteroidMap,1);
    % customMade grid:
    figure; hold on; ylim([0,playGroundSize]); xlim([0,playGroundSize]);
    for x = 0 : playGroundSize
        xline(x);
    end
    for y = 0 : playGroundSize
        yline(y);
    end
    
    for x = 1 : playGroundSize
        for y = 1 : playGroundSize
            if (asteroidMap(x,y)) % found an asteroid
                plot(y-0.5,x-0.5, 'k*')
            end
        end
    end
end