#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
struct node
{
    int key; 
    long int left_sum,right_sum,root_sum;
    struct node *left,*right;
};
long int max(long int a,long int b)
{
    return (a>b)?a:b;
}
int step=1,last_random=0,count[20010]={0},flag=1;
long int maxi=-10100;
struct node *max_head;
float generate_random(int flag,int n)
{
    int r;
    float a;
    time_t t;
    srand((unsigned) time(&t)+last_random);
    srand((unsigned) time(&t)+n+step+last_random);
    if(flag==1)
    {
    
        while(1)
        {
            srand((unsigned) time(&t) +rand()%100 +1+n+step+last_random);
            a= (rand()%100 -rand()%100)*1.0;
            last_random=a;
            if(count[(int)a+10000]==0)
                break;
        }
        count[(int)a+10000]=1;
    }
    else
        a= (rand()%20  +40.0)/100.0;
//    if(flag==0)
 //       printf("\t %f %d  \n",a,flag);    
        
    return  a;
}
struct node* generate_tree(int no_of_nodes)
{
    step++;
    if(no_of_nodes==0)
        return NULL;
    float p=generate_random(0,no_of_nodes);
    int m=(int)ceil(p*(no_of_nodes-1));
    struct node *new;     
    new=(struct node *)malloc(sizeof(struct node)); step++;
    new->left=NULL;
    new->right=NULL;        new->left_sum=-1000;new->right_sum=-1000;new->root_sum=-1000;
    new->key=(int)generate_random(1,no_of_nodes);
    new->left=generate_tree(m);
    new->right=generate_tree(no_of_nodes-m-1);
    return new;    
}
void inorder(struct node *head)
{
    if(head==NULL)
        return ;
    inorder(head->left);
    printf("%d ",head->key);
    inorder(head->right);
}
void preorder(struct node *head)
{
    if(head==NULL)
        return;
    printf("%d ",head->key);
    preorder(head->left);
    preorder(head->right);
}
void postorder(struct node *head)
{
    if(head==NULL)
        return ;
    postorder(head->left);
    postorder(head->right);
    printf("%d ",head->key);
}
long int max_sum_root_leaf(struct node *head)
{
    if(head==NULL)
    {
        return 0;
    }
    if(head->right==NULL && head->left==NULL)
    {
        head->left_sum=head->right_sum=head->key;
        return head->key;
    }
    else if(head->right==NULL)
    {
        head->right_sum=-10000;
        head->left_sum=max_sum_root_leaf(head->left);
        return head->left_sum+head->key;       
    }
    else if(head->left==NULL)
    {
        head->left_sum=-10000;
        head->right_sum=max_sum_root_leaf(head->right);
        return head->right_sum+head->key;
    }
    else
    {
        head->left_sum=max_sum_root_leaf(head->left)+head->key,head->right_sum=max_sum_root_leaf(head->right)+head->key;
        if(head->left_sum>head->right_sum)
            return head->left_sum;
        else
            return head->right_sum;
    }
}
void print_key_root_leaf(struct node *head)
{
    if(head==NULL)
        return;
    else if(head->left==NULL && head->right==NULL)
    {
        printf("%d ",head->key);        
    }
    else if(head->left==NULL)
    {
        printf("%d ",head->key);
        print_key_root_leaf(head->right);
    }
    else if(head->right==NULL)
    {
        printf("%d ",head->key);
        print_key_root_leaf(head->left);
    }
    else
    {
        printf("%d ",head->key);
        if(head->left_sum>head->right_sum)
            print_key_root_leaf(head->left);
        else
            print_key_root_leaf(head->right);
    }
}
long int max_sum_all_path(struct node *head)
{
    if(head==NULL)
        return 0;
    head->left_sum=max_sum_all_path(head->left)+head->key;
    head->right_sum=max_sum_all_path(head->right)+head->key;
    head->root_sum=head->left_sum + head->right_sum - head->key;
    long int present=max(max(max(head->left_sum,head->right_sum),head->root_sum),head->key);
    if(present>maxi)
    {
        maxi=present;
        max_head=head;        
    }
    return max(max(head->left_sum,head->right_sum),head->key);
}
void print_key_max_path(struct node *head)
{
    long int present_max=max(max(head->left_sum,head->right_sum),head->key);
    printf("%d ",head->key);

    if(present_max==head->key)
        return;
    else if(present_max==head->left_sum)
        print_key_max_path(head->left);
    else
        print_key_max_path(head->right);
    
    
}
void print_key_max_root(struct node *head,struct node *root)
{    
    long int present_max=max(max(head->left_sum,head->right_sum),head->key);
    if(present_max==head->key)
    {
        printf("%d ",head->key);
        return;
    }
    else if(root==head)
        print_key_max_root(head->left,root);
    else
    {
        if(head->left_sum==present_max)
            print_key_max_root(head->left,root);
        else
            print_key_max_root(head->right,root);
        printf("%d ",head->key);
    }

}
int main()
{
    int n,sum=0,i;
    long int maximum;
    printf("Enter number of nodes in binary tree\n");
    scanf("%d",&n);
    struct node* head=generate_tree(n); printf("Inorder of the binary tree is:\n");
    inorder(head);   printf("\nPreorder of the binary tree is:\n");
    preorder(head);  printf("\nPostorder of the binary tree is:\n");
    postorder(head); printf("\n");
    printf("Maximum sum from root to leaf is %ld\n",max_sum_root_leaf(head));
    printf("The keys are along maximum sum path from root to leaf are :\n");
    print_key_root_leaf(head);
    maximum=max_sum_all_path(head);
    printf("\nThe maximum sum among all paths is %ld\n",maxi);
    printf("The keys along the maximum sum path from any 2 nodes are:\n");
    maximum=max(max(max_head->left_sum,max_head->right_sum),max_head->key);
    if(maxi==maximum)
        print_key_max_path(max_head);
    else
    {
        print_key_max_root(max_head,max_head);
        printf("%d ",max_head->key);
        print_key_max_path(max_head->right);
    }
    printf("\n");
    return 0;
}
