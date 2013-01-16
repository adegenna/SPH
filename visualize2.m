close all
clear all
%% Load SPH results
load spherefallingoutput.dat
load fluid.dat
%load fluidlltestoutput.dat
%fluid = sphereoninclineoutput;
%fluid = spherefallingoutput;
%fluid = fluidlltestoutput;
t = fluid(:,1);
x = fluid(:,2:2:end);
y = fluid(:,3:2:end);

%% Plots

% figure
% plot(x, y, '.-')
% xlabel('x')
% ylabel('y')
% 
% figure
% subplot 121
% plot(t, x, '.-')
% xlabel('t')
% ylabel('x')
% subplot 122
% plot(t, y, '.-')
% xlabel('t')
% ylabel('y')
% axis([0 10 0 10])

%% Video
F = figure
for k=1:length(t)*0.25
 %   if k == 1
     %   plot([-20 60],[21 -59] ,'k',x(k,:), y(k,:), '.','MarkerSize',5)
        plot([-10 10],[0 0] ,'k',x(k,:), y(k,:), '.','MarkerSize',5)
%     else
   %      plot(x(1:k,:), y(1:k,:), '-', x(k,:), y(k,:), '.')
%     end
    xlabel('x')
    ylabel('y')
    axis([-25 25 -30 20])
    %axis([0 10 0 10])
    title(['t = ' num2str(t(k))])
    %set(gcf,'Position',[200 200 400 400])
    drawnow
    %filename = sprintf('Sphereincline_%d.png',k)
%filename =['SphereFlat_' int2str(k) '.png'];
%saveas(F,filename)
    %pause
    
end
%%
% figure
%  plot(x(1,:), y(1,:), '.','MarkerSize',60)