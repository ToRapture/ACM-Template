/*
    Time  Memory
    343ms 6412KB
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<queue>
#define M 1010
#define INF 0x3f3f3f3f

using namespace std;
int dist[M][M];    //记录地图各店岩浆的最早到达时间
bool vis[M][M];
char pic[M][M];
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
int n,m;

struct node {
    int x,y,step;
} s;

queue<node>q;

bool ok(node x) {
    return x.x >= 0 && x.x < n && x.y >= 0 && x.y < m;
}
void init() {       //将原图转换为新图
    while(!q.empty()) {
        node pre = q.front();
        dist[pre.x][pre.y] = pre.step;
        q.pop();
        for(int i=0; i<4; ++i) {
            node now = pre;
            now.x += dx[i];
            now.y += dy[i];
            now.step++;
            if(ok(now) && now.step < dist[now.x][now.y]) {
                q.push(now);
                dist[now.x][now.y] = now.step;
            }
        }
    }
}
bool bfs() {
    while(!q.empty()) q.pop();
    memset(vis,false,sizeof(vis));
    q.push(s);
    vis[s.x][s.y] = true;
    while(!q.empty()) {
        node pre = q.front();
        q.pop();
//        if(pic[pre.x][pre.y] == 'E') return true;     //该句不加也可以AC
        for(int i=0; i<4; ++i) {
            node now = pre;
            now.x += dx[i];
            now.y += dy[i];
            now.step++;
            if(pic[now.x][now.y] == 'E' && now.step <= dist[now.x][now.y]) return true; //如果岩浆在到达改点之后到达，该点为终点
            if(ok(now) && !vis[now.x][now.y] && now.step < dist[now.x][now.y]) {        //如果岩浆在到达该点之后到达，该点不为终点，岩浆会覆盖他，故不能走这个点
                q.push(now);
                vis[now.x][now.y] = true;
            }
        }
    }
    return false;
}

int main() {
    int T;
    while(cin >> T) {
        while(T--) {
            cin >> n >> m;
            memset(dist,INF,sizeof(dist));
            while(!q.empty()) q.pop();

            for(int i=0; i<n; ++i) {
                cin >> pic[i];
                for(int j=0; j<m; ++j) {
                    if(pic[i][j] == 'S') {
                        s.x = i;
                        s.y = j;
                        s.step = 0;
                    }
                    else if(pic[i][j] == '!') {
                        node temp;
                        temp.x = i, temp.y = j, temp.step = 0;
                        q.push(temp);
                    }
                    else if(pic[i][j] == '#') {
                        dist[i][j] = 0;
                    }
                }
            }
            init();
            puts(bfs() ? "Yes" : "No");
        }
    }
    return 0;
}
