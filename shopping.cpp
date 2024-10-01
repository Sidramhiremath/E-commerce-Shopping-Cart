 E-commerce Shopping Cart
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

// Abstract base class
class Product {
public:
    virtual void display() const = 0; // Pure virtual function
    virtual float getPrice() const = 0; // Pure virtual function
    virtual ~Product() {}
};

class Electronics : public Product {
private:
    std::string name;
    float price;
    std::string brand;

public:
    Electronics(const std::string& name, float price, const std::string& brand)
        : name(name), price(price), brand(brand) {}

    void display() const override {
        std::cout << "Electronics: " << name << ", Brand: " << brand << ", Price: $" << std::fixed << std::setprecision(2) << price << "\n";
    }

    float getPrice() const override {
        return price;
    }
};

class Clothing : public Product {
private:
    std::string name;
    float price;
    std::string size;

public:
    Clothing(const std::string& name, float price, const std::string& size)
        : name(name), price(price), size(size) {}

    void display() const override {
        std::cout << "Clothing: " << name << ", Size: " << size << ", Price: $" << std::fixed << std::setprecision(2) << price << "\n";
    }

    float getPrice() const override {
        return price;
    }
};

class Cart {
private:
    std::vector<Product*> products;

public:
    void addProduct(Product* product) {
        products.push_back(product);
        std::cout << "Product added to cart.\n";
    }

    void viewCart() const {
        std::cout << "Your Cart:\n";
        float total = 0.0;
        for (const auto& product : products) {
            product->display();
            total += product->getPrice();
        }
        std::cout << "Total: $" << total << "\n";
    }

    ~Cart() {
        for (auto product : products) {
            delete product; // Clean up dynamically allocated products
        }
    }
};

class User {
public:
    std::string username;
    Cart cart;

    User(const std::string& username) : username(username) {}
};

void displayMenu() {
    std::cout << "\nE-commerce Shopping Cart\n";
    std::cout << "1. Add Electronics to Cart\n";
    std::cout << "2. Add Clothing to Cart\n";
    std::cout << "3. View Cart\n";
    std::cout << "4. Exit\n";
    std::cout << "Select an option: ";
}

int main() {
    User user("Guest");
    Cart& cart = user.cart;

    int choice;
    while (true) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string name, brand;
                float price;
                std::cout << "Enter Electronics name: ";
                std::cin >> name;
                std::cout << "Enter Electronics price: ";
                std::cin >> price;
                std::cout << "Enter Electronics brand: ";
                std::cin >> brand;
                cart.addProduct(new Electronics(name, price, brand));
                break;
            }
            case 2: {
                std::string name, size;
                float price;
                std::cout << "Enter Clothing name: ";
                std::cin >> name;
                std::cout << "Enter Clothing price: ";
                std::cin >> price;
                std::cout << "Enter Clothing size: ";
                std::cin >> size;
                cart.addProduct(new Clothing(name, price, size));
                break;
            }
            case 3:
                cart.viewCart();
                break;
            case 4:
                std::cout << "Exiting the application.\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
