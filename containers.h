#ifndef CONTAINERS_H_INCLUDED
#define CONTAINERS_H_INCLUDED

#include <vector>
#include <list>
#include <algorithm>
#include "iterators.h"
#include "header.h"

class Container {
public:
    virtual void insert(SpMeshok* item) = 0;
    virtual void display() = 0;
};

// Vector container implementation
class VectorContainer : public Container {
private:
    std::vector<SpMeshok*> items;

public:
    const std::vector<SpMeshok*>& getItems() const {
        return items;
    }

    std::vector<SpMeshok*>& accessItems() {
        return items;
    }

    void insert(SpMeshok* item) override {
        items.push_back(item);
    }

    void display() override {
        for (const auto& item : items) {
            item->describe();
        }
    }

    VectorContainerIterator createIterator(); // объявление
};

// Добавим определение функции createIterator
VectorContainerIterator VectorContainer::createIterator() {
    return VectorContainerIterator(items);
}

// Array container implementation
class ArrayContainer : public Container {
private:
    static const int MAX_SIZE = 10;
    SpMeshok* items[MAX_SIZE];
    int currentSize;

public:
    ArrayContainer() : currentSize(0) {}

    void insert(SpMeshok* item) override {
        if (currentSize < MAX_SIZE) {
            items[currentSize] = item;
            currentSize++;
        } else {
            std::cout << "Container is full!" << std::endl;
        }
    }

    void display() override {
        for (int i = 0; i < currentSize; ++i) {
            items[i]->describe();
        }
    }

    ArrayContainerIterator createIterator(); // объявление
};

// Добавим определение функции createIterator
ArrayContainerIterator ArrayContainer::createIterator() {
    return ArrayContainerIterator(items, currentSize);
}

#endif // CONTAINERS_H_INCLUDED
