%스크립트 파일 사용과 사용자 정의 함수

%1. for문을 이용하여 자연수를 입력 받아 1부터 입력 받은 수까지의 합을 구하는 함수를 생성하고 스크립트 파일로 저장하라
x = input('enter number : ');
y = 0;

for z = 0: inf
    if(x <= 0)
        disp('자연수가 아닙니다!')
        x = input('enter number : ');
    else 
        disp('자연수입니다!')
        for k = 0: 1: x
            y = y + k;
        end
        disp('총 합은 ')
        y
        break
    end
end

