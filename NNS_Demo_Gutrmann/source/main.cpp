/*
* Author: Gregory Gutmann
* Nearest neighbor search algorithm demo
* Don't print or keep track of neighbors in a list during simulaion
*/

#include <globals.hpp>
#include <sort.hpp>
#include <particle.hpp>
#include <time.h>

int main() {

	// Feel free to change these values to test
	int xDimension = X_DIM;
	int yDimension = Y_DIM;
	int cellSize = CELL_SIZE;
	int gridBuffer = GRID_BUFFER;
	int particleCount = PARTICLE_COUNT;


	NNS sortObject;
	Particle partObject;

	sortObject.init(particleCount, xDimension, yDimension, cellSize, gridBuffer);
	partObject.init(particleCount, xDimension, yDimension);

	// Simulation loop starts here
	sortObject.hash(partObject.locations);

	sortObject.printCellIndexPair(); printf("\n\n");
	sortObject.kvSort();
	sortObject.printCellIndexPair(); printf("\n\n");

	sortObject.findCellStartEnd();
	sortObject.printCellStartEnd(); printf("\n\n");

	// Improves memory access pattern, also the algorim functions in sorted order
	sortObject.reorder(partObject.locations, partObject.sortedLoc);


	sortObject.countNeighbors(partObject.sortedLoc, partObject.neighborCount, partObject.neighborList);
	partObject.printNeighborCount(); printf("\n\n");
	//Simulation loop ends here


	
#if !PERFORMANCE_TEST
	// Testing (Debug)
	partObject.countNeighborsN2(cellSize);
	partObject.printNeighborN2Count(); printf("\n\n");
	partObject.check(); printf("\n\n");
#endif

#if PERFORMANCE_TEST
	clock_t t;
	float nnsTime, ataTime;
	// Running 1000x to get a larger time for the timer, and to get a more repeatable performance number
	printf("Running 1000 iterations of NNS and all-to-all\n");
	
	// NNS
	{
		t = clock();
		for (int i = 0; i < 1000; i++) {
			sortObject.hash(partObject.locations);
			sortObject.kvSort();
			sortObject.findCellStartEnd();
			sortObject.reorder(partObject.locations, partObject.sortedLoc);
			sortObject.countNeighbors(partObject.sortedLoc, partObject.neighborCount, partObject.neighborList);
		}
		t = clock() - t;
		nnsTime = ((float)t) / CLOCKS_PER_SEC;
		printf("NNS time %0.3f\n", nnsTime);
	}

	// All-to-all
	{
		t = clock();
		for (int i = 0; i < 1000; i++) {
			partObject.countNeighborsN2(cellSize);
		}
		t = clock() - t;
		ataTime = ((float)t) / CLOCKS_PER_SEC;
		printf("All-to-all time %0.3f\n", ataTime);
	}

	printf("\nPerformance difference: %.1fx\n", ataTime / nnsTime);

	printf("\nAverage particles per non buffer cell: %.2f (2.0 is not sparse) \n", partObject.getParticleCount() / (float)sortObject.getNonBuffCellCount());
	printf("At greater densities the NNS performance gain will decrease\n");
#endif

	// Hashing example
	//int hash = sortObject.hash(make_float2(-9, -9));
	//printf("%d\n", hash);
	return 0;
}

/*

<Performance test output on desktop>

Running 1000 iterations of NNS and all-to-all
NNS time 0.374
All-to-all time 11.788

Performance difference: 31.5x

Average particles per non buffer cell: 2.00 (2.0 is not sparse)
At greater densities the NNS performance gain will decrease

*/