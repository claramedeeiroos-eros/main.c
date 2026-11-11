#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "inventory.txt"

void addItem() {
    FILE *file = fopen(FILE_NAME, "a");

    char name[100];
    int quantity;

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter the item name: ");
    scanf(" %99[^\n]", name);

    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    if (quantity <= 0) {
        printf("Invalid quantity!\n");
        fclose(file);
        return;
    }

    fprintf(file, "%s\n%d\n", name, quantity);

    fclose(file);

    printf("Item added successfully!\n");
}

void removeItem() {
    FILE *file = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    char name[100];
    char itemName[100];
    int quantity, removeQuantity;
    int found = 0;

    if (file == NULL || temp == NULL) {
        printf("Error opening file!\n");
        if (file != NULL) fclose(file);
        if (temp != NULL) fclose(temp);
        return;
    }

    printf("Enter the item name: ");
    scanf(" %99[^\n]", name);

    printf("Enter the quantity to be removed: ");
    scanf("%d", &removeQuantity);

    if (removeQuantity <= 0) {
        printf("Invalid quantity!\n");
        fclose(file);
        fclose(temp);
        remove("temp.txt");
        return;
    }

    while (fscanf(file, " %99[^\n]", itemName) == 1) {
        if (fscanf(file, "%d", &quantity) != 1) {
            break;
        }

        if (strcmp(itemName, name) == 0 && !found) {
            found = 1;

            if (quantity >= removeQuantity) {
                quantity -= removeQuantity;

                if (quantity == 0) {
                    printf("Item removed from inventory!\n");
                    continue;
                } else {
                    printf("Quantity successfully updated!\n");
                }
            } else {
                printf("Insufficient stock. Available quantity: %d\n",
                       quantity);
            }
        }

        fprintf(temp, "%s\n%d\n", itemName, quantity);
    }

    if (!found) {
        printf("Item not found.\n");
    }

    fclose(file);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
}

void listInventory() {
    FILE *file = fopen(FILE_NAME, "r");

    char name[100];
    int quantity;
    int empty = 1;

    printf("=============================\n");
    printf("       Current Inventory\n");
    printf("=============================\n");

    if (file == NULL) {
        printf("The inventory is empty.\n");
        return;
    }

    while (fscanf(file, " %99[^\n]", name) == 1) {
        if (fscanf(file, "%d", &quantity) != 1) {
            break;
        }

        empty = 0;

        printf("Name: %s\n", name);
        printf("Quantity: %d\n\n", quantity);
    }

    if (empty) {
        printf("The inventory is empty.\n");
    }

    fclose(file);
}

int main() {
    int option;
    char again = 'y';

    while (again == 'y' || again == 'Y') {

        printf("\n==================================\n");
        printf("       Inventory Control\n");
        printf("==================================\n");

        printf("1. Add Item\n");
        printf("2. Remove Item\n");
        printf("3. List Inventory\n");
        printf("4. Exit\n");

        printf("Option: ");

        if (scanf("%d", &option) != 1) {
            printf("Invalid option! Please try again.\n");

            int c;
            while ((c = getchar()) != '\n' && c != EOF);

            continue;
        }

        switch (option) {

            case 1:
                addItem();
                break;

            case 2:
                removeItem();
                break;

            case 3:
                listInventory();
                break;

            case 4:
                printf("Thank you for using Inventory Control! See you next time.\n");
                return 0;

            default:
                printf("Invalid option! Please try again.\n");
                continue;
        }

        printf("\nDo you want to perform another operation? (y/n): ");
        scanf(" %c", &again);
    }

    printf("Thank you for using Inventory Control! See you next time.\n");

    return 0;
}