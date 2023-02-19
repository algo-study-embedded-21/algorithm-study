#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct gps { int y, x; };

int n, m;
int map[100][100];
int visit[100][100]; 
int air[100][100]; // 공기가 있는지 여부 표시

int yy[4] = { 0,0,1,-1 };
int xx[4] = { 1,-1,0,0 };

void aircheck(gps st) // 공기위치 파악
{
    queue<gps> q;
    vector<gps> v; // 그룹화 된 좌표 모음
    q.push(st);
    v.push_back(st);
    visit[st.y][st.x] = 1;
    int hole = 0; // 구멍인지 여부 표시
    while (!q.empty())
    {
        gps now = q.front();
        q.pop();
        for (int d = 0; d < 4; d++)
        {
            gps next = { now.y + yy[d],now.x + xx[d] };
            if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>m - 1)continue;
            if (visit[next.y][next.x] == 1)continue;
            if (map[next.y][next.x] == 1)continue;
            if (next.y == 0 || next.y == n - 1 || next.x == 0 || next.x == m - 1) hole = 1; // 맵 끝과 연결되어 있다면 구멍이다
            else
            {
                visit[next.y][next.x] = 1;
                q.push(next);
                v.push_back(next); // 그룹 표시
            }

        }
    }
    if (hole) // 구멍인 경우
    {
        for (int i = 0; i < v.size(); i++) // 그룹에 공기 표시하기
        {
            gps now = v[i];
            air[now.y][now.x] = 1;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n >> m;
    int cnt = 0; // 남은 치즈의 수
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == 1)cnt++;
        }
    }
    int ans = 0; // 걸리는 시간
    int last = 0; // 1시간전 치즈의 수
    while (cnt) // 치즈가 다 녹을떄 까지
    {
        last = cnt; // 녹기전 치즈수 갱신
        memset(visit, 0, sizeof(visit)); // 초기화
        memset(air, 0, sizeof(air));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (map[i][j] == 1)continue;
                if (visit[i][j] == 1)continue;
                aircheck({ i,j }); // 맵을돌며 구멍 체크
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (map[i][j] == 1) // 치즈라면
                {
                    for (int d = 0; d < 4; d++)
                    {
                        gps now = { i + yy[d],j + xx[d] };
                        if (air[now.y][now.x]) // 4방향중 공기가 있는경우
                        {
                            map[i][j] = 0; // 녹는다
                            cnt--; // 치즈수 감소
                            break;
                        }
                    }
                }
            }
        }
        ans++; // 시간 갱신
    }
    cout << ans << "\n" << last;

    return 0;
}
