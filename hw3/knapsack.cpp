//Grace Bullock
//bullocgr@oregonstate.edu
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int knapsackDP(int W, int n, int* val, int* wt);
int findMax(int n1, int n2);
int knapsackR(int W, int n, int* wt, int* val);
void print(int W, int n, long time, int result);
long calcTimeDP(int* val, int* wt, int W, int n);
float calcTimeR(int* val, int* wt, int W, int n);

int main() {

    //seed
    srand(time(NULL));
    //set the values for n and W
    int n = 10;
    int W = 100;

    //loop through how many test cases we want
    for(int i = 0; i < 7; i++) {
        //create a wt array and val array
        int* wt = new int[n];
        int* val = new int[n];
        
        //fill the arrays with random values between 1 and 100
        for(int j = 0; j < 10; j++) {
            wt[j] = rand()%99 + 1;
            val[j] = rand()%99 + 1;
        }

        //check the time and value of the recursive algorithm
        float RTime = calcTimeR(val, wt, W, n);
        int R = knapsackR(W, n, wt, val);
        // check the time and value of the DP algorithm
        long DPTime = calcTimeDP(val, wt, W, n);
        int DP = knapsackDP(W, n, val, wt);

        //print the results
        std::cout<<"DP: ";
        print(W, n, DPTime, DP);
        std::cout<<"R: ";
        print(W, n, RTime, R);

        //increment n and W when needed
        n+=5;
        // W+=500;
    }
  


    return 0;
}

//the DP solution to knapsack
int knapsackDP(int W, int n, int* val, int* wt) {
    int i, w;
    //create a dynamic array
    int **V = new int*[n+1];
    for(i = 0; i < n+1; i++) {
        V[i] = new int[W+1];
    }

    //loop through number of items
    for(i = 0; i <= n; i++) {
        //loop through the capacity
        for(w = 0; w <= W; w++) {
            //fill the first row and column with 0
            if(i == 0 || w == 0) {
                V[i][w] == 0;
                //check if the weight of the last item is less than the capacity of the knapsack
                //item can be included
            } else if(wt[i - 1] <= w) {
                //if yes then find the max between if the item is included versus if it is not included
                V[i][w] = findMax(val[i-1] + V[i-1][w-wt[i-1]], V[i-1][w]);
            } else {
                //otherwise just look at the last item
                V[i][w] = V[i-1][w];
            }
        }
    }

    //return what is stored
    return V[n][W];
}

//the recursive solution to knapsack
int knapsackR(int W, int n, int* wt, int* val) {
    //if the weight and size is 0 return 0
    if (n == 0 || W == 0) {
        return 0;
    }
    //check if the weight of the item is greater than W
    //if it is it can't be included in the final answer
    if (wt[n-1] > W) {
        return knapsackR(W, n-1, wt, val);
    }

    //return the max of the item included and the item not included
    else {
        return findMax(val[n-1] + knapsackR(W-wt[n-1], n-1, wt, val), knapsackR(W, n-1, wt, val));
    }
}

//calculate the time it took to run the DP program
long calcTimeDP(int* val, int* wt, int W, int n) {
    clock_t t1,t2;
    t1=clock();
	//sort
    knapsackDP(W, n, val, wt);
    t2=clock();
	//find how long it took to run the algorithm
    long diff ((long)t2-(long)t1);
	//convert to seconds
    long seconds = diff / CLOCKS_PER_SEC;
    return seconds;
}

//calculate the time it took to run the R program
float calcTimeR(int* val, int* wt, int W, int n) {
    clock_t t1,t2;
    t1=clock();
	//sort
    knapsackR(W, n, wt, val);
    t2=clock();
	//find how long it took to run the algorithm
    float diff ((float)t2-(float)t1);
	//convert to seconds
    float seconds = diff / CLOCKS_PER_SEC;
    return seconds;
}

//find the max of 2 numbers
int findMax(int n1, int n2) {
	if(n1 > n2) {
		return n1;
	}
	return n2;
}

//print what we want to see
void print(int W, int n, long time, int result) {
    std::cout<<"N = "<<n<<" W = "<<W<<" Time = "<<time<<" Result = "<<result<<std::endl;
}