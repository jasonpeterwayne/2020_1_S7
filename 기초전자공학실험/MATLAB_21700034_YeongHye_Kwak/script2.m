%스크립트 파일 사용과 사용자 정의 함수

%2. 숫자를 입력받아 짝수 혹은 홀수를 판별하는 함수를 생성하고 스크립트 파일로 저장하라

for z = 0: inf
    x = input('enter number (0-exit the loop): ');
    y = mod(x,2);
    
    if(x == 0)
        disp('짝수입니다!')
        disp('반복문을 종료합니다!')
        break
    end
    
    if (y == 0)
        disp('짝수입니다!')
    else
        disp('홀수입니다!')
    end
end