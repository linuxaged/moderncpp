#include <cstdio>
#include <cerrno>
#include <string>

class LvrFile
{
public:
    LvrFile(const char* path, const char* type);
    ~LvrFile();
    LvrFile(const LvrFile&) = delete;
    LvrFile& operator=(const LvrFile&) = delete;

    size_t read(void* data, size_t element_size, size_t count);
    void write(const void* data, size_t element_size, size_t count);
    static std::string readToString(const char* filename);

private:
    FILE* file;
};

std::string LvrFile::readToString(const char *filename)
{
    std::FILE *fp = std::fopen(filename, "rb");
    if (fp)
    {
        std::string contents;
        std::fseek(fp, 0, SEEK_END);
        contents.resize(std::ftell(fp));
        std::rewind(fp);
        std::fread(&contents[0], 1, contents.size(), fp);
        std::fclose(fp);
        return (contents);
    }
    throw (errno);
}

LvrFile::LvrFile(const char* path, const char* type)
{
    printf("open file %s\n", path);
    file = fopen(path, type);
}

LvrFile::~LvrFile()
{
    printf("close opened file\n");
    fclose(file);
}

size_t LvrFile::read(void* data, size_t element_size, size_t count)
{
    return fread(data, element_size, count, file);
}

void LvrFile::write(const void* data, size_t element_size, size_t count)
{
    size_t result = fwrite(data, element_size, count, file);
}

int main(int argc, char const *argv[])
{
    char output[1024];
    LvrFile tmp("/tmp/array.cpp", "r");
    size_t readsize;
    readsize = tmp.read(output, 1, 1024);
    output[readsize] = '\0';
    printf("%s\n", output);
    return 0;
}