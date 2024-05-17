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

// Итератор для VectorContainer
class VectorContainerIterator : public Iterator {
private:
    std::vector<SpMeshok*> items;
    size_t currentIndex;

public:
    VectorContainerIterator(std::vector<SpMeshok*>& items) : items(items), currentIndex(0) {}

    VectorContainerIterator() : currentIndex(0) {} // конструктор по умолчанию


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

// Итератор для ArrayContainer
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



#endif // ITERATORS_H_INCLUDED
