#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

struct node{
    int x,y,dir;        
};
node tmp;
int dx[8]={0,-1,-1,-1,0,1,1,1};
int dy[8]={-1,-1,0,1,1,1,0,-1};
node fish[17];
int result=0;
int arr[4][4];

void move_fish(){
    for(int i=1;i<17;i++){
        int cx = fish[i].x;
        int cy = fish[i].y;
        int cd = fish[i].dir;

        if(cd==-1) continue; 
            int nx,ny;
            int nd = cd;
        for(int j=0;j<8;j++){
            nx = cx+dx[nd];
            ny = cy+dy[nd];
            if(nx>=0 && ny>=0 && nx<4 && ny<4){
                int idx = arr[ny][nx];
                if(idx==0){ 
                    nd = (nd+1)%8;
                    continue;
                }
                
                arr[ny][nx] = i;
                fish[i].x = nx;
                fish[i].y = ny;
                fish[i].dir = nd;
                
                arr[cy][cx] = idx;
                fish[idx].x = cx;
                fish[idx].y = cy;
                
                break;
            }
            nd = (nd+1)%8;
        }
    }
}

void dfs(int y, int x, int dir, int sum){
    node fdup[17];
    int dup[4][4];
    
    for(int i=1;i<17;i++)
        fdup[i] = fish[i];
    
    memcpy(dup,arr,sizeof(dup));
    
    move_fish();
    
    int nx = x;
    int ny = y;
    
    while(1){
        nx+=dx[dir];
        ny+=dy[dir];
    
        if(nx>=0 && ny>=0 && nx<4 && ny<4){
    
            int idx = arr[ny][nx];
    
            if(idx==-1)   continue;   
            int fd = fish[idx].dir;
    
            fish[idx].dir = -1;
            arr[y][x] = -1;
            arr[ny][nx] = 0;
    
            dfs(ny,nx,fd,sum+idx);
    
            fish[idx].dir = fd;
            arr[y][x] = 0;
            arr[ny][nx] = idx;
        }
        else break;
    }
    result = max(result,sum);
    
    memcpy(arr,dup,sizeof(dup));
    for(int i=1;i<17;i++)
        fish[i] = fdup[i];
    return;
}

int main() {
    int a, b,val;
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++){
            cin>>a>>b;
            arr[i][j]=a;
            fish[a].x=j;
            fish[a].y=i;
            fish[a].dir=b-1;
        }
    val = arr[0][0];
    int sd = fish[val].dir;
    fish[val].dir=-1;
    arr[0][0]=0;
 
    dfs(0,0,sd,val);   
 
    cout << result << '\n';
 
    return 0;
}