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
int bfs(struct graph *G)
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
     return search;



}
void print_path(struct graph *G,int start,int end)
{
    if(start==end)
        printf("%d->",start);
    else if(G->parent[end]==100)
        printf("path doesnt exist");
    else
    {
        print_path(G,start,G->parent[end]);        /*recursively prints parent pointers*/
        printf("%d->",end);
    }

}
int main()
{
    int i,j;
    struct graph *G;
    G=(struct graph *)malloc(sizeof(struct graph));
    j=bfs(G);
    for(i=1;i<=G->ver;i++)
        printf("%d\n",G->dist[i]);
    scanf("%d",&i);
    print_path(G,j,i);
    return 0;
}
