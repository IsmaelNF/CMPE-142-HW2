#include <stdio.h>
#include <stdlib.h>

void main(){

	char ch, file_name[30];
   	printf("Enter name of a file:\n");
   	gets(file_name);
 
   	FILE *fp = fopen(file_name, "r"); // open file in read mode
 
   	if (fp == NULL) //throw handler in case file is empty
   	{
      		perror("Error opening the file.\n");
      		exit(EXIT_FAILURE);
   	}
 	
	printf("The contents of %s file are:\n", file_name);
	
	//create arrays to parse data into
	char id[100];
	char arrival[100];
	char duration[100];
		
   	while((ch = fgetc(fp)) != EOF){ //Read through file
      		printf("%c", ch);
		
 	}

   	fclose(fp);
   	return 0;
}
