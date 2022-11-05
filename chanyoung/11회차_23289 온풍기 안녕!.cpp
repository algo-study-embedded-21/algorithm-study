#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string.h>
using namespace std;

struct gps { int y, x; };

int r, c, k;
int w;
int map[20][20];
vector<gps> heater; // 온풍기들의 위치
vector<gps> check;  // 온도 체크를 해야하는 곳들의 위치
int rwall[19][20]; // 가로벽 표시
int cwall[20][19]; // 세로벽 표시
int temp[20][20]; // 온도표
int plustemp[20][20]; // 온도 변화 표
int choco; // 초콜릿 갯수

int yy[4] = { 0,0,-1,1 };
int xx[4] = { 1,-1,0,0 };

int pos(gps now, gps next) // now에서 next로 갈때 벽이있으면 1반환
{
    if (next.y > now.y && rwall[now.y][now.x] == 0)return 0;
    else if (next.y < now.y && rwall[next.y][next.x] == 0)return 0;
    else if (next.x > now.x && cwall[now.y][now.x] == 0)return 0;
    else if (next.x < now.x && cwall[now.y][next.x] == 0)return 0;
    else return 1;
}

int outmap(gps next) // next가 맵 밖으로 나가면 1 반환
{
    if (next.y<0 || next.y>r - 1 || next.x<0 || next.x>c - 1)return 1;
    else return 0;
}

void tempplus() // 온도 변화 합산
{
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            temp[i][j] += plustemp[i][j];
        }
    }
}

void wind(gps st) // 바람 불기
{
    queue<gps> q;
    int d = map[st.y][st.x] - 1;
    st = { st.y + yy[d],st.x + xx[d] };
    q.push(st);
    int visit[20][20] = { 0 };
    visit[st.y][st.x] = 5;
    int zero = 5;
    while (!q.empty() && zero>0) // 더이상 바람불곳이 없거나 추가되는 온도가 없을때 까지
    {
        gps now = q.front();
        q.pop();
        for (int i = 0; i < 3; i++)
        {
            gps next;
            if (i == 0) // 나아가는 방향
            {
                next = { now.y + yy[d],now.x + xx[d] };
                if (outmap(next))continue;
                if (pos(now, next)) continue;
            }
            else if (i == 1) // 첫번째 대각 방향
            {
                if (d < 2) // 좌우 방향인 경우 
                {
                    next = { now.y + yy[2],now.x + xx[2] }; // 일단 상하로 이동 가능한지 
                    if (outmap(next))continue;
                    if (pos(now, next)) continue;
                    gps mid = next;
                    next = { mid.y + yy[d],mid.x + xx[d] }; // 다음 좌우로 이동가능한지
                    if (outmap(next))continue;
                    if (pos(mid, next))continue;
                }
                else // 상하 방향인 경우
                {
                    next = { now.y + yy[0],now.x + xx[0] }; // 좌우로 이동 가능한지
                    if (outmap(next))continue;
                    if (pos(now, next)) continue;
                    gps mid = next;
                    next = { mid.y + yy[d],mid.x + xx[d] }; // 상하로 이동 가능한지
                    if (outmap(next))continue;
                    if (pos(mid, next))continue;
                }
            }
            else // 두번째 대각 방향
            {
                if (d < 2)
                {
                    next = { now.y + yy[3],now.x + xx[3] };
                    if (outmap(next))continue;
                    if (pos(now, next)) continue;
                    gps mid = next;
                    next = { mid.y + yy[d],mid.x + xx[d] };
                    if (outmap(next))continue;
                    if (pos(mid, next))continue;
                }
                else
                {
                    next = { now.y + yy[1],now.x + xx[1] };
                    if (outmap(next))continue;
                    if (pos(now, next)) continue;
                    gps mid = next;
                    next = { mid.y + yy[d],mid.x + xx[d] };
                    if (outmap(next))continue;
                    if (pos(mid, next))continue;
                }
            }
            visit[next.y][next.x] = visit[now.y][now.x] - 1;
            zero = visit[next.y][next.x]; // 추가되는 온도 갱신
            q.push(next);
        }
    }
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            plustemp[i][j] += visit[i][j];
        }
    }
}

int checking() // 종료조건 탐색
{
    for (int i = 0; i < check.size(); i++)
    {
        gps ch = check[i];
        if (temp[ch.y][ch.x] < k) return 0;
    }
    return 1;
}

void avg() // 온도 조절
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            gps now = { i,j };
            int nowtemp = temp[now.y][now.x]; // 현재 위치의 온도
            for (int d = 1; d < 3; d++) // 중복을 피하기위해 좌,상 방향으로만 진행
            {
                gps next = { now.y + yy[d],now.x + xx[d] };
                if (outmap(next))continue;
                if (pos(now, next))continue;
                int nexttemp = temp[next.y][next.x]; // 인근 위치의 온도
                if (nowtemp > nexttemp) // 현재위치가 더 높은 온도
                {
                    int m = (nowtemp - nexttemp) / 4;
                    plustemp[now.y][now.x] -= m;
                    plustemp[next.y][next.x] += m;
                }
                else if (nexttemp > nowtemp) // 인근 위치가 더 높은 온도
                {
                    int m = (nexttemp - nowtemp) / 4;
                    plustemp[next.y][next.x] -= m;
                    plustemp[now.y][now.x] += m;
                }
            }
        }
    }
}

void heating() // 모든 프로세스
{
    while (choco <= 100)
    {
        for (int n = 0; n < heater.size(); n++)
        {
            gps h = heater[n];
            memset(plustemp, 0, sizeof(plustemp));
            wind(h);
            tempplus();
        }
        memset(plustemp, 0, sizeof(plustemp));
        avg();
        tempplus();
        for (int i = 0; i < r; i++){ // 외곽 온도 1씩 감소
            for (int j = 0; j < c; j++){
                if ((i == 0 || i == r - 1 || j == 0 || j == c - 1) && temp[i][j] > 0) temp[i][j] -= 1;
            }
        }
        choco++;
        if (checking())return; // 종료조건
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> r >> c >> k;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == 5)check.push_back({ i,j });
            else if (map[i][j] > 0) heater.push_back({ i,j });
        }
    }
    cin >> w;
    for (int i = 0; i < w; i++)
    {
        int x, y, t;
        cin >> x >> y >> t;
        if (t == 0) rwall[x - 2][y - 1] = 1;
        else cwall[x - 1][y - 1] = 1;
    }
    heating();
    cout << choco;
    return 0;
}