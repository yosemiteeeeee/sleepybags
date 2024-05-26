#ifndef CONTAINERS_H_INCLUDED
#define CONTAINERS_H_INCLUDED

#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include "sqlite3.h"
#include "iterators.h"
#include "header.h"

class Container {
public:
    virtual void insert(SpMeshok* item) = 0;
    virtual void display() = 0;
    virtual Iterator* createIterator() = 0;
};

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

    Iterator* createIterator() override {
        return new VectorContainerIterator(items);
    }

};



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

    Iterator* createIterator() override {
        return new ArrayContainerIterator(items, currentSize);
    }

};


// SQL container
class SQLiteSpMeshok : public Container
{
private:
    sqlite3 *db;

public:
    sqlite3* getDB()
    {
        return db;
    }
    SQLiteSpMeshok(const char* path)
    {
        int rc = sqlite3_open(path, &db);
        if (rc)
            {
                std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
                sqlite3_close(db);
                exit(1);
            } else
            {
                std::cout << "\nOpened database successfully" << std::endl;
            }
    }

    ~SQLiteSpMeshok() {
        sqlite3_close(db);
    }

    void createTable() {
        char* errMsg;
        const char* sql = "CREATE TABLE IF NOT EXISTS SleepyBags("
                          "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                          "Brand TEXT NOT NULL,"
                          "TemperatureRating INTEGER NOT NULL,"
                          "Type TEXT,"
                          "InsulationType TEXT,"
                          "DoubleZipper BOOLEAN);";

        int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        } else {
            std::cout << "Table created successfully" << std::endl;
        }
    }

    void insert(SpMeshok* meshok) override {
    if (Kokon* kokon = dynamic_cast<Kokon*>(meshok)) {
        std::string doubleZipperValue = "N/A"; // Set default value for Double Zipper

        std::string insertSQL = "INSERT INTO SleepyBags (Brand, TemperatureRating, Type, InsulationType, DoubleZipper) VALUES ('" + kokon->getBrand() + "', " + std::to_string(kokon->getTemperatureRating()) + ", 'Kokon', '" + kokon->getInsulationType() + "', '" + doubleZipperValue + "');";
        char* errMsg;
        int rc = sqlite3_exec(db, insertSQL.c_str(), nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
        else {
            std::cout << "Data inserted successfully" << std::endl;
        }
    }
    else if (Odeyalo* odeyalo = dynamic_cast<Odeyalo*>(meshok)) {
        std::string insulationTypeValue = "N/A"; // Set default value for Insulation Type

        std::string insertSQL = "INSERT INTO SleepyBags (Brand, TemperatureRating, Type, InsulationType, DoubleZipper) "
                                " VALUES ('" + odeyalo->getBrand() + "', " + std::to_string(odeyalo->getTemperatureRating()) + ", 'Odeyalo', '" + insulationTypeValue + "', " + (odeyalo->hasZipperOnBothSides() ? "1" : "0") + ");";
        char* errMsg;
        int rc = sqlite3_exec(db, insertSQL.c_str(), nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
        else {
            std::cout << "Data inserted successfully" << std::endl;
        }
    }
    else {
        std::cerr << "Invalid SpMeshok type" << std::endl;
    }
}


    void display() override {
        const char* sql = "SELECT * FROM SleepyBags;";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: Could not execute SELECT statement" << std::endl;
        } else {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                int id = sqlite3_column_int(stmt, 0);
                const unsigned char* brand = sqlite3_column_text(stmt, 1);
                int tempRating = sqlite3_column_int(stmt, 2);
                const unsigned char* type = sqlite3_column_text(stmt, 3);
                const unsigned char* insulationType = sqlite3_column_text(stmt, 4);
                int doubleZipper = sqlite3_column_int(stmt, 5);

                std::cout << "ID: " << id << ", Brand: " << brand << ", Temperature Rating: " << tempRating
                        << ", Type: " << type << ", Insulation Type: " << insulationType
                        << ", Double Zipper: " << (doubleZipper ? "Yes" : "No") << std::endl;
            }
        }
        sqlite3_finalize(stmt);
    }

    Iterator* createIterator() override {
        const char* sql = "SELECT * FROM SleepyBags;";
        return new SQLiteSpMeshokIterator(db, sql);
    }

};


#endif // CONTAINERS_H_INCLUDED
