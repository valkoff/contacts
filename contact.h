#ifndef CONTACT_H
#define CONTACT_H

typedef struct {
    char name[100];
    char phoneNumber[15];
    char email[100];
} Contact;

void addContact(const char *name, const char *phoneNumber, const char *email);
void listContacts();
void removeContact(const char *name);
void saveContact(Contact *contact);
void loadDatabase();
void saveDatabase();
void initDatabase();

#endif