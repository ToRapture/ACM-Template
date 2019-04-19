const int BUF=40000000;
char Buf[BUF],*buf=Buf;
const int OUT=20000000;
char Out[OUT],*ou=Out;int Outn[30],Outcnt;
inline void write(int x){
  if(!x)*ou++=48;
  else{
    for(Outcnt=0;x;x/=10)Outn[++Outcnt]=x%10+48;
    while(Outcnt)*ou++=Outn[Outcnt--];
  }
}
inline void writell(ll x){
  if(!x)*ou++=48;
  else{
    for(Outcnt=0;x;x/=10)Outn[++Outcnt]=x%10+48;
    while(Outcnt)*ou++=Outn[Outcnt--];
  }
}
inline void writechar(char x){*ou++=x;}
inline void writeln(){*ou++='\n';}
inline void read(int&a){for(a=0;*buf<48;buf++);while(*buf>47)a=a*10+*buf++-48;}


//这句话放到代码中
fread(Buf,1,BUF,stdin);

//样例
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int BUF=40000000;
char Buf[BUF],*buf=Buf;
const int OUT=20000000;
char Out[OUT],*ou=Out;int Outn[30],Outcnt;
inline void write(int x){
  if(!x)*ou++=48;
  else{
    for(Outcnt=0;x;x/=10)Outn[++Outcnt]=x%10+48;
    while(Outcnt)*ou++=Outn[Outcnt--];
  }
}
inline void writell(ll x){
  if(!x)*ou++=48;
  else{
    for(Outcnt=0;x;x/=10)Outn[++Outcnt]=x%10+48;
    while(Outcnt)*ou++=Outn[Outcnt--];
  }
}
inline void writechar(char x){*ou++=x;}
inline void writeln(){*ou++='\n';}
inline void read(int&a){for(a=0;*buf<48;buf++);while(*buf>47)a=a*10+*buf++-48;}

int main(){
    fread(Buf,1,BUF,stdin);
    int a,b;
    read(a),read(b);
    write(a+b);
    writeln();
    fwrite(Out,1,ou-Out,stdout);
}