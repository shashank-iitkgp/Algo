#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct particle
{
    float x,y,vx,vy,rad,time;
    char color[10];
    
};
struct coll_queue
{
    float tim;
    int p1,p2; 
    
};
struct particle par[1050];
int earlier_random=0;
int t1=23;
int generate_random(int param)
{
    time_t t;
    srand((unsigned) time(&t));
    srand((unsigned) time(&t)+ rand()+rand()%100 +rand()%1000);
    srand((unsigned) time (&t)+ earlier_random+t+rand()%10000 +rand()%(10+earlier_random)+param+t1++);
    int a;
    if(param==1)
        a=1+rand()%100;
    else if(param==2)
        a=1+rand()%10;
    else if(param==3)
        a=1+rand()%5;
    else
        a=1+rand()%20;
    earlier_random=a;
    if(rand()%2==0 && param!=4 && param!=3)
        a=-a;
    return a;
}
float dot(float x1,float y1,float x2,float y2)
{
    //printf("Dot product is %f \n",x1*x2+y1*y2 );
  return (x1*x2+y1*y2);
}
int collide(float rx1,float ry1,float vx1,float vy1,float rad1,float rx2,float ry2,float vx2,float vy2,float rad2,float *t)
{
    float d;
    d=pow(dot(vx1-vx2,vy1-vy2,rx1-rx2,ry1-ry2),2)-dot(vx1-vx2,vy1-vy2,vx1-vx2,vy1-vy2)*(dot(rx1-rx2,ry1-ry2,rx1-rx2,ry1-ry2)-pow(rad1+rad2,2));
    if(dot(vx1-vx2,vy1-vy2,rx1-rx2,ry1-ry2)>=0 || d<0 )
        return 0;
    else
    {
        *t=-(dot(vx1-vx2,vy1-vy2,rx1-rx2,ry1-ry2)+pow(d,0.5))/(dot(vx1-vx2,vy1-vy2,vx1-vx2,vy1-vy2));
        //printf("The particles are colliding after %f \n",*t);
        return 1;   
    }
}
void print_state(int size,float tim)
{
    int i;
    //printf("\t%d %f \n",size,tim);
    for(i=0;i<size;i++)
        printf("The generated particle %d after %f seconds is at (%f,%f) with velocity %f i + %f j having radius %f \n",i,tim,par[i].x,par[i].y,par[i].vx,par[i].vy,par[i].rad );
}
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
void min_heapify(struct coll_queue priority_queue[],int i,int n)
{
    int smallest;
    struct coll_queue temp;
    if(lchild(i)<=n && priority_queue[lchild(i)].tim<priority_queue[i].tim)
        smallest=lchild(i);
    else
        smallest=i;
    if(rchild(i)<=n && priority_queue[rchild(i)].tim<priority_queue[smallest].tim)
        smallest=rchild(i);
    if(smallest!=i)
    {
        //printf("\t%d swap %d\n",i,largest);
        temp=priority_queue[smallest];
        priority_queue[smallest]=priority_queue[i];
        priority_queue[i]=temp;
        min_heapify(priority_queue,smallest,n);
    }
    return;
}
void build_minheap(struct coll_queue priority_queue[],int n)
{
    int i;
    for(i=n/2;i>0;i--)
        min_heapify(priority_queue,i,n);
    return;
}
int update_queue(struct coll_queue priority_queue[],int size)
{
    int i,j,size1=1,collision=0;
    float t;
    for(i=0;i<size;i++)
        for(j=i+1;j<size;j++)
        {
            if(i==j)
                continue;
            else
            {
                priority_queue[size1].p1=i;
                priority_queue[size1].p2=j;
                priority_queue[size1].tim=10000.0;
                if(collide(par[i].x,par[i].y,par[i].vx,par[i].vy,par[i].rad,par[j].x,par[j].y,par[j].vx,par[j].vy,par[j].rad,&t))
                {
                        priority_queue[size1].tim=t;
                        collision++;
                        printf("Particle %d and %d collide after %fseconds\n",priority_queue[size1].p1,priority_queue[size1].p2,priority_queue[size1].tim );
                }
                size1++;                
            }
        }
    //printf("The number of colliding particles are : %d \n",collision );
    build_minheap(priority_queue,size1-1);/*
    printf("The queue contains\n");
    for(i=1;i<size1;i++)
        printf("Particle %d and %d collide after %fseconds\n",priority_queue[i].p1,priority_queue[i].p2,priority_queue[i].tim );
    printf("\n");*/

}
void after_collision(int i,int j)
{
    float mass1=pow(par[i].rad,3),mass2=pow(par[i].rad,3),vx_n,vy_n,vx_t,vy_t,v1_n,v1_t,v2_n,v2_t,unit_vector,v1_new_n,v2_new_n;
    unit_vector=pow(pow(par[i].x-par[j].x,2)+pow(par[i].y-par[j].y,2),0.5);
    vx_n=(par[i].x-par[j].x)/unit_vector; 
    vy_n=(par[i].y-par[j].y)/unit_vector;
    vx_t=-vy_n;
    vy_t=vx_n;
    v1_n=dot(vx_n,vy_n,par[i].vx,par[i].vy);
    v2_n=dot(vx_n,vy_n,par[j].vx,par[j].vy);
    v1_t=dot(vx_t,vy_t,par[i].vx,par[i].vy);
    v2_t=dot(vx_t,vy_t,par[j].vx,par[j].vy);
    v1_new_n=(v1_n*(mass1-mass2)+2*mass2*v2_n)/(mass1+mass2);
    v2_new_n=(v2_n*(mass2-mass1)+2*mass1*v1_n)/(mass1+mass2);
    par[i].vx=vx_n*v1_new_n+vx_t*v1_t;
    par[i].vy=vy_n*v1_new_n+vy_t*v1_t;
    par[j].vx=vx_n*v2_new_n+vx_t*v2_t;
    par[j].vy=vy_n*v2_new_n+vy_t*v2_t;
    printf("After collision data of particle %d is %f i + %f j \n",i,par[i].vx,par[i].vy);
    printf("After collision data of particle %d is %f i + %f j \n",j,par[j].vx,par[j].vy);
}
void simulate(struct coll_queue priority_queue[],int size)
{
    float interval,present=0;
    int i;
    while(priority_queue[1].tim!=10000.0)
    {
        //printf("The priority time is %f \n",priority_queue[1].tim );
        interval=priority_queue[1].tim;
        //printf("Particles colliding are %d and %d\n",priority_queue[1].p1,priority_queue[1].p2 );
        for(i=0;i<size;i++)
        {
            par[i].x=par[i].x+par[i].vx*interval;
            par[i].y=par[i].y+par[i].vy*interval;
            //printf("Updated position for %d is (%f,%f) \n",i,par[i].vx,par[i].vy);
            
        }
        after_collision(priority_queue[1].p1,priority_queue[1].p2);
        present+=interval;
        print_state(size,present);
        update_queue(priority_queue,size);
        

    }
}
int main()
{
    int size1,i,size2=0;
    
    struct coll_queue priority_queue[1050];   
    priority_queue[1].tim=10000.0;
    printf("Enter the number of particles\n");   /*scanf("%d",&size1);*/size1=generate_random(4);
    printf("The number of particles generated are %d\n",size1); 
    for(i=0;i<size1;i++)
    {
        par[i].x=1.0*generate_random(1); par[i].y=1.0*generate_random(1);
        par[i].vx=1.0*generate_random(2); par[i].vy=1.0*generate_random(2);
        par[i].rad=1.0;//*generate_random(3);
        //scanf("%f %f %f %f %f",&par[i].x,&par[i].y,&par[i].vx,&par[i].vy,&par[i].rad);
        printf("The generated particle is at (%f,%f) with velocity %f i + %f j having radius %f \n",par[i].x,par[i].y,par[i].vx,par[i].vy,par[i].rad );
    }
    //print_state(size1,0);
    update_queue(priority_queue,size1);
    simulate(priority_queue,size1);
    return 0;
    
}
