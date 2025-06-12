//
//  main.cpp
//  ShoppingCart
//
//  Created by Josh Schaefer on 6/9/25.
//
// cd /Users/joshschaefer/Desktop/Code/ShoppingCart
// git commit -am "Your message" && git push


#include <iostream>
#include <cmath>
#include "Product.h"
#include <vector>

using namespace std;

void viewStoreItems(const std::vector<Product>& store) {
    std::cout << "\nAvailable Store Items:\n";
    for (const auto& item : store) {
            std::cout << "- " << item.getName() << " - $" << item.getPrice() << "\n";
    }
    cout << "--------------------\n";
}

int main() {
    vector<Product> store;

    store.push_back(Product("Apple", 0.99));
    store.push_back(Product("Milk", 2.49));
    store.push_back(Product("Bread", 1.99));
    
    while(true){
        cout << "1: View store items\n"
             << "2: Add item to cart\n"
             << "3: View cart\n"
             << "4: Checkout\n"
             << "5: Exit" << endl;
        int choice;
        cin >> choice;
        if (choice == 1){
            viewStoreItems(store);
        }
        if (choice == 5){
            break;
        }
    }
    return 0;
}



