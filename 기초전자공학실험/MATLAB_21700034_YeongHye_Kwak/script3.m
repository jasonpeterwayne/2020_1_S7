%스크립트 파일 사용과 사용자 정의 함수

%3. 입력 받은 2개의 행렬을 곱하는 함수를 생성하고 스크립트 파일로 저장하라. 
% 이 때 생성한 함수는 예외처리를 포함하고 있어야 한다.
x = input('첫번째 행렬(각 행은 세미콜론(;)으로 구분!): ', 's');
X = str2num(x)
disp('첫번째 행렬의 크기')
size_X = size(X)
y = input('두번째 행렬(각 행은 세미콜론(;)으로 구분!): ', 's');
Y = str2num(y)
disp('두번째 행렬의 크기')
size_Y = size(Y)

%A1 = zeros(1,3);
%TF = ismatrix(A1)

try
    Z = X*Y
catch
    disp('두번째 행의 크기와 첫번째 열의 크기는 같아야 행렬의 곱이 가능해집니다!')
    disp('첫번째 행렬의 크기')
    size_X = size(X)
end

