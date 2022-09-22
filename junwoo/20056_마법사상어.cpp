#include <iostream>
#include <vector>

using namespace std;
struct Fireball{
    int x;
    int y;
    int m;
    int s;
    int d;
};

int dx[] = {-1,-1,0,1,1,1,0,-1};
int dy[] = {0,1,1,1,0,-1,-1,-1};
int evenD[] = {0,2,4,6};
int oddD[] = {1,3,5,7};
int N,M,K;
int answer;

vector<Fireball> MAP[55][55];
vector<Fireball> balls;

void initMAP(){
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= N; j++)
            MAP[i][j].clear();
}

void move(){
    initMAP();

    for(int i = 0; i < balls.size(); i++){
        int speed = balls[i].s % N;
        int x = balls[i].x;
        int y = balls[i].y;
        int d = balls[i].d;
        int m = balls[i].m;

        int nx = x + (dx[d] * speed);
        int ny = y + (dy[d] * speed);

        if(nx > N) nx -= N;
        if(ny > N) ny -= N;
        if(nx < 1) nx += N;
        if(ny < 1) ny += N;
        MAP[nx][ny].push_back({nx,ny,m,balls[i].s,d});
        
    }

    balls.clear();
}

void boom(int i, int j){
    int Mass = 0;
    int Speed = 0;
    int Dir = 0;
    int cnt = MAP[i][j].size();

    for(int t = 0; t < MAP[i][j].size();t++){
        Mass += MAP[i][j][t].m;
        Speed += MAP[i][j][t].s;
        if(MAP[i][j][t].d == 0) Dir += 2;
        else Dir += MAP[i][j][t].d;
    }

    Mass /= 5;
    Speed /= cnt;
    if(Mass == 0) return;
    if(Dir % 2 == 0){
        for(int t = 0; t < 4; t++)
            balls.push_back({i,j,Mass,Speed,evenD[t]});
    }
    else{
        for(int t = 0; t < 4; t++)
            balls.push_back({i,j,Mass,Speed,oddD[t]});
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M >> K;

    for(int i = 0; i < M; i++){
        int r,c,m,s,d;
        cin >> r >> c >> m >> s >> d;
        MAP[r][c].push_back({r,c,m,s,d});
        balls.push_back({r,c,m,s,d});
    }

    for(int i = 0; i < K; i++){
        move();
        for(int x = 1; x <= N; x++)
            for(int y = 1; y <= N; y++){
                if(MAP[x][y].size() > 1)
                    boom(x,y);
                else if(MAP[x][y].size() == 1)
                    balls.push_back(MAP[x][y][0]);
            }
    }

    for(int i = 0; i < balls.size(); i++)
        answer += balls[i].m;

    cout << answer;
}