# NNS_Cpp_SingleThread
Nearest Neighbor Search

Designed as an introduction to one implementation of a nearest neighbor search. Coded in a C/C++ style.
It was created as a teaching tool for my work at Tokyo Institute of Technology. 

Simplicity was preferred over performance in this code.

# Main steps are as follows

1. hash              // Function that takes particle locations and ouputs the cell ID that they are in

2. kvSort            // Function that uses C++'s std::sort, can be replaced with any key value sort

3. findCellStartEnd  // Function to find the start and stop particle indexies for each cell

4. reorder           // Function to reorder the primary data structures that are used

5. countNeighbors    // Function that uses the results of the NNS to do the users work


Author: Greg Gutmann
