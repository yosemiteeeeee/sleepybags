#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#pragma once

#include <iostream>
#include <string>

// �������� �����
class SpMeshok
{
protected:
    std::string brand;
    int temperatureRating; //  ������������� �������

public:
    SpMeshok(std::string brand, int tempRating) : brand(brand), temperatureRating(tempRating) {}

    virtual void describe() = 0;

    virtual void use()
    {
        std::cout << "Lie down in a sleeping bag" << std::endl;
    }
};

// �����-�����
class Kokon : public SpMeshok
{
private:
    std::string insulationType; // ��� �������

public:
    Kokon(std::string brand, int tempRating, std::string insulation) : SpMeshok(brand, tempRating), insulationType(insulation) {}

    virtual void describe() override
    {
        std::cout << "Brand: " << brand << ", Temperature Rating: " << temperatureRating << " C, " << "Insulation type: " << insulationType << std::endl;
    }

    virtual void hoodUp()
    {
        std::cout << "Wrap yourself in the cocoon" << std::endl;
    }
};

// �����-������
class Odeyalo : public SpMeshok
{
private:
    bool zipperOnBothSides; // ������ � ����� ������

public:
    Odeyalo(std::string brand, int tempRating, bool doubleZipper) : SpMeshok(brand, tempRating), zipperOnBothSides(doubleZipper) {}

    virtual void describe() override
    {
        std::cout << "Brand: " << brand << ", Temperature Rating: " << temperatureRating << " C, Double Zipper: " << (zipperOnBothSides ? "Yes" : "No") << std::endl;
    }

    virtual void unzipCompletely()
    {
        std::cout << "Unzip the bag and lie down" << std::endl;
    }
};

#endif // HEADER_H_INCLUDED
