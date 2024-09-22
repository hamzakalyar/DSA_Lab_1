#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;


class House {
private:
    string owner;
    string address;
    int bedrooms;
    float price;

public:
    House() {
        owner = "";
        address = "";
        bedrooms = 0;
        price = 0.0;
    }

  
    void inputHouseDetails() {
        cout << "Enter owner's name (up to 20 characters): ";
        getline(cin, owner);
        if (owner.length() > 20) {
            owner = owner.substr(0, 20);  
        }

        cout << "Enter address (up to 20 characters): ";
        getline(cin, address);
        if (address.length() > 20) {
            address = address.substr(0, 20);  
        }

        cout << "Enter the number of bedrooms: ";
        cin >> bedrooms;

        cout << "Enter the price of the house: ";
        cin >> price;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }


    void displayHouseDetails() const {
        cout << "Owner: " << owner << endl;
        cout << "Address: " << address << endl;
        cout << "Bedrooms: " << bedrooms << endl;
        cout << fixed << setprecision(2);
        cout << "Price: $" << price << endl;
    }

    
    string getAddress() const {
        return address;
    }

    int getBedrooms() const {
        return bedrooms;
    }

    float getPrice() const {
        return price;
    }

    
    float getPriceToSizeRatio() const {
        return price / bedrooms;
    }
};


void searchHouses(const House houses[], int numHouses, float maxPrice, int minBedrooms, const string& city) {
    cout << "\nHouses that meet your criteria:\n";
    bool found = false;
    for (int i = 0; i < numHouses; ++i) {
        if ((maxPrice == -1 || houses[i].getPrice() <= maxPrice) &&
            (minBedrooms == -1 || houses[i].getBedrooms() >= minBedrooms) &&
            (city == "?" || houses[i].getAddress().find(city) != string::npos)) {
            houses[i].displayHouseDetails();
            cout << "-------------------------\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No houses meet your criteria.\n";
    }
}


void findHouseWithLowestPrice(const House houses[], int numHouses) {
    int index = 0;
    for (int i = 1; i < numHouses; ++i) {
        if (houses[i].getPrice() < houses[index].getPrice()) {
            index = i;
        }
    }

    cout << "\nHouse with the lowest price:\n";
    houses[index].displayHouseDetails();
}


void findLargestHouse(const House houses[], int numHouses) {
    int index = 0;
    for (int i = 1; i < numHouses; ++i) {
        if (houses[i].getBedrooms() > houses[index].getBedrooms()) {
            index = i;
        }
    }

    cout << "\nLargest house by number of bedrooms:\n";
    houses[index].displayHouseDetails();
}


void findBestPriceToSizeRatio(const House houses[], int numHouses) {
    int index = 0;
    for (int i = 1; i < numHouses; ++i) {
        if (houses[i].getPriceToSizeRatio() < houses[index].getPriceToSizeRatio()) {
            index = i;
        }
    }

    cout << "\nHouse with the best price/size ratio:\n";
    houses[index].displayHouseDetails();
}

int main() {
    const int MAX_HOUSES = 100;
    House available[MAX_HOUSES]; 
    int numHouses; 

    cout << "How many houses do you want to enter? (Max 100): ";
    cin >> numHouses;

    if (numHouses > MAX_HOUSES) {
        cout << "You can only enter up to 100 houses." << endl;
        return 1; 
    }

    cin.ignore(); 


    for (int i = 0; i < numHouses; ++i) {
        cout << "\nEntering details for house " << i + 1 << ":" << endl;
        available[i].inputHouseDetails();
    }

    system("cls");
    cout << "\nHouse details entered:" << endl;
    for (int i = 0; i < numHouses; ++i) {
        cout << "\nHouse " << i + 1 << ":" << endl;
        available[i].displayHouseDetails();
    }

    char choice;
    do {
        float maxPrice = -1;
        int minBedrooms = -1;
        string city;

        cout << "\nEnter maximum price (or ? to skip): ";
        string priceInput;
        cin >> priceInput;
        if (priceInput != "?") {
            maxPrice = stof(priceInput);
        }

        cout << "Enter minimum number of bedrooms (or ? to skip): ";
        string bedroomsInput;
        cin >> bedroomsInput;
        if (bedroomsInput != "?") {
            minBedrooms = stoi(bedroomsInput);
        }

        cout << "Enter city (or ? to skip): ";
        cin.ignore();
        getline(cin, city);

        searchHouses(available, numHouses, maxPrice, minBedrooms, city);

        findHouseWithLowestPrice(available, numHouses);
        findLargestHouse(available, numHouses);
        findBestPriceToSizeRatio(available, numHouses);

        cout << "\nDo you want to perform another search? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    return 0;
}
