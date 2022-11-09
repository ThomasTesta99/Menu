#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>.
using namespace std;

class MenuItem{
public:
    string menuItem;
    double menuPrice;
    int count = 0;
};

class Menu{
private:
    int menuCapacity;
    int menuSize;
    MenuItem* menu;
public:
    Menu(){
        menuCapacity = 10;
        menu = new MenuItem[menuCapacity];
    }
    void fillMenu();
    void displayMenu();
    void order();
    void check();
    ~Menu(){delete [] menu;}
};

class Resturant{
private:
    Menu resturantMenu;
public:
    void createMenu()  {resturantMenu.fillMenu();}
    void displayMenu() {resturantMenu.displayMenu();}
    void beginOrder() {resturantMenu.order();}
    void checkOut() {resturantMenu.check();}
};

void Menu::fillMenu(){
    ifstream menuList;
    menuList.open("menu.txt");
    if(!menuList){
        cout << "File not found" << endl;
        exit(1);
    }
    
    int countMenuLength = 0, itemNum = 0;
    while(!menuList.eof() && getline(menuList, menu[itemNum].menuItem,'$') && menuList >> menu[itemNum].menuPrice){
        itemNum++;
        countMenuLength++;
        if(countMenuLength >= menuCapacity){
            menuCapacity*=2;
            MenuItem* temp = new MenuItem[menuCapacity];
            for(int i=0; i< countMenuLength; i++){
                temp[i].menuItem = menu[i].menuItem;
                temp[i].menuPrice = menu[i].menuPrice;
            }
            delete [] menu;
            menu = temp;
        }
    }
    menuSize = countMenuLength;
}

void Menu::displayMenu(){
    cout << "Menu: " << endl;
    for(int i=0; i<menuSize; i++){
        cout << menu[i].menuItem << "$" << menu[i].menuPrice;
    }
    cout << endl;
}

void Menu::order(){
    string name;
    int amount = 1, numInMenu = 0;
    char add = 'y';
    while(add == 'y' || add == 'Y'){
        cout << "\nPlease type the number of the item you would like" << endl;
        cin >> numInMenu;
        cout << "How many would you like?\n";
        cin >> amount;
        menu[numInMenu-1].count = amount;
        cout << "\nWould you like another item? Please type 'y' or 'n'\n";
        cin >> add;
    }
}

void Menu::check(){
    double sum = 0;
    const double tax = 0.0833;
    
    ofstream check;
    check.open("Check.txt");
    
    check << "Here is your bill: \n" << endl;
    for(int i=0; i<menuSize; i++){
        if(menu[i].count >= 1){
            check << left << setw(32) << menu[i].menuItem << setw(10) << menu[i].count << setw(8) << menu[i].menuPrice;
            sum += (menu[i].menuPrice * menu[i].count);
        }
    }
    check << endl << endl;
    double total = sum+(sum*tax);
    check << "Subtotal: $" << sum << endl;
    check << "Tax: " << 100 * tax << "%" << endl;
    check << "Grand total: $" << total << endl;
}

int main(){
    cout << fixed << setprecision(2);
    Resturant resturant;
    resturant.createMenu();
    resturant.displayMenu();
    resturant.beginOrder();
    resturant.checkOut();
}
