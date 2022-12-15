#include <iostream>
#include <queue>
using namespace std;

struct Dice {
    int x = 1;
    int y = 1;
    int dir = 0;
    int side[] = {0, 1, 2, 3, 4, 5, 6};
};

int N, M, K;
int map[21][21];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
Dice dice;
int total_score = 0;

int bfs() {
    int cnt = 1;
    int visit[21][21] = {0, };
    queue<pair<int, int>> q;
    q.push({dice.x, dice.y});
    visit[dice.x][dice.y] = 1;
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int d=0; d<4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx < 1 || nx > N || ny < 1 || ny > M) continue;
            if (visit[nx][ny] || map[nx][ny] != map[dice.x][dice.y]) continue;
            visit[nx][ny] = 1;
            cnt ++;
            q.push({nx, ny});
        }
    }
    
    return cnt;
}

void move() {
    dice.x += dx[dice.dir];
    dice.y += dy[dice.dir];
    if (dice.x < 1 || dice.x > N || dice.y < 1 || dice.y > M) {
        dice.x -= dx[dice.dir];
        dice.y -= dy[dice.dir];
        dice.dir = (dice.dir + 2) % 4;
        dice.x += dx[dice.dir];
        dice.y += dy[dice.dir];
    }
    
    int temp = dice.side[1];
    
    switch (dice.dir) {
        case 0:
            dice.side[1] = dice.side[4];
            dice.side[4] = dice.side[6];
            dice.side[6] = dice.side[3];
            dice.side[3] = temp;
            break;
            
        case 1:
            dice.side[1] = dice.side[2];
            dice.side[2] = dice.side[6];
            dice.side[6] = dice.side[5];
            dice.side[5] = temp;
            break;
            
        case 2:
            dice.side[1] = dice.side[3];
            dice.side[3] = dice.side[6];
            dice.side[6] = dice.side[4];
            dice.side[4] = temp;
            break;
            
        case 3:
            dice.side[1] = dice.side[5];
            dice.side[5] = dice.side[6];
            dice.side[6] = dice.side[2];
            dice.side[2] = temp;
            break;
    }
}

void play() {
    move();
    
    int C = bfs();
    int B = map[dice.x][dice.y];
    total_score += (B * C);
    
    if (dice.side[6] > B) dice.dir = (dice.dir + 1) % 4;
    else if (dice.side[6] < B) dice.dir = (dice.dir + 3) % 4;
}

int main() {
    cin >> N >> M >> K;
    for (int i=1; i<=N; i++) {
        for (int j=1; j<=M; j++) {
            cin >> map[i][j];
        }
    }
    
    for (int k=0; k<K; k++) {
        play();
    }
    
    cout << total_score << endl;
    
    return 0;
}
