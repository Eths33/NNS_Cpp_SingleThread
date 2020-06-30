/*
* Author: Gregory Gutmann
* Nearest neighbor search algorithm demo
*/

#ifndef SORT_H
#define SORT_H

#include <globals.hpp>
#include <vector>

struct KeyValuePair {
    int cellID;    // Grid cell
    int index;     // Particle index
};

class NNS {
    
    int cellLength;
    int bufferSize; // as a buffer and to handle truncation from dividing by cell size problem

    int cellCount;
    int nonBufferCellEstimate;

    int cellDimx;
    int cellDimy;

    float simDimx_buffered;
    float simDimy_buffered;

    std::vector<uint32_t> cellStart;
    std::vector<uint32_t> cellEnd;

    int particleCount;

    std::vector<KeyValuePair> cellIndexPair;

    KeyValuePair makeKeyValue(int cell, int idx);

public:

    void init(int count, int dimx, int dimy, int cell, int buffer);

    void hash(std::vector<float>& locations);
    int hash(float2 location);
    void kvSort();
    void findCellStartEnd();
    void reorder(std::vector<float>& locations, std::vector<float>& sortedLoc);
    void countNeighbors(std::vector<float>& sortedLoc, std::vector<int>& neighborCount, std::vector<std::vector<int>>& neighborList);

    // Printing main data strutures used in the NNS
    void printCellIndexPair(int printCount = 0);
    void printCellStartEnd(int printCount = 0);

    int getCellCount();
    int getNonBuffCellCount();
};

#endif // SORT_H