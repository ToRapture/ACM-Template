#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#define M 105
#define mt(a,b) memset(a,b,sizeof(a))
using namespace std;
int n,nKeys;
int sx,sy;      //起点坐标
int cnt;        //蛇总数
struct node {
    int x,y;
    int key,snake,time;         //蛇的状态用二进制表示
    friend bool operator < (node A,node B) {
        return A.time > B.time;
    }
    node(int xx,int yy,int k,int s,int t) {     //构造函数
        x = xx, y = yy, key = k, snake = s, time = t;
    }

};
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
char pic[M][M];
bool vis[M][M][15][35];     //多开了两维，记录钥匙与被杀的蛇的状态
struct SNAKE {
    int x,y;
} s[10];
priority_queue<node>q;      //因为会处理蛇，所以使用优先队列
bool ok(node A) {
    return (A.key == nKeys && pic[A.x][A.y] == 'T');
}
int bfs(int x,int y) {
    while(!q.empty()) q.pop();
    vis[x][y][0][0] = true;
    q.push(node(x,y,0,0,0));
    while(!q.empty()) {
        node pre = q.top();
        q.pop();
        if(ok(pre)) return pre.time;
        for(int dir=0; dir<4; ++dir) {
            node now(pre.x+dx[dir],pre.y+dy[dir],pre.key,pre.snake,pre.time+1);
            if(!(now.x >= 0 && now.y >= 0 && now.x < n && now.y < n) || pic[now.x][now.y] == '#' || vis[now.x][now.y][now.key][now.snake])
                continue;       //判断是否(出界 || 非法 || 重复)
            if(pic[now.x][now.y] >= '1' && pic[now.x][now.y] <= '9') {      //遇到钥匙
                int KEY = pic[now.x][now.y] - '1';          //并且这把钥匙是应该拿的
                if(KEY == now.key) now.key++;
            }
            else if(pic[now.x][now.y] == 'S') {     //遇到蛇
                for(int i=0; i<cnt; ++i) {      //寻找是第几条蛇
                    if(now.x == s[i].x && now.y == s[i].y) {
                        if(!(now.snake & 1<<i))     //如果该状态下这条蛇没被杀死
                            now.time++, now.snake |= 1<<i;      //记录状态
                        break;
                    }
                }
            }
            vis[now.x][now.y][now.key][now.snake] = true;
            q.push(now);
        }
    }
    return -1;      //失败
}
int main() {
    while(cin>>n>>nKeys && n|nKeys) {
        mt(pic,0);
        mt(vis,0);
        mt(s,0);
        cnt = 0;
        for(int i=0; i<n; ++i) {
            cin>>pic[i];
            for(int j=0; j<n; ++j) {
                if(pic[i][j] == 'K') sx = i,sy = j;
                else if(pic[i][j] == 'S') s[cnt].x = i,s[cnt].y = j,cnt++;
            }
        }
        int ans = bfs(sx,sy);
        ~ans ? cout<<ans<<endl : cout<<"impossible"<<endl;
    }
    return 0;
}
