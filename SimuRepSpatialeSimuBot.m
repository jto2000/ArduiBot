%% Init
%cube_matrix = ones(50); %cube_matrix(50,50) = ones(50);
cube_matrix = zeros(50); %cube_matrix(50,50) = ones(50);

%% Values

% SimuRepSpatiale(18,20,true,10,10,10)
heading = 330;
distCapt = 100; % en mm
isLeft = true;
resolCapt = 20; % en deg
xPos = 300; % En mm
yPos = 40; % En mm


%% Tracer la représentation graphique de la position du robot :
% En x et y :
plot(xPos,yPos,'+');
if isLeft
    angle2 = heading - resolCapt;
else
    angle2 = heading + resolCapt;
end

% Heading :
% Flèche d'angle et longeur donnée

% position heading :
% xHead, yHead 
xHead = sin(deg2rad(heading))*distCapt + xPos;
yHead = cos(deg2rad(heading))*distCapt + yPos;
%plot(xHead,yHead)
line([xPos, xHead], [yPos, yHead]);
xRes = sin(deg2rad(angle2))*distCapt + xPos;
yRes = cos(deg2rad(angle2))*distCapt + yPos;
line([xPos, xRes], [yPos, yRes])

axis([1 500 1 500])


%% Compute :
cube_matrix = SimuRepSpatiale(heading, distCapt, isLeft, resolCapt, xPos, yPos, cube_matrix);

pcolor(cube_matrix)