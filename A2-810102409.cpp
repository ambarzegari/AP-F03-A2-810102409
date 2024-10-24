#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

const string REQUEST_SPOT = "request_spot";
const string ASSIGN_SPOT = "assign_spot";
const string CHECKOUT = "checkout";
const string PASS_TIME = "pass_time";

struct cars
{
    string name;
    int size;
};

struct parkings
{
    int id;
    int size;
    string type;
    bool status;
    int PastDays;
};

struct prices
{
    int size;
    int static_price;
    int price_per_day;
};

vector<cars> GetDataFromCarsFile(vector<cars> Car, char argv[])
{
    ifstream CarsFile(argv);
    string line, word;
    cars NewCar;
    getline(CarsFile, line);

    while (getline(CarsFile, line))
    {

        stringstream X(line);

        for (int i = 1; getline(X, word, ','); i++)
        {
            if (i == 1)
            {
                NewCar.name = word;
            }
            if (i == 2)
            {
                NewCar.size = stoi(word);
                Car.push_back(NewCar);
            }
        }
    }
    CarsFile.close();
    return Car;
}

vector<parkings> GetDataFromParkingsFile(vector<parkings> Parking, char argv[])
{
    ifstream ParkingFile(argv);
    string line, word;
    parkings NewParking;
    getline(ParkingFile, line);

    while (getline(ParkingFile, line))
    {

        stringstream X(line);

        for (int i = 1; getline(X, word, ','); i++)
        {
            if (i == 1)
            {
                NewParking.id = stoi(word);
            }
            if (i == 2)
            {
                NewParking.size = stoi(word);
            }
            if (i == 3)
            {
                NewParking.type = word;
                NewParking.status = true;
                NewParking.PastDays = 0;
                Parking.push_back(NewParking);
            }
        }
    }

    sort(Parking.begin(), Parking.end(),
         [](const parkings &left, const parkings &right)
         { return (left.id < right.id); });

    ParkingFile.close();
    return Parking;
}

vector<prices> GetDataFromPricesFile(vector<prices> Price, char argv[])
{
    ifstream PriceFile(argv);
    string line, word;
    prices NewPrice;
    getline(PriceFile, line);

    while (getline(PriceFile, line))
    {

        stringstream X(line);

        for (int i = 1; getline(X, word, ','); i++)
        {
            if (i == 1)
            {
                NewPrice.size = stoi(word);
            }
            if (i == 2)
            {
                NewPrice.static_price = stoi(word);
            }
            if (i == 3)
            {
                NewPrice.price_per_day = stoi(word);
                Price.push_back(NewPrice);
            }
        }
    }
    PriceFile.close();
    return Price;
}

void ShowProperParking(vector<cars> Car, vector<parkings> Parking, vector<prices> Price)
{

    string CarName;
    int size;
    cin >> CarName;

    int static_price;
    int price_per_day;

    for (int i = 0; i < Car.size(); i++)
    {
        if (Car[i].name == CarName)
        {
            size = Car[i].size;
        }
    }

    for (int i = 0; i < Price.size(); i++)
    {
        if (Price[i].size == size)
        {
            static_price = Price[i].static_price;
            price_per_day = Price[i].price_per_day;
        }
    }

    for (int i = 0; i < Parking.size(); i++)
    {
        if (Parking[i].size == size && Parking[i].status == true)
        {
            if (Parking[i].type == "normal")
            {
                cout << Parking[i].id << ": " << Parking[i].type << " " << static_price << " " << price_per_day << endl;
            }

            else if (Parking[i].type == "covered")
            {
                cout << Parking[i].id << ": " << Parking[i].type << " " << static_price + 50 << " " << price_per_day + 30 << endl;
            }
            else if (Parking[i].type == "CCTV")
            {
                cout << Parking[i].id << ": " << Parking[i].type << " " << static_price + 80 << " " << price_per_day + 60 << endl;
            }
        }
    }
}

vector<parkings> AssignSpot(vector<parkings> Parking)
{

    int parking_id;
    cin >> parking_id;

    for (int i = 0; i < Parking.size(); i++)
    {
        if (Parking[i].id == parking_id)
        {
            Parking[i].status = false;
            cout << "Spot " << parking_id << " is occupied now." << endl;
        }
    }

    return Parking;
}

vector<parkings> PassTime(vector<parkings> Parking)
{

    int past_days;
    cin >> past_days;

    for (int i = 0; i < Parking.size(); i++)
    {
        if (Parking[i].status == false)
        {
            Parking[i].PastDays += past_days;
        }
    }

    return Parking;
}

vector<parkings> CheckOut(vector<parkings> Parking, vector<prices> Price)
{

    int total_cost = 0;
    int parking_id;

    int cost_1 = 0; 
    int cost_2 = 0; 

    cin >> parking_id;

    for (int i = 0; i < Parking.size(); i++)
    {
        if (Parking[i].id == parking_id)
        {
            if (Parking[i].type == "normal")
            {
                cost_1 = Price[Parking[i].size - 1].static_price;
                cost_2 = Price[Parking[i].size - 1].price_per_day;
            }
            else if (Parking[i].type == "covered")
            {
                cost_1 = Price[Parking[i].size - 1].static_price + 50;
                cost_2 = Price[Parking[i].size - 1].price_per_day + 30;
            }
            else if (Parking[i].type == "CCTV")
            {
                cost_1 = Price[Parking[i].size - 1].static_price + 80;
                cost_2 = Price[Parking[i].size - 1].price_per_day + 60;
            }
            total_cost = cost_1 + cost_2 * Parking[i].PastDays;

            Parking[i].status = true;
            Parking[i].PastDays = 0;
            cout << "Spot " << parking_id << " is free now." << endl;
            cout << "Total cost: " << total_cost << endl;
        }
    }

    return Parking;
}

int main(int argc, char *argv[])
{

    vector<cars> Car;
    vector<parkings> Parking;
    vector<prices> Price;

    string input;

    Car = GetDataFromCarsFile(Car, argv[1]);
    Parking = GetDataFromParkingsFile(Parking, argv[2]);
    Price = GetDataFromPricesFile(Price, argv[3]);

    while (cin >> input)
    {
        if (input == REQUEST_SPOT)
        {
            ShowProperParking(Car, Parking, Price);
        }
        else if (input == ASSIGN_SPOT)
        {
            Parking = AssignSpot(Parking);
        }
        else if (input == CHECKOUT)
        {
            Parking = CheckOut(Parking, Price);
        }
        else if (input == PASS_TIME)
        {
            Parking = PassTime(Parking);
        }
    }

    return 0;
}