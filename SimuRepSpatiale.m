function out_cube = SimuRepSpatiale(heading, distCapt, isLeft, resolCapt, xPos, yPos, cube_matrix)
% global cube_matrix
% cube_matrix = ones(50); %cube_matrix(50,50) = ones(50);
global int pas_mat;
pas_mat = 10;
%PositionY = yPos;
out_cube = cube_matrix;

    if ~isLeft
        resolCapt = -resolCapt;
    end

    theta1 = deg2rad(90 - heading);
    theta2 = deg2rad(90 - heading + resolCapt);
    
    
    xth1 = xPos + cos(theta1)*distCapt; 
    xth2 = xPos + cos(theta2)*distCapt;
    
    xMin = min(xPos, min(xth1,xth2));
    xMax = max(xPos, max(xth1,xth2));    
    
    xMinPas = floor(xMin/pas_mat);
    xMaxPas = floor(xMax/pas_mat);
    
    if xMinPas < 0 ; xMinPas = 0; end;
    if xMaxPas > length(cube_matrix); xMaxPas = length(cube_matrix);end
    
    for xn = xMinPas : xMaxPas

       % calcul de l'iteration sur y
%        yan = yPos + sin(theta1)*(xn-xPos)*pas_mat;
%        ybn = yPos + sin(theta2)*(xn-xPos)*pas_mat;
       yan = yPos + tan(theta1)*(xn*pas_mat-xPos);
       ybn = yPos + tan(theta2)*(xn*pas_mat-xPos);

           
       if yan < ybn
           yMin = floor((yan)/pas_mat);
           yMax = floor((ybn)/pas_mat);
       else
           yMax = floor((yan)/pas_mat);
           yMin = floor((ybn)/pas_mat);
       end
       if yMin < 1 ; yMin = 1; end;
       %if yMax < 1 ; yMax = 0; end; % attention les deux valeurs peuvent déborder !
       if yMax > length(cube_matrix); yMax = length(cube_matrix);end
       
        if yMin ~= yMax          
            for yn = yMin : yMax
              out_cube(yn,xn) = 1;
              disp(['No object at ' num2str(xn) ', ' num2str(yn)])
            end
        end
        
    end
   %out_cube = cube_matrix;
end