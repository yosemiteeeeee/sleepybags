#include <iostream>
#include <string>
#include <vector>
#include "header.h"
#include "containers.h"
#include "decorators.h"
#include "iterators.h"
#include "fm.h"

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    VectorContainer vecContainer;
    KokonFactory kokonFactory;
    OdeyaloFactory odeyaloFactory;


    populateContainer(vecContainer, kokonFactory, rand() % 5 + 1);
    populateContainer(vecContainer, odeyaloFactory, rand() % 5 + 1);


    vecContainer.display();

    return 0;
}
