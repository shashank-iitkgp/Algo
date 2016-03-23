#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct node
{
	int key,degree,mark;
	struct node *p,*left,*right,*child;	
};
struct heap
{
	struct node *min;
	int n;
	
};
struct heap *Make_Fib_Heap()
{
	struct heap *H=(struct heap *)malloc(sizeof(struct heap));
	H->n=0;
	H->min=NULL;
	return H;
}
void print_list(struct node *present,struct node *head)
{
	printf("Node: %d Child %d\t",present->key,present->degree );
	if(present!=head)
		print_list(present->right,head);
	return;
		

}
void Fib_Heap_Insert(struct heap *H,struct node *x)
{
	x->degree=0;
	x->p=NULL;
	x->child=NULL;
	x->mark=0;
	if(H->min==NULL)
	{
		x->left=x;
		x->right=x;
		H->min=x;
	}
	else
	{
		H->min->right->left=x;
		x->left=H->min;
		x->right=H->min->right;
		H->min->right=x;
		if(x->key<H->min->key)
			H->min=x;
	}
	H->n++;
}
struct heap *Fib_Heap_Union(struct heap *H1,struct heap *H2)
{
	struct heap *H=Make_Fib_Heap();
	if(H1->min!=NULL && H2->min!=NULL)
	{
		H->min=H1->min;
		H->min->left->right=H2->min->right;
		H2->min->right->left=H->min->left;
		H->min->left=H2->min;
		H2->min->right=H->min;
		if((H1->min==NULL) || ((H2->min!=NULL) && (H2->min->key<H1->min->key)))
			H->min=H2->min;

	}
	else if(H1->min!=NULL)
		H->min=H1->min;
	else if(H2->min!=NULL)
		H->min=H2->min;
	H->n=H1->n+H2->n;
	return H;

}
void Fib_Heap_Link(struct heap *H,struct node *y,struct node *x)
{
	y->left->right=y->right;
	y->right->left=y->left;
	y->p=x;
	y->right=y;
	y->left=y;
	if(x->child!=NULL)
	{
		y->right=x->child->right;
		y->left=x->child;
		x->child->right->left=y;
		x->child->right=y;
	}
	else
	{
		y->right=y;
		y->left=y;
	}
	x->child=y;
	x->degree++;
	y->mark=0;
	// printf("Heap link\n");
	// print_list(x,x->left);
}
void consolidate(struct heap *H)
{
	int Dn=(int)floor(log10(H->n-1)/log10(2));
//	printf("node is %d \n",H->n );
	int i;
	struct node **A=(struct node **)malloc((Dn+1)*sizeof(struct node *)),*arr[10000];
	for(i=0;i<=Dn;i++)
		A[i]=NULL;
//	printf("Working\n");
	struct node *w=H->min,*x,*tmp,*y,*buf,*z;
	int d,num=0,k=0;
	if(H->min!=NULL)
	{
		num++;
		arr[num-1]=H->min;
		while(w!=H->min->left)
		{
			num++;
			buf=w->right;
			w=buf;
			arr[num-1]=w;
		}
	}
	/*
	z=H->min;
	for(k=0;k<num;k++)
	{
		//printf("%d \n",z->key );
		z=z->right;
	}*/
//	printf("Nodes in root list are %d\n",num );
	w=H->min;
//	printf("w %d\n",w->key);
	for(k=0;k<num;k++)
	{
		x=arr[k];
		d=x->degree;
		while(A[d]!=NULL)
		{
			y=A[d];
			if(x->key>y->key)
			{	
				buf=x;
				x=y;
				y=buf;
			}			
			Fib_Heap_Link(H,y,x);
			//printf("X-> %d with %d and Y-> %d with %d \n",x->key,x->degree,y->key,y->degree );
			A[d]=NULL;
			d++;
		}
		A[d]=x;
		//printf("Loop A[d]=%d   \n",x->key);
		tmp=x->right;
		w=tmp;
	}
	H->min=NULL;
	for(i=0;i<=Dn;i++)
	{
		//printf("Loop 2\n");
		if(A[i]!=NULL)
		{
			if(H->min==NULL)
			{
//				printf("Root list  %d with %d children \n",A[i]->key,A[i]->degree);
				A[i]->left=A[i];
				A[i]->right=A[i];
				H->min=A[i];
			}
			else
			{
//				printf("Root list  %d with %d children \n",A[i]->key,A[i]->degree);
				H->min->right->left=A[i];   				//	H->min->right->left=x;
				A[i]->left=H->min;							//	x->left=H->min;
				A[i]->right=H->min->right;					//	x->right=H->min->right;
				H->min->right=A[i];							//	H->min->right=x;
				if(A[i]->key<H->min->key)					//	if(x->key<H->min->key)
					H->min=A[i];							//		H->min=x;

			}

		}
	}
///	printf("The min is %d\n",H->min->key );
}
struct node * Fib_Heap_Extract_Min(struct heap *H)
{
	struct node *z=H->min,*temp,*x,*y,*w=H->min->child,*buf; int i,num=H->min->degree;
//	int num=0,i;
	//printf("ddddd%d \n",H->min->key );
/*	if(w!=NULL)
	{
		num++;
		while(w!=H->min->child->left)
		{
			num++;
			buf=w->right;
			w=buf;
		}
	}
	printf("The number of children of %d are %d \n",H->min->key,num );
*/  
	if(z!=NULL)
	{
		y=H->min->child;
		for(i=0;i<num;i++)
		{
			x=y;
			y=y->right;
			H->min->right->left=x;
			x->right=H->min->right;
			x->left=H->min;
			H->min->right=x;
			x->p=NULL;	
		}
		z->right->left=z->left;
		z->left->right=z->right;
		//printf("If condition %d\n",z==z->right )
		if(z==z->right)
			H->min=NULL;
		else
		{
			H->min=z->right;
			//printf("Round of %d \n",z->key );
			//print_list(H->min,H->min->left);
			consolidate(H);
		}
		H->n--;
	}
	return z;/*
	struct node *z=H->min;
	if(z)
	{
		if(z==z->right)
		{
			H->min=z->child;
			consolidate(H);
		}
		else
		{
			if(z->child==NULL)
			{
				z->left->right=z->right;
				z->right->left=z->left;
				H->min=z->right;
				consolidate(H);
			}
			else
			{
				z->left->right=z->child;
				z->right->left=z->child->left;
				z->child->left->right=z->right;
				z->child->left=z->left;
				H->min=z->right;
				consolidate(H);
			}
		}
		H->n--;
	}
	return z;*/
}
void Cut(struct heap *H,struct node *x,struct node *y)
{
	if(x==x->right)
		y->child=NULL;
	else
	{
		x->left->right=x->right;
		x->right->left=x->left;
	}
	y->degree--;
	H->min->right->left=x;
	x->right=H->min->right;
	x->left=H->min;
	H->min->right=x;
	x->p=NULL;
	x->mark=0;
}
void Cascade_Cut(struct heap *H,struct node *y)
{
	struct node *z=y->p;
	if(z!=NULL)
	{
		if(y->mark==0)
			y->mark=1;
		else
		{
			Cut(H,y,z);
			Cascade_Cut(H,z);
		}
	}
}
void Fib_Heap_Decrease_Key(struct heap *H,struct node *x,int k)
{
	if(k>x->key)
		printf("Error! New key is bigger than current\n");
	else
	{
		x->key=k;
		struct node *y=x->p;
		if (y!=NULL &&  (x->key<y->key))
		{
			Cut(H,x,y);
			Cascade_Cut(H,y);
		}
		if(x->key<H->min->key)
			H->min=x;
	}
}
int main()
{
	int k,a[20][1000],i,m,j;
	struct heap *Master,*List;
	struct node *new;
	printf("Enter the number of lists K \n" );
	scanf("%d",&k);
	printf("Enter the total numbers present in each block M\n");
	scanf("%d",&m);
	printf("Enter the numbers of each block in sorted order\n");
	for(i=0;i<k;i++)
		for(j=0;j<m;j++)
			scanf("%d",&a[i][j]);
	Master=Make_Fib_Heap();
	for(i=0;i<k;i++)
	{
		List=Make_Fib_Heap();
		for(j=0;j<m;j++)
		{
			new=(struct node *)malloc(sizeof(struct node));
			new->key=a[i][j];
			Fib_Heap_Insert(List,new);
		}
		if(i==0)
			Fib_Heap_Decrease_Key(List,new,List->min->key-1);
		else
			Fib_Heap_Decrease_Key(List,new,Master->min->key-1);
		Master=Fib_Heap_Union(Master,List);
	}		
	printf("The merged list is :\n");
	for(i=0;i<k*m;i++)
		printf("%d ",Fib_Heap_Extract_Min(Master)->key );
	printf("\n");
	return 0;
}