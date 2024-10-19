#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Car {
    int id;
    char model[100];
    int available;   
    float price;     
    int quantity;   
    struct Car* next;
} Car;

void addCar(Car** head, int id, const char* model, int available, float price, int quantity) {
    Car* newCar = (Car*)malloc(sizeof(Car));  
    newCar->id = id;                          
    strcpy(newCar->model, model);            
    newCar->available = available;            
    newCar->price = price;                   
    newCar->quantity = quantity;              
    newCar->next = *head;                   
    *head = newCar; 
}

void displayCars(Car* head) {
    Car* current = head;
    printf("Available Cars:\n");
    while (current != NULL) {
        printf("ID: %d, Model: %s, Price for 1 day: Rs%.2f, Available: %s, Quantity: %d\n", 
               current->id, current->model, current->price, 
               current->available ? "Yes" : "No", current->quantity);
        current = current->next;
    }
}

void rentCar(Car* head, int id) {
    Car* current = head;
    int hours;
    float totalCost;

    while (current != NULL) {
        if (current->id == id && current->available && current->quantity > 0) {
            printf("Enter rental duration in hours (3, 6, 12, 24): ");
            scanf("%d", &hours);

            if (hours != 3 && hours != 6 && hours != 12 && hours != 24) {
                printf("Invalid duration. Only 3, 6, 12, or 24 hours are allowed.\n");
                return;
            }

            if (hours == 24) {
                totalCost = current->price;  
            } else {
                totalCost = (current->price / 24) * hours; 
            }

            current->quantity -= 1;  
            if (current->quantity == 0) {
                current->available = 0;  
            }

            // Print the rental bill
            printf("\n--- Rental Bill ---\n");
            printf("Car Rented: %s\n", current->model);
            printf("Rental Duration: %d hours\n", hours);
            printf("Price per day: Rs%.2f\n", current->price);
            printf("Total Cost: Rs%.2f\n", totalCost);
            printf("-------------------\n");

            return;
        }
        current = current->next;
    }
    printf("Car with ID %d is not available for rent.\n", id);  
}

void sortCarsById(Car** head) {
    if (*head == NULL) {
        return;
    }
    
    Car* sorted = NULL;
    Car* current = *head;
    
    while (current != NULL) {
        Car* next = current->next;
        
        if (sorted == NULL || sorted->id >= current->id) {
            current->next = sorted;
            sorted = current;
        } else {
            Car* temp = sorted;
            while (temp->next != NULL && temp->next->id < current->id) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        
        current = next;
    }
    
    *head = sorted;
}

int main() {
    Car* head = NULL; 
    int choice, id;
    char model[100];
    float price;
    int quantity;

    addCar(&head, 3, "\tFord Mustang\t",            1, 115000, 5); 
    addCar(&head, 1, "\tToyota Supra MK4\t",        1, 75000, 3);  
    addCar(&head, 2, "\tHonda Civic\t",             1, 20000, 10);  
    addCar(&head, 4, "\tFortuner\t",                1, 45000, 4);  
    addCar(&head, 6, "\tMaruti Suzuki Brezza\t",    1, 7900, 12);  
    addCar(&head, 5, "\tBMW M340I\t",               1, 120000, 2);  
    addCar(&head, 7, "\tMecedes  Benz C Class\t",   1, 80000, 4);  
    
    sortCarsById(&head);

    while (1) {
        printf("\nCar Rental System Menu:\n");
        printf("1. Display Cars\n");
        printf("2. Rent a Car\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayCars(head);  
                break;
            case 2:
                printf("Enter Car ID to rent: ");
                scanf("%d", &id);  
                rentCar(head, id);  
                break;
            case 3:
                printf("Exiting...\n");
                exit(0); 
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
