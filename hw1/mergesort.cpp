#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>


void storeFile(int* numsToSort, std::ifstream & dataFile, int nums);
void merge(int* arr, int left, int mid, int r);
void mergeSort(int* arr, int left, int r);


int main() {

	std::ifstream dataFile;
	std::ofstream myFile;
	//open the files
	dataFile.open("data.txt");
	myFile.open("mergesort.txt");

	//check to see how big the array needs to be
	int nums;
	dataFile >> nums;
	int* numsToSort = new int[nums];


	//store the numbers into the array called numsToSort
	storeFile(numsToSort, dataFile, nums);

	//sort!
	mergeSort(numsToSort, 0, 10);

	//put the sorted list into the appropriate file
	for(int i = 0; i < nums; i++) {
		myFile << numsToSort[i] << " ";
	}

	return 0;
}


//this function just stores the values from the data file into the proper array
void storeFile(int* numsToSort, std::ifstream & dataFile, int nums) {
	for(int i = 0; i < nums; i++) {
		dataFile >> numsToSort[i];
	}
}


//this is how we merge the lists back together
void merge(int* arr, int left, int mid, int right) { 
	//this is the value for how many values there are on the left side of the merge
	int n1 = mid - left + 1; 
	//this calculates for the right side
	int n2 =  right - mid; 

	//create arrays for the left and right side
	int ar1[n1], ar2[n2]; 

	//loop through and set the first array to everything that is on the left side
	for (int i = 0; i < n1; i++) {
		ar1[i] = arr[left + i]; 
	}

	//loop through and set the second array to everything that is on the right side
	for (int j = 0; j < n2; j++) {
		ar2[j] = arr[mid + 1+ j]; 
	}


	int i = 0; 
	int j = 0; 
	int k = left; 

	//check these conditions so we know when to merge the lists together
	//if i is less than n1 and j is less than n2 then the list could be merged
	while (i < n1 && j < n2) { 
		if (ar1[i] <= ar2[j]) { 
			//if the value on the left is less than the value on the right
			//put the value of the left into the appropriate index of the original array
		    arr[k] = ar1[i]; 
		    i++; 
		} 

		else{ 
			//otherwise the right is less than the left and needs to be put at the appropriate index of the original array
		    arr[k] = ar2[j]; 
		    j++; 
		} 

		k++; 
		//increment everything
	} 

	//if this is true then the list on the left is sorted and must be put into the original array
	while (i < n1) { 
		arr[k] = ar1[i]; 
		i++; 
		k++; 
	} 

	//the same goes for this
	while (j < n2) { 
		arr[k] = ar2[j]; 
		j++; 
		k++; 
		} 
	} 
  

//this is where the sorting happens
void mergeSort(int* arr, int left, int right) { 
	if (left < right) { 
		//this finds the middle point of the array
		int mid = left + (right-left) / 2; 

		//call merge sort on the left of the array so we can break it down all the way to one index
		mergeSort(arr, left, mid); 
		//call merge sort on the right side of the array so we can break it down all the way to one index
		mergeSort(arr, mid+1, right); 

		//sort and merge the arrays that are broken down
		merge(arr, left, mid, right); 
	} 
} 













