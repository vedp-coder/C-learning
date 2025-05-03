#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BOOKS 100
#define MAX_TITLE_LEN 100
#define MAX_AUTHOR_LEN 50
#define MAX_ID_LEN 20
#define FILENAME "library.dat"

// Book structure
typedef struct {
    char id[MAX_ID_LEN];       // Book ID
    char title[MAX_TITLE_LEN]; // Book title
    char author[MAX_AUTHOR_LEN]; // Author name
    int year;                  // Publication year
    int isAvailable;           // 1 if available, 0 if borrowed
    char borrower[50];         // Name of person who borrowed the book
} Book;

// Function prototypes
void mainMenu();
void addBook(Book library[], int *bookCount);
void displayBooks(Book library[], int bookCount);
void searchBook(Book library[], int bookCount);
void borrowBook(Book library[], int bookCount);
void returnBook(Book library[], int bookCount);
void saveToFile(Book library[], int bookCount);
int loadFromFile(Book library[]);
void generateID(char *id, int bookCount);
void clearInputBuffer();
int isValidYear(int year);

int main() {
    Book library[MAX_BOOKS];
    int bookCount = 0;
    int choice;
    
    // Load existing books from file
    bookCount = loadFromFile(library);
    
    printf("\n===== Library Management System =====\n");
    
    do {
        mainMenu();
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                addBook(library, &bookCount);
                break;
            case 2:
                displayBooks(library, bookCount);
                break;
            case 3:
                searchBook(library, bookCount);
                break;
            case 4:
                borrowBook(library, bookCount);
                break;
            case 5:
                returnBook(library, bookCount);
                break;
            case 6:
                saveToFile(library, bookCount);
                printf("\nExiting program. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
        
    } while (choice != 6);
    
    return 0;
}

// Function to display main menu
void mainMenu() {
    printf("\n===== Main Menu =====\n");
    printf("1. Add a new book\n");
    printf("2. Display all books\n");
    printf("3. Search for a book\n");
    printf("4. Borrow a book\n");
    printf("5. Return a book\n");
    printf("6. Save and exit\n");
    printf("Enter your choice (1-6): ");
}

// Function to add a new book
void addBook(Book library[], int *bookCount) {
    if (*bookCount >= MAX_BOOKS) {
        printf("\nLibrary is full. Cannot add more books.\n");
        return;
    }
    
    Book newBook;
    
    // Generate a unique ID for the book
    generateID(newBook.id, *bookCount);
    
    printf("\n===== Add New Book =====\n");
    printf("Book ID: %s (automatically generated)\n", newBook.id);
    
    printf("Enter title: ");
    fgets(newBook.title, MAX_TITLE_LEN, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0; // Remove newline
    
    printf("Enter author: ");
    fgets(newBook.author, MAX_AUTHOR_LEN, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0; // Remove newline
    
    int yearValid = 0;
    while (!yearValid) {
        printf("Enter publication year: ");
        scanf("%d", &newBook.year);
        clearInputBuffer();
        
        if (isValidYear(newBook.year)) {
            yearValid = 1;
        } else {
            printf("Invalid year. Please enter a year between 1000 and current year.\n");
        }
    }
    
    // Set as available by default
    newBook.isAvailable = 1;
    strcpy(newBook.borrower, "None");
    
    // Add book to library
    library[*bookCount] = newBook;
    (*bookCount)++;
    
    printf("\nBook added successfully!\n");
    printf("Book ID: %s\n", newBook.id);
}

// Function to display all books
void displayBooks(Book library[], int bookCount) {
    if (bookCount == 0) {
        printf("\nNo books in the library.\n");
        return;
    }
    
    printf("\n===== Library Books (%d) =====\n", bookCount);
    printf("%-10s %-30s %-20s %-6s %s\n", "ID", "Title", "Author", "Year", "Status");
    printf("-----------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < bookCount; i++) {
        printf("%-10s %-30s %-20s %-6d ", 
               library[i].id,
               library[i].title,
               library[i].author,
               library[i].year);
               
        if (library[i].isAvailable) {
            printf("Available\n");
        } else {
            printf("Borrowed by %s\n", library[i].borrower);
        }
    }
}

// Function to search for a book
void searchBook(Book library[], int bookCount) {
    if (bookCount == 0) {
        printf("\nNo books in the library.\n");
        return;
    }
    
    char searchTerm[100];
    int found = 0;
    
    printf("\n===== Search Books =====\n");
    printf("Enter search term (title, author, or ID): ");
    fgets(searchTerm, sizeof(searchTerm), stdin);
    searchTerm[strcspn(searchTerm, "\n")] = 0; // Remove newline
    
    // Convert search term to lowercase for case-insensitive search
    for (int i = 0; searchTerm[i]; i++) {
        searchTerm[i] = tolower(searchTerm[i]);
    }
    
    printf("\n===== Search Results =====\n");
    printf("%-10s %-30s %-20s %-6s %s\n", "ID", "Title", "Author", "Year", "Status");
    printf("-----------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < bookCount; i++) {
        // Create lowercase copies for comparison
        char titleLower[MAX_TITLE_LEN];
        char authorLower[MAX_AUTHOR_LEN];
        char idLower[MAX_ID_LEN];
        
        strcpy(titleLower, library[i].title);
        strcpy(authorLower, library[i].author);
        strcpy(idLower, library[i].id);
        
        for (int j = 0; titleLower[j]; j++) titleLower[j] = tolower(titleLower[j]);
        for (int j = 0; authorLower[j]; j++) authorLower[j] = tolower(authorLower[j]);
        for (int j = 0; idLower[j]; j++) idLower[j] = tolower(idLower[j]);
        
        // Check if search term matches title, author or ID
        if (strstr(titleLower, searchTerm) || 
            strstr(authorLower, searchTerm) || 
            strstr(idLower, searchTerm)) {
            
            printf("%-10s %-30s %-20s %-6d ", 
                   library[i].id,
                   library[i].title,
                   library[i].author,
                   library[i].year);
                   
            if (library[i].isAvailable) {
                printf("Available\n");
            } else {
                printf("Borrowed by %s\n", library[i].borrower);
            }
            
            found = 1;
        }
    }
    
    if (!found) {
        printf("No matching books found.\n");
    }
}

// Function to borrow a book
void borrowBook(Book library[], int bookCount) {
    if (bookCount == 0) {
        printf("\nNo books in the library.\n");
        return;
    }
    
    char bookID[MAX_ID_LEN];
    char borrower[50];
    int found = 0;
    
    displayBooks(library, bookCount);
    
    printf("\n===== Borrow a Book =====\n");
    printf("Enter the ID of the book to borrow: ");
    fgets(bookID, sizeof(bookID), stdin);
    bookID[strcspn(bookID, "\n")] = 0; // Remove newline
    
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(library[i].id, bookID) == 0) {
            found = 1;
            
            if (!library[i].isAvailable) {
                printf("\nThis book is already borrowed by %s.\n", library[i].borrower);
                return;
            }
            
            printf("Enter borrower's name: ");
            fgets(borrower, sizeof(borrower), stdin);
            borrower[strcspn(borrower, "\n")] = 0; // Remove newline
            
            library[i].isAvailable = 0;
            strcpy(library[i].borrower, borrower);
            
            printf("\nBook "%s" has been borrowed by %s.\n", library[i].title, borrower);
            saveToFile(library, bookCount); // Save changes to file
            return;
        }
    }
    
    if (!found) {
        printf("\nBook with ID %s not found.\n", bookID);
    }
}

// Function to return a book
void returnBook(Book library[], int bookCount) {
    if (bookCount == 0) {
        printf("\nNo books in the library.\n");
        return;
    }
    
    char bookID[MAX_ID_LEN];
    int found = 0;
    
    // Display only borrowed books
    printf("\n===== Currently Borrowed Books =====\n");
    printf("%-10s %-30s %-20s %s\n", "ID", "Title", "Author", "Borrower");
    printf("---------------------------------------------------------------\n");
    
    int borrowedCount = 0;
    for (int i = 0; i < bookCount; i++) {
        if (!library[i].isAvailable) {
            printf("%-10s %-30s %-20s %s\n", 
                   library[i].id,
                   library[i].title,
                   library[i].author,
                   library[i].borrower);
            borrowedCount++;
        }
    }
    
    if (borrowedCount == 0) {
        printf("No books are currently borrowed.\n");
        return;
    }
    
    printf("\n===== Return a Book =====\n");
    printf("Enter the ID of the book to return: ");
    fgets(bookID, sizeof(bookID), stdin);
    bookID[strcspn(bookID, "\n")] = 0; // Remove newline
    
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(library[i].id, bookID) == 0) {
            found = 1;
            
            if (library[i].isAvailable) {
                printf("\nThis book is not borrowed. It's already available in the library.\n");
                return;
            }
            
            printf("\nReturning book "%s" previously borrowed by %s.\n", 
                   library[i].title, library[i].borrower);
                   
            library[i].isAvailable = 1;
            strcpy(library[i].borrower, "None");
            
            saveToFile(library, bookCount); // Save changes to file
            printf("Book returned successfully!\n");
            return;
        }
    }
    
    if (!found) {
        printf("\nBook with ID %s not found.\n", bookID);
    }
}

// Function to save library to file
void saveToFile(Book library[], int bookCount) {
    FILE *file = fopen(FILENAME, "wb");
    
    if (file == NULL) {
        printf("\nError: Could not open file for writing.\n");
        return;
    }
    
    fwrite(&bookCount, sizeof(int), 1, file);
    fwrite(library, sizeof(Book), bookCount, file);
    
    fclose(file);
}

// Function to load library from file
int loadFromFile(Book library[]) {
    FILE *file = fopen(FILENAME, "rb");
    int bookCount = 0;
    
    if (file == NULL) {
        printf("\nNo existing library file found. Starting with an empty library.\n");
        return 0;
    }
    
    fread(&bookCount, sizeof(int), 1, file);
    fread(library, sizeof(Book), bookCount, file);
    
    fclose(file);
    printf("\nLoaded %d books from library file.\n", bookCount);
    
    return bookCount;
}

// Function to generate a unique book ID
void generateID(char *id, int bookCount) {
    sprintf(id, "B%04d", bookCount + 1);
}

// Function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to validate publication year
int isValidYear(int year) {
    int currentYear = 2023; // This should ideally be obtained from the system
    return (year >= 1000 && year <= currentYear);
}
