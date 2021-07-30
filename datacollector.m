clear
clc
a = serialport('COM8', 9600);

for ii = 1:10000
    data(ii,2) = readline(a);
    disp(ii)
end
    