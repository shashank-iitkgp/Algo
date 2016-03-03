#include <stdio.h>
#include <stdlib.h>

struct node
{
	int exec_time,height,priority,process_id;
	int color;
	struct node *left,*right,*parent;
	
};

void update_height(struct node *root);
void inorder(struct node *root);
FILE *fp;
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
//	printf("\t Left Rotate\n");
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
//	printf("\tRight Rotate\n");
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
struct node *insert(struct node **root,int data)
{
	struct node *new=(struct node *)malloc(sizeof(struct node));
	new->exec_time=data;
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
			if(new->exec_time>pres->exec_time)
				pres=pres->right;
			else
				pres=pres->left;
		}
		new->parent=pres_parent;
		if(pres_parent->exec_time>new->exec_time)
			pres_parent->left=new;
		else
			pres_parent->right=new;
	}
	new->color=1;
	Fix_Insert(root,new);
    return new;
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
	if(v!=NULL)
		v->parent=u->parent;	
}
void Fix_Delete(struct node **root,struct node *x)
{
	struct node *w;
//	printf("in\n");
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
				//printf("%d\n",w->data );
				w->color=x->parent->color;
				x->parent->color=0;
				if(w->right!=NULL)
					w->right->color=0;
				Left_Rotate(root,x->parent);
				break;
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
				break;
			}

		}
	}
	x->color=0;
}
void delete(struct node **root,struct node *z)
{
	struct node *y=z,*x,*dummy_parent;
	int original=y->color,flag=0,lefty=0,righty=0;/*
	if(z==*root && z->left==NULL && z->right==NULL)
		*root=NULL;*/
	if(z==*root)
		*root=NULL;
	else if(z->left==NULL)
    {
    //	printf("left\n");
        x=z->right;
        if(x==NULL)
        {
        	flag=1;
        	x=(struct node *)malloc(sizeof(struct node));
        	x->left=x->right=NULL;
        	x->color=0;
        	x->parent=z;
        	z->right=x;
        	dummy_parent=z->parent;
        	if(z->parent->right==z)
        		righty=1;
        	else 
        		lefty=1;
        }
        transplant(root,z,z->right);
    }
    else if(z->right==NULL)
    {
    //	printf("right\n");
    	x=z->left;
        if(x==NULL)
        {
        	flag=1;
        	x=(struct node *)malloc(sizeof(struct node));
        	x->left=x->right=NULL;
        	x->parent=z;
        	x->color=0;
        	z->left=x;
        	dummy_parent=z->parent;
        	if(z->parent->right==z)
        		righty=1;
        	else
        		lefty=1;    
        }
    	transplant(root,z,z->left);
    }
    else
    {
    //	printf("z %d\n",z->right->data);
    	y=tree_min(z->right);
    	
    	original=y->color;
    	x=y->right;
        if(x==NULL)
        {
        	flag=1;
        	x=(struct node *)malloc(sizeof(struct node));
        	x->left=x->right=NULL;
        	
        	x->color=0;
        	y->right=x;
            if(y->parent==z)
            {
                x->parent=y;	
            	dummy_parent=y;
            }
            else
            {
            	x->parent=y->parent;
            	dummy_parent=y->parent;
            }
        	if(y->parent->right==y)
        		righty=1;
        	else
        		lefty=1;
        }
    //	printf("dd %d \n",y->data);
    	if(y->parent!=z)
    	{
    	//	printf("dafda\n");
    		transplant(root,y,y->right);
    		y->right=z->right;
    		y->right->parent=y;
    	}
    //	printf("add\n");
    	transplant(root,z,y);
    	y->left=z->left;
    	y->left->parent=y;
    	y->color=z->color;
    	free(z);
    	
    }
    if(original==0)
    	Fix_Delete(root,x);
    if(flag==1)
    {

    	x->left=x->right=NULL;
    	x->parent=NULL;/*
    	if(x->parent->left==x)
    		x->parent->left=NULL;
    	else if(x->parent->right==x)
    		x->parent->right=NULL;*/
    	x=NULL;
    //    printf("\thhf %d %d %d\n",dummy_parent->data,lefty,righty );
        if(lefty==1)
        	dummy_parent->left=NULL;
        else
        	dummy_parent->right=NULL;
        //printf("misssss %d\n",dummy_parent->data );
    	free(x);
    }
	
}

void update_height(struct node *root)
{
	//printf("ff %d \n",root->data);
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
      //  printf("dd %d\n",root->data );
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
		fprintf(stdout,"\t");
	fprintf(stdout,"%d %d\n",root->exec_time,root->color);
	inorder(root->right);
}
int earlier_random=0;
int uniq[1010]={0},present=0,pid=1;
long int t=0;

int generate_random(int exec)
{
	time_t t;
	srand((unsigned) time(&t));
	srand((unsigned) time(&t)+ rand()+rand()%100 +rand()%1000);
	srand((unsigned) time (&t)+ earlier_random+t+rand()%10000);
	if(exec==1)
	{
		int a;
		while(1)
		{
			a=1+rand()%1000;
			if(uniq[a]==0)
			{
				uniq[a]=1;
				break;
			}
		}
		earlier_random=a;
		return a;
	}
	else if(exec==0)
		return 1+rand()%4;
	else if(exec==2)
		return rand();

}
struct node * smallest_node(struct node *head)
{
	if(head->left==NULL)
		return head;
	return smallest_node(head->left);
}
int total_process(struct node *head)
{
	if(head==NULL)
		return 0;
	else if(head->left==NULL && head->right==NULL)
		return 1;
	else if(head->left==NULL)
		return total_process(head->right)+1;
	else if(head->right==NULL)
		return total_process(head->left)+1;
	else
		return total_process(head->left)+total_process(head->right)+1;
}
void process_creator(int N,int M,struct node **root)
{
	if(present<M)
	{
		int i,process_created,less;
		less=((M-present)<(N-total_process(*root)))?(M-present):(N-total_process(*root));
		process_created=generate_random(2)%(less)+1;
		fprintf(stdout,"%ld:\tCreated %d processes\n",t,process_created );		
		struct node *new_process;
		present+=process_created;
		for(i=0;i<process_created;i++)
		{
			new_process=insert(root,generate_random(1));
			new_process->priority=generate_random(0);
			new_process->process_id=pid;
			fprintf(stdout,"%ld:\tInserted process in the tree:\tP_Id:%d Execution time: %d Priority: %d \n",t,pid++,new_process->exec_time,new_process->priority);
		}
		printf("The process structure looks like \n");
		update_height(*root);
		inorder(*root);
	}
}
void process_scheduler(int N,int M,struct node **root)
{
	int done=0,remaining_time,pres_priority,pres_pid;
	long int i;
	struct node *smallest,*process_exec;
	while(done<M)
	{
		process_creator(N,M,root);/*
		//fprintf(fp,"Running process creator again %d\n",*root==NULL );
		if(done==M-2)
		{
			for(i=t;i<t+(*root)->exec_time;i=i+50*(*root)->priority)
			{
				fprintf(fp,"%ld:\t Process Scheduled %d\n",i,(*root)->process_id );
				fprintf(fp,"%ld:\t Process Preempted %d\n",i+50*(*root)->priority,(*root)->process_id );
			}
			fprintf(fp,"%ld:\t Process %d finished execution \n",t+(*root)->exec_time,(*root)->process_id );
			break;
		}*/

	    smallest=smallest_node(*root);
        fprintf(stdout,"%ld:\tProcess Scheduled is %d \n",t,smallest->process_id);
        if(smallest->exec_time>50*smallest->priority)
        {
        	t+=50*smallest->priority;
        	fprintf(stdout,"%ld:\tProcess Preempted is %d \n",t,smallest->process_id);
        	remaining_time=smallest->exec_time-50*smallest->priority;
        	pres_priority=smallest->priority;
        	pres_pid=smallest->process_id;
        //	printf("ddddd\n");
        	delete(root,smallest);
        	process_exec=insert(root,remaining_time);
        	process_exec->priority=pres_priority;
        	process_exec->process_id=pres_pid;
        }
        else
        {
        	t+=smallest->exec_time;
        	fprintf(stdout,"%ld:\tProcess %d finished execution \n",t,smallest->process_id);
        	delete(root,smallest);
        	done++;
        }
        
	}
}
int main()
{
	fp=fopen("output.txt","w");
	struct node *root=NULL;
	int n,m,i;
	fprintf(stdout,"Enter the maximum number of live processes N\n");
	scanf("%d",&n);
	fprintf(stdout,"Enter total number of processes M to be completed\n");
	scanf("%d",&m);
	fprintf(stdout, "TIME\t DESCRIPTION\n");
	process_scheduler(n,m,&root);
	fclose(fp);
	return 0;
}