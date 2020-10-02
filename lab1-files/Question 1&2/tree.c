#include <stdio.h>
struct Node {
char * data;
struct Node *ltree;
struct Node *rtree;
};

struct Node* head;
struct Node* newTree(char *p){
struct Node * n = malloc(sizeof(struct Node));
n->data = malloc(strlen(p)+1);
strcpy(n->data,p);
n->ltree=n->rtree = NULL;
return n;
}

struct Node * insert(struct Node* tree,char *p){
if (tree == NULL)
   return newTree(p);
int cmp =strcmp(p,tree->data);
if (cmp <= 0 )
   tree->ltree = insert(tree->ltree,p);
else
   tree->rtree = insert(tree->rtree,p);
return tree;
}

void inorder(struct Node* tree){
if (tree == NULL)
   return ;
   inorder(tree->ltree);
   printf("%s\n",tree->data);
   inorder(tree->rtree);
}

main(){
//head =insert(head,"hello ");
//head =insert(head,"good ");
//head =insert(head,"jack ");
//head =insert(head,"james ");
//head =insert(head,"mary ");
//inorder(head);
	
	char * filename = "name.txt";
	FILE * fp = fopen(filename, "r");
	if (fp == NULL) return 1;
	char c;
	int count = 0;
	while((c = fgetc(fp)) != EOF)
	{
		if(c == ' ' || c == '\n')
		{
			printf("\n");
			++count;
		}
                else{
			printf("%c", c);
                        head = insert(head,c);
                       inorder(head);

		}
           
	}

	fclose(fp);
 
	printf("This file has %d words in it. They are now in order \n", count);
	return 0;
}

