#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CONTACTS 100
#define MAX_NAME_LEN 50
#define MAX_PHONE_LEN 15
#define MAX_EMAIL_LEN 50
#define MAX_ADDRESS_LEN 100
#define FILENAME "contacts.dat"

// Structure for a contact
typedef struct {
    char name[MAX_NAME_LEN];
    char phone[MAX_PHONE_LEN];
    char email[MAX_EMAIL_LEN];
    char address[MAX_ADDRESS_LEN];
} Contact;

// Function prototypes
void displayMenu();
void addContact(Contact contacts[], int *contactCount);
void viewContacts(Contact contacts[], int contactCount);
void searchContact(Contact contacts[], int contactCount);
void editContact(Contact contacts[], int contactCount);
void deleteContact(Contact contacts[], int *contactCount);
void sortContacts(Contact contacts[], int contactCount);
void saveToFile(Contact contacts[], int contactCount);
int loadFromFile(Contact contacts[]);
int isValidEmail(const char *email);
int isValidPhone(const char *phone);
void clearInputBuffer();

int main() {
    Contact contacts[MAX_CONTACTS];
    int contactCount = 0;
    int choice;
    
    // Load existing contacts
    contactCount = loadFromFile(contacts);
    
    printf("\n===== Contact Management System =====\n");
    
    do {
        displayMenu();
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch(choice) {
            case 1:
                addContact(contacts, &contactCount);
                break;
            case 2:
                viewContacts(contacts, contactCount);
                break;
            case 3:
                searchContact(contacts, contactCount);
                break;
            case 4:
                editContact(contacts, contactCount);
                break;
            case 5:
                deleteContact(contacts, &contactCount);
                break;
            case 6:
                sortContacts(contacts, contactCount);
                viewContacts(contacts, contactCount);
                break;
            case 7:
                saveToFile(contacts, contactCount);
                printf("Contacts saved successfully.\n");
                break;
            case 0:
                saveToFile(contacts, contactCount);
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);
    
    return 0;
}

// Function to display the menu
void displayMenu() {
    printf("\n===== Main Menu =====\n");
    printf("1. Add a new contact\n");
    printf("2. View all contacts\n");
    printf("3. Search for a contact\n");
    printf("4. Edit a contact\n");
    printf("5. Delete a contact\n");
    printf("6. Sort contacts by name\n");
    printf("7. Save contacts to file\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

// Function to add a new contact
void addContact(Contact contacts[], int *contactCount) {
    if (*contactCount >= MAX_CONTACTS) {
        printf("Contact list is full!\n");
        return;
    }
    
    Contact newContact;
    int valid;
    
    printf("\n===== Add New Contact =====\n");
    
    printf("Enter name: ");
    fgets(newContact.name, MAX_NAME_LEN, stdin);
    newContact.name[strcspn(newContact.name, "\n")] = 0;
    
    // Get phone with validation
    do {
        printf("Enter phone number: ");
        fgets(newContact.phone, MAX_PHONE_LEN, stdin);
        newContact.phone[strcspn(newContact.phone, "\n")] = 0;
        
        valid = isValidPhone(newContact.phone);
        if (!valid) {
            printf("Invalid phone number! Use only digits, +, -, and spaces.\n");
        }
    } while (!valid);
    
    // Get email with validation
    do {
        printf("Enter email: ");
        fgets(newContact.email, MAX_EMAIL_LEN, stdin);
        newContact.email[strcspn(newContact.email, "\n")] = 0;
        
        valid = isValidEmail(newContact.email);
        if (!valid) {
            printf("Invalid email format!\n");
        }
    } while (!valid);
    
    printf("Enter address: ");
    fgets(newContact.address, MAX_ADDRESS_LEN, stdin);
    newContact.address[strcspn(newContact.address, "\n")] = 0;
    
    contacts[*contactCount] = newContact;
    (*contactCount)++;
    
    printf("Contact added successfully!\n");
}

// Function to display all contacts
void viewContacts(Contact contacts[], int contactCount) {
    if (contactCount == 0) {
        printf("No contacts to display.\n");
        return;
    }
    
    printf("\n===== Contact List (%d contacts) =====\n", contactCount);
    printf("%-4s %-20s %-15s %-25s %s\n", "No.", "Name", "Phone", "Email", "Address");
    printf("----------------------------------------------------------------------------\n");
    
    for (int i = 0; i < contactCount; i++) {
        printf("%-4d %-20s %-15s %-25s %s\n", 
               i+1, 
               contacts[i].name, 
               contacts[i].phone, 
               contacts[i].email, 
               contacts[i].address);
    }
}

// Function to search for a contact
void searchContact(Contact contacts[], int contactCount) {
    if (contactCount == 0) {
        printf("No contacts available to search.\n");
        return;
    }
    
    char searchTerm[50];
    int found = 0;
    
    printf("Enter search term (name, phone, or email): ");
    fgets(searchTerm, sizeof(searchTerm), stdin);
    searchTerm[strcspn(searchTerm, "\n")] = 0;
    
    // Convert search term to lowercase for case-insensitive search
    for (int i = 0; searchTerm[i]; i++) {
        searchTerm[i] = tolower(searchTerm[i]);
    }
    
    printf("\n===== Search Results =====\n");
    printf("%-4s %-20s %-15s %-25s %s\n", "No.", "Name", "Phone", "Email", "Address");
    printf("----------------------------------------------------------------------------\n");
    
    for (int i = 0; i < contactCount; i++) {
        // Create lowercase copies for comparison
        char nameLower[MAX_NAME_LEN];
        char phoneLower[MAX_PHONE_LEN];
        char emailLower[MAX_EMAIL_LEN];
        
        strcpy(nameLower, contacts[i].name);
        strcpy(phoneLower, contacts[i].phone);
        strcpy(emailLower, contacts[i].email);
        
        for (int j = 0; nameLower[j]; j++) nameLower[j] = tolower(nameLower[j]);
        for (int j = 0; phoneLower[j]; j++) phoneLower[j] = tolower(phoneLower[j]);
        for (int j = 0; emailLower[j]; j++) emailLower[j] = tolower(emailLower[j]);
        
        // Check if search term is in name, phone or email
        if (strstr(nameLower, searchTerm) || 
            strstr(phoneLower, searchTerm) || 
            strstr(emailLower, searchTerm)) {
            
            printf("%-4d %-20s %-15s %-25s %s\n", 
                   i+1, 
                   contacts[i].name, 
                   contacts[i].phone, 
                   contacts[i].email, 
                   contacts[i].address);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No matching contacts found.\n");
    }
}

// Function to edit a contact
void editContact(Contact contacts[], int contactCount) {
    if (contactCount == 0) {
        printf("No contacts available to edit.\n");
        return;
    }
    
    int index, choice, valid;
    
    viewContacts(contacts, contactCount);
    
    printf("\nEnter the number of the contact to edit (1-%d): ", contactCount);
    scanf("%d", &index);
    clearInputBuffer();
    
    if (index < 1 || index > contactCount) {
        printf("Invalid contact number!\n");
        return;
    }
    
    // Adjust index to 0-based
    index--;
    
    printf("\nEditing contact: %s\n", contacts[index].name);
    printf("1. Edit name\n");
    printf("2. Edit phone\n");
    printf("3. Edit email\n");
    printf("4. Edit address\n");
    printf("5. Edit all fields\n");
    printf("0. Cancel\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    clearInputBuffer();
    
    switch(choice) {
        case 1:
            printf("Enter new name: ");
            fgets(contacts[index].name, MAX_NAME_LEN, stdin);
            contacts[index].name[strcspn(contacts[index].name, "\n")] = 0;
            break;
        case 2:
            do {
                printf("Enter new phone number: ");
                fgets(contacts[index].phone, MAX_PHONE_LEN, stdin);
                contacts[index].phone[strcspn(contacts[index].phone, "\n")] = 0;
                
                valid = isValidPhone(contacts[index].phone);
                if (!valid) {
                    printf("Invalid phone number! Use only digits, +, -, and spaces.\n");
                }
            } while (!valid);
            break;
        case 3:
            do {
                printf("Enter new email: ");
                fgets(contacts[index].email, MAX_EMAIL_LEN, stdin);
                contacts[index].email[strcspn(contacts[index].email, "\n")] = 0;
                
                valid = isValidEmail(contacts[index].email);
                if (!valid) {
                    printf("Invalid email format!\n");
                }
            } while (!valid);
            break;
        case 4:
            printf("Enter new address: ");
            fgets(contacts[index].address, MAX_ADDRESS_LEN, stdin);
            contacts[index].address[strcspn(contacts[index].address, "\n")] = 0;
            break;
        case 5:
            printf("Enter new name: ");
            fgets(contacts[index].name, MAX_NAME_LEN, stdin);
            contacts[index].name[strcspn(contacts[index].name, "\n")] = 0;
            
            do {
                printf("Enter new phone number: ");
                fgets(contacts[index].phone, MAX_PHONE_LEN, stdin);
                contacts[index].phone[strcspn(contacts[index].phone, "\n")] = 0;
                
                valid = isValidPhone(contacts[index].phone);
                if (!valid) {
                    printf("Invalid phone number! Use only digits, +, -, and spaces.\n");
                }
            } while (!valid);
            
            do {
                printf("Enter new email: ");
                fgets(contacts[index].email, MAX_EMAIL_LEN, stdin);
                contacts[index].email[strcspn(contacts[index].email, "\n")] = 0;
                
                valid = isValidEmail(contacts[index].email);
                if (!valid) {
                    printf("Invalid email format!\n");
                }
            } while (!valid);
            
            printf("Enter new address: ");
            fgets(contacts[index].address, MAX_ADDRESS_LEN, stdin);
            contacts[index].address[strcspn(contacts[index].address, "\n")] = 0;
            break;
        case 0:
            return;
        default:
            printf("Invalid choice!\n");
            return;
    }
    
    printf("Contact updated successfully!\n");
}

// Function to delete a contact
void deleteContact(Contact contacts[], int *contactCount) {
    if (*contactCount == 0) {
        printf("No contacts available to delete.\n");
        return;
    }
    
    int index;
    char confirm;
    
    viewContacts(contacts, *contactCount);
    
    printf("\nEnter the number of the contact to delete (1-%d): ", *contactCount);
    scanf("%d", &index);
    clearInputBuffer();
    
    if (index < 1 || index > *contactCount) {
        printf("Invalid contact number!\n");
        return;
    }
    
    // Adjust index to 0-based
    index--;
    
    printf("Are you sure you want to delete %s? (y/n): ", contacts[index].name);
    scanf(" %c", &confirm);
    clearInputBuffer();
    
    if (tolower(confirm) != 'y') {
        printf("Deletion cancelled.\n");
        return;
    }
    
    // Shift all elements after the deleted one
    for (int i = index; i < *contactCount - 1; i++) {
        contacts[i] = contacts[i + 1];
    }
    
    (*contactCount)--;
    printf("Contact deleted successfully!\n");
}

// Function to sort contacts alphabetically by name
void sortContacts(Contact contacts[], int contactCount) {
    if (contactCount <= 1) {
        return; // No need to sort
    }
    
    Contact temp;
    
    // Simple bubble sort
    for (int i = 0; i < contactCount - 1; i++) {
        for (int j = 0; j < contactCount - i - 1; j++) {
            if (strcasecmp(contacts[j].name, contacts[j+1].name) > 0) {
                // Swap contacts
                temp = contacts[j];
                contacts[j] = contacts[j+1];
                contacts[j+1] = temp;
            }
        }
    }
    
    printf("Contacts sorted by name!\n");
}

// Function to save contacts to file
void saveToFile(Contact contacts[], int contactCount) {
    FILE *file = fopen(FILENAME, "wb");
    
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    
    fwrite(&contactCount, sizeof(int), 1, file);
    fwrite(contacts, sizeof(Contact), contactCount, file);
    
    fclose(file);
}

// Function to load contacts from file
int loadFromFile(Contact contacts[]) {
    FILE *file = fopen(FILENAME, "rb");
    int contactCount = 0;
    
    if (file == NULL) {
        return 0; // No existing file or error opening
    }
    
    fread(&contactCount, sizeof(int), 1, file);
    
    if (contactCount > 0 && contactCount <= MAX_CONTACTS) {
        fread(contacts, sizeof(Contact), contactCount, file);
    } else {
        contactCount = 0; // Reset if invalid count
    }
    
    fclose(file);
    return contactCount;
}

// Function to validate email format
int isValidEmail(const char *email) {
    int atCount = 0, dotCount = 0;
    int atPos = -1, dotPos = -1;
    int len = strlen(email);
    
    // Check for minimum length
    if (len < 5) return 0;
    
    // Check for @ and . characters
    for (int i = 0; i < len; i++) {
        if (email[i] == '@') {
            atCount++;
            atPos = i;
        } else if (email[i] == '.') {
            dotCount++;
            dotPos = i;
        }
    }
    
    // Basic checks for valid email format
    if (atCount != 1 || dotCount < 1) return 0;
    if (atPos == 0 || atPos == len - 1) return 0;
    if (dotPos < atPos || dotPos == len - 1) return 0;
    
    return 1;
}

// Function to validate phone number
int isValidPhone(const char *phone) {
    int len = strlen(phone);
    
    // Check for minimum length
    if (len < 7) return 0;
    
    // Check for valid characters (digits, +, -, space)
    for (int i = 0; i < len; i++) {
        if (!isdigit(phone[i]) && phone[i] != '+' && phone[i] != '-' && phone[i] != ' ') {
            return 0;
        }
    }
    
    return 1;
}

// Function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
