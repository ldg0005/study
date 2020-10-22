#include <chrono>

int main()
{
	auto start = std::chrono::high_resolution_clock::now();
  
  // 구현
  
	auto end = std::chrono::high_resolution_clock::now();
	auto Duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	double f64Count = (double)Duration.count() / 1000.;
	
	printf(("%.2f ms\n"), f64Count);

	return 0;
}
