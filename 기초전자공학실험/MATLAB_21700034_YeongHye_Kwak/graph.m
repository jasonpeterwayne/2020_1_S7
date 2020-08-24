%그래프 그리기

%1. y = exp(x)에 대한 그래프를 0 <= x <= 10의 범위에 대해 그려라. 
% 데이터 값들은 사각형표식으로 표현되고 적색 실, 선 두께는 1포인트, 사각형 표식의 크기는 2 포인트.
% 표식은 녹색 테두리 선과 황색 배경색을 가지는 2차원 그래프를 그림창에 나타내어라.
x = [0:0.01:10];
y = exp(x);

f1 = figure(1);
plot(x, y, '-rs', 'LineWidth', 1, 'markersize', 2, 'markerEdgeColor', 'g', 'markerfacecolor', 'y')

%2. -3 <= x <= 5에 대하여 y = 4*x^4 + 3*x^2 - 3*x + 20 함수, 1차 도함의 그래프를 같은 그림에
%표시하라.
x = -3:0.008:5;
y = 4*x.^4 + 3*x.^2 - 3*x + 20;
f2 = figure(2);
hold on
plot(x,y, '-rs')
y1 = diff(y)/0.008;
plot(x(:,1:length(y1)),y1, '-bs')
