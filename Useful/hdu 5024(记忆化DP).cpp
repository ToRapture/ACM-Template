#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define M 105
using namespace std;
int dx[] = {0, -1, 0, 1, -1, 1, 1, -1};     ///˳����Ҫ
int dy[] = {-1, 0, 1, 0, -1, -1, 1, 1};
int n;
int ans;
char pic[M][M];
int dp[M][M][8];
///DFS����:��(x,y)����������dir��������ǰ����������,����(x,y)��
int dfs(int x,int y,int dir) {
    if(~dp[x][y][dir])
        return dp[x][y][dir];
     if((x + dx[dir] >= 0 && x + dx[dir] < n && y + dy[dir] >= 0 && y + dy[dir] < n) && pic[x + dx[dir]][y + dy[dir]] == '.')
        return dp[x][y][dir] = 1 + dfs(x + dx[dir],y + dy[dir],dir);
    else
        return dp[x][y][dir] = 1;
}
///������(x,y)Ϊֱ�ǹյ㣬(����dir1����ǰ���������� + ����dir2����ǰ���������� -1)
void caclu(int x,int y,int dir1,int dir2) {
    ans = max(ans,dfs(x,y,dir1) + dfs(x,y,dir2) - 1);
}
int main() {
    while(~scanf("%d",&n) && n) {
        ans = 0;
        /**
          ��ʼ�����̣�dp[][][]��ʼ��Ϊ0Ҳ����
        */
        memset(pic,0,sizeof(pic));
        memset(dp,-1,sizeof(dp));
        for(int i=0; i<n; ++i)
            scanf("%s",pic[i]);
        for(int i=0; i<n; ++i)
            for(int j=0; j<n; ++j)
                if(pic[i][j] == '.')     ///��ÿһ���Ϸ���Ϊֱ�ǹյ㣬����8��ֱ�ǣ�����������
                    for(int k=0; k<4; ++k) {
                            /*  .......
                                .
                                .
                                .  ������ֱ�� ����������
                            */
                        caclu(i,j,k % 4,(k+1) % 4);
                        /*
                                .
                              .   .
                            .       .
                          .           .  ������ֱ��  ����������
                        */
                        caclu(i,j,4 + (k % 4),4 + (k+1) % 4);
                        ///����caclu����û���Ⱥ��ϵ�����������dx[],dy[]�����й�
                    }
        printf("%d\n",ans);
    }
    return 0;
}
