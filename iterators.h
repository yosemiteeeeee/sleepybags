#ifndef ITERATORS_H_INCLUDED
#define ITERATORS_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include "header.h"
#include "containers.h"
#include "decorators.h"



// Iterator VectorContainer
class VectorContainerIterator : public Iterator {
private:
    std::vector<SpMeshok*> items;
    size_t currentIndex;

public:
    VectorContainerIterator(std::vector<SpMeshok*>& items) : items(items), currentIndex(0) {}

    VectorContainerIterator() : currentIndex(0) {}


    bool hasNext() const override {
        return currentIndex < items.size();
    }

    SpMeshok* next() override {
        return items[currentIndex++];
    }

    auto getLambdaFilter() {
        return [](SpMeshok* item) {
            return item->getTemperatureRating() < 0;
        };
    }
};

// Iterator ArrayContainer
class ArrayContainerIterator : public Iterator {
private:
    SpMeshok** items;
    size_t currentIndex;
    size_t maxSize;

public:
    ArrayContainerIterator(SpMeshok** items, size_t maxSize) : items(items), currentIndex(0), maxSize(maxSize) {}

    bool hasNext() const {
        return currentIndex < maxSize && items[currentIndex] != nullptr;
    }

    SpMeshok* next() {
        return items[currentIndex++];
    }
};

// SQL iterator
class SQLiteSpMeshokIterator : public Iterator {
private:
    sqlite3_stmt* stmt;

public:
    SQLiteSpMeshokIterator(sqlite3 *db, const char* query) {
        int rc = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: Could not prepare SELECT statement" << std::endl;
        }
    }

    ~SQLiteSpMeshokIterator() {
        sqlite3_finalize(stmt);
    }

    bool hasNext() const override {
        return sqlite3_step(stmt) == SQLITE_ROW;
    }

    SpMeshok* next() override {
        int tempRating = sqlite3_column_int(stmt, 2);
        const unsigned char* brand = sqlite3_column_text(stmt, 1);
        const unsigned char* type = sqlite3_column_text(stmt, 3);
        const unsigned char* insulationType = sqlite3_column_text(stmt, 4);
        int doubleZipper = sqlite3_column_int(stmt, 5);

        if (std::string(reinterpret_cast<const char*>(type)) == "Kokon") {
            return new Kokon(std::string(reinterpret_cast<const char*>(brand)), tempRating, std::string(reinterpret_cast<const char*>(insulationType)));
        } else if (std::string(reinterpret_cast<const char*>(type)) == "Odeyalo") {
            return new Odeyalo(std::string(reinterpret_cast<const char*>(brand)), tempRating, doubleZipper == 1);
        } else {
            std::cerr << "Unknown type in the database" << std::endl;
            return nullptr;
        }
    }
};

#endif // ITERATORS_H_INCLUDED
