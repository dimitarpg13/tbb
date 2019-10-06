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
        for (int i = range.begin(); i != range.end(); ++i) {
            m_vOutput[i] = m_vInput[i];
            if (i > range.begin())
                m_vOutput[i] += m_vInput[i - 1]; 
            if (i < range.end() - 1)
                m_vOutput[i] += m_vInput[i + 1];
            m_vOutput[i] /= (1.0f + (float)(i > range.begin()) + (float)(i < range.end() - 1));
        }
    }
    Average(std::vector<float>& vInput, std::vector<float>& vOutput) : m_vInput(vInput), m_vOutput(vOutput) {}
};

// Note: the input must be padded such that input[n-1] and input[n] can be used
// to calculate the first and last output values
void ParallelAverage(std::vector<float>& vInput, std::vector<float>& vOutput, const size_t n) {
    Average avg(vInput, vOutput);
    parallel_for(blocked_range<int>(0, n, 1000), avg);
}

int main() {
    const size_t n = 100;
    std::vector<float> vInput(n, 0.0f), vOutput(n, 0.0f);
    for (int i = 0; i < n; ++i)
        vInput[i] = i * i;

    ParallelAverage(vInput, vOutput, n);
    for (int j = 0; j < n; ++j)
        std::cout << "vOutput[" << j << "]=" << vOutput[j] << "\n";

    return 0;
}