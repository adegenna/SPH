close all
clear all

load fluid.dat

t = fluid(:,1);
x = fluid(:,2:2:end);
y = fluid(:,3:2:end);

%% Plots


F = figure
for k=1:length(t)

        plot(x(k,:), y(k,:), '.','MarkerSize',5)
    xlabel('x')
    ylabel('y')
    axis([0 30 0 20]) %this can change according to the simulation

    title(['t = ' num2str(t(k))])
    %set(gcf,'Position',[200 200 400 400])
    drawnow
    %To save files to make a movie:
    %filename = sprintf('output_%d.png',k)
%filename =['SphereFlat_' int2str(k) '.png'];
%saveas(F,filename)
    %pause
    
end
