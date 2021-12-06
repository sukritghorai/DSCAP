#include "include/Parser.h"


int main(int argc, char **argv) {
    Parser UI;
    if (argc == 2) {
//        UI.Open(argv[1]);
//        UI.Read();
//        UI.Close();
        UI.Init(argv[1]);
        UI.Read();
        return EXIT_SUCCESS;
    } else {
        std::cout << "usage: app <file_name>"
                  << std::endl;
        return -1;
    }


}