#include "Functions.h"
int main()
{
    std::string firstParentGen;
    std::string secondParentGen = readGenotypes(firstParentGen);
    printGenerations(firstParentGen, secondParentGen);
    return 0;
}

//Example:
//aaBBCc AaBbCc
