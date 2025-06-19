//
//  main.cpp
//  ShoppingCart
//
//  Created by Josh Schaefer on 6/9/25.
//
// cd /Users/joshschaefer/Desktop/Code/ShoppingCart
// git commit -am "Your message" && git push

// Input and output streams
#include <iostream>
// Math opperations
#include <cmath>
// Imports from Product.h
#include "Product.h"
// Imports vector data structure
#include <vector>
// Allows file input and output
#include <fstream>
// String parsing to break down the store.txt data
#include <sstream>
// Helps display exactly two decminal points
#include <iomanip>
// data structure for cart
#include <map>


using namespace std;


#include <unistd.h>
#include <limits.h>



// This function is a for loop that prints out all of the current products of the store.
void viewStoreItems(const std::vector<Product>& store) {
    std::cout << "\nAvailable Store Items:\n";
    std::cout << std::fixed << std::setprecision(2);  // This line ensures that it will display two decimal points

    for (const auto& item : store) {
        std::cout << item.getName() << " - $" << item.getPrice() << "\n";
    }

    std::cout << "----------------------\n";
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





// This function adds item objects to the cart data structure.
void addToCart(const std::vector<Product>& store, std::map<std::string, int>& cart) {
    std::string productName;
    std::cin.ignore(); // Clear leftover newline from previous input

    while (true) {
        std::cout << "\nEnter the name of the item to add to cart (or 0 to finish): ";
        std::getline(std::cin, productName);

        if (productName == "0") {
            std::cout << "Done adding items to cart.\n";
            break;
        }

        bool found = false;
        for (const auto& item : store) {
            if (item.getName() == productName) {
                cart[productName]++;
                std::cout << productName << " added to cart.\n";
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "Item not found in store.\n";
        }
    }
}


// This is the view cart function
void viewCart(const std::map<std::string, int>& cart, const std::vector<Product>& store) {
    if (cart.empty()) {
        std::cout << "\nYour cart is empty.\n";
        return;
    }

    std::cout << "\nYour Cart:\n";
    std::cout << std::fixed << std::setprecision(2);

    double subtotal = 0.0;

    for (const auto& pair : cart) {
        const std::string& name = pair.first;
        int quantity = pair.second;

        // Find product in store to get price
        double price = 0.0;
        for (const auto& item : store) {
            if (item.getName() == name) {
                price = item.getPrice();
                break;
            }
        }

        double itemTotal = price * quantity;
        subtotal += itemTotal;

        std::cout << "- " << name << " x" << quantity
                  << " @ $" << price << " = $" << itemTotal << "\n";
    }

    std::cout << "-------------------------\n";
    std::cout << "Subtotal: $" << subtotal << "\n";
}


void saveReceipt(const std::map<std::string, int>& cart,
                 const std::vector<Product>& store,
                 double payment,
                 double change) {

    std::ofstream file("/Users/joshschaefer/Desktop/Code/ShoppingCart/receipt.txt");

    if (!file) {
        std::cerr << "Error: Could not write receipt.\n";
        return;
    }

    file << std::fixed << std::setprecision(2);
    file << "====== Receipt ======\n";

    double total = 0.0;

    for (const auto& pair : cart) {
        const std::string& name = pair.first;
        int quantity = pair.second;
        double price = 0.0;

        for (const auto& item : store) {
            if (item.getName() == name) {
                price = item.getPrice();
                break;
            }
        }

        double itemTotal = price * quantity;
        total += itemTotal;

        file << name << " x" << quantity << " @ $" << price
             << " = $" << itemTotal << "\n";
    }

    file << "---------------------\n";
    file << "Total:   $" << total << "\n";
    file << "Paid:    $" << payment << "\n";
    file << "Change:  $" << change << "\n";
    file << "=====================\n";
    file << "Thank you for shopping!\n";

    file.close();
}


void checkout(std::map<std::string, int>& cart, const std::vector<Product>& store) {
    if (cart.empty()) {
        std::cout << "\nYour cart is empty. Nothing to checkout.\n";
        return;
    }

    std::cout << "\nCheckout Summary:\n";
    std::cout << std::fixed << std::setprecision(2);

    double total = 0.0;

    for (const auto& pair : cart) {
        const std::string& name = pair.first;
        int quantity = pair.second;

        // Lookup price in store
        double price = 0.0;
        for (const auto& item : store) {
            if (item.getName() == name) {
                price = item.getPrice();
                break;
            }
        }

        double itemTotal = price * quantity;
        total += itemTotal;

        std::cout << "- " << name << " x" << quantity
                  << " @ $" << price << " = $" << itemTotal << "\n";
    }

    std::cout << "-------------------------\n";
    std::cout << "Total: $" << total << "\n";

    double payment;
    std::cout << "Enter payment amount: $";
    std::cin >> payment;

    if (payment >= total) {
        double change = payment - total;
        std::cout << "Payment accepted. Your change is $" << change << "\n";
        std::cout << "Thank you for your purchase!\n";
        saveReceipt(cart, store, payment, change);
        cart.clear();
    } else {
        std::cout << "Insufficient funds. You still owe $" << (total - payment) << "\n";
        std::cout << "Returning to main menu.\n";
    }
}



// This is the main menu function that will call other functions inside it.
int main() {
    vector<Product> store;
    std::map<std::string, int> cart;
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
        if (choice == 2){
            addToCart(store, cart);
        }
        if (choice == 3){
            viewCart(cart, store);
        }
        if (choice == 4){
            checkout(cart, store);
        }
        if (choice == 5){
            break;
        }
    }
    return 0;
}



