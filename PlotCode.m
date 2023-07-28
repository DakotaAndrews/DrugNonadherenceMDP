clear all
clc

Data1 = load('data.txt');
X = (Data1(:,1))
Y = (Data1(:,2))
figure(1)
plot(X,Y,'b.')
title('Single vs Double Dosage')
xlabel('Half-Life')
ylabel('Concentration')


