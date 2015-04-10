#include <fstream>
#include "master.hpp"

int main(int argc, char *argv[])
{
    master app;
    if(app.parse_options(argc, argv)) app.run();

    return 0;
}