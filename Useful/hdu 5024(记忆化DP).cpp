#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define M 105
using namespace std;
int dx[] = {0, -1, 0, 1, -1, 1, 1, -1};     ///顺序重要
int dy[] = {-1, 0, 1, 0, -1, -1, 1, 1};
int n;
int ans;
char pic[M][M];
int dp[M][M][8];
///DFS返回:从(x,y)出发，沿着dir方向所能前进的最大距离,包括(x,y)点
int dfs(int x,int y,int dir) {
    if(~dp[x][y][dir])
        return dp[x][y][dir];
     if((x + dx[dir] >= 0 && x + dx[dir] < n && y + dy[dir] >= 0 && y + dy[dir] < n) && pic[x + dx[dir]][y + dy[dir]] == '.')
        return dp[x][y][dir] = 1 + dfs(x + dx[dir],y + dy[dir],dir);
    else
        return dp[x][y][dir] = 1;
}
///计算以(x,y)为直角拐点，(沿着dir1方向前进的最大距离 + 沿着dir2方向前进的最大距离 -1)
void caclu(int x,int y,int dir1,int dir2) {
    ans = max(ans,dfs(x,y,dir1) + dfs(x,y,dir2) - 1);
}
int main() {
    while(~scanf("%d",&n) && n) {
        ans = 0;
        /**
          初始化过程，dp[][][]初始化为0也可以
        */
        memset(pic,0,sizeof(pic));
        memset(dp,-1,sizeof(dp));
        for(int i=0; i<n; ++i)
            scanf("%s",pic[i]);
        for(int i=0; i<n; ++i)
            for(int j=0; j<n; ++j)
                if(pic[i][j] == '.')     ///以每一个合法点为直角拐点，遍历8种直角，并获得最大结果
                    for(int k=0; k<4; ++k) {
                            /*  .......
                                .
                                .
                                .  这样的直角 ↓↓↓↓↓
                            */
                        caclu(i,j,k % 4,(k+1) % 4);
                        /*
                                .
                              .   .
                            .       .
                          .           .  这样的直角  ↓↓↓↓↓
                        */
                        caclu(i,j,4 + (k % 4),4 + (k+1) % 4);
                        ///两个caclu函数没有先后关系，方向参数与dx[],dy[]数组有关
                    }
        printf("%d\n",ans);
    }
    return 0;
}
