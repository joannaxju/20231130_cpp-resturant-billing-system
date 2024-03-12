#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct MenuItemType
{
    string menuItem;    
    double menuPrice;     
};

struct OrderItem
{
    MenuItemType item;    
    int quantity;         
};

void getData(vector<MenuItemType> &);  

void showMenu(vector<OrderItem> &, const vector<MenuItemType>);  

void printCheck(const vector<OrderItem>);

int main()
{
    vector<MenuItemType> menuList;
    vector<OrderItem> order;
  
    getData(menuList);
    showMenu(order, menuList);
    printCheck(order);
    return 0;
}

void getData(vector<MenuItemType> &menuList) 
{
    string menuFile;
    cout << "Enter filename: \n";
    cin >> menuFile;
    cout << endl;
  
    ifstream inFile;
    inFile.open(menuFile.c_str());
    while(inFile)
    {
        MenuItemType item;
        getline(inFile, item.menuItem, '$');
        inFile >> item.menuPrice;
        inFile.ignore(100, '\n');
        menuList.push_back(item);
    }
    inFile.close();
}

void showMenu(vector<OrderItem> &order, const vector<MenuItemType> menuList) 
{
    int itemNum, quantity;
    do
    {
        cout << "Welcome to the Restaurant\n\n";
        cout << "             Menu\n\n";
        for(int i = 0; i < menuList.size(); i++)
        {
            cout << i + 1 << ". " ;
            cout << left << setw(20);
            cout << menuList[i].menuItem << "$";
            cout << right << setw(5);
            cout << setprecision(2) << showpoint << fixed;
            cout << menuList[i].menuPrice;
            cout << endl;
        }
        cout << endl;
        cout << "Enter 0 when you finish your order.\n\n";

        cout << "Enter the item number: ";
        cin >> itemNum;
        if(itemNum != 0)
        {
            cout << "\nHow many would you like to order? ";
            cin >> quantity;
            cout << endl << endl << endl;
            OrderItem currentItem;
            currentItem.item = menuList[itemNum - 1];
            currentItem.quantity = quantity;
            order.push_back(currentItem);
        }
        else
            cout << endl << endl << endl;
    }
    while(itemNum != 0);
}

void printCheck(const vector<OrderItem> order) 
{
    double tax = 0, total = 0;
    cout << setprecision(2) << showpoint << fixed;
    cout << "Welcome to the Restaurant\n\n";
    cout << "             SALE\n\n";
    for(int i = 0; i < order.size(); i++)
    {
        cout << left << setw(3);
        cout << order[i].quantity;
        cout << left << setw(20);
        cout << order[i].item.menuItem << "$";
        cout << right << setw(5);
        cout << order[i].quantity * order[i].item.menuPrice;
        cout << endl;  
        tax += order[i].quantity * order[i].item.menuPrice;
        total += order[i].quantity * order[i].item.menuPrice;
    }
    tax = tax * 0.05;
    cout << "Tax";
    cout << left << setw(20) << " " << "$";   
    cout << right << setw(5) << tax << endl;
    cout << "-----------------------------" << endl;
    cout << "Amount Due             $";
    cout << setw(5) << total + tax << endl << endl;
}