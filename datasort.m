clear
clc
load('rawbeacon.mat')

length = size(data);
row = length(2);
column= length(1);

% 비콘  MAC 주소
b3 = "c8:fd:19:8d:1d:4f" + char(13);
b2 = "58:7a:62:3a:71:56" + char(13);
b1 = "18:93:d7:2a:8e:a4" + char(13);
b4 = "fc:69:47:74:c3:68" + char(13);

sorted_data = strings(column, row);
sorted_data(1,1) = b1;
sorted_data(1,2) = b2;
sorted_data(1,3) = b3;
sorted_data(1,4) = b4;

index = 1;
ii = 1;
while index < 2000
     mac = data(index, 2);
     disp(mac)
     if strcmp(b1, mac)
         sorted_data(ii+1 , 1) = data(index+1, 2);
         
     elseif strcmp(b2, mac)
         sorted_data(ii+1, 2)= data(index+1, 2);
         
     elseif strcmp(b3, mac)
         sorted_data(ii+1 , 3)= data(index+1, 2);
         
     elseif strcmp(b4, mac)
         sorted_data(ii+1, 4)= data(index+1, 2);
             
     else
         disp("error");
     end
     
     index = index + 3;
     ii = ii + 1;
end

