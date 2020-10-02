#include<stdio.h>
#include<typec.h>



buf[200];
void main()
{
	
	FILE *fp;
	int i=0,size,j;
	char ch; 
 
	fp=fopen("new.txt","r");
	if(fp==NULL)
	{ 
	printf("\n Cannot open the file \n");
	exit(0);
	}
	while(fgets(buf,200,fp)
	{
        char *p=buf;

for(*p;p++){
}
	ch=fgetc(fp); 
	i++;  
	} 
	
	fp=fopen("empsorted.txt","w");
	for(i=0;i<size;i++)
	fprintf(fp,"%s ");
	printf("\n The file is sorted alphbetical. \n \n");
}
