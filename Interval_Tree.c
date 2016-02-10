#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct list{
    int data;
    struct list *next;
};

struct node{
    int l,u,h,count;
    struct list *top;
    struct node *left,*right;
};
int lower[100],upper[100],size;
struct node *root;
int max(int a,int b)
{
    return (a>b)?a:b;
}
int intersect(struct node *head,struct node *N)
{
   return ((head->u>N->l && head->l<=N->l) || (head->l<=N->l && head->u>N->l) || (head->l>=N->l && N->u>=head->u));
}
void insert_list(struct  list **head,int i)
{
    struct list *key=(struct list *)malloc(sizeof(struct list));
    struct list *prev=*head;
    key->data=i;
    key->next=NULL;
    if(*head==NULL)
    {
        *head=key;
        return;
    }
    else
    {
        while(prev->next!=NULL)
            prev=prev->next;
        prev->next=key;
        return;
    }
}
void insert_interval_tree(struct node *head,int i)
{ 
    
    if(i<(head->u) && i>=(head->l))
    {
        insert_list(&head->top,i);
        return;
    }
    else if(i<(head->l))
        return insert_interval_tree(head->left,i);
    else
        return insert_interval_tree(head->right,i);    
}
void generate_random(int n,int l,int u)
{
    int r,i,a,width=u-l;
    time_t t; 
    srand((unsigned) time(&t));
    srand((unsigned) time(&t)+n);
 //   printf("\tOK1\n");
    for(i=0;i<n;i++) 
    { 
        srand((unsigned) time(&t)+i);
        a=rand()%width;
        a+=l;            
        insert_interval_tree(root,a);
    } 
    return ;
}
void create_interval(int l,int u,int n,int start)
{
    float step=1.0*(u-l)/n;
    int last=n,i;
    if(step-(int)step!=0)
    {
        step=(int)ceil(step);
        last=floor(1.0*(u-l)/step);      
    } 
    for(i=0+start;i<last+start;i++)
    {     
        lower[i]=l+step*(i-start);
        upper[i]=l+step*(i+1-start);            
    }
    if(n-last!=0)
        create_interval(upper[i-1],u,n-last,i);

}
int update_height(struct node *head)
{
    if(head==NULL)
        return 0;
    else
    {
        head->h=max(update_height(head->left),update_height(head->right))+1;
        return head->h;
    }
}
struct node * create_interval_tree(int start,int end)
{
    struct node *head=(struct node *)malloc(sizeof(struct node ));
    head->l=lower[(start+end)/2]; 
    head->left=NULL;    
    head->top=NULL;
    head->u=upper[(start+end)/2]; 
    head->right=NULL;   
    head->h=0;head->count=0;
    if(((start+end)/2)-start>0)
        head->left=create_interval_tree(start,(start+end)/2-1);
    if(end-((start+end)/2)>0)
        head->right=create_interval_tree((start+end)/2+1,end);
    return head;
}

void pretty_print (struct node *head)
{
    if(head==NULL)
        return;
    int i;
    pretty_print(head->left);
    for(i=0;i<head->h;i++)
        printf("\t");
    printf("[%d,%d] ",head->l,head->u);
    struct list *a=head->top;
   // printf("fal %d",a==NULL);
    while(a!=NULL)
    {
        printf("%d ",a->data);
        a=a->next;
    }
    printf("\n");
    pretty_print(head->right);
}
void subtree(struct node *N,struct node *head)
{
    if(head==NULL)
        return;
    else if(head->u<N->l)
        subtree(N,head->right);
    else if(head->l>N->u)
        subtree(N,head->left);
    else if(head->l>=N->l && N->u>=head->u)
    {
        struct list *a=head->top;
        if(a!=NULL)
        {
            while(a!=NULL)
            {
                insert_list(&N->top,a->data);
                a=a->next;
            }
        }
        subtree(N,head->left);
        subtree(N,head->right);
    }
    else if(head->u>=N->l)
    {
        struct list *a=head->top;
        if(a!=NULL)
        {
            while(a!=NULL)
            {
                if(a->data>N->l)
                    insert_list(&N->top,a->data);
            }
        }
        head->u=N->l-1;
        head->right=NULL;
        N->left=head;
        subtree(N,head->right);
    }
    else
    {
        struct list *a=head->top;
        if(a!=NULL)
        {
            while(a!=NULL)
            {
                if(a->data<N->u)
                    insert_list(&N->top,a->data);
            }
        }
        head->l=N->u+1;
        head->left=NULL;
        N->right=head;
        subtree(N,head->left);
    }
    
}
void merge(struct node *head,int l,int u)
{
    struct node *N=(struct node *)malloc(sizeof(struct node)),*parent=head,*present=head;
    N->u=u;    N->l=l;
    N->top=NULL; N->left=NULL; N->right=NULL;
    int flag=0,dir=0;
    if(intersect(head,N))
        flag=1;
    else
    {
        while(1)
        {
            if(intersect(present,N))
                break;
            else if(N->l>present->u)
            {
                parent=present;
                present=present->right;
                dir=2;
            }
            else
            {
                parent=present;
                present=present->left;
                dir=1;
            }        
        }
    }
    subtree(N,head);
    if(flag==0 && dir==1)
        parent->left=N;
    else if(flag==0 && dir==2)
        parent->right=N;
    else if(flag==1)
        head=N;
    return;
}
int main()
{
    int l,u,n,i;
    float step;
//    printf("Enter lower limit, upper limit and number of intervals :");
    scanf("%d %d %d",&l,&u,&n);
    create_interval(l,u,n,0);
    root=create_interval_tree(0,n-1);
    step=(int)update_height(root);
    pretty_print(root);
  //  printf("Enter the number i ");
    scanf("%d",&i);
    generate_random(i,l,u);
    pretty_print(root);
    scanf("%d %d",&l,&u);
    merge(root,l,u);
    pretty_print(root);
    
     //   pretty_print(root);
    return 0;
}
