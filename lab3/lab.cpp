#include <iostream>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <vector>

using namespace std;

double Runtest(size_t _size, int _num_itr){
	vector<double> random_vector(_size);
	clock_t k = clock();
	clock_t start;
	do start = clock();
	while (start == k);
	for(int i = 0; i < _num_itr; ++i){
		generate(random_vector.begin(), random_vector.end(), rand);
		sort(random_vector.begin(), random_vector.end());
	}
	clock_t end = clock();
	double elapsed_time = double(end - start) / double(CLOCKS_PER_SEC);
	return elapsed_time / double(_num_itr);
}

int main(){
	cout << "Size? ";
	int size;
	cin >> size;
	cout << "Iterations? ";
	int itr;
	cin >> itr;
	cout << Runtest(size, itr) << '\n';
}
