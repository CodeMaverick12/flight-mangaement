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

int main() {
    struct airline airline = {
        .flightcount = 3,
        .flights = {
            {"FL001", "karachi", "Dehli", 50, 6},
            {"FL002", "Quetta", "Mumbai", 30, 4},
            {"FL003", "Lahore", "Peshawar", 20, 3},
        },
        .passengercount = 0,
    };

    initializeFoodMenu(&airline.foodmenu);

    int choice;
    char flightnumber[10];
    char passengername[50];
    int foodchoice;
    char comfortlevel;

    do {
        // Display menu
        printf("\nAirline Management System\n");
        printf("1. Display Available Flights\n");
        printf("2. Display Passengers on a Flight\n");
        printf("3. Display Food Menu\n");
        printf("4. Book a Flight\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Display available flights
                displayFlights(&airline);
                break;
            case 2:
                // Display passengers on a flight
                printf("Enter Flight Number: ");
                scanf("%s", flightnumber);
                displayPassengers(&airline, flightnumber);
                break;
            case 3:
                // Display food menu
                displayFoodMenu(&airline.foodmenu);
                break;
            case 4:
                // Book a flight
                printf("Enter Flight Number: ");
                scanf("%s", flightnumber);
                printf("Enter Passenger Name: ");
                scanf("%s", passengername);
                printf("Select Food (Enter corresponding number from the menu): ");
                scanf("%d", &foodchoice);
                printf("Select Comfort Level (E for Economy, L for Luxury): ");
                scanf(" %c", &comfortlevel);
                bookFlight(&airline, flightnumber, passengername, foodchoice, comfortlevel);
                break;
            case 5:
                // Exit the program
                printf("Exiting Airline Management System. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5);

    return 0;
}


