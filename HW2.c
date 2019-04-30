#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void bubbleSort(int arr1[], int arr2[], int arr3[], int size);
void swap(int *i, int *j);
void arrCopy(int arr1[], int arr2[], int size);
void bubbleSortReverse(int arr1[], int arr2[], int arr3[], int size);

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

		//Saved parsed data to arrays
		id_arr[i] = id;
		arrival_arr[i] = arrival;
		duration_arr[i] = duration;
		i++;
	}
	
	//Below are test prints to check if file is being properly parsed
	for(int x = 0; x < i; x++){
		printf("%d %d %d\n", id_arr[x], arrival_arr[x], duration_arr[x]);
        }


//FIFO Scheduling algorithm implemented below
	bubbleSort(arrival_arr, id_arr, duration_arr, i); //sort based on arrival time
	
	printf("\nFIFO Scheduling:\n");

	/*//Check to see if arrays are holding the correct data
        for(int x = 0; x < i; x++){
                printf("%d %d %d\n", id_arr[x], arrival_arr[x], duration_arr[x]);
        }*/
	
	//Output FIFO Start and Finish  Time for each job
	int fifo_finish_time[100];  
	int fifo_elapsed_time[100];
	int fifo_response_time[100];
	for(int x = 0; x < i; x++){
		//Calculating finish time for each process
                printf("ID: %d\t   Start Time: %d\t   ", id_arr[x], arrival_arr[x]);
		if(x==0){
                        fifo_finish_time[x] = arrival_arr[x] + duration_arr[x];
		}
                else if(fifo_finish_time[x-1] < arrival_arr[x]){
                        fifo_finish_time[x] = arrival_arr[x] + duration_arr[x];
                }
                else{
                        fifo_finish_time[x] = fifo_finish_time[x-1] + duration_arr[x];
                }
                printf("Finish time: %d\t ",  fifo_finish_time[x]);
		
		//Calculating elapsed time for each process
		if(x==0){
                        fifo_elapsed_time[x] = arrival_arr[x] + duration_arr[x];
                }
                else if(fifo_elapsed_time[x-1] < arrival_arr[x]){
                        fifo_elapsed_time[x] = arrival_arr[x] + duration_arr[x];
                }
                else{
                        fifo_elapsed_time[x] = fifo_elapsed_time[x-1] + duration_arr[x];
                }
                printf("Elapsed time: %d\t ", fifo_elapsed_time[x]);
		
		//Calculating response time for each process
		if(x == 0){
                        fifo_response_time[x] = duration_arr[x] - arrival_arr[x];
                }
                else{
                        fifo_response_time[x] = fifo_finish_time[x]  - arrival_arr[x];
                }
                printf("Response time: %d\n", fifo_response_time[x]);
        }
	printf("\n");	
//SJF Scheduling algorithm implemented below
/*Check to see if arrays are holding the correct data
	for(int x = 0; x < i; x++){
		printf("%d %d %d\n", id_arr[x], arrival_arr[x], duration_arr[x]);
	}*/
        bubbleSort(duration_arr, id_arr, arrival_arr, i);
        /*for(int y = 0; y < i; y++)
        {
            printf("%d\t",duration_arr[y]);
            printf("%d\t", id_arr[y]);
            printf("%d\t", arrival_arr[y]); 
        }*/
        int finishSJF[100];
        int elapsedSJF[100];
        int responseSJF[100];
	int marked[100] = {0};
        int start = 0;
        bool status = true;
	
	int minimum = arrival_arr[0];
	int count = 0;
	for(int y = 1; y < i; y++)
	{
		if(arrival_arr[y] < minimum)
		{
			minimum = arrival_arr[y];
			count = y;
		}
	}
        marked[count] = 1;
	finishSJF[0] = arrival_arr[count] + duration_arr[count];
        elapsedSJF[0] = arrival_arr[count] + duration_arr[count];
        responseSJF[0] = duration_arr[count] - arrival_arr[count]; 
	printf("Shortest Job First Scheduling:\n");
        printf("ID: %d\t Start Time: %d\t Finish Time: %d\t Elapsed Time: %d\t Response Time: %d\n", id_arr[count], arrival_arr[count], finishSJF[0], elapsedSJF[0], responseSJF[0]);
	
        int finished = finishSJF[0];
	for(int y = 0; y < i; y++)
	{
                //int finished = finishedSJF[y];
		if(arrival_arr[y] <= finishSJF[y] && marked[y] == 0)
		{
			finishSJF[y+1] = finishSJF[y] + duration_arr[y];
			elapsedSJF[y+1] = finishSJF[y] + duration_arr[y];
                        responseSJF[y+1] = finishSJF[y+1] - arrival_arr[y];
                        marked[y] = 1;                               
		}
		else
		{
                        y = y+1;
                        elapsedSJF[y+1] = finishSJF[y-1] + duration_arr[y];
                        finishSJF[y+1] = finishSJF[y-1] + duration_arr[y];
                        responseSJF[y+1] = finishSJF[y+1] - arrival_arr[y];
                        /*printf("ID NEXT: %d\n", id_arr[y+1]);
			printf("%d\n", finishSJF[y]);
               		printf("%d\n", arrival_arr[y]);
                        */
                        /*while(finishSJF[y] != arrival_arr[y])
                        {
			    finishSJF[y] = finishSJF[y] + 1;
                            printf("%d\n", finishSJF[y]);
                        }*/
		}

                printf("ID: %d\t Start Time: %d\t Finish Time: %d\t Elapsed Time: %d\t  Response Time: %d\n", id_arr[y], arrival_arr[y], finishSJF[y+1], elapsedSJF[y+1], responseSJF[y+1]);
	}
	printf("\n");   

        //printf("%d\t %d\t %d", finishSJF[0], elapsedSJF[0], responseSJF[0]);
        /*while(status)
	{
            for(int y = 0; y < i; y++)
	    {

		if(y == 0)
		    {
		       	    finishSJF[y] = arrival_arr[y] + duration_arr[y];
                            finished = finishSJF[y];
			    marked[y] = 1;
		    }
        	    else if(arrival_arr[y] < finished)
	      	    { 
		    }
            } 
	} 
        */
        
	bubbleSortReverse(duration_arr, id_arr, arrival_arr, i);
        
	int finishBJF[100];
        int elapsedBJF[100];
        int responseBJF[100];
        int markedBJF[100] = {0};
        int startBJF = 0;
        bool statusBJF = true;

        int minimumBJF = arrival_arr[0];
        int countBJF = 0;
        for(int y = 1; y < i; y++)
        {
                if(arrival_arr[y] < minimumBJF)
                {
                        minimumBJF = arrival_arr[y];
                        countBJF = y;
                }
        }
        markedBJF[count] = 1;
        finishBJF[0] = arrival_arr[countBJF] + duration_arr[countBJF];
        elapsedBJF[0] = arrival_arr[countBJF] + duration_arr[countBJF];
        responseBJF[0] = duration_arr[countBJF] - arrival_arr[countBJF];
        printf("Biggest Job First Scheduling:\n");
        printf("ID: %d\t Start Time: %d\t Finish Time: %d\t Elapsed Time: %d\t Response Time: %d\n", id_arr[countBJF], arrival_arr[countBJF], finishBJF[0], elapsedBJF[0], responseBJF[0]);
        

	int finishedBJF = finishBJF[0];
        for(int y = 0; y < i; y++)
        {
                //int finished = finishedSJF[y];
                if(arrival_arr[y] <= finishBJF[y] && markedBJF[y] == 0)
                {
                        finishBJF[y+1] = finishBJF[y] + duration_arr[y];
                        elapsedBJF[y+1] = finishBJF[y] + duration_arr[y];
                        responseBJF[y+1] = finishBJF[y+1] - arrival_arr[y];
                        markedBJF[y] = 1;
                }
                else
                {
                        y = y+1;
                        elapsedBJF[y+1] = finishBJF[y-1] + duration_arr[y];
                        finishBJF[y+1] = finishBJF[y-1] + duration_arr[y];
                        responseBJF[y+1] = finishBJF[y+1] - arrival_arr[y];
                        /*printf("ID NEXT: %d\n", id_arr[y+1]);
                        printf("%d\n", finishSJF[y]);
                        printf("%d\n", arrival_arr[y]);
                        */
                        /*while(finishSJF[y] != arrival_arr[y])
                        {
                            finishSJF[y] = finishSJF[y] + 1;
                            printf("%d\n", finishSJF[y]);
                        }*/
                }
	

                printf("ID: %d\t Start Time: %d\t Finish Time: %d\t Elapsed Time: %d\t  Response Time: %d\n", id_arr[y], arrival_arr[y], finishBJF[y+1], elapsedBJF[y+1], responseBJF[y+1]);
	}
	printf("\n");

        bubbleSort(arrival_arr, id_arr, duration_arr, i);
	printf("Round Robin Scheduling (Quantum = 2)\n");
        int cp[100];
        arrCopy(duration_arr, cp, i);
	
	int timer = 0;
	int quantum = 2;
	int finishRR[100];
        int elapsedRR[100];
        int turnaroundRR[100];
	int responseRR[100];
        int waitRR[100];
	int finalRR[100];
        int startRR = 0;
	while(1)
	{
		bool done = true;
		for(int k = 0; k < i; k++)
		{
			//printf("IN FOR\n");
			if(cp[k] > 0)
			{
				done = false;
				if(cp[k] > quantum)
				{
					cp[k] = cp[k] - quantum;
					timer = timer + quantum;
					//printf("pid: %d (%d)\t",id_arr[k], cp[k]);
				}
				else
				{
					//printf("IN ELSE\n");
					timer = timer + cp[k];
					cp[k] = 0;
					finalRR[k] = timer;
					elapsedRR[k] = finalRR[k];
					waitRR[k] = timer - duration_arr[k];
					//printf("pid: %d (%d)\t",id_arr[k], cp[k]);
				}
			}
		}
		
		if(done == true)
		{
			break;
		}
	}
	for(int k = 0; k < i; k++)
	{
		turnaroundRR[k] = finalRR[k] - arrival_arr[k];
		printf("ID: %d\t Start Time: %d\t Finish Time: %d\t Elapsed Time: %d\t Turnaround Time: %d\n", id_arr[k], arrival_arr[k], finalRR[k], elapsedRR[k], turnaroundRR[k]);
	}
        printf("\n");   
       

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

void bubbleSortReverse(int arr1[], int arr2[], int arr3[], int size){
        for(int i = 0; i < size; i++){
                for(int j = 0; j < size-i-1; j++){
                        if(arr1[j] < arr1[j+1]){
                                swap(&arr1[j], &arr1[j+1]);
                                swap(&arr2[j], &arr2[j+1]);
                                swap(&arr3[j], &arr3[j+1]);
                        }
                }
        }
}
