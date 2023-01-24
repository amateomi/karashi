#include "shell.hpp"

int main(int argc, char* argv[])
{
    Shell shell { argc, argv };
    shell.Run();
}
