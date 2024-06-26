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

// ��������� ��� ���������� ����������� ������ � ���������
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
            order++;
        }
        return item;
    }

    ~OrderDecorator() override {
        delete iterator;
    }
};

// ��������� ��� ���������� ��������� �� ��������
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

// ��������� ��� ��������� ������� ������
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

// SQL decorator
class SQLDecorator : public Iterator {
private:
    Iterator* iterator;
    sqlite3* db;

public:
    SQLDecorator(Iterator* iter, sqlite3* database) : iterator(iter), db(database) {}

    bool hasNext() const override {
        return iterator->hasNext();
    }

    SpMeshok* next() override {
        return iterator->next();
    }

    // ������� �����, ������� ����� �������� ���������� � ������ �������� � ������� SQL-�������
    void displaySQLFormat() {
        while (hasNext()) {
            SpMeshok* item = next();
            if (item) {
                std::cout << "INSERT INTO SleepyBags (Brand, TemperatureRating, Type, InsulationType, DoubleZipper) VALUES ('"
                          << item->getBrand() << "', " << item->getTemperatureRating();
                if (Kokon* kokon = dynamic_cast<Kokon*>(item)) {
                    std::cout << ", 'Kokon', '" << kokon->getInsulationType() << "', 'N/A');";
                } else if (Odeyalo* odeyalo = dynamic_cast<Odeyalo*>(item)) {
                    std::cout << ", 'Odeyalo', 'N/A', " << (odeyalo->hasZipperOnBothSides() ? "Yes" : "No") << ");";
                }
                std::cout << std::endl;
            }
        }
    }

    ~SQLDecorator() override {
        delete iterator;
    }
};




#endif // DECORATORS_H_INCLUDED
