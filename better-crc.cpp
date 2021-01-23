#include "CRC.h"
#include <iomanip>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;
using namespace fs;

int main (int argc, char **argv) {
    if (argc < 2) {
        cout << "better-crc: No file specified." << endl;
        return 1;
    }
    if (is_directory(argv[1])) {
        cout << "better-crc: " << argv[1] << ": Can't calculate CRC32 for directory." << endl;
        return 1;
    }
    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        cout << "better-crc: " << argv[1] << ": Failed to open file." << endl;
        return 1;
    }
    fseek(file, 0, 2);
    long int filesize = ftell(file);
    fseek(file, 0, 0);
    char *data = (char *)malloc(filesize);
    int readsize = fread(data, sizeof(char), filesize, file);
    fclose(file);
    if (readsize != filesize) {
        cout << "better-crc: " << argv[1] << ": An error occurred while reading file." << endl;
        return 1;
    }
    unsigned int crc = CRC::Calculate(data, filesize, CRC::CRC_32());
    cout << hex << setw(8) << setfill('0') << crc << endl;
	return 0;
}
