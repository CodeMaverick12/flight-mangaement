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
void initializeFoodMenu(struct FoodMenu *foodMenu) {
    foodMenu->itemCount = 3;
    strcpy(foodMenu->items[0], "Snack Box");
    strcpy(foodMenu->items[1], "Vegetarian Meal");
    strcpy(foodMenu->items[2], "Chicken Meal");
    foodMenu->prices[0] = 5;
    foodMenu->prices[1] = 10;
    foodMenu->prices[2] = 12;
}

void displayFoodMenu(struct FoodMenu *foodMenu) {
    printf("\nFood Menu:\n");
    for (int i = 0; i < foodMenu->itemCount; i++) {
        printf("%d. %s - Rs%d\n", i + 1, foodMenu->items[i], foodMenu->prices[i]);
    }
}

void displayFlights(struct Airline *airline) {
    printf("\nAvailable Flights:\n");
    for (int i = 0; i < airline->flightCount; i++) {
        printf("%s: %s to %s, Total Hours: %d, Available Seats: %d\n", airline->flights[i].flightNumber,
               airline->flights[i].origin, airline->flights[i].destination, airline->flights[i].totalHours,
               airline->flights[i].availableSeats);
    }
}

void displayPassengers(struct Airline *airline, char flightNumber[]) {
    printf("\nPassengers on Flight %s:\n", flightNumber);
    for (int i = 0; i < airline->passengerCount; i++) {
        if (strcmp(airline->passengers[i].flightNumber, flightNumber) == 0) {
            printf("%s - Comfort Level: %s, Food: %s\n", airline->passengers[i].name,
                   airline->passengers[i].comfortLevel, airline->passengers[i].selectedFood);
        }
    }
}

void bookFlight(struct Airline *airline, char flightNumber[], char passengerName[], int foodChoice, char comfortLevel) {
    for (int i = 0; i < airline->flightCount; i++) {
        if (strcmp(airline->flights[i].flightNumber, flightNumber) == 0) {
            if (airline->flights[i].availableSeats > 0) {
                strcpy(airline->passengers[airline->passengerCount].name, passengerName);
                strcpy(airline->passengers[airline->passengerCount].flightNumber, flightNumber);
                strcpy(airline->passengers[airline->passengerCount].selectedFood,
                       airline->foodMenu.items[foodChoice - 1]);
                strcpy(airline->passengers[airline->passengerCount].comfortLevel, (comfortLevel == 'E') ? "Economy" : "Luxury");
                airline->passengerCount++;
                airline->flights[i].availableSeats--;
                printf("Booking successful!\n");
            } else {
                printf("Sorry, no available seats on this flight.\n");
            }
            return;
        }
    }
    printf("Invalid flight number.\n");
}

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


