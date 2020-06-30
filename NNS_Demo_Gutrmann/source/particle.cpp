/*
* Author: Gregory Gutmann
* Nearest neighbor search algorithm demo.
*/

#include <particle.hpp>
#include <globals.hpp>

void Particle::init(int particleCount, int dimx, int dimy) {
	float halfDimx = dimx / 2.0f;
	float halfDimy = dimy / 2.0f;

	count = particleCount;

	// Place particles at random locations
	for (int i = 0; i < particleCount; i++) {
		float xLoc = ((rand() % (dimx * 10)) / 10.0f) - halfDimx;
		float yLoc = ((rand() % (dimy * 10)) / 10.0f) - halfDimy;
		locations.push_back(xLoc);
		locations.push_back(yLoc);
		neighborCount.push_back(0);
	}

	sortedLoc.resize(locations.size());
	neighborCountN2.resize(neighborCount.size());

	std::vector<std::vector<int>> temp(neighborCount.size());
	neighborList = temp;
	neighborN2List = temp;
}

// All-to-all interaction alogithim O(n^2)
void Particle::countNeighborsN2(int cellLength) {

    for (int currIdx = 0; currIdx < count; currIdx++) {
        float2 thisLoc = make_float2(locations[currIdx * 2 + 0], locations[currIdx * 2 + 1]);

        int localCount = 0;

		for (int checkIdx = 0; checkIdx < count; checkIdx++) { 

			if (checkIdx != currIdx) // Dont compute with its self
			{
				float2 checkIdxLoc = make_float2(locations[checkIdx * 2 + 0], locations[checkIdx * 2 + 1]);
				float2 p2pVec = make_float2(checkIdxLoc.x - thisLoc.x, checkIdxLoc.y - thisLoc.y);
				float dist = sqrtf((p2pVec.x * p2pVec.x) + (p2pVec.y * p2pVec.y));
				if (dist < (float)cellLength)
				{
					++localCount;
#if !PERFORMANCE_TEST
					neighborN2List[currIdx].push_back(checkIdx);
#endif
				}
			}
		}

        neighborCountN2[currIdx] = localCount;

    }
}

// Helper
int minimizePrinting(int loop) {
	if (loop > 100) {
		printf("Count is high will only print 10\n");
		loop = 10;
	}
	return loop;
}

void Particle::printLoc(int printCount) {
	int loop = (printCount) ? printCount : count;
	loop = minimizePrinting(loop);
	
	for (int i = 0; i < loop; i++) {
		printf("%.3f %.3f\n", locations[i * 2 + 0], locations[i * 2 + 1]);
	}
}

// Printing NNS results
void Particle::printNeighborCount(int printCount) {
#if PERFORMANCE_TEST
	printNeighborLess(printCount);
#else
	printNeighborMore(printCount);
#endif
}
void Particle::printNeighborLess(int printCount) {
	int loop = (printCount) ? printCount : count;
	loop = minimizePrinting(loop);

	for (int i = 0; i < loop; i++) {
		printf("Particle %d, Neighbor   count %d\n", i, neighborCount[i]);
	}
}
void Particle::printNeighborMore(int printCount) {
	int loop = (printCount) ? printCount : count;
	loop = minimizePrinting(loop);

	for (int i = 0; i < loop; i++) {
		printf("Particle %d, Neighbor count %d    \t { ", i, neighborCount[i]);
		for (int n = 0; n < neighborList[i].size(); n++) {
			printf("%d%s", neighborList[i][n], (n == neighborList[i].size() - 1) ? " }" : ", ");
		}
		printf("\n");
	}
}

// Printing all-to-all results
void Particle::printNeighborN2Count(int printCount) {
#if PERFORMANCE_TEST
	printNeighborN2Less(printCount);
#else
	printNeighborN2More(printCount);
#endif
}
void Particle::printNeighborN2Less(int printCount) {
	int loop = (printCount) ? printCount : count;
	loop = minimizePrinting(loop);

	for (int i = 0; i < loop; i++) {
		printf("Particle %d, NeighborN2 count %d\n", i, neighborCountN2[i]);
	}
}
void Particle::printNeighborN2More(int printCount) {
	int loop = (printCount) ? printCount : count;
	loop = minimizePrinting(loop);

	for (int i = 0; i < loop; i++) {
		printf("Particle %d, NeighborN2 count %d  \t { ", i, neighborCountN2[i]);
		for (int n = 0; n < neighborN2List[i].size(); n++) {
			printf("%d%s", neighborN2List[i][n], (n == neighborN2List[i].size() -1) ? " }" : ", ");
		}
		printf("\n");
	}
}

// Testing: comparing NNS and all-to-all results
void Particle::check() {
	int foundError = 0;
	printf("Checking for differences between NNS and all-to-all\n");

	for (int i = 0; i < count; i++) {
		int firstMissing = 1;
		
		for (int n = 0; n < neighborN2List[i].size(); n++) {
			int found = 0;
			int search = neighborN2List[i][n];
			
			for (int p = 0; p < neighborList[i].size(); p++) {
				if (search == neighborList[i][p]) {
					found = 1;
				}
			}
			
			if (!found) {
				++foundError;
				if (firstMissing) {
					printf("Particle %d\n", i);
				}
				float2 iLoc = make_float2(locations[i * 2 + 0], locations[i * 2 + 1]);
				float2 nLoc = make_float2(locations[search * 2 + 0], locations[search * 2 + 1]);
				float2 p2pVec = make_float2(nLoc.x - iLoc.x, nLoc.y - iLoc.y);
				float dist = sqrtf((p2pVec.x * p2pVec.x) + (p2pVec.y * p2pVec.y));
				printf("\tNNS didnt find %d, distance of %.2f\n", search, dist);
			}
		}
	}
	
	if (foundError) {
		printf("\tFound %d errors (some may be mirrors of eachother)\n", foundError);
	}
	else {
		printf("\tSuccess!\n");
	}
}

int Particle::getParticleCount() {
	return count;
}