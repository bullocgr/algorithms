//Grace Bullock
//bullocgr@oregonstate.edu
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int knapsackDP(int* wt, int* val, int n, int W, std::vector<int> &v);
int findMax(int n1, int n2);

int main() {
    //declare variables
    int testCases;
    int n;
    int val[100];
    int wt[100];
    int numFam;
    int W = 0;
    std::ifstream dataFile;
	std::ofstream myFile;
    std::vector<std::vector<int> > vec(100);

    //open the shopping text
    dataFile.open("shopping.txt");
    if(!dataFile.is_open()) {
        std::cout<<"Error opening shopping.txt"<<std::endl;
        return 1;
    }

    //open the output text
    myFile.open("results.txt");
    if(!myFile.is_open()) {
        std::cout<<"Error opening results.txt"<<std::endl;
        return 1;
    }

    //read in how many test cases there are
    dataFile>>testCases;

    //loop through test cases
    for (int i = 0; i < testCases; i++) {
        //read in how many items are in the test case
        dataFile>>n;

        //loop through and get the value and the weight of each item
        for(int j = 0; j < n; j++) {
            dataFile>>val[j];
            dataFile>>wt[j];
        }

        //read in the number of family members next
        int maxPrice = 0;
        dataFile>>numFam;

        //loop through the number of family members
        for(int k = 0; k < numFam; k++) {
            //read in how much weight they can carry
            dataFile>>W;
            //use this to calculate the max price for the first person
            //store that number and continue to calculate until we reach the max for the family
            maxPrice = maxPrice + knapsackDP(wt, val, n, W, vec[k]);
        }

        //print everything to the results.txt
        myFile<<"Test case "<<i+1<<std::endl;
        myFile<<"Total Price "<<maxPrice<<std::endl;
        myFile<<"Member Items"<<std::endl;
        //loop thorugh the number of family members to get ready to print what they can carry
        for (int x = 0; x < numFam; x++) {
            //sort the vector
            sort(vec[x].begin(), vec[x].end());
            //print x + 1 for formatting
            myFile<<x+1<<":";
            for (int s = 0; s < vec[x].size(); s++) {
                //loop through the size of the vector and print out what each family member carried
                myFile << vec[x][s] << " ";
            }
            //new line at the end of each person
            myFile<<std::endl;
        }
    }
    
    //close the files
    dataFile.close();
    myFile.close();

    return 0;
}

//DP algorithm
int knapsackDP(int* wt, int* val, int n, int W, std::vector<int> &v) {
    //create a 2D array to compare values
    int V[n+1][W+1];

    //loop through n and W
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            //set the first row and column values to 0
            if (i == 0 || w == 0){
                V[i][w] = 0;
                //check if the weight of the last item is less than the capacity of the knapsack
                //item can be included
            } else if (wt[i-1] <= w) {
                //if yes then find the max between if the item is included versus if it is not included
                V[i][w] = findMax(val[i-1] + V[i-1][w-wt[i-1]], V[i-1][w]);
            } else {
                //otherwise just look at the last item
                V[i][w] = V[i-1][w];
            }
        }
    }

    //this is to fill the vector with the results
    int result = V[n][W];
    int w = W;
    //
    for (int i = n; i > 0 && result > 0; i--) {
        //item is not included
        if (result == V[i - 1][w]){
            continue;
        } else {
            //item is included so put it in the vector
            v.push_back(i);
            //calculate what the value printed should be
            result = result - val[i - 1];
            //weight is included so the value is deducted to find the actual item
            w = w - wt[i - 1];
        }
    }

    //return the max value
    return V[n][W];
}

//find the max between two values
int findMax(int n1, int n2) {
	if(n1 > n2) {
		return n1;
	}
	return n2;
}