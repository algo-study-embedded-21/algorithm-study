// 로컬에서는 맞게 나오는데 백준에서 바로 틀렸다고 떠서
// 질문 검색을 찾아보고 x랑 y를 바꿔주니까 됐다.
// (y, x)로 넣었음..문제 잘 읽어보자..

#include <iostream>
#include <algorithm>
using namespace std;

// 주사위 구조체
struct DICE
{
    int right = 0;
    int left = 0;
    int front = 0;
    int back = 0;
    int top = 0;
    int bottom = 0;
    int y = 0;
    int x = 0;
};

int N, M, x, y, K;
int map[25][25];

DICE dice; // 주사위 선언

int dy[5] = { 0, 0, 0, -1, 1 }; // 북 남
int dx[5] = { 0, 1, -1, 0, 0 }; // 동 서


// 동쪽(dir == 1)으로 이동했을 때 주사위 변화
void moveEast()
{
    int temp = dice.right; // 값을 변경하기 위해 빈 변수에 주사위 값 하나 담아두기
    dice.right = dice.bottom;
    dice.bottom = dice.left;
    dice.left = dice.top;
    dice.top = temp;
    dice.x += 1;
}

// 서쪽(dir == 2)으로 이동했을 때 주사위 변화
void moveWest()
{
    int temp = dice.left; // 값을 변경하기 위해 빈 변수에 주사위 값 하나 담아두기
    dice.left = dice.bottom;
    dice.bottom = dice.right;
    dice.right = dice.top;
    dice.top = temp;
    dice.x -= 1;
}

// 북쪽(dir == 3)으로 이동했을 때 주사위 변화
void moveNorth()
{
    int temp = dice.top; // 값을 변경하기 위해 빈 변수에 주사위 값 하나 담아두기
    dice.top = dice.front;
    dice.front = dice.bottom;
    dice.bottom = dice.back;
    dice.back = temp;
    dice.y -= 1;
}

// 남쪽(dir == 4)으로 이동했을 때 주사위 변화
void moveSouth()
{
    int temp = dice.back; // 값을 변경하기 위해 빈 변수에 주사위 값 하나 담아두기
    dice.back = dice.bottom;
    dice.bottom = dice.front;
    dice.front = dice.top;
    dice.top = temp;
    dice.y += 1;
}

void moving(int dir)
{
    // 다음 칸으로 갈 수 있는지 확인하기 위한 좌표
    int ny = dice.y + dy[dir];
    int nx = dice.x + dx[dir];

    if (ny < 0 || nx < 0 || ny >= N || nx >= M) return; // 지도 범위를 넘는 경우 함수 종료
    if (dir == 1) moveEast();
    else if (dir == 2) moveWest();
    else if (dir == 3) moveNorth();
    else if (dir == 4) moveSouth();

    if (map[dice.y][dice.x] == 0) { // 이동한 칸의 수가 0이면 주사위 바닥면을 지도로 복사
        map[dice.y][dice.x] = dice.bottom;
    }
    else { // 이동한 칸의 수가 0이 아니면 수를 주사위 바닥면으로 복사
        dice.bottom = map[dice.y][dice.x];
        map[dice.y][dice.x] = 0;
    }

    cout << dice.top << endl;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> N >> M >> y >> x >> K;

    // 지도 구성하기
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
        }
    }

    // 주사위 처음 위치
    dice.y = y;
    dice.x = x;

    // 주사위 이동
    for (int i = 0; i < K; i++) {
        int dir;
        cin >> dir;
        moving(dir);
    }


}