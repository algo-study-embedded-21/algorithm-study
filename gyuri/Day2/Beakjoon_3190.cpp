// 이 문제는 방향 전환하는 부분과 뱀 몸통을 구현하는 부분이
// 어려워서 다른 코드를 참고해서 풀었다.
// 시간 지나고 다시 풀어볼 것

#include <iostream>
#include <queue>
#define endl '\n'
using namespace std;

int N, K;
int L;
int board[105][105];
char dirArr[10002]; // index : 시간, value : 방향 인 DAT 배열
int bodyArr[105][105]; // 뱀의 몸통이 있는지 저장하는 배열. 0: 없음, 1: 있음. 
int totalTime = 0;// 총 시간
int nowDir = 0; // 현재 방향 인덱스

int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };

queue<pair<int, int>> snakeBody;

void changeDir(int total_time) {

    // 오른쪽일 때
    if (dirArr[total_time] == 'D') {
        nowDir++;
        if (nowDir == 4 ) nowDir = 0; // 범위를 넘어갈 때 초기화
    }

    // 왼쪽일 때
    else if (dirArr[total_time] == 'L') {
        nowDir--;
        if (nowDir == -1) nowDir = 3; // 범위를 넘어갈 때 초기화
    }
}

int move(int total_time) {

    int ny = snakeBody.back().first + dy[nowDir]; // 가장 마지막 위치에서 이동할 다음 위치
    int nx = snakeBody.back().second + dx[nowDir]; // 가장 마지막 위치에서 이동할 다음 위치

    // 보드 밖으로 벗어나면 finish 리턴
    if (ny < 1 || nx < 1 || ny > N || nx > N) return -1;
    // 이동할 부분에 몸통이 존재하면 finish 리턴
    if (bodyArr[ny][nx] == 1) return -1;
    else bodyArr[ny][nx] = 1;
  

    // 몸통이 있는 좌표 넣기
    snakeBody.push({ ny, nx });

    // 방향 전환
    changeDir(total_time);
    
    if (board[ny][nx] == 1) { // 만약 사과가 있다면
        board[ny][nx] = 0; // 뱀이 사과를 먹고 없어짐
    }
    else { // 사과가 없다면
        bodyArr[snakeBody.front().first][snakeBody.front().second] = 0; // 꼬리 사라짐
        snakeBody.pop(); // 꼬리 위치 비워주기 (길이 변화는 없음)
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    // 보드 구성
    cin >> N >> K;
    for (int i = 0; i < K; i++) {
        int ay, ax;
        cin >> ay >> ax;
        board[ay][ax] = 1; // 사과는 1로 저장
    }

    // 방향 명령어
    cin >> L;
    for (int i = 0; i < L; i++) {
        int t;
        char dir;
        cin >> t >> dir;
        dirArr[t] = dir;
    }

    snakeBody.push({ 1, 1 }); // 시작 몸통 위치 저장
    bodyArr[1][1] = 1; // 시작 몸통 위치 저장

    while (1) {
        totalTime++;

        int n = move(totalTime);
        if (n == -1) break;
    }
    cout << totalTime << endl;

    return 0;
}