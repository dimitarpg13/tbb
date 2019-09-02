/*
    Copyright (c) 2005-2019 Intel Corporation

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>    //std::max
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"

static const size_t N = 23;

int main() {

    std::cout << "My first test.." << std::endl;
     
    std::string str[N] = { std::string("a"), std::string("b") };
    for (size_t i = 2; i < N; ++i) str[i] = str[i-1]+str[i-2];
    std::string &to_scan = str[N-1];
    size_t num_elem = to_scan.size();

    size_t *max = new size_t[num_elem];
    size_t *pos = new size_t[num_elem];

    // add code to populate max and pos here
    //

    for (size_t i = 0; i < num_elem; ++i)
        std::cout << " " << max[i] << "(" << pos[i] << ")" << std::endl;

    delete[] pos;
    delete[] max;

    return 0;
}

