#ifndef FM_H_INCLUDED
#define FM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "header.h"

class SpMeshokFactory {
public:
    virtual ~SpMeshokFactory() {}
    virtual SpMeshok* createSpMeshok() = 0;
};

class KokonFactory : public SpMeshokFactory {
public:
    SpMeshok* createSpMeshok() override {
        std::string type = "Kokon";
        int tempRating = rand() % 30;
        std::vector<std::string> brands = {"The North Face", "REI", "Outventure"};
        std::string brand = brands[rand() % brands.size()];
        std::vector<std::string> insulationTypes = {"Down", "Synthetic", "Feather"};
        std::string insulation = insulationTypes[rand() % insulationTypes.size()];

        return new Kokon(brand, tempRating, insulation);
    }
};

class OdeyaloFactory : public SpMeshokFactory {
public:
    SpMeshok* createSpMeshok() override {
        std::string type = "Odeyalo";
        int tempRating = rand() % 30;
        bool doubleZipper = rand() % 2 == 0;
        std::vector<std::string> brands = {"The North Face", "REI", "Columbia"};
        std::string brand = brands[rand() % brands.size()];

        return new Odeyalo(brand, tempRating, doubleZipper);
    }
};

void populateContainer(Container& container, SpMeshokFactory& factory, int count) {
    for (int i = 0; i < count; ++i) {
        container.insert(factory.createSpMeshok());
    }
}


#endif // FM_H_INCLUDED
