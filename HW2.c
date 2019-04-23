#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int arr1[], int arr2[], int arr3[], int size);
void swap(int *i, int *j);
void bubbleSort_duration(int arr1[], int arr2[], int arr3[], int size);
void arrCopy(int arr1[], int arr2[], int size);

int main(){

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
	
	//create variables to temporarily parse data into
	char line[2048];
	int id;
	int arrival;
	int duration;
	
	//create variables to store parsed data into
	int id_arr[100];
	int arrival_arr[100];
	int duration_arr[100];

	int i = 0; //counter for array
	while(fgets(line, sizeof(line), fp) != NULL) //while fgets does not fail to scan a line
	{
    		if(sscanf(line, "%d %d %d", &id, &arrival, &duration) !=3) //If sscanf failed to scan everything from the scanned line
      		{    
         		printf("Bad line detected\n");
         		exit(-1);                   
    		}

		/*Below are test prints to check if file is being properly parsed
        	printf("ID= %d\n", id);
    		printf("Arrival= %d\n", arrival);
    		printf("Duration= %d\n\n", duration);*/
		
		//Saved parsed data to arrays
		id_arr[i] = id;
		arrival_arr[i] = arrival;
		duration_arr[i] = duration;
		i++;
	}
	
//FIFO Scheduling algorithm implemented below
	bubbleSort(arrival_arr, id_arr, duration_arr, i); //sort based on arrival time
	
	//Creating copy of data to implement edge case for elapsed time without altering original scheduling	
	int arrival_arr_copy[100], id_arr_copy[100], duration_arr_copy[100];
	arrCopy(arrival_arr, arrival_arr_copy, 100);
	arrCopy(id_arr, id_arr_copy, 100);
	arrCopy(duration_arr, duration_arr_copy, 100);

	bubbleSort_duration(arrival_arr_copy, id_arr_copy, duration_arr_copy, i); //Resorting data to be able to implement elapsed time

	//Check to see if arrays are holding the correct data
        for(int x = 0; x < i; x++){
                printf("%d %d %d\n", id_arr[x], arrival_arr[x], duration_arr[x]);
        }
	
	//Output FIFO Start and Finish  Time for each job
	for(int x = 0; x < i; x++){
                printf("ID: %d   Start Time: %d   Finish Time: %d\n", id_arr[x], arrival_arr[x], duration_arr[x]+arrival_arr[x]);
        }
	
	for(int x = 0; x < i; x++){
                printf("ID_copy: %d   Start Time_copy: %d   Finish Time_copy: %d\n", id_arr_copy[x], arrival_arr_copy[x], duration_arr_copy[x]+arrival_arr_copy[x]);
        }
	

//SJF Scheduling algorithm implemented below (not yet done, just formatting)

	/*Check to see if arrays are holding the correct data
	for(int x = 0; x < i; x++){
		printf("%d %d %d\n", id_arr[x], arrival_arr[x], duration_arr[x]);
	}*/

   	fclose(fp); //close file
   	return 0;
}

//All arrays are sorted based on the index of first argument, arr1[]
void bubbleSort(int arr1[], int arr2[], int arr3[], int size){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size-i-1; j++){
			if(arr1[j] > arr1[j+1])
			{	
				swap(&arr1[j], &arr1[j+1]);
				swap(&arr2[j], &arr2[j+1]);
				swap(&arr3[j], &arr3[j+1]);				
			}
		}
	}	
}

//Bubble sort is re-written so that if the arrival time is the same for two ID's, the duration is used to sort 
void bubbleSort_duration(int arr1[], int arr2[], int arr3[], int size){
        for(int i = 0; i < size; i++){
                for(int j = 0; j < size-i-1; j++){
                        if(arr1[j] == arr1[j+1] && arr3[j] > arr3[j+1]){
                                swap(&arr1[j], &arr1[j+1]);
                                swap(&arr2[j], &arr2[j+1]);
                                swap(&arr3[j], &arr3[j+1]);

                        }
                }
        }
}


void swap(int *i, int *j)
{
    int temp = *i;
    *i = *j;
    *j = temp;
}

void arrCopy(int arr1[], int arr2[], int size){
	for(int i = 0; i < size; i++){
		arr2[i] = arr1[i];
	}
}
