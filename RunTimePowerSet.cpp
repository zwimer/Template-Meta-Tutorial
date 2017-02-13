#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>


#define BUILD_NUM_TIMES 1000

/* Compile with:
g++ RunTimePowerSet.cpp -Wall -Ofast -std=c++14 -Wno-enum-compare -ftemplate-depth=1000000 -frename-registers -march=native -fomit-frame-pointer -fmerge-all-constants -o RunTimePowerSet.out

computer_power_set by: Toshi Piazza

*/

//Computer the power set
template <typename T> std::vector<T> compute_power_set(const T &power)
{
    std::vector<T> ret;
    unsigned long size = std::pow(2, power.size());
    ret.reserve(size);
    for (unsigned long i = 0; i < size; ++i) {
        T tmp;
        for (unsigned long j = 0; j < power.size(); ++j) {
            if (i & (1 << j))
                tmp.push_back(power[j]);
        }
        ret.push_back(tmp);
    }
    return ret;
}

//Print the matrix
static inline void pntM(auto power) {
    for (auto &v : power) {
		std::cout << "  [ ";
        for (auto &i : v) std::cout << i << ", ";
        std::cout << "]\n";
    }
	std::cout << std::endl;
}

//Run the program
inline void buildSet(const bool p) {

	//Make the set
    std::vector<int> A = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	//Make the power set of A
    auto B = compute_power_set(A);

	//Print B if requested
	if (p) pntM(B);
}

//Get the current time
static inline __attribute__((always_inline)) auto time() {
	return std::chrono::high_resolution_clock::now();
}

//Print the current time
static inline __attribute__((always_inline)) int getTime(auto t) { 
	using namespace std; using namespace chrono;
	return duration_cast<microseconds>(t).count();
}

//Main function
int main() {

	//Create time variables
	auto s = time(), e = time();
	int time1;

	//Create the set n times, and time it
	const int n = BUILD_NUM_TIMES; s = time();
	for(int i = 0; i < n; ++i) buildSet(false);
	e = time(); time1 = getTime(e-s);
	
	//Build the set, print it, and time it
	s = time(); buildSet(true); e = time();

	//Print out the time it took
	printf("Build it n times: \t%d us\n", time1);
	printf("Built and printed: \t%d us\n", getTime(e-s));
	printf("Total elapsed time: \t%d us\n", time1 + getTime(e-s));

	//Success
	return 0;
}
