#include <cstdio>
#include <fstream>

int main(int argc, char const *argv[])
{
	std::FILE* f = fopen( "test.txt", "w");
	fprintf(f, "this is a test text\r\n");
	fflush(f);
	fclose(f);

	std::ofstream os;
	os.open("test.txt", std::ofstream::app);
	os << "now we reopen and add some text\r\n";
	os.flush();
	os.close();

	return 0;
}