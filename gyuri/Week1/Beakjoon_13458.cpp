#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 1000001
using namespace std;

int N; // 시험장 개수
int B, C; // 총 감독관이 감시할 수 있는 응시자 수, 부감독관이 감시할 수 있는 응시자 수

int arr[MAX]; // index: 응시자 수, value: 응시자 수 카운팅
long long result;

int main() {
    cin >> N;
    
    for(int i=0; i<N; i++){
        int A; // 응시자의 수
        cin >> A;
        arr[i] = A;
    }
    cin >> B >> C;

    for(int i=0; i<N; i++){
        int sub = 0; // 부 감독관 수
        int temp = arr[i]-B; // 응시자수 - 총 감독관이 감시할 수 있는 응시자 수
        if (temp > 0) {
            if (temp%C > 0) sub++; // 나머지가 있을 떄 부 감독관 수를 1명 더 늘려줘야 됨
            sub += temp/C;
        }

        result += (1+sub); // (총 감독관 수 + 부 감독관 수) * 
    }
    cout << result;

    return 0;
}
// ***느낀점***
// 이 문제는 따로 필요한 알고리즘이 없는 계산 문제라 굉장히 쉬웠지만
// 정수 자료형 범위를 int로 하면 안된다는 함정이 있었다.
// 로컬에서는 모두 정답으로 나오지만 백준에서는 틀리다고 나와 무엇이 문제인지 알지 못했다.
// 때문에 구글링을 했고 자료형이 문제라는 것을 알 수 있었다.
// int 범위 : -2,147,483,648 ~ 2,147,483,647
// long long 범위 : -9,223,372,036,854,775,808 ~ 9,223,372,036,854,775,807