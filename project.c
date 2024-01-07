#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>


struct passenger {
    int id;
    char name[50];
    int seats;
    char origin[20];
    char destination[20];
} passenger;

// Function declarations
void flightBooking(void); // SECOND INTERFACE
void nationalFlight(void);
void internationalFlight(void);
void printcities(int choice);
int cityverification(int choice);
int passengerID(void);
void flightReview(void); // SECOND INTERFACE
void updateSeats(int id);
void updateOriginDestination(int id);
void flightCancel(void); // SECOND INTERFACE
void deletePassenger(int id);
int passengerVerification(int id, const char name[]); // VERIFICATION
void infostore(void); // STORAGE

//#########################################################################################
int main() { // FIRST INTERFACE

    system("cls");
    printf("\t\t*************************************************\n");
    printf("\t\t*                                               *\n");
    printf("\t\t*          AIRLINE MANAGEMENT SYSTEM            *\n");
    printf("\t\t*                                               *\n");
    printf("\t\t*************************************************\n\n");
    printf("1. TO BOOK A FLIGHT\n");
    printf("2. TO UPDATE FLIGHT\n");
    printf("3. TO CANCEL FLIGHT\n");
    printf("4. TO EXIT\n\n");

    int choice;
    printf("ENTER YOUR CHOICE: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            flightBooking();
            break;

        case 2:
            flightReview();
            break;

        case 3:
            flightCancel();
            break;

        case 4:
            system("cls");
            printf("Thank You!");
            sleep(2);
            exit(0);
            break;

        default:
            printf("INVALID CHOICE");
            getch();
            main();
            break;
    }

    return 0;
}

//#########################################################################################
void flightBooking(void) // SECOND INTERFACE
{
    flightBooking:
    system("cls");
    printf("1. Domestic Flight\n");
    printf("2. International Flight\n");
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            nationalFlight();
            break;

        case 2:
            internationalFlight();
            break;

        default:
            printf("INVALID CHOICE");
            sleep(2);
            goto flightBooking;
            break;
    }
    getch();
    main();
}

void nationalFlight(void) // THIRD INTERFACE
{
    int n;
    n = passengerID();
    printf("\nYour passenger ID is %d\n", n);
    printf("Enter your name: ");
    scanf("%s", passenger.name);
    printf("How many seats you want? ");
    scanf("%d", &passenger.seats);
    printcities(1);
    choice:
    printf("\nEnter your origin and destination: \n");
    scanf("%s %s", passenger.origin, passenger.destination);

    if (cityverification(1) == 0) {
        goto choice;
    }

    infostore();
    printf("FLIGHT BOOKED, THANK YOU!");
}

void internationalFlight(void) // THIRD INTERFACE
{
    int n;
    n = passengerID();
    printf("\nYour passenger ID is %d\n", n);
    printf("Enter your name: ");
    scanf("%s", passenger.name);
    printf("How many seats you want? ");
    scanf("%d", &passenger.seats);
    printcities(2);
    choice:
    printf("\nEnter your origin and destination: \n");
    scanf("%s %s", passenger.origin, passenger.destination);

    if (cityverification(2) == 0) {
        goto choice;
    }

    infostore();
    printf("YOUR FLIGHT IS BOOKED, THANK YOU!");
}

void printcities(int choice)
{
    FILE *fptr;
    char cityname[50];
    int count = 0;
    if (choice == 1) {
        fptr = fopen("nationalCities.txt", "r");
    } else {
        fptr = fopen("internationalCities.txt", "r");
    }

    if (fptr == NULL) {
        perror("Error opening file");
        exit(1);
    }

    while (fscanf(fptr, "%s", cityname) != EOF) {
        printf("%20s", cityname);
        count++;
        if (count % 4 == 0)
            printf("\n");
    }
    fclose(fptr);
}

int cityverification(int choice)
{
    if (strcmp(passenger.origin, passenger.destination) == 0) {
        return 0;
    }

    char cityname[50];
    int flag1 = 0, flag2 = 0;
    FILE *fptr;
    if (choice == 1) {
        fptr = fopen("nationalCities.txt", "r");
    } else {
        fptr = fopen("internationalCities.txt", "r");
    }

    if (fptr == NULL) {
        perror("Error opening file");
        exit(1);
    }

    while (fscanf(fptr, "%s", cityname) != EOF) {
        if (strcmp(passenger.origin, cityname) == 0) {
            flag1 = 1;
        }
        if (strcmp(passenger.destination, cityname) == 0) {
            flag2 = 1;
        }
    }

    fclose(fptr);

    if (flag1 == 1 && flag2 == 1) {
        return 1;
    }
    return 0;
}

int passengerID(void)
{
    int id;
    FILE *fptr;
    fptr = fopen("passengerID.txt", "r");

    if (fptr == NULL) {
        perror("Error opening file");
        exit(1);
    }

    fscanf(fptr, "%d", &id);
    fclose(fptr);
    id = id + 1;
    passenger.id = id;
    fptr = fopen("passengerID.txt", "w");
    fprintf(fptr, "%d", id);
    fclose(fptr);
    return id;
}

//#########################################################################################
void flightReview(void) // SECOND INTERFACE
{
    system("cls");
    int id;
    char name[50];

    printf("Enter your passenger ID: ");
    scanf("%d", &id);

    printf("Enter your name: ");
    scanf("%s", name);

    if (passengerVerification(id, name) == 1) {
        printf("\n1. Update Number of Seats\n");
        printf("2. Update Origin and Destination\n");
        printf("3. Go Back to Home Page\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                updateSeats(id);
                break;

            case 2:
                updateOriginDestination(id);
                break;

            case 3:
                main();
                break;

            default:
                printf("Invalid Choice\n");
                break;
        }
    } else {
        printf("Passenger not found\n");
    }
    getch();
    main();
}

void updateSeats(int id)
{
    FILE *fptr;
    int currentId;
    char currentName[50];
    int seats;
    char origin[20];
    char destination[20];

    fptr = fopen("infostore.txt", "r");

    if (fptr == NULL) {
        perror("Error opening file");
        exit(1);
    }

    FILE *tempFile = fopen("temp.txt", "w");

    if (tempFile == NULL) {
        perror("Error opening temporary file");
        exit(1);
    }

    while (fscanf(fptr, "%d %s %d %s %s", &currentId, currentName, &seats, origin, destination) != EOF) {
        if (currentId == id) {
            printf("\nEnter the new number of seats: ");
            scanf("%d", &seats);
        }
        fprintf(tempFile, "%d %s %d %s %s\n", currentId, currentName, seats, origin, destination);
    }

    fclose(fptr);
    fclose(tempFile);

    remove("infostore.txt");
    rename("temp.txt", "infostore.txt");

    printf("Number of seats updated successfully!\n");
}

void updateOriginDestination(int id)
{
    FILE *fptr;
    int currentId;
    char currentName[50];
    int seats;
    char origin[20];
    char destination[20];

    fptr = fopen("infostore.txt", "r");

    if (fptr == NULL) {
        perror("Error opening file");
        exit(1);
    }

    FILE *tempFile = fopen("temp.txt", "w");

    if (tempFile == NULL) {
        perror("Error opening temporary file");
        exit(1);
    }

    while (fscanf(fptr, "%d %s %d %s %s", &currentId, currentName, &seats, origin, destination) != EOF) {
        if (currentId == id) {
            printf("\nEnter the new origin: ");
            scanf("%s", origin);
            printf("Enter the new destination: ");
            scanf("%s", destination);
        }
        fprintf(tempFile, "%d %s %d %s %s\n", currentId, currentName, seats, origin, destination);
    }

    fclose(fptr);
    fclose(tempFile);

    remove("infostore.txt");
    rename("temp.txt", "infostore.txt");

    printf("Origin and destination updated successfully!\n");
}

//#########################################################################################
void flightCancel(void) // SECOND INTERFACE
{
    system("cls");
    int id;
    char name[50];
    char confirm;

    printf("Enter your passenger ID: ");
    scanf("%d", &id);

    printf("Enter your name: ");
    scanf("%s", name);

    if (passengerVerification(id, name) == 1) {
        printf("\nCONFIRMATION\nDo you want to CANCEL FLIGHT (Y/N): ");
        scanf(" %c", &confirm);

        if (confirm == 'Y' || confirm == 'y') {
            deletePassenger(id);
            printf("\nFLIGHT CANCELLED SUCCESSFULLY\n");
        } else {
            printf("\nCancellation aborted.\n");
        }
    } else {
        printf("Passenger not found\n");
    }

    getch();
    main();
}

void deletePassenger(int id)
{
    FILE *fptr;
    int currentId;
    char currentName[50];
    int seats;
    char origin[20];
    char destination[20];

    fptr = fopen("infostore.txt", "r");

    if (fptr == NULL) {
        perror("Error opening file");
        exit(1);
    }

    FILE *tempFile = fopen("temp.txt", "w");

    if (tempFile == NULL) {
        perror("Error opening temporary file");
        exit(1);
    }

    while (fscanf(fptr, "%d %s %d %s %s", &currentId, currentName, &seats, origin, destination) != EOF) {
        if (currentId == id) {
            continue;
        }
        fprintf(tempFile, "%d %s %d %s %s\n", currentId, currentName, seats, origin, destination);
    }

    fclose(fptr);
    fclose(tempFile);

    remove("infostore.txt");
    rename("temp.txt", "infostore.txt");

    printf("Passenger deleted successfully!\n");
}

//#########################################################################################
int passengerVerification(int id, const char name[]) // VERIFIACTION
{
    FILE *fptr;
    int currentId;
    char currentName[50];
    int seats;
    char origin[20];
    char destination[20];

    fptr = fopen("infostore.txt", "r");

    if (fptr == NULL) {
        perror("Error opening file");
        exit(1);
    }

    while (fscanf(fptr, "%d %s %d %s %s", &currentId, currentName, &seats, origin, destination) != EOF) {
        if (currentId == id && strcmp(currentName, name) == 0) {
            printf("\nPassenger Found\n");
            printf("Your current information:\n");
            printf("Seats = %d\n", seats);
            printf("Origin = %s\n", origin);
            printf("Destination = %s\n", destination);
            fclose(fptr);
            return 1; // Passenger found
        }
    }

    fclose(fptr);
    return 0; // Passenger not found
}

void infostore(void) // STORAGE
{
    FILE *fptr;
    fptr = fopen("infostore.txt", "a");

    if (fptr == NULL) {
        perror("Error opening file");
        exit(1);
    }

    fprintf(fptr, "%d %s %d %s %s\n", passenger.id, passenger.name, passenger.seats, passenger.origin, passenger.destination);
    fclose(fptr);
}
