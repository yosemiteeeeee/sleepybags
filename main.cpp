#include <iostream>
#include <string>
#include <vector>
#include "header.h"
#include "containers.h"
#include "decorators.h"
#include "iterators.h"

int main() {
    VectorContainer vecContainer;
    ArrayContainer arrContainer;

    vecContainer.insert(new Kokon("Yeti", -10, "Down"));
    vecContainer.insert(new Odeyalo("Patagonia", -2, false));

    arrContainer.insert(new Kokon("Mountain Hardwear", -8, "Synthetic"));
    arrContainer.insert(new Odeyalo("Columbia", 3, true));

    std::cout << "Items in VectorContainer:" << std::endl;
    VectorContainerIterator vecIterator = vecContainer.createIterator();
    while (vecIterator.hasNext()) {
        vecIterator.next()->describe();
    }

    std::cout << "\nItems in ArrayContainer (Reversed):" << std::endl;
    ArrayContainerIterator arrIterator = arrContainer.createIterator();
    ReverseDecorator reversedArrIterator(&arrIterator);
    while (reversedArrIterator.hasNext()) {
        reversedArrIterator.next()->describe();
    }

    auto& vecItems = vecContainer.getItems();
    VectorContainerIterator vecIteratorFiltered = vecContainer.createIterator();
    Iterator* filteredIterator = new FilterDecorator(&vecIteratorFiltered, vecIteratorFiltered.getLambdaFilter());

    std::cout << "\nItems in VectorContainer (Filtered by Temperature < 0):" << std::endl;
    while (filteredIterator->hasNext()) {
        filteredIterator->next()->describe();
    }

    delete filteredIterator;
    return 0;
}
//sdfsdfsdf
