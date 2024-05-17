#ifndef DECORATORS_H_INCLUDED
#define DECORATORS_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include "header.h"
#include "iterators.h"
#include "containers.h"

class Iterator {
public:
    virtual bool hasNext() const = 0;
    virtual SpMeshok* next() = 0;
    virtual ~Iterator() = default;
};

// Декоратор для добавления порядкового номера к элементам
class OrderDecorator : public Iterator {
private:
    Iterator* iterator;
    size_t order;

public:
    OrderDecorator(Iterator* iter) : iterator(iter), order(1) {}

    bool hasNext() const override {
        return iterator->hasNext();
    }

    SpMeshok* next() override {
        SpMeshok* item = iterator->next();
        if (item) {
            std::cout << "[" << order << "] ";
            order++;
        }
        return item;
    }

    ~OrderDecorator() override {
        delete iterator;
    }
};

// Декоратор для фильтрации элементов по критерию
class FilterDecorator : public Iterator {
private:
    Iterator* iterator;
    bool (*filterFunc)(SpMeshok*);

public:
    FilterDecorator(Iterator* iter, bool (*filter)(SpMeshok*)) : iterator(iter), filterFunc(filter) {}

    bool hasNext() const override {
        while (iterator->hasNext()) {
            if (filterFunc(iterator->next())) {
                return true;
            }
        }
        return false;
    }

    SpMeshok* next() override {
        return iterator->next();
    }

    ~FilterDecorator() override {
        delete iterator;
    }
};

// Декоратор для изменения порядка обхода
class ReverseDecorator : public Iterator {
private:
    Iterator* iterator;
    std::vector<SpMeshok*> reversedItems;
    int currentIndex;

public:
    ReverseDecorator(Iterator* iter) : iterator(iter), currentIndex(-1) {
        reversedItems.reserve(10);
        while (iterator->hasNext()) {
            reversedItems.push_back(iterator->next());
        }
        currentIndex = reversedItems.size();
    }

    bool hasNext() const override {
        return currentIndex > 0;
    }

    SpMeshok* next() override {
        return reversedItems[--currentIndex];
    }

    ~ReverseDecorator() override {
        delete iterator;
    }
};

#endif // DECORATORS_H_INCLUDED
