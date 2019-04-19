#include<cstdio>
#include<iostream>
#include<cstring>
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define INF 0x7f7f7f7f
using namespace std;
int nColumns,nRows;
int start_x,start_y,goal_x,goal_y;
int ans = INF;
int Map[25][25];

void solve(int x,int y,int step) {
    if(step > 10) return;
    for(int dir=0; dir<4; dir++) {
        if(dir == UP) {
            if(x-1 >= 0 && Map[x-1][y] != 1) {
                bool flag = true;
                for(int i=x-1; i>=0; i--) {
                    if(Map[i][y] == 1) {
                        flag = false;
                        Map[i][y] = 0;
                        solve(i+1,y,step+1);
                        Map[i][y] = 1;
                    }
                    if(!flag) break;
                    if(Map[i][y] == 3)
                        ans = min(ans,step);
                }
            }
        }
        if(dir == DOWN) {
            if(x+1 < nRows && Map[x+1][y] != 1) {
                bool flag = true;
                for(int i=x+1; i<nRows; i++) {
                    if(Map[i][y] == 1) {
                        flag = false;
                        Map[i][y] = 0;
                        solve(i-1,y,step+1);
                        Map[i][y] = 1;
                    }
                    if(!flag) break;
                    if(Map[i][y] == 3)
                        ans = min(ans,step);
                }
            }
        }
        if(dir == LEFT) {
            if(y-1 >= 0 && Map[x][y-1] != 1) {
                bool flag = true;
                for(int j=y-1; j>=0; j--) {
                    if(Map[x][j] == 1) {
                        flag = false;
                        Map[x][j] = 0;
                        solve(x,j+1,step+1);
                        Map[x][j] = 1;
                    }
                    if(!flag) break;
                    if(Map[x][j] == 3)
                        ans = min(ans,step);
                }
            }
        }
        if(dir == RIGHT) {
            if(y+1 < nColumns && Map[x][y+1] != 1) {
                bool flag = true;
                for(int j=y+1; j<nColumns; j++) {
                    if(Map[x][j] == 1) {
                        flag = false;
                        Map[x][j] = 0;
                        solve(x,j-1,step+1);
                        Map[x][j] = 1;
                    }
                    if(!flag) break;
                    if(Map[x][j] == 3)
                        ans = min(ans,step);
                }
            }
        }
    }

}


int main() {
    while(scanf("%d%d",&nColumns,&nRows) == 2 && nColumns|nRows) {
        for(int i=0; i<nRows; i++)
            for(int j=0; j<nColumns; j++) {
                scanf("%d",&Map[i][j]);
                if(Map[i][j] == 2) {
                    start_x = i;
                    start_y = j;
                }
                if(Map[i][j] == 3) {
                    goal_x = i;
                    goal_y = j;
                }
            }
        ans = INF;
        solve(start_x,start_y,1);
        if(ans == INF) puts("-1");
        else printf("%d\n",ans);
    }
    return 0;
}

