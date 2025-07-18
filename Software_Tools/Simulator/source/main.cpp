#include "Axolotl.hpp"


int main(int argc, char *argv[])
{
    Axolotl& app = Axolotl::getInstance();
    if(argc != 2){
        std::cout << "use is : \n" << "./emulate fileNameToEmulate" << std::endl;
        return -1;
    }
    std::ifstream inputFile(argv[1]);
    if(inputFile.is_open()){
        app.Emulate(inputFile);
    }
    else{
        std::cout << "Failed to open the file " << argv[1] << std::endl; 
    }
}