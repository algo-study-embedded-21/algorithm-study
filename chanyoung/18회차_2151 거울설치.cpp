#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct gps { int y, x; };
struct light { gps g; int d; int cnt; }; // 빛의 위치, 진행방향, 지나온거울의 수+1

int n;
char room[50][50];
vector<gps> mirror; // 거울을 놓을수 있는 위치 정보
vector<gps> door; // 문 위치

int yy[4] = { 1,-1,0,0 };
int xx[4] = { 0,0,-1,1 };

int non[4] = { 1,0,3,2 }; // now[d] = 방향 d로 입사한 빛이 정반사 되는 방향 인덱스

int check()
{
    int visit[50][50][4] = {0};
    gps st = door[0]; // 입구
    queue<light> q;
    for (int d = 0; d < 4; d++) // 입구기준 4방향 정보 큐에 넣기
    {
        visit[st.y][st.x][d] = 1;
        q.push({ st,d,1 });
    }
    while (!q.empty())
    {
        light now = q.front();
        q.pop();
        if (room[now.g.y][now.g.x] != '!') // 거울이 있을수 있는곳이 아닌경우
        {
            gps next = { now.g.y + yy[now.d],now.g.x + xx[now.d] }; // 기존 빛이 진행하던 방향 그대로 진행 
            if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>n - 1)continue;
            if (room[next.y][next.x] == '*')continue;
            if (visit[next.y][next.x][now.d] == 0)visit[next.y][next.x][now.d] = now.cnt; // 이 방향으로 처음 빛이 도달했을때
            else visit[next.y][next.x][now.d] = min(now.cnt, visit[next.y][next.x][now.d]); // 이미 빛이 이방향으로 지나간적이 있으면 최솟값으로 갱신
            if(room[next.y])
            q.push({ next,now.d,now.cnt });
        }
        else // 거울이 있을수 있는 위치라면 반사 고려하기
        {
            for (int i = 0; i < 4; i++)
            {
                if (i == non[now.d])continue; // 정반사는 제외
                gps next = { now.g.y + yy[i],now.g.x + xx[i] };
                if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>n - 1)continue;
                if (room[next.y][next.x] == '*')continue;
                if (visit[next.y][next.x][i] > 0 && visit[next.y][next.x][i] <= now.cnt)continue; // 이전에 이경로로 지나간 빛이 now보다 최적경로라면 now를 더이상 진행x
                if (i == now.d) { // 위치에 거울을 놓지 않은경우 빛이 통과 >> 거쳐간 거울수 변화 없음
                    if (visit[next.y][next.x][i] == 0) visit[next.y][next.x][i] = now.cnt;
                    else visit[next.y][next.x][i] = min(now.cnt, visit[next.y][next.x][i]);
                    q.push({ next,i,now.cnt});
                }
                else { // 빛이 반사된 경우 거쳐간 거울수 +1
                    if (visit[next.y][next.x][i] == 0) visit[next.y][next.x][i] = now.cnt + 1;
                    else visit[next.y][next.x][i] = min(now.cnt + 1, visit[next.y][next.x][i]);
                    q.push({ next,i,now.cnt + 1 });
                }
            }
        }
    }
    int ans = 213456789;
    for (int d = 0; d < 4; d++) // 출구위치에서 4방향으로 들어온 빛중 가장 적게 거울을 거친 빛 찾기
    {
        if (visit[door[1].y][door[1].x][d] == 0)continue;
        ans = min(ans, visit[door[1].y][door[1].x][d]);
    }
    return ans - 1;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n;
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> room[i][j];
            if (room[i][j] == '!')mirror.push_back({ i,j });
            else if (room[i][j] == '#') door.push_back({ i,j });
        }
    }
    int ans = check();
    cout << ans;

    return 0;
}
