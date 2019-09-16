#include <iostream>
#include <string>
#include <vector>
#include <algorithm>    //std::max
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"

using namespace tbb;

template<typename Iterator> 

struct ParallelMergeRange {
	static size_t grainsize;
	Iterator begin1, end1; // [begin1,end1) is the first sequence to be merged
	Iterator begin2, end2; // [begin2, end2) is the 2nd sequence to be merged
	Iterator out; // where to put merged sequence
	bool empty() const { return (end1 - begin1) + (end2 - begin2) == 0; }
	bool is_divisible() const {
		return std::min(end1 - begin1, end2 - begin2) > grainsize;
	}

};



int main() {
	std::cout << "Hello!" << std::endl;
	return 0;
}