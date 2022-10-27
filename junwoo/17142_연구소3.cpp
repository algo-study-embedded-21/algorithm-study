#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;

struct node{
    int x;
    int y;
};

int N,M;
int MAP[51][51];
int visited[51][51];
vector<node> viruses;
vector<node> selected;
bool used[10];
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
int minval = 2134567890,maxval;

void init(){
    memset(visited,0,sizeof(visited));
    maxval = -2134567890;
}

void flood(vector<node> v){
    queue<node> q;

    for(node i : v){
        q.push(i);
        visited[i.x][i.y] = 1;
    }

    while(!q.empty()){
        node now = q.front();
        q.pop();

        for(int i = 0; i < 4; i++){
            int nx = now.x + dx[i];
            int ny = now.y + dy[i];

            if(nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if(MAP[nx][ny]) visited[nx][ny] = -1;
            if(visited[nx][ny] != 0) continue;

            visited[nx][ny] = visited[now.x][now.y] + 1;
            q.push({nx,ny});
        }
    }
}

int check(){
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(visited[i][j] == 0) return 1;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            maxval = max(maxval,visited[i][j]);
    
    return 0;
}

void dfs(int vi){
    if(vi == M){
        init();
        flood(selected);
        if(check() == 1) return;
        minval = min(minval,maxval);
        return;
    }

    for(int i = 0; i < viruses.size(); i++){
        used[i] = true;
        selected.push_back(viruses[i]);
        dfs(vi + 1);
        selected.pop_back();
        used[i] = false;
    }
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie();

    cin >> N >> M;

    int flag = 0;

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++){
            cin >> MAP[i][j];

            if(MAP[i][j] == 2)
                viruses.push_back({i,j});
            if(!MAP[i][j])
                flag = 1;
        }
    
    if(!flag){
        cout << 0 <<'\n';
        return 0;
    }
    
    dfs(0);

    if(minval == 2134567890) cout << -1 << '\n';
    else cout << minval - 1<< '\n';
}