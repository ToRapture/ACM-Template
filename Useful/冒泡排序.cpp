#include<stdio.h>

void swap(int &x, int &y)
{
    x ^= y ^= x ^= y;
}

int main()
{
    int n;
    int a[100];
    while(~scanf("%d",&n))
    {
        for(int i=0; i<n; i++)
            scanf("%d",&a[i]);

        for(int i=0; i<n-1; i++)
            for(int j=0; j<n-1-i; j++)
                if(a[j]>a[j+1]) swap(a[j],a[j+1]);

        for(int i=0; i<n; i++)
            printf("%d ",a[i]);
        puts("");
    }
    return 0;
}
