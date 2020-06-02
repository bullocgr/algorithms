##########################################################################################
#Final Project
#Description: This is the final project where we solve for the traveling salesman problem.
#We solve this problem through the use of the nearest neighbor algorithm.
#Group 46: Grace Bullock, Gabriela Velazquez, Steven Nguyen
##########################################################################################
import math
import sys
import timeit  

#defining of the function buildAdMatrix
#use of this function is to read in the files in order to 
#build the needed adjacency matrix
def buildAdMatrix(inputFileName):
	with open(inputFileName) as f:
        #defining of nodes
		nodes = [tuple(map(int, i.split())) for i in f]

    #defining of needed integers
	numNodes = len(nodes)
	w, h = numNodes, numNodes
    #defining of matrix to help us solve for it
	Matrix = [[-1 for x in range(w)] for y in range(h)]

    #actual building of the matrix
	for i in range(0, numNodes):
		for j in range(0, numNodes):
			if i == j:
				Matrix[i][j] = 0
			elif Matrix[i][j] == -1:
				dx = nodes[j][1] - nodes[i][1]
				dy = nodes[j][2] - nodes[i][2]
				Matrix[i][j] = int(round(math.sqrt(dx * dx + dy * dy)))
				Matrix[j][i] = Matrix[i][j]
    #once completed, we return the matrix
	return Matrix

#function printTour will help print out the tour 
#by taking in the following arguements 
def printTour(tour, length, outputFileName):
	with open(outputFileName, 'w') as o:
		print >> o, length
		for vertex in tour:
			print >> o, vertex

#function tourLength is defined in order to help
#us find the tour length through the use of the for loop
#thus returning the sum 
def tourLength(tour, Matrix):
    #redefining of numNodes
	numNodes = len(tour) 
	sum = 0 
	for i in range(0, numNodes - 1):
		sum += Matrix[tour[i]][tour[i + 1]]
	sum += Matrix[tour[-1]][tour[0]]
    #this will add the edge that returns us to the start
	return sum

#function nNeighbor will begin to apply the nearest neighbor alg 
def nNeighbor(Matrix, outputFileName):
	numNodes = len(Matrix)
	if numNodes > 1000:
		iterations = 10
	else:
		iterations = numNodes
    
	minDistPath = float('inf')
	bestTour = []

	for start in range(0, iterations):
        #we will start the tour empty with the vertices left unvisited
        #this will be like "starting at zero"
		tour = []
		unvisited = range(0, numNodes)
		current = start
		tour.append(current)
        #this will add a start vertex to our tour
		unvisited.remove(current)

		#keep adding next closest unvisited vertex to tour
        #while the vertex is unvisited we will add it to the tour
		while unvisited:
			low = float('inf')
			for i in unvisited:
				if Matrix[current][i] < low:
					low = Matrix[current][i]
					nextMove = i
			current = nextMove
			unvisited.remove(nextMove)
			tour.append(nextMove)

        #tourDistance is set to tourLength(the function stated prior)
		tourDistance = tourLength(tour, Matrix)

        #if statement indicated that is the tourDistance is less than minDistPath
        #then minDistPath will be set to tourDistance and bestTour will be set to tour
		if tourDistance < minDistPath:
			minDistPath = tourDistance
			bestTour = tour
			printTour(bestTour, minDistPath, outputFileName)
    #when completed, this will return the best tour and minDistPath
	return bestTour, minDistPath

inputFileName = sys.argv[1]
outputFileName = inputFileName + ".tour"

#if inf flag is set, then run for unlimited time, otherwise run for 3 min
#when a flag is set, this will run for an unlimted time
#though if this is not the case, then this will run for a 3 minutes
if len(sys.argv) == 3:
	if sys.argv[2] == "inf":
		timeLimit = float('inf')
else:
    #time if the else statement is taken
	timeLimit = 180

#utilized for our use of collecting time
start_time = timeit.default_timer()

#read input file and create a weighted adjacency matrix
Matrix = buildAdMatrix(inputFileName)

#this will locate the first solution
#through the use of the nearest neighbor algorithm
appxTour, minLength = nNeighbor(Matrix, outputFileName)

#this will print out the time elapsed at the end
elapsed = timeit.default_timer() - start_time
print + round(elapsed, 2)