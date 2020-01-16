#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>


void storeFile(int* numsToSort, std::ifstream & dataFile, int nums);
void insertSort(int* arr, int num);

int main() {

	std::ifstream dataFile;
	std::ofstream myFile;
	//open the files
	dataFile.open("data.txt");
	myFile.open("insertsort.txt");

	//read in the first number so we know how big to make the array
	int nums;
	dataFile >> nums;
	int* numsToSort = new int[nums];
	
	//store the numbers of the file into the array
	storeFile(numsToSort, dataFile, nums);

	//sort the array
	insertSort(numsToSort, nums);

	//send the contents to the appropriate file
	for(int i = 0; i < nums; i++) {
		myFile << numsToSort[i] << " ";
	}

	return 0;
}


//this function will store the contents of the file into the array of numbers that we want sorted
void storeFile(int* numsToSort, std::ifstream & dataFile, int nums) {
	for(int i = 0; i < nums; i++) {
		dataFile >> numsToSort[i];
	}
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

