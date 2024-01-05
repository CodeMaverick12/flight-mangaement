#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_FLIGHT 10
#define MAX_PASSENGERS 50
#define MAX_FOOD_ITEMS 5
struct flight{
    char flightnumber[10];
    char origin[20];
    int avaialble_seats;
    char destination[20];
    int totalhours;

};
struct passengers{
    char name[50];
    char flightnumber[10];
    char selectedfood[20];
    char comfortlevel[10];

};
struct foodmenu{
    char items[MAX_FOOD_ITEMS][20];
    int prices[MAX_FOOD_ITEMS];
    int itemscount;
};
struct airline{
    struct flight flights[MAX_FLIGHT];
    int flightcount;
    struct passengers passengers[MAX_PASSENGERS];
    int passengercount;
    struct foodmenu foodmenu;


};




