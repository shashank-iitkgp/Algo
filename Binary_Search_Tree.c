#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node *left;
    struct node *right;
};
struct node *find_node(struct node *head,int key)
{
    if(head->data>key)
       {
           if(head->left==NULL)
               return head;
           else
               return find_node(head->left,key);
       }
    else
    {
        if(head->right==NULL)
            return head;
        else
            return find_node(head->right,key);
    }
}
struct node *make_binary_search_tree(struct node *head)
{
    int j,flag=1;
    struct node *p,*q;
    while(1)
    {
        printf("Do you  want enter in BST\n");
        scanf("%d",&j);
        if(j==0)
            break;
        q=(struct node *)malloc(sizeof(struct node));
        q->right=NULL;
        q->left=NULL;
        scanf("%d",&q->data);
        if(flag)
            {
                head=q;
                flag=0;
            }
        else
        {
        p=find_node(head,q->data);
        if(p->data>q->data)
            p->left=q;
        else
            p->right=q;
        }
    }

    return head;
}
void inorder_tree_walk(struct node *head)
{
if(head!=NULL)
{
    inorder_tree_walk(head->left);
    printf("%d\n",head->data);
    inorder_tree_walk(head->right);
}
}
void preorder_tree_walk(struct node*head)
{
if(head!=NULL)
{
    printf("%d\n",head->data);
    preorder_tree_walk(head->left);
    preorder_tree_walk(head->right);
}
}
void postorder_tree_walk(struct node*head)
{
if(head!=NULL)
{
    preorder_tree_walk(head->left);
    preorder_tree_walk(head->right);
    printf("%d\n",head->data);
}
}
int main()
{
    int i=0;
    struct node *head,*p,*q;
    head=make_binary_search_tree(head);
    q=head;
    p=head;
    printf("Inorder\n");
    inorder_tree_walk(p);
    printf("Preorder\n");
    preorder_tree_walk(p);
    printf("Postorder\n");
    postorder_tree_walk(p);
    //printf("%d\n",i);
    return 0;
}