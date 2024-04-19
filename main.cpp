#include <iostream>
#include <string>
#include "header.h"

int main()
{
    Kokon* kokon1 = new Kokon("The North Face", -5, "Fluff");
    Odeyalo* odeyalo1 = new Odeyalo("REI", 0, true);

    kokon1->describe();
    kokon1->use();

    if (kokon1)
        kokon1->hoodUp();

    odeyalo1->describe();
    odeyalo1->use();

    if (odeyalo1)
        odeyalo1->unzipCompletely();

    return 0;
}
