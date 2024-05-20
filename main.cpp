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
    SQLiteSpMeshokContainer.createTable();
    SQLKokonFactory SQLkokonFactory;
    SQLOdeyaloFactory SQLodeyaloFactory;

    int numOfKokon = rand() % 5 + 1;
    int numOfOdeyalo = rand() % 5 + 1;

    for (int i = 0; i < numOfKokon; ++i) {
        SpMeshok* newKokon = SQLkokonFactory.createSpMeshok();
        SQLiteSpMeshokContainer.insert(newKokon);
    }

    for (int i = 0; i < numOfOdeyalo; ++i) {
        SpMeshok* newOdeyalo = SQLodeyaloFactory.createSpMeshok();
        SQLiteSpMeshokContainer.insert(newOdeyalo);
    }

    // METHOD insert
    //SpMeshok* insertMeshok = new Kokon("Columbia", -20, "Down");

    //SQLiteSpMeshokContainer.insert(insertMeshok);

    // METHOD display
    SQLiteSpMeshokContainer.display();

    const char* selectQuery = "SELECT * FROM SleepyBags;";

    // SQL-ITERATOR
    SQLiteSpMeshokIterator sqlIterator(SQLiteSpMeshokContainer.getDB(), selectQuery);

    std::cout << "\nItems from SQL Container:" << std::endl;
    while (sqlIterator.hasNext()) {
        SpMeshok* item = sqlIterator.next();
        if (item) {
            item->describe();
        }
    }

    SQLDecorator* sqlDecorator = new SQLDecorator(&sqlIterator, SQLiteSpMeshokContainer.getDB());

    std::cout << "\nSQL Queries for SleepyBags Table:" << std::endl;
    sqlDecorator->displaySQLFormat();

    delete sqlDecorator;

    return 0;
}
