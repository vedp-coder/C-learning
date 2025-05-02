#include <stdio.h>

// Function declarations for calculator operations
float add(float a, float b) {
    return a + b;
}

float subtract(float a, float b) {
    return a - b;
}

float multiply(float a, float b) {
    return a * b;
}

float divide(float a, float b) {
    if (b != 0) {
        return a / b;
    } else {
        printf("Error: Division by zero!\n");
        return 0;
    }
}

int main() {
    int choice;
    float num1, num2, result;
    char repeat;
    
    printf("\n===== Simple Calculator =====\n");
    
    do {
        printf("\nEnter first number: ");
        scanf("%f", &num1);
        
        printf("Enter second number: ");
        scanf("%f", &num2);
        
        printf("\nOperations:\n");
        printf("1. Addition (+)\n");
        printf("2. Subtraction (-)\n");
        printf("3. Multiplication (*)\n");
        printf("4. Division (/)\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                result = add(num1, num2);
                printf("%.2f + %.2f = %.2f\n", num1, num2, result);
                break;
            case 2:
                result = subtract(num1, num2);
                printf("%.2f - %.2f = %.2f\n", num1, num2, result);
                break;
            case 3:
                result = multiply(num1, num2);
                printf("%.2f * %.2f = %.2f\n", num1, num2, result);
                break;
            case 4:
                result = divide(num1, num2);
                if (num2 != 0) {
                    printf("%.2f / %.2f = %.2f\n", num1, num2, result);
                }
                break;
            default:
                printf("Invalid choice!\n");
        }
        
        printf("\nDo another calculation? (y/n): ");
        scanf(" %c", &repeat);
        
    } while (repeat == 'y' || repeat == 'Y');
    
    printf("\nThank you for using the calculator!\n");
    
    return 0;
}
