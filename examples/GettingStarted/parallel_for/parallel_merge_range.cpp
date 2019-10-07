#include <iostream>
#include <string>
#include <vector>
#include <algorithm>    // std::max
#include <stdlib.h>     // srand, rand
#include <time.h>       // time 
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
    ParallelMergeRange(ParallelMergeRange& r, split) {
        if (r.end1 - r.begin1 < r.end2 - r.begin2) {
            std::swap(r.begin1, r.begin2);
            std::swap(r.end1, r.end2);
        }
        Iterator m1 = r.begin1 + (r.end1 - r.begin1) / 2;
        Iterator m2 = std::lower_bound(r.begin2, r.end2, *m1);
        begin1 = m1;
        begin2 = m2;
        end1 = r.end1;
        end2 = r.end2;
        out = r.out + (m1 - r.begin1) + (m2 - r.begin2);
        r.end1 = m1;
        r.end2 = m2;
    }
    ParallelMergeRange(Iterator begin1_, Iterator end1_,
        Iterator begin2_, Iterator end2_,
        Iterator out_) :
        begin1(begin1_), end1(end1_),
        begin2(begin2_), end2(end2_), out(out_)
    {}
};

template<typename Iterator>
size_t ParallelMergeRange<Iterator>::grainsize = 1000;

template<typename Iterator>
struct ParallelMergeBody {
    void operator() (ParallelMergeRange<Iterator>& r) const {
        std::merge(r.begin1, r.end1, r.begin2, r.end2, r.out);
    }
};

template<typename Iterator>
void ParallelMerge(Iterator begin1, Iterator end1, Iterator begin2, Iterator end2, Iterator out) {
	parallel_for(
		ParallelMergeRange<Iterator>(begin1, end1, begin2, end2, out),
		ParallelMergeBody<Iterator>(),
		simple_partitioner()
	);
};


int main() {
	std::cout << "Hello!" << std::endl;
	const size_t n = 100;
	std::vector<float> vInput1(n, 0.0f), vInput2(n, 0.0f), vOutput(n, 0.0f);
	bool flipFlop = false;
	int rval = -1;
	srand(time(0));
	for (int i = 0; i < n; ++i) {
		/* initialize random seed: */
		rval = rand() % 10;
		flipFlop = rval >= 5;
		std::cout << "rval=" << rval << "\n";
		if (!flipFlop)
		{
			vInput1[i] = i * i;
			vInput2[i] = i * (i + 1);
		}
		else
		{
			vInput1[i] = i * (i + 1);
			vInput2[i] = i * i;
		}
	}

	for (int i = 0; i < n; ++i) {
		std::cout << "vInput1[" << i << "]=" << vInput1[i] << ", vInput2[" << i << "]=" << vInput2[i] << "\n";
	}

	ParallelMerge(vInput1.begin(), vInput1.end(), vInput2.begin(), vInput2.end(), vOutput.begin());

	for (int i = 0; i < n; ++i) {
		std::cout << "vOutput[" << i << "]=" << vOutput[i] << "\n";
	}

	return 0;
}