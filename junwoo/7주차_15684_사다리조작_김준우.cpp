#include <iostream>

using namespace std;

int N, M, H;
bool MAP[31][11];
int cnt; 
bool flag = false;
 
void dfs(int y, int ladder){
    if(cnt == ladder){
        bool possible = true;
        for (int i = 1; i <= N; i++){
            int ny = i;
            for (int j = 0; j < H; j++){
                int nx = j;
 
                if(MAP[nx][ny]){
                    ny++;
                }else if(ny > 1 && MAP[nx][ny - 1]){
                    ny--;
                }
            }
            if(ny != i){
                possible = false; 
                break;
            }
        }
        if(possible){
            flag = true; 
        }
        return;
    }

    for (int i = y; i < H;i++){
        for (int j = 1; j < N; j++){
            if(!MAP[i][j-1] && !MAP[i][j] && !MAP[i][j+1]){
                MAP[i][j] = true;
                dfs(i, ladder + 1); 
                MAP[i][j] = false; 
            }
        }
    }
    return;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie();

    cin >> N >> M >> H;
 
    for (int i = 0; i < M; i++){   
        int a, b;
        cin >> a >> b;
        MAP[a-1][b] = true;
    }
 
    for (int i = 0; i <= 3; i++){
        cnt = i;
        dfs(0, 0);
        if(flag){
            cout << cnt << endl;
            return 0;
        }
    }
 
    cout << -1 << endl;
    return 0;
}