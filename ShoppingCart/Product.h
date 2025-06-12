//
//  Product.h
//  ShoppingCart
//
//  Created by Josh Schaefer on 6/12/25.
//


#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    std::string name;
    double price;

public:
    Product(std::string name, double price);
    std::string getName() const;
    double getPrice() const;
};

#endif
