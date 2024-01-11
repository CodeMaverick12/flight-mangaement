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