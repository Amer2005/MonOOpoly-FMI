#include <iostream>
#include "Monopoly.h"

int main()
{
    Monopoly* monopoly = new Monopoly();

    monopoly->run();

    int a;

    std::cin >> a;

    return 0;
}