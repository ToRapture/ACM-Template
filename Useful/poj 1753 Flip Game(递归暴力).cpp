/*2015/3/24
Memory(KB) 668
Time(ms) 47
�������Ͼ�д����90%����������һ���ǳ��޴��Ĵ��󣬵����ҿ���һ�� = =
�����õĵݹ� + λ���㣬�뷨Ҳ�ܼ� = =��
*/
#include<cstring>
#include<iostream>
#include<cstdio>
#define BLACK 65535     //ʮ��λ����1��Ӧ��ʮ������
#define WHITE 0         //ʮ��λ����0��Ӧ��ʮ������
#define INF 0x7f7f7f7f
using namespace std;

int state;
int minFlips = INF;     //��С�Ĳ��������ȸ�ֵΪ�����޴�

void flip(int i) {      //��ת��i����ĺ���,ÿ�η�ת�󶼻�ı�state��ֵ
    int temp = 0;
    temp |= 1<<i;
    if(i%4 != 0) temp |= 1<<(i-1);
    if((i+1)%4 != 0) temp |= 1<<(i+1);
    if(i+4 < 16) temp |= 1<<(i+4);
    if(i-4 >= 0) temp |= 1<<(i-4);
    state ^= temp;
}
void solve(int n,int nFlips) {      //n������η�ת���ǵ�n����n��0��ʼ��nFlips�����ܹ���ת�Ĵ���,nFlipsҲ���㿪ʼ
    if(n == 15) {       //�ݹ���ڣ�����ת���15�������Ժ�����ݹ�
        flip(n);        //���µ�15�����ӣ�Ȼ���ж��Ƿ���һɫ��
        if(state == BLACK || state == WHITE)
            if(nFlips + 1 < minFlips) minFlips = nFlips + 1;
        flip(n);        //�����Ǹ����Ӱ���һ�£��൱��ȡ���ղŵ���Ϊ��Ȼ���ж����û�а��µ�15�����Ӷ�Ӧ��state
        if(state == BLACK || state == WHITE)
        if(nFlips < minFlips) minFlips = nFlips;
    }
    else {
        flip(n);    //���µ�n�����ӣ�����+1����ȥ�����n+1������
        solve(n+1,nFlips+1);
        flip(n);    //��n������û�а��£������n+1������
        solve(n+1,nFlips);
    }
}

int main() {
    minFlips = INF;
    state = 0;
    int nChars = 0;
    char ch;
    while(nChars != 16) {
        ch = getchar();
        if(ch == 'w' || ch == 'b') {    //���״̬Ϊ111111...1111111��ô���һ��1�����һλ
            if(ch == 'b') state |= 1<<nChars;
            nChars++;
        }
    }
    solve(0,0); //�ӵ�0λ��ʼ��
    if(minFlips == INF) cout<<"Impossible"<<endl;
    else cout<<minFlips<<endl;
    return 0;
}


