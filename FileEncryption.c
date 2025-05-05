/*
 * Simple Text File Encryption/Decryption Program
 * Implements Caesar cipher for encrypting and decrypting text files
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Function to encrypt or decrypt a character using Caesar cipher
char processChar(char ch, int key, int encrypt) {
    // Only process alphabetic characters
    if (ch >= 'a' && ch <= 'z') {
        int offset = ch - 'a';
        if (encrypt) {
            return 'a' + ((offset + key) % 26);
        } else {
            return 'a' + ((offset - key + 26) % 26);
        }
    } else if (ch >= 'A' && ch <= 'Z') {
        int offset = ch - 'A';
        if (encrypt) {
            return 'A' + ((offset + key) % 26);
        } else {
            return 'A' + ((offset - key + 26) % 26);
        }
    }
    return ch; // Non-alphabetic characters remain unchanged
}

// Function to process (encrypt or decrypt) a file
int processFile(const char* inputPath, const char* outputPath, int key, int encrypt) {
    FILE *inputFile, *outputFile;
    char buffer[BUFFER_SIZE];
    size_t bytesRead;
    
    // Open input file for reading
    inputFile = fopen(inputPath, "r");
    if (inputFile == NULL) {
        printf("Error opening input file: %s\n", inputPath);
        return -1;
    }
    
    // Open output file for writing
    outputFile = fopen(outputPath, "w");
    if (outputFile == NULL) {
        printf("Error opening output file: %s\n", outputPath);
        fclose(inputFile);
        return -1;
    }
    
    // Process the file in chunks
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, inputFile)) > 0) {
        // Process each character in the buffer
        for (size_t i = 0; i < bytesRead; i++) {
            buffer[i] = processChar(buffer[i], key, encrypt);
        }
        
        // Write processed chunk to output file
        fwrite(buffer, 1, bytesRead, outputFile);
    }
    
    // Clean up
    fclose(inputFile);
    fclose(outputFile);
    
    return 0;
}

int main() {
    char inputPath[256];
    char outputPath[256];
    int key, choice;
    
    printf("=== Simple Text File Encryption/Decryption ===\n\n");
    
    printf("Enter operation (1 for encryption, 2 for decryption): ");
    scanf("%d", &choice);
    
    if (choice != 1 && choice != 2) {
        printf("Invalid choice. Exiting.\n");
        return -1;
    }
    
    printf("Enter the input file path: ");
    scanf("%s", inputPath);
    
    printf("Enter the output file path: ");
    scanf("%s", outputPath);
    
    printf("Enter the encryption key (1-25): ");
    scanf("%d", &key);
    
    if (key < 1 || key > 25) {
        printf("Invalid key. Key must be between 1 and 25.\n");
        return -1;
    }
    
    if (processFile(inputPath, outputPath, key, choice == 1) == 0) {
        if (choice == 1) {
            printf("File encrypted successfully.\n");
        } else {
            printf("File decrypted successfully.\n");
        }
    } else {
        printf("Operation failed.\n");
    }
    
    return 0;
}
