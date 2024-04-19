#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#pragma once

#include <iostream>
#include <string>

// spalniy meshok
class SpMeshok
{
protected:
    std::string brand;
    int temperatureRating; //  температурный рейтинг

public:
    SpMeshok(std::string brand, int tempRating) : brand(brand), temperatureRating(tempRating) {}

    virtual void describe() = 0;

    virtual void use()
    {
        std::cout << "Lie down in a sleeping bag" << std::endl;
    }
};

// мешок-кокон
class Kokon : public SpMeshok
{
private:
    std::string insulationType; // вид набивки

public:
    Kokon(std::string brand, int tempRating, std::string insulation) : SpMeshok(brand, tempRating), insulationType(insulation) {}

    void describe() override
    {
        std::cout << "Brand: " << brand << ", Temperature Rating: " << temperatureRating << "C, " << "insulation type: " << insulationType << std::endl;
    }

    void hoodUp()
    {
        std::cout << "Pulling up the hood" << std::endl;
    }
};

// мешок-одеяло
class Odeyalo : public SpMeshok {
private:
    bool zipperOnBothSides; // молния с обеих сторон

public:
    Odeyalo(std::string brand, int tempRating, bool doubleZipper) : SpMeshok(brand, tempRating), zipperOnBothSides(doubleZipper) {}

    void describe() override {
        std::cout << "Brand: " << brand << ", Temperature Rating: " << temperatureRating << "C, Double Zipper: " << (zipperOnBothSides ? "Yes" : "No") << std::endl;
    }

    void unzipCompletely() {
        std::cout << "Unzipping the bag" << std::endl;
    }
};

#endif // HEADER_H_INCLUDED
