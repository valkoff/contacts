#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "contact.h"
#include "vendor/cJSON/cJSON.h"

#define MAX_CONTACTS 100
#define FILENAME "storage/contacts.json"

cJSON *jsonContacts;
Contact contacts[MAX_CONTACTS];
int contactCount = 0;

void initDatabase() {   
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        // File does not exist, initialize the jsonContacts array
        jsonContacts = cJSON_CreateArray();
        // Save the empty array to the file
        saveDatabase();
        return;
    }
    fclose(file);
    loadDatabase();
}

void saveDatabase() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    char *jsonString = cJSON_Print(jsonContacts);
    fprintf(file, "%s", jsonString);
    free(jsonString);

    fclose(file);
}

void loadDatabase() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *jsonString = malloc(fileSize + 1);
    fread(jsonString, 1, fileSize, file);
    fclose(file);

    jsonString[fileSize] = '\0'; // Ensure null-terminated string
    jsonContacts = cJSON_Parse(jsonString);
    free(jsonString);

    if (jsonContacts == NULL) {
        printf("Error parsing JSON data.\n");
        return;
    }

    cJSON *contact;
    cJSON_ArrayForEach(contact, jsonContacts) {
        Contact *c = &contacts[contactCount];
        cJSON *name = cJSON_GetObjectItemCaseSensitive(contact, "name");
        cJSON *phoneNumber = cJSON_GetObjectItemCaseSensitive(contact, "phoneNumber");
        cJSON *email = cJSON_GetObjectItemCaseSensitive(contact, "email");

        if (cJSON_IsString(name) && cJSON_IsString(phoneNumber) && cJSON_IsString(email)) {
            snprintf(c->name, sizeof(c->name), "%s", name->valuestring);
            snprintf(c->phoneNumber, sizeof(c->phoneNumber), "%s", phoneNumber->valuestring);
            snprintf(c->email, sizeof(c->email), "%s", email->valuestring);
            contactCount++;
        }
    }
}

void saveContact(Contact *contact) {
    cJSON *jsonContact = cJSON_CreateObject();
    cJSON_AddStringToObject(jsonContact, "name", contact->name);
    cJSON_AddStringToObject(jsonContact, "phoneNumber", contact->phoneNumber);
    cJSON_AddStringToObject(jsonContact, "email", contact->email);
    cJSON_AddItemToArray(jsonContacts, jsonContact);
    saveDatabase();
}

void addContact(const char *name, const char *phoneNumber, const char *email) {
    if (contactCount >= MAX_CONTACTS) {
        printf("Contact list is full\n");
        return;
    }

    Contact *contact = &contacts[contactCount];
    snprintf(contact->name, sizeof(contact->name), "%s", name);
    snprintf(contact->phoneNumber, sizeof(contact->phoneNumber), "%s", phoneNumber);
    snprintf(contact->email, sizeof(contact->email), "%s", email);

    contactCount++;
    saveContact(contact);
    printf("Contact added\n");
}

void listContacts() {
    for (int i = 0; i < contactCount; i++) {
        Contact *contact = &contacts[i];
        printf("Name: %s\n", contact->name);
        printf("Phone: %s\n", contact->phoneNumber);
        printf("Email: %s\n", contact->email);
        printf("\n");
    }
}

void removeContact(const char *name) {
    for (int i = 0; i < contactCount; i++) {
        Contact *contact = &contacts[i];
        if (strcmp(contact->name, name) == 0) {
            for (int j = i; j < contactCount - 1; j++) {
                contacts[j] = contacts[j + 1];
            }

            contactCount--;
            saveDatabase();
            printf("Contact removed\n");
            return;
        }
    }

    printf("Contact not found\n");
}
