#include <iostream>
#include <string>
#include <vector>
#include "sqlite3.h"
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

    VectorContainerIterator* iterator = new VectorContainerIterator(vecContainer.accessItems());

    // Dekorator dlya filtracii (temperatura <= 10)
    FilterDecorator* filterDecorator = new FilterDecorator(iterator, [](SpMeshok* item) {
        return item->getTemperatureRating() <= 10;
    });

    OrderDecorator* orderDecorator = new OrderDecorator(filterDecorator);

    while (orderDecorator->hasNext()) {
        orderDecorator->next()->describe();
    }

    SQLiteSpMeshok SQLiteSpMeshokContainer("sleepybags.db");
    //SQLiteSpMeshokContainer.createTable();


    // METHOD insert
    SpMeshok* insertMeshok = new Odeyalo("InsertBrand", 12, true);
    SQLiteSpMeshokContainer.insert(insertMeshok);

    // METHOD display
    SQLiteSpMeshokContainer.display();

    const char* selectQuery = "SELECT * FROM SleepyBags;";

    // SQL-ITERATOR
    SQLiteSpMeshokIterator sqlIterator(SQLiteSpMeshokContainer.getDB(), selectQuery);

    std::cout << "Items from SQL Container:" << std::endl;
    while (sqlIterator.hasNext()) {
        SpMeshok* item = sqlIterator.next();
        if (item) {
            item->describe();
        }
    }

    return 0;
}
