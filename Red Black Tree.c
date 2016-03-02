#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data,height;
	int color;
	struct node *left,*right,*parent;
	
};
int col(struct node *head)
{
	if(head==NULL)
		return 0;
	return head->color;
}
int max(int a,int b)
{
	return a>b?a:b;
}
void Left_Rotate(struct node **root,struct node *x)
{
	struct node *y=x->right;
	x->right=y->left;
	if(y->left!=NULL)
		y->left->parent=x;
	y->parent=x->parent;
	if(x->parent==NULL)
		*root=y;
	else if(x->parent->left==x)
		x->parent->left=y;
	else
		x->parent->right=y;
	y->left=x;
	x->parent=y;

}
void Right_Rotate(struct node **root,struct node *x)
{
	struct node *y=x->left;
	x->left=y->right;
	if(y->right!=NULL)
		y->right->parent=x;
	y->parent=x->parent;
	if(x->parent==NULL)
		*root=y;
	else if(x->parent->left==x)
		x->parent->left=y;
	else
		x->parent->right=y;
	y->right=x;
	x->parent=y;
}
/*void Fix_Insert(struct node **root,struct node *z)
{
    // iterate until z is not the root and z's parent color is red
    while (z != *root && z->parent->color == 1)
    {
        struct node *y;
        int col1;
        // Find uncle and store uncle in y
        if (z->parent == z->parent->parent->left)
            y = z->parent->parent->right;
        else
            y = z->parent->parent->left;
 
        // If uncle is RED, do following
        // (i)  Change color of parent and uncle as BLACK
        // (ii) Change color of grandparent as RED
        // (iii) Move z to grandparent
        if (y != NULL && y->color == 1) // correction
        {
            y->color = 0;
            z->parent->color = 0;
            z->parent->parent->color = 1;
            z = z->parent->parent;
        }
 
        // Uncle is BLACK, there are four cases (LL, LR, RL and RR)
        else
        {
            // Left-Left (LL) case, do following
            // (i)  Swap color of parent and grandparent
            // (ii) Right Rotate Grandparent
            if (z->parent == z->parent->parent->left &&
                z == z->parent->left)
            {
                col1 = z->parent->color ;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = col1;
                Right_Rotate(root,z->parent->parent);
				
            }
 
            // Left-Right (LR) case, do following
            // (i)  Swap color of current node  and grandparent
            // (ii) Left Rotate Parent
            // (iii) Right Rotate Grand Parent
            if (z->parent == z->parent->parent->left &&
                z == z->parent->right)
            {
                col1 = z->color ;
                z->color = z->parent->parent->color;
                z->parent->parent->color = col1;
                Left_Rotate(root,z->parent);
                Right_Rotate(root,z->parent); // correction
			//	continue; // correction
            }
 
            // Right-Right (RR) case, do following
            // (i)  Swap color of parent and grandparent
            // (ii) Left Rotate Grandparent
            if (z->parent == z->parent->parent->right &&
                z == z->parent->right)
            {
                col1= z->parent->color ;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = col1;
                Left_Rotate(root,z->parent->parent);
				//continue;
            }
 
            // Right-Left (RL) case, do following
            // (i)  Swap color of current node  and grandparent
            // (ii) Right Rotate Parent
            // (iii) Left Rotate Grand Parent
            if (z->parent == z->parent->parent->right &&
                z == z->parent->left)
            {
                col1 = z->color ;
                z->color = z->parent->parent->color;
                z->parent->parent->color = col1;
                Right_Rotate(root,z->parent);
                Left_Rotate(root,z->parent); // correction
				//continue; // correction
            } 
        }
    }
    (*root)->color = 0; //keep root always black
}*/
/*
void Fix_Insert(struct node **root, struct node *z)
{
    while(z!=*root && z->parent->color==1)
    {
        struct node *y;
        int col1;
        if(z->parent==z->parent->parent->left)
            y=z->parent->parent->right;
        else
            y=z->parent->parent->left;
        if(y->color==1)
        {
            y->color=0;
            z->parent->color=0;
            z->parent->parent->color=1;
            z=z->parent->parent;
        }
        else
        {
            if(z->parent==z->parent->parent->left && z==z->parent->left)
            {
                col1=z->parent->color;
                z->parent->color=z->parent->parent->color;
                z->parent->parent->color=col1;
                Right_Rotate(root,z->parent->parent);
                
            }
            if(z->parent==z->parent->parent->left && z->parent->right==z)
            {
                col1=z->color;
                z->color=z->parent->parent->color;
                z->parent->parent->color=col1;
                Left_Rotate(root,z->parent);
                Right_Rotate(root,z->parent->parent);
                
            }

            if(z->parent==z->parent->parent->right && z->parent->right==z)
            {
                col1=z->parent->color;
                z->parent->color=z->parent->parent->color;
                z->parent->parent->color=col1;
                Left_Rotate(root,z->parent->parent);
                
            }
            if(z->parent==z->parent->parent->right && z->parent->left==z)
            {
                col1=z->color;
                z->color=z->parent->parent->color;
                z->parent->parent->color=col1;
                Right_Rotate(root,z->parent);
                Left_Rotate(root,z->parent->parent);
                
            }
        }
    }
    (*root)->color=0;
}*/
void Fix_Insert(struct node **root,struct node *x)
{
	while(x!=*root && x->parent->color==1)
	{
		struct node *y;
		if(x->parent->parent->left==x->parent)
		{
			y=x->parent->parent->right;/*
			if(y==NULL)
			{
				x->parent->color=0;
				x->parent->parent->color=1;
				x=x->parent->parent;
			}*/
			if(y!=NULL && y->color==1)
			{
				x->parent->color=y->color=0;
				x->parent->parent->color=1;
				x=x->parent->parent;
			}
			else
			{
				if(x->parent->right==x)
				{
					x=x->parent;
					Left_Rotate(root,x);
				}
				x->parent->color=0;
				x->parent->parent->color=1;
				Right_Rotate(root,x->parent->parent);
			}

		}
		else
		{
			y=x->parent->parent->left;/*
			if(y==NULL)
			{
				x->parent->color=0;
				x->parent->parent->color=1;
				x=x->parent->parent;
			}*/
			if(y!=NULL && y->color==1)
			{
				x->parent->color=y->color=0;
				x->parent->parent->color=1;
				x=x->parent->parent;
			}
			else
			{
				if(x->parent->left==x)
				{
					x=x->parent;
					Right_Rotate(root,x);
				}
				x->parent->color=0;
				x->parent->parent->color=1;
				Left_Rotate(root,x->parent->parent);
			}
		}
	}
	(*root)->color=0;
	
}
void insert(struct node **root,int data)
{
	struct node *new=(struct node *)malloc(sizeof(struct node));
	new->data=data;
	new->height=0;
	new->left=new->right=new->parent=NULL;
	if(*root==NULL)
		*root=new;
	else
	{
		struct node *pres=*root,*pres_parent=NULL;
		while(pres!=NULL)
		{
			pres_parent=pres;
			if(new->data>pres->data)
				pres=pres->right;
			else
				pres=pres->left;
		}
		new->parent=pres_parent;
		if(pres_parent->data>new->data)
			pres_parent->left=new;
		else
			pres_parent->right=new;
	}
	new->color=1;
	Fix_Insert(root,new);
    
}
struct node *tree_min(struct node *head)
{
	if(head->left==NULL)
		return head;
	return tree_min(head->left);
}
void transplant(struct node **root,struct node *u,struct node *v)
{
	if(u->parent==NULL)
		*root=v;
	else if(u==u->parent->left)
		u->parent->left=v;
	else
		u->parent->right=v;
	v->parent=u->parent;	
}
void Fix_Delete(struct node **root,struct node *x)
{
	struct node *w;
	while(x!=*root && x->color==0)
	{
		if(x==x->parent->left)
		{
			w=x->parent->right;
			if(col(w)==1)
			{
				w->color=0;
				x->parent->color=1;
				Left_Rotate(root,x->parent);
				w=x->parent->right;
			}
			else if(col(w->left)==0 && col(w->right)==0)
			{
				w->color=1;
				x=x->parent;
			}
			else if(col(w->right)==0)
			{
				if(w->left!=NULL)
					w->left->color=0;
				w->color=1;
				Right_Rotate(root,w);
				w=x->parent->right;
			}
			else
			{
				w->color=x->parent->color;
				x->parent->color=0;
				if(w->right!=NULL)
					w->right->color=0;
				Left_Rotate(root,x->parent);
				*root=x;
			}

		}
		else
		{
			w=x->parent->left;
			if(col(w)==1)
			{
				w->color=0;
				x->parent->color=1;
				Right_Rotate(root,x->parent);
			}
			else if(col(w->left)==0 && col(w->right)==0)
			{
				w->color=1;
				x=x->parent;
			}
			else if(col(w->left)==0)
			{
				w->right->color=0;
				w->color=1;
				Left_Rotate(root,w);
				w=x->parent->left;
			}
			else
			{
				w->color=x->parent->color;
				x->parent->color=0;
				if(w->left!=NULL)
					w->left->color=0;
				Right_Rotate(root,x->parent);
				*root=x;
			}

		}
	}
	x->color=0;
}
void delete(struct node **root,struct node *z)
{
	struct node *y=z,*x;

	int original=y->color;

	if(z->left==NULL)
    {
    	printf("left\n");
        x=z->right;
        transplant(root,z,z->right);
    }
    else if(z->right==NULL)
    {
    	printf("right\n");
    	x=z->left;
    	transplant(root,z,z->left);
    }
    else
    {
    	//printf("else\n");
    	y=tree_min(z);
    	//printf("ddd\n");
    	original=y->color;
    	x=y->right;
    	//printf("dd\n");
    	if(y->parent==z)
    		x->parent=y;
    	else
    	{
    		transplant(root,y,y->right);
    		y->right=z->right;
    		y->right->parent=y;
    	}
    	transplant(root,z,y);
    	y->left=z->left;
    	y->left->parent=y;
    	y->color=z->color;
    }
    if(original==0)
    	Fix_Delete(root,x);
	
}

void update_height(struct node *root)
{
	if(root==NULL)
		return;
	if(root->left==NULL && root->right==NULL)
		root->height=1;
	else if(root->left==NULL)
    {
    	update_height(root->right);
    	root->height=root->right->height+1;
    }
    else if(root->right==NULL)
    {
    	update_height(root->left);
    	root->height=root->left->height+1;
    }
    else
    {
    	update_height(root->left);
    	update_height(root->right);
    	root->height=max(root->left->height,root->right->height)+1;
    }

}
void inorder(struct node *root)
{
	if(root==NULL)
		return;
	int i;
	inorder(root->left);
	for(i=0;i<root->height;i++)
		printf("\t");
	printf("%d %d\n",root->data,root->color);
	inorder(root->right);
}
int main()
{
	struct node *root=NULL;
	insert(&root,1);
	insert(&root,2);
	insert(&root,3);
	insert(&root,4);
	insert(&root,5);
	insert(&root,6);
	insert(&root,7);
	delete(&root,root);
    update_height(root);
	inorder(root);
	return 0;
}
