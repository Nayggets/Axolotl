#include <iostream>
#include <fstream>
#include "Axolotl_Assembly.hpp"

int main(int argc,char* argv[])
{
    if(argc != 3){
        std::cout << "<usage> ./Axolotl_as input_file_name output_file_name\n" << "you can ./Axolotl_as --help" << std::endl;
        return -1;
    }
    return treat_file(argv[1],argv[2]);
}