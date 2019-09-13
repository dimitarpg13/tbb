#include <iostream>
#include <string>
#include <vector>
#include <algorithm>    //std::max
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"

using namespace tbb;

struct Average {
	std::vector<float>& m_vInput;
	std::vector<float>& m_vOutput;
	void operator() (const blocked_range<int>& range) const {
		for (int i = range.begin(); i != range.end(); ++i)
			m_vOutput[i] = (m_vInput[i - 1] + m_vInput[i] + m_vInput[i + 1]) * (1 / 3.0f);
	}
	Average(std::vector<float>& vInput, std::vector<float>& vOutput) : m_vInput(vInput), m_vOutput(vOutput) {}
};

// Note: the input must be padded such that input[n-1] and input[n] can be used
// to calculate the first and last output values
void ParallelAverage(std::vector<float>& vOutput, std::vector<float>& vInput, size_t n) {
	Average avg(vInput, vOutput);
	parallel_for(blocked_range<int>(0, n, 1000), avg);
}

int main() {
	/*std::string str[N] = { std::string("a"), std::string("b") };
	for (std::size_t i = 2; i < N; ++i)
		str[i] = str[i - 1] + str[i - 2];
	std::string& to_scan = str[N - 1];
	const std::size_t num_elem = to_scan.size();

	std::vector<std::size_t> max(num_elem);
	std::vector<std::size_t> pos(num_elem);

	tbb::parallel_for(tbb::blocked_range<std::size_t>(0, num_elem),
		SubStringFinder(to_scan, max, pos));

	for (std::size_t i = 0; i < num_elem; ++i)
		std::cout << " " << max[i] << "(" << pos[i] << ")" << std::endl;
     */




	return 0;
}