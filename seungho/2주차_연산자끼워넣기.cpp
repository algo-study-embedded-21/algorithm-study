#include <iostream>
using namespace std;

int n;
int arr[12];
int cal[4];
int result=0;
int maxresult = -2134567890;
int minresult = 2134567890;


void dfs(int level) {                       // dfs로 모든 경우 탐색
    if (level == n) {                     // 모든 연산을 했을 경우 리턴
        if (result > maxresult) {
            maxresult = result;
        }
        if (result < minresult) {
            minresult = result;
        }
        return;
    }
    for (int i = 0; i < 4; i++) {           // 사칙연산 중 한 가지 선택
        if (cal[i] == 0) continue;      
        int temp = result;
        switch (i) {
            case 0: result += arr[level];
                break;
            case 1: result -= arr[level];
                break;
            case 2: result *= arr[level];
                break;
            case 3: result /= arr[level];
                break;
        }
        cal[i] --;
        dfs(level + 1);                 
        cal[i] ++;                          // 리턴 시 사칙연산 개수 초기화
        result = temp;                      // 리턴 시 연산 복구
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {           //수 입력받기
        cin >> arr[i];
    }
    result = arr[0];
    for (int i = 0; i < 4; i++) {           //사칙연산 입력받기
        cin >> cal[i];
    }
    dfs(1);
    cout << maxresult << "\n" << minresult;
}
