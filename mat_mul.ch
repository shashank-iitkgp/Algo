#include<stdio.h>
int summation(int a[],int b[],int n)
{
    int i,sum=0;
for(i=0;i<n;i++)
        sum=sum+b[i]*a[i];
return sum;
}
main()
{
    int i,j,m,n,r,p,k;
    do
    {
        printf("Enter the size of the first matrix\n");
        scanf("%d %d",&m,&n);
        printf("Enter the size of the second matrix\n");
        scanf("%d %d",&r,&p);
    }
while(r!=n);
        int a[m][n],b[r][p],d[n],e[n],c[m][p];
        for(i=0;i<m;i++)
            for(j=0;j<n;j++)
            scanf("%d",&a[i][j]);
for(i=0;i<r;i++)
            for(j=0;j<p;j++)
            scanf("%d",&b[i][j]);
        for(i=0;i<m;i++)
            for(j=0;j<p;j++)
        {
                for(k=0;k<n;k++)
                    d[k]=a[i][k];
                for(k=0;k<n;k++)
                    e[k]=b[k][j];
        c[i][j]=summation(d,e,n);
        }
        for(i=0;i<m;i++)
            {for(j=0;j<p;j++)
               printf("%4d",c[i][j]);
             printf("\n");}
}

