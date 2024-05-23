#include <stdio.h>
#include "contact.h"

void showMenu() {
    printf("1. Add contact\n");
    printf("2. List contacts\n");
    printf("3. Remove contact\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    char name[100];
    char phoneNumber[15];
    char email[100];

    initDatabase();

    while (1) {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter phoneNumber number: ");
                scanf("%s", phoneNumber);
                printf("Enter email: ");
                scanf("%s", email);
                addContact(name, phoneNumber, email);
                break;
            case 2:
                listContacts();
                break;
            case 3:
                printf("Enter name: ");
                scanf("%s", name);
                removeContact(name);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}