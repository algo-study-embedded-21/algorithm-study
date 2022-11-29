#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string.h>
using namespace std;

struct gps { int y, x; };

vector<int> map[4][4]; 
vector<int> cmap[4][4]; // ���� ���� ��
vector<int> mvmap[4][4]; // ����� �̵� ��
vector<gps> shpath; // �� ������ ���
vector<gps> path; // dfs ���
int smell[4][4]; // ������
int visit[4][4]; // dfs visit
int outfish; // ���ڿ��� ���ܵǴ� ����� ��
int m, s;
gps sh; // ����� ��ġ

int yy[8] = { 0,-1,-1,-1,0,1,1,1 }; // ��:2,��:6,��0,��:4
int xx[8] = { -1,-1,0,1,1,1,0,-1 };

int shdir[4] = { 2, 0, 6, 4 }; // �����Ͽ� ������ ��� �̵� �迭 �ε���

void copy(int finish) // ��� ���� finish = 0 �϶� ���� ���� , 1�϶� �����Ϸ�
{
    if (!finish)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                cmap[i][j].clear();
                for (int n = 0; n < map[i][j].size(); n++)
                {
                    cmap[i][j].push_back(map[i][j][n]);
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int n = 0; n < cmap[i][j].size(); n++)
                {
                    map[i][j].push_back(cmap[i][j][n]);
                }
            }
        }
    }
}

void move() // ����� �̵�
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            vector<int> tmp;
            for (int n = 0; n < map[i][j].size(); n++)// �ʿ� �ִ� ����� �� ��ŭ
            {
                int dd = map[i][j][n];
                int flag = 1;
                for (int d = 0; d < 8; d++) // 8����
                {
                    int dr = (8 + dd - d) % 8; // �ݽð����
                    gps mv = { i + yy[dr],j + xx[dr] };
                    if (mv.y < 0 || mv.y>3 || mv.x < 0 || mv.x>3)continue;
                    if (smell[mv.y][mv.x]> 0)continue;
                    if (mv.y == sh.y && mv.x == sh.x)continue;
                    mvmap[mv.y][mv.x].push_back(dr);
                    flag = 0; // ����Ⱑ �̵�������
                    break;
                }
                if (flag)tmp.push_back(dd); // �̵����� �ʾҴٸ� �ٽ� ���ڸ��� �־��ֱ� ���� tmp�� ���
            }
            for (int n = 0; n < tmp.size(); n++) // �̵����� ����� ����ġ
            {
                mvmap[i][j].push_back(tmp[n]);
            }
        }
    }
    for (int i = 0; i < 4; i++) // �̵������� ���� �� ������
    {
        for (int j = 0; j < 4; j++)
        {
            map[i][j] = mvmap[i][j];
            mvmap[i][j].clear();
        }
    }
}

void dfs(int level,gps mvsh,int cnt) // ��� �̵���� ã��
{
    if (level == 3)
    {
        if (cnt > outfish) // ���� ���� ����⸦ ���ܽ�ų�� �ִ°��
        {
            outfish = cnt;
            shpath = path;
        }
        return;
    }
    for (int i = 0; i < 4; i ++)
    {
        int d = shdir[i]; // �����Ͽ� �ε���
        gps next = { mvsh.y + yy[d],mvsh.x + xx[d] };
        if (next.y < 0 || next.y>3 || next.x < 0 || next.x>3)continue;
        if (visit[next.y][next.x] == 1) // �ߺ��� ��ġ�� �̵����������� ���ܵǴ� ������ �ߺ� ����
        {
            path.push_back(next);
            dfs(level + 1, next, cnt);
            path.pop_back();
        }
        else
        {
            cnt += map[next.y][next.x].size();
            path.push_back(next);
            visit[next.y][next.x] = 1;
            dfs(level + 1, next, cnt);
            path.pop_back();
            cnt -= map[next.y][next.x].size();
            visit[next.y][next.x] = 0;
        }
    }
}

void shmove() // ��� �̵�
{
    for (int i = 0; i < shpath.size(); i++) // ã�� ��η� �����̱�
    {
        gps now = shpath[i];
        if (map[now.y][now.x].size() > 0)
        {
            smell[now.y][now.x] = 3; // ���ʿ� 3���� ����, ������ ���� �ֱ� ���� 1���� �Ǵܰ���
            map[now.y][now.x].clear();
        }
    }
    sh = shpath[2]; // ������ ����� ��ġ
    shpath.clear();
    for (int i = 0; i < 4; i++) // ������ �����ִ� ���� -1
    {
        for (int j = 0; j < 4; j++)
        {
            if(smell[i][j]>0)smell[i][j] -= 1;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> m >> s;
    for (int i = 0; i < m; i++)
    {
        int x, y, d;
        cin >> x >> y >> d;
        map[x-1][y-1].push_back(d-1);
    }
    int x, y;
    cin >> x >> y;
    sh = { x-1,y-1 };
    for (int i = 0; i < s; i++)
    {
        copy(0);
        move();
        outfish = -1;
        shpath.clear();
        dfs(0,sh,0);
        shmove();
        copy(1);
    }
    int ans = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ans += map[i][j].size();
        }
    }
    cout << ans;

    return 0;
}