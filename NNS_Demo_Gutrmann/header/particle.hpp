/*
* Author: Gregory Gutmann
* Nearest neighbor search algorithm demo
*/

#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>

class NNS;

class Particle {
    int count;

public:
    // Primary particle data
    std::vector<float> locations;
    std::vector<float> sortedLoc;
    std::vector<int> neighborCount;

    /// Testing (N2 stands for n squared, O(n^2) efficiency)
    std::vector<int> neighborCountN2;

    // Checking found particles
    std::vector<std::vector<int>> neighborList;
    std::vector<std::vector<int>> neighborN2List;

    /// Functions
    void init(int particleCount, int dimx, int dimy);
    
    void countNeighborsN2(int cellLength);
    void countNeighbors(NNS sort);

    void printLoc(int printCount = 0);

    // Printing NNS results
    void printNeighborCount(int printCount = 0);
    void printNeighborLess(int printCount);
    void printNeighborMore(int printCount);
    
    // Printing all-to-all results
    void printNeighborN2Count(int printCount = 0);
    void printNeighborN2Less(int printCount);
    void printNeighborN2More(int printCount);

    // Testing: comparing NNS and all-to-all results
    void check();

    int getParticleCount();
};

#endif // PARTICLE_H