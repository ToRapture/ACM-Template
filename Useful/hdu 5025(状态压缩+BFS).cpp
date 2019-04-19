#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#define M 105
#define mt(a,b) memset(a,b,sizeof(a))
using namespace std;
int n,nKeys;
int sx,sy;      //�������
int cnt;        //������
struct node {
    int x,y;
    int key,snake,time;         //�ߵ�״̬�ö����Ʊ�ʾ
    friend bool operator < (node A,node B) {
        return A.time > B.time;
    }
    node(int xx,int yy,int k,int s,int t) {     //���캯��
        x = xx, y = yy, key = k, snake = s, time = t;
    }

};
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
char pic[M][M];
bool vis[M][M][15][35];     //�࿪����ά����¼Կ���뱻ɱ���ߵ�״̬
struct SNAKE {
    int x,y;
} s[10];
priority_queue<node>q;      //��Ϊ�ᴦ���ߣ�����ʹ�����ȶ���
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
                continue;       //�ж��Ƿ�(���� || �Ƿ� || �ظ�)
            if(pic[now.x][now.y] >= '1' && pic[now.x][now.y] <= '9') {      //����Կ��
                int KEY = pic[now.x][now.y] - '1';          //�������Կ����Ӧ���õ�
                if(KEY == now.key) now.key++;
            }
            else if(pic[now.x][now.y] == 'S') {     //������
                for(int i=0; i<cnt; ++i) {      //Ѱ���ǵڼ�����
                    if(now.x == s[i].x && now.y == s[i].y) {
                        if(!(now.snake & 1<<i))     //�����״̬��������û��ɱ��
                            now.time++, now.snake |= 1<<i;      //��¼״̬
                        break;
                    }
                }
            }
            vis[now.x][now.y][now.key][now.snake] = true;
            q.push(now);
        }
    }
    return -1;      //ʧ��
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
