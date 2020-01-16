#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <time.h>
#include <ctime>

void insertSort(int* arr, int num);

int main() {
	srand(time(NULL));

	int* numsToSort = new int[40000];
	for(int i = 0; i < 40000; i++) {
		//randomly fill the array
		numsToSort[i] = rand();
	}

	//start the timer of the clock
	float start_s=clock();
	//sort!!
   	insertSort(numsToSort, 40000);
   	//end the clock
	float stop_s=clock();
	//subtract the start and finish time and multiply to get ms
	std::cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;
	return 0;
}

//this is the insertion sort algorithm
void insertSort(int* arr, int num) {
	for (int i = 1; i < num; i++) {
		//set a key value so we can remember what the original value was we want to move  
		int key = arr[i]; 
		//set j to the previous index so we can move across the array 
		int j = i - 1;  

			//check to make sure the previous index is larger than the current one
			//when this isn't true anymore the sorting for that ONE INDEX is done
			while (j >= 0 && arr[j] > key) { 
				//swap the index at i and j 
				arr[j + 1] = arr[j];
				//set j to the value 2 previous
				j = j - 1;
			}
		//set the key to the current index
		arr[j + 1] = key;  
	}  
}

