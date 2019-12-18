clearvars; close all; clc

% NOTE: workaround - I'm working on a fliped map!
%% retrieve the input:
file = fopen('inputs/10.txt');
asteroidMap = zeros(36);
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
aCoords = aCoords - 0.5;
[allCoords(2,:), allCoords(1,:)] = find( ones( size( asteroidMap)));
canSee = zeros(1,numAsteroids);

% shoot a ray at all other asteroids and get its slope
ind = 0;

for pt1 = aCoords % for every Asteroid
    ind = ind+1;
    tryToDetect = aCoords;
    tryToDetect(:,ind) = [];
    
    x1 = pt1(1); % starting point -- set that as origin:
    y1 = pt1(2);

    for pt2 = tryToDetect 
        x2 = pt2(1);
        y2 = pt2(2);
%         plot([x1, x2], [y1, y2],'r');
%         pause(0.2)

        slope = atan2(y2-y1, x2-x1);
        % get thisAsteroid -> otherAsteroids slopes   
        slopes = atan2(tryToDetect(2,:) - y1, tryToDetect(1,:)-x1);

        % check     
        if sum( slopes == slope) % if there is something in that direction
            canSee(ind) = canSee(ind)+1;
            tryToDetect(:,slopes == slope) = [];
        end        
         
    end
  
end

[M, I] = max( canSee);

base = aCoords(:,I);
[xBase,yBase] = getCoordinates(base, playGroundSize);

%% PART 2: start the vaporization from this point:
 
%plotMap(asteroidMap);
x1 = base(1);
y1 = base(2);
aCoords(:,I) = []; % don't try to shoot yourself
slopes = atan2(aCoords(2,:) - y1, aCoords(1,:)-x1);

[slopes_sorted, I_slopes] = sort(slopes, 'descend');
aCoords = aCoords(:,I_slopes);

whereToBegin = find(slopes_sorted == pi/2, 1, 'first'); %% todo - might not be there!
aCoords = [aCoords(:, whereToBegin:end), aCoords(:, 1:whereToBegin-1)];
slopes_sorted = [slopes_sorted(whereToBegin:end), slopes_sorted(1:whereToBegin-1)];
ind = 1;
while ind < length(aCoords)

    ind1 = ind;
    while ind1 ~= length(slopes_sorted) && slopes_sorted(ind) == slopes_sorted(ind1+1)
        ind1 = ind1+1;
    end
    clusters{ind} = aCoords(:, ind:ind1);
    ind = ind1+1;
end

clusters = clusters(~cellfun(@isempty, clusters));
%d = getDistance(base, clusters{3})
tmp = clusters{200};
[X,Y] = getCoordinates(tmp, playGroundSize)


if size(tmp,2) == 1
    % sort the same slopes by distance
end

% for target = aCoords
%     plot([base(1), target(1)],[base(2), target(2)], 'g' )
%     pause(0.2)
% end


function dist = getDistance(pt1, pt2)
    dist = sqrt((pt1(1)-pt2(1,:)).^2 + (pt1(2) - pt2(2,:)).^2);
end
 
function [X, Y] = getCoordinates(pt, sz)
    x = pt(1); y = pt(2);
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