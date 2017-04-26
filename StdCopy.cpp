#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iterator>

int main(int argc, char const *argv[])
{
	int fromArray[10];
	// std::memset(fromArray, 10, sizeof(fromArray));
	std::fill_n(fromArray, sizeof fromArray / sizeof fromArray[0], 10);
	int DestArray[10];
	// std::memset(DestArray, 0, sizeof(DestArray));
	std::fill_n(DestArray, sizeof DestArray / sizeof DestArray[0] , 0);

	// std::copy(std::begin(fromArray), std::end(fromArray), std::begin(DestArray));
	std::copy(fromArray, fromArray + 10, DestArray);
	for(int i=0; i<10; i++)
	{
		printf("%d\n", DestArray[i]);
	}
	return 0;
}