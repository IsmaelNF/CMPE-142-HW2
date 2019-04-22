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
	
	//create variables to parse data into
	char line[2048];
	int id;
	int arrival;
	int  duration;
	
	while(fgets(line, sizeof(line), fp) != NULL) //while fgets does not fail to scan a line
	{
    		if(sscanf(line, "%d %d %d", &id, &arrival, &duration) !=3) //If sscanf failed to scan everything from the scanned line
      		{    
         		printf("Bad line detected\n");
         		exit(-1);                   
    		}

    	printf("ItemCode= %d\n", id);
    	printf("Item= %d\n", arrival);
    	printf("Price= %d\n\n", duration);
        //Print scanned items
	}

   	fclose(fp); //close file
   	return 0;
}
