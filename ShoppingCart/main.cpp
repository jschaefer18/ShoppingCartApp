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
#include <fstream>
#include <sstream>



using namespace std;

// This function is a for loop that prints out all of the current products of the store.
void viewStoreItems(const std::vector<Product>& store) {
    std::cout << "\nAvailable Store Items:\n";
    for (const auto& item : store) {
            std::cout << "- " << item.getName() << " - $" << item.getPrice() << "\n";
    }
    cout << "----------------------\n";
}


// This function loads the product data from the store.txt file and stores it in a vector data structure.
void loadStoreFromFile(std::vector<Product>& store, const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string name;
        double price;

        if (getline(ss, name, ',') && ss >> price) {
            store.push_back(Product(name, price));
        }
    }

    file.close();
}
// This is the main menu function that will call other functions inside it.
int main() {
    vector<Product> store;
    loadStoreFromFile(store, "store.txt");
    
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



