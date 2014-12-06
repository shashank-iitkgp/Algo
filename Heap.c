#include<stdio.h>
#include<stdlib.h>
int parent(int i)
{
    return i/2;
}
int lchild(int i)
{
    return 2*i;
}
int rchild(int i)
{
    return 2*i+1;
}
void maxheapify(int a[],int i,int n)
{
    int largest;
    if(lchild(i)<=n && a[lchild(i)]>a[i])
        largest=lchild(i);
    else
        largest=i;
    if(rchild(i)<=n && a[rchild(i)]>a[largest])
        largest=rchild(i);
    if(largest!=i)
    {
        //printf("\t%d swap %d\n",i,largest);
        a[i]=a[i]+a[largest];
        a[largest]=a[i]-a[largest];
        a[i]=a[i]-a[largest];
        maxheapify(a,largest,n);
    }
    return;
}
void build_maxheap(int a[],int n)
{
    int i;
    for(i=n/2;i>0;i--)
        {
            maxheapify(a,i,n);
        }
    return;

}
void heapsort(int a[],int n)
{
    int i;
    build_maxheap(a,n);
    for(i=n;i>=2;i--)
    {
        a[1]=a[1]+a[i];
        a[i]=a[1]-a[i];
        a[1]=a[1]-a[i];
        maxheapify(a,1,--n);

    }
}
int main()
{
    int n,*a,i,j;
    scanf("%d",&n);
    a=(int *)malloc((n+1)*sizeof(int));
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    heapsort(a,n);
    for(i=1;i<=n;i++)
        printf("%d ",a[i]);

}
