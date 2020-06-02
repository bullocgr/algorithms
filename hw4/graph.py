#Grace Bullock
#bullocgr@oregonstate.edu

import math
import sys


#create a graph class that will use the original graph to make the MST
class Graph:
    def __init__(ogGraph, vertices):
        #define the vertices of the graph
        ogGraph.v = vertices
        #define the graph by looping through and setting the columns to 0 and the rows to 0-vertices
        ogGraph.graph = [[0 for column in range(vertices)] for row in range(vertices)]

    # this will calculate the distance between points
    def calcDistance(ogGraph, x1, y1, x2, y2):
        #subtract x1 and x2 and take the absolute value
        xs = abs(x1 - x2)
        # do the same with the y points
        ys = abs(y1 - y2)
        # find the difference and the square root (given in the assignent)
        diff = math.sqrt((xs * xs) + (ys * ys))
        # we want the floor value (also said in the assignment) so return the floor of the difference
        return int(math.floor(diff))

    # this will find the minimum weighted edge in the MST
    def findMin(ogGraph, point, inMST):
        # set the minimum to the largest value that python has to offer
        min = sys.maxint
        # loop through the vertices
        for i in range(ogGraph.v):
            # we want to check if the weight at i is less than the minimum value we have stored
            # we also want to check if that edge is in the MST already
            if point[i] < min and inMST[i] == False:
                # if the statement passes then we want to set the min to the smallest edge we found
                min = point[i]
                # and move the current index to whatever i is at
                minIndex = i
        # return the min index so we can find what the value at the index is later
        return minIndex

    # this is just to print what the professor wants
    def printMST(ogGraph, parent, x, y):
        # set the total distance to 0
        totalDistance = 0
        print "Edges in ogGraph"
        print "Point (x, y)                     Distance"
        # loop through the number of vertices
        for i in range(1, ogGraph.v):
            # set a placeholder for the index so we can find x1 and y1
            u = parent[i]
            # set another placeholder for the index so we can find x2 and y2
            v = i
            print "(", x[u], ", ", y[u], ") - (", x[v], ", ", y[v], ")            ", ogGraph.graph[v][u]
            # calculate the total distance and print it
            totalDistance += ogGraph.graph[v][u]
        print "Total distance ", totalDistance

    # this will find the MST
    def findMST(ogGraph, x, y):
        # set the weight indexes to a really high number
        weight = [sys.maxint]*ogGraph.v
        # set the parent graph to just the number of vertices
        parent = [None]*ogGraph.v
        # we only care that the first weight is there so we can compare it
        weight[0] = 0
        # set every index to false because we haven't created the tree yet
        inMST = [False]*ogGraph.v
        # set the parent to -1 so we know that it's a garbage weight that will change
        parent[0] = -1
        # loop through the vertices
        for i in range(ogGraph.v):
            # find the minimum index
            minIndex = ogGraph.findMin(weight, inMST)
            # set that index to true cause then we know it's in the mst
            inMST[minIndex] = True
            # loop through the vertices
            for j in range(ogGraph.v):
                # if the weight we want has an actual weight and it's not in the mst and it's less than the weight we just looked at
                if ogGraph.graph[minIndex][j] > 0 and inMST[j] == False and weight[j] > ogGraph.graph[minIndex][j]:
                    # set the weight at j to the current weight
                    weight[j] = ogGraph.graph[minIndex][j]
                    # reset the parent index so we know what to look at
                    parent[j] = minIndex;
        # print the mst
        ogGraph.printMST(parent, x, y)

# open the file and read in the command line argument
file = open(sys.argv[1], "r")
# set the number of vertices to the first line in the file
vertices = file.readline()

# create a graph of size vertices
g = Graph(int(vertices))
# create an x grid and a y grid and initialize all values to null
x = [None]*g.v
y = [None]*g.v

# loop through vertices
for i in range(g.v):
    # read in the coordinates
    coord = file.readline()
    # split the line at the first whitespace and store the values into x and y
    edge = coord.split()
    x[i] = int(edge[0])
    y[i] = int(edge[1])

for i in range(g.v):
    for j in range(g.v):
        # loop through the graph at i and j
        # calculate the distances and store those in the graph
        g.graph[i][j] = g.calcDistance(x[i], y[i], x[j], y[j])

file.close()
# find the mst using the distances
g.findMST(x, y) 

