#include<stdio.h>
#include<stdlib.h>
struct graph{
   int adj[100][100],color[100],dist[100],parent[100],ver,edj;
};
void enqueue(int Q[],int x,int *tail,int size)
{
    Q[*tail]=x;
    if(*tail==size-1)
       *tail=0;
    else
       (*tail)++;
    return;

}
int dequeue(int Q[],int *head,int *tail,int size)
{
    int res;
    res=Q[*head];
    if(*head==*tail)
       res=0;
    if(*head==size-1)
       *head=0;
    else
       (*head)++;
    return res;

}
void bfs(struct graph *G)
{
     int i,j,search,head=0,tail=0,queue[100],u;
     for(i=0;i<100;i++)
     {
         G->color[i]=0;
         G->parent[i]=0;
         G->dist[i]=100;
         for(j=0;j<100;j++)
             G->adj[i][j]=0;
     }
     scanf("%d%d",&G->ver,&G->edj);
     while((G->edj)--)
     {
         scanf("%d%d",&i,&j);
         G->adj[i][j]=1;
         //G->adj[j][i]=1;
     }
     scanf("%d",&search);
     G->dist[search]=0;
     enqueue(queue,search,&tail,100);
     while(1)
     {
         u=dequeue(queue,&head,&tail,100);
         if(u==0)
           break;
         for(i=1;i<=G->ver;i++)
         {
             if(G->adj[u][i]==1)
             {
                if(G->color[i]==0)
                {
                   G->color[i]=1;
                   G->dist[i]=G->dist[u]+1;
                   G->parent[i]=u;
                   enqueue(queue,i,&tail,100);
                }
             }
             G->color[u]=2;
         }

     }



}
int main()
{
    int i,j;
    struct graph *G;
    G=(struct graph *)malloc(sizeof(struct graph));
    bfs(G);
    for(i=1;i<=G->ver;i++)
        printf("%d\n",G->dist[i]);
    return 0;
}
