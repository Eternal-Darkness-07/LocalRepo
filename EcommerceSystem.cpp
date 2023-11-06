#include <iostream>
#include <vector>
#include <algorithm>
bool login_admin = false;
bool login_user = false;
using namespace std;

class product
{
public:
    int product_Id;
    string name;
    double price;
    int quantity;

    void setProduct(string name, int product_id, double price)
    {
        this->name = name;
        this->product_Id = product_id;
        this->price = price;
    }

    void setQuantity(int q)
    {
        this->quantity = q;
    }
};

class ProductList
{
public:
    vector<product *> Products;

    void addProductToList(product *pr)
    {
        Products.push_back(pr);
    }

    void removeProductFromList(int pID)
    {
        for (auto i : Products)
        {
            if (i->product_Id == pID)
            {
                auto it = find(Products.begin(), Products.end(), i);
                Products.erase(it);
                delete i;
                return;
            }
        }
        cout << "Your Product is not in the list" << endl;
    }

    void showList()
    {
        for (auto pr : Products)
        {
            cout << "Name     : " << pr->name << endl;
            cout << "ID       : " << pr->product_Id << endl;
            cout << "Price    : " << pr->price << endl;
            cout << "---------------------------------------------------\n";
        }
    }

    product *getProduct(int id)
    {
        for (auto i : Products)
        {
            if (i->product_Id == id)
            {
                return i;
            }
        }
        return nullptr;
    }
};

class ShoppingCart
{
    vector<product *> cartProducts;

public:
    void addProduct(product *pr)
    {
        product *cartProduct = new product;                           // Create a new product for the cart
        cartProduct->setProduct(pr->name, pr->product_Id, pr->price); // Copy details from the list product
        cartProduct->setQuantity(pr->quantity);                       // Set the quantity
        cartProducts.push_back(cartProduct);
    }

    void removeProduct(int pID)
    {
        for (auto i : cartProducts)
        {
            if (i->product_Id == pID)
            {
                auto it = find(cartProducts.begin(), cartProducts.end(), i);
                cartProducts.erase(it);
                delete i;
                return;
            }
        }
        cout << "Product is not in your cart" << endl;
    }

    void calculateTotalPrice()
    {
        this->displayCart();
        double totalPrice = 0.0;
        for (auto pr : cartProducts)
        {
            double price = pr->price * static_cast<double>(pr->quantity);
            totalPrice += price;
        }
        cout << "Total Bill: " << totalPrice << "\n-------------------------------------\n";
    }

    void displayCart()
    {
        for (auto pr : cartProducts)
        {
            cout << "Name     : " << pr->name << endl;
            cout << "ID       : " << pr->product_Id << endl;
            cout << "Price    : " << pr->price << endl;
            cout << "Quantity : " << pr->quantity << endl;
            cout << "---------------------------------------------------\n";
        }
    }
};

void admin(ProductList &list)
{
    system("cls");
    int n;
    cout << "1. Add to list\n2. Delete from list\n3. Show list\nChoice: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        cout << "How many products you want to add?: ";
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            product *pr = new product;
            string name;
            double price;
            int Id;
            cout << "Name: ";
            cin >> name;
            cout << "Price: ";
            cin >> price;
            cout << "ID: ";
            cin >> Id;
            cout << "---------------------------------------------\n";
            pr->setProduct(name, Id, price);
            list.addProductToList(pr);
        }
        break;
    case 2:
        cout << "How many products you want to delete?: ";
        cin >> n;
        list.showList();
        for (int i = 0; i < n; i++)
        {
            int Id;
            cout << "ID: ";
            cin >> Id;
            list.removeProductFromList(Id);
        }
        break;
    case 3:
        list.showList();
        break;
    default:
        cout << "Invalid choice..." << endl;
        break;
    }
}

void user(ProductList &list, ShoppingCart &cart)
{
    system("cls");
    int n;
    cout << "1. Add to Cart\n2. Delete from cart\n3. Show cart\n4. Total bill\nChoice: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        list.showList();
        cout << "How many products you want to add?: ";
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            int Id;
            int q;
            cout << "ID: ";
            cin >> Id;
            cout << "Quantity: ";
            cin >> q;
            cout << "---------------------------------------------\n";
            product *pr = list.getProduct(Id);
            if (pr != nullptr)
            {
                pr->setQuantity(q);
                cart.addProduct(pr);
            }
            else
            {
                cout << "Product not found in the list." << endl;
            }
        }
        break;
    case 2:
        cout << "How many products you want to delete?: ";
        cin >> n;
        cart.displayCart();
        for (int i = 0; i < n; i++)
        {
            int Id;
            cout << "ID: ";
            cin >> Id;
            cart.removeProduct(Id);
        }
        break;
    case 3:
        cart.displayCart();
        break;
    case 4:
        cart.calculateTotalPrice();
        break;
    default:
        cout << "Invalid choice..." << endl;
        break;
    }
}

int main()
{
    ProductList list;
    ShoppingCart cart;
    bool login = false;
    int q = 2;
    do
    {
        switch (q)
        {
        case 1:
            system("cls");
            if (login_admin)
                admin(list);
            else
                user(list, cart);
            break;
        case 2:
            system("cls");
            while (!login)
            {
                cout << "Login as \n1. Shopkeeper\n2. User\nChoice: ";
                int choice;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    admin(list);
                    login_admin = true;
                    login_user = false;
                    login = true;
                    break;
                case 2:
                    user(list, cart);
                    login_user = true;
                    login_admin = false;
                    login = true;
                    break;
                default:
                    break;
                }
            }
            login = false;
            break;
        case 3:
            return 0;
        default:
            cout << "Invalid choice...\n";
            break;
        }
        cout << "1.Want to continue...\n2.Go to login page\n3.exit\nChoice: ";
        cin >> q;
    } while (q != 3);
}