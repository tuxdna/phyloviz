#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<math.h>
#define TRUE 1
#define FALSE 0

struct node{
	struct node *prev,
		    *next,
		    *parent,
		    *child;
	char *label;
	float weight;
};
typedef struct node node;

// label variables
char label[100]={0};
int label_ptr=0;
int label_flag=FALSE;
//weight variables
char weight[100]={0};
int weight_ptr=0;
int weight_flag=FALSE;
FILE *fileptr;

int getnext()
{
	int c;
	while(isspace(c=fgetc(fileptr)));
	if(EOF==c)
	{
		fprintf(stderr,"End Of File encountered! Exiting...\n");
		exit(EXIT_FAILURE);
	}
	return c;
}

node *
get_new_node()
{
	node *tmp;
	tmp=(node*)malloc(sizeof(node));
	if(tmp==NULL)
	{
		fprintf(stderr,"Isufficient memory\n");
		exit(EXIT_FAILURE);
	}
	tmp->prev = tmp->next = tmp->parent = tmp->child = NULL;
	tmp->label  =NULL;
	tmp->weight =0.1;
	return tmp;
}

node * 
ph2iv()
{
	int c;	
	int depth=0;
	int i;
	
	node *root=NULL;
	node *n=NULL;
//	printf("%s\n","# Inventor V2.0 ascii");
//	printf("Separator");

	//E1: Start
	root = n = NULL;

	root=get_new_node();
	goto state1;

state1:
	c=getnext();
	
	if(c=='(')//E2: Create a subtree
	{
		//branch to child
		n=get_new_node();
		n->parent=root;
		if( NULL == root->child )
			root->child=n;
		root=n;	

/*		for(i=0;i<depth;++i)
			printf("\t");
		putchar('(');
		putchar('\n');
*/		depth++;
		goto state1;
	}
	else//E3: Create a node
	{
		//start the label
		label[0]='\0';
		label_ptr=0;

		ungetc(c, fileptr);	
		goto state2;
	}
state2:
	c=getnext();
	if(c==':')//E5:
	{
		//end the label
		label[label_ptr]='\0';

		root->label=malloc(strlen(label)+1);
		strcpy(root->label, label);

/*		for(i=0;i<depth;++i)
			printf("\t");
		printf("Label: %s\n",label);
*/
		//start weight
		weight[0]='\0';
		weight_ptr=0;

		goto state3;
	}
	else //E4:
	{
		//accumulate label text
		label[label_ptr++]=c;

		goto state2;
	}

state3:
	c=getnext();
	if(c==',')//E7:
	{
		//end weight
		weight[weight_ptr]='\0';

		root->weight=atof(weight);

		//create a new sibling
		n=get_new_node();
		n->prev=root;
		n->parent=root->parent;
		root->next=n;
		root=n;

/*		for(i=0;i<depth;++i)
			printf("\t");
		printf("Weight: %s\n", weight);
*/
		goto state1;
	}
	else if(c==')')//E8:
	{


		//end weight
		weight[weight_ptr]='\0';

		root->weight=atof(weight);

		//check parent!=NULL here
		if(NULL==root->parent)
		{
			printf("NULL at weight %s", weight);
		}
		root=root->parent;

/*		for(i=0;i<depth;++i)
			printf("\t");
		printf("Weight: %s\n", weight);
*/
		depth--;
/*		for(i=0;i<depth;++i)
			printf("\t");
		putchar(')');
		putchar('\n');
*/
		goto state4;
	}
	else//E6:
	{
		weight[weight_ptr++]=c;
		goto state3;
	}

state4:
	c=getnext();
	if(c==':')//E10:
	{
		//start weight
		weight[0]='\0';
		weight_ptr=0;

		goto state3;
	}
	else if(c==';')//E11:
	{
		goto state5;
	}
	else//E9:
	{
		
		goto state4;
	}

state5:
/*	printf("\nEOF\n");
*/
	return root;
}

int 
parse_tree(node *root, int depth)
{
	int i;
	node *tmp;
	if(NULL==root)
	{
		return;
	}

	//process root 

	if(NULL!=root->label) // leaf node
	{
		for(i=0;i<depth;++i)
			putchar(' ');
		printf("%s:%f\n",root->label,root->weight);
	}
	else //internal node
	{
		//print ( at current depth
		for(i=0;i<depth;++i)
			putchar(' ');	
		putchar('(');
		putchar('\n');

		//visit the first child
		parse_tree(root->child,depth+1);

		//print ) and weight at current depth
		for(i=0;i<depth;++i)
			putchar(' ');	
		putchar(')');
		printf(":%f\n",root->weight);
	}

	//process root->next
	parse_tree(root->next,depth);
}

int 
indentation(int depth)
{
	int i;
	for(i=0;i<depth;++i)
		printf("    ");
}

int 
parse2iv(node *root, int depth, int num_sibling, int curr_sibling)
{	
	float x,y;
	float theta;
	if(NULL==root)
	{
		return;
	}

	//process the node

	theta = curr_sibling * (M_PI/(num_sibling+1.0));
	x=cos(theta)*(root->weight);
	y=sin(theta)*(root->weight);

	if(NULL!=root->label) // leaf node
	{
		indentation(depth);
		printf("Separator{\n");
		indentation(depth);
		printf(" Translation{ translation %f %f %f }\n",-x,-y,0.0);
		indentation(depth);
		printf(" Rotation{ rotation 0 0 1 %f }\n", theta-(M_PI/2.0));
		indentation(depth);
		printf(" Material{}\n");
		indentation(depth);
		printf(" Cylinder{");
		indentation(depth);
       		printf("  radius %f\n", 0.001);
//       		printf("  radius %f\n", 0.02*(root->weight));
		indentation(depth);
       		printf("  height %f\n", 2.0*(root->weight));
		indentation(depth);
       		printf(" }");
		indentation(depth);
		printf(" Translation{ translation %f %f %f }\n",0.0,-(root->weight),0.0);
		indentation(depth);
		printf(" Scale{ scaleFactor %f %f %f }\n",0.01*(root->weight),0.01*(root->weight),0.01*(root->weight));
		indentation(depth);
		printf(" Text3{\n");
		indentation(depth);
		printf("  string \" %s \"\n", root->label);
		indentation(depth);
       		printf(" }\n");
		indentation(depth);
		printf("}\n");
	}
	else //internal node
	{
		node *tmp;
		int count=0;

		indentation(depth);
		printf("Separator{\n");
		indentation(depth);
		printf(" Translation{ translation %f %f %f }\n",-x,-y,0.0);
		indentation(depth);
		printf(" Rotation{ rotation 0 0 1 %f }\n", theta-(M_PI/2.0));
		indentation(depth);
		printf(" Material{}\n");
		indentation(depth);
		printf(" Cylinder{");
		indentation(depth);
       		printf("  radius %f\n", 0.001);
//       		printf("  radius %f\n", 0.02*(root->weight));
		indentation(depth);
       		printf("  height %f\n", 2.0*(root->weight));
		indentation(depth);
       		printf(" }");
		indentation(depth);
		printf(" Translation{ translation %f %f %f }\n",0.0,-(root->weight),0.0);
		indentation(depth);
		printf(" Sphere{ radius %f }\n", 0.003);
//		printf(" Sphere{ radius %f }\n", 0.1*(root->weight));
		indentation(depth);
	
		//count the number of children
		for(count=0, tmp=root->child;tmp!=NULL;tmp=tmp->next)
			count++;

		//visit the first child
		parse2iv(root->child,depth+1,count,1);

		//print ) and weight at current depth
		indentation(depth);
		printf("}\n");
	}

	//process root->next
	parse2iv(root->next,depth, num_sibling, curr_sibling+1);
}

int
generate_iv(node* root)
{
	printf("#Inventor V2.0 ascii\n");
printf("Separator{\n");
printf("Sphere{ radius 0.01 }\n\n");
	parse2iv(root,0,1,1);
printf("\n}\n");
}

int main(int argc, char *argv[])
{
	FILE *fp;

	if(argc>=2)
		fp=fopen(argv[1],"r");
	else
		fp=fopen("test.ph","r");
	if(fp==NULL)
	{
		perror("File not opened");
		exit(EXIT_FAILURE);
	}
	fileptr=fp;
	node *root;
	root=ph2iv();
	if(root==NULL)
	{
		printf("Error creating the tree!\n");
	}
	else
	{
//		printf("Tree created successfully!\n");
//		printf("Now, traversing the tree:\n");
		//parse_tree(root, 0);
		generate_iv(root);
	}


	return 0;
}

