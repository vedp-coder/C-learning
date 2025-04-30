#include <stdio.h>

void celsius_to_fahrenheit(float celsius) {
    float fahrenheit = (celsius * 9 / 5) + 32;
    printf("%.2f Celsius = %.2f Fahrenheit\n", celsius, fahrenheit);
}

void celsius_to_kelvin(float celsius) {
    float kelvin = celsius + 273.15;
    printf("%.2f Celsius = %.2f Kelvin\n", celsius, kelvin);
}

void fahrenheit_to_celsius(float fahrenheit) {
    float celsius = (fahrenheit - 32) * 5 / 9;
    printf("%.2f Fahrenheit = %.2f Celsius\n", fahrenheit, celsius);
}

void fahrenheit_to_kelvin(float fahrenheit) {
    float kelvin = (fahrenheit - 32) * 5 / 9 + 273.15;
    printf("%.2f Fahrenheit = %.2f Kelvin\n", fahrenheit, kelvin);
}

void kelvin_to_celsius(float kelvin) {
    float celsius = kelvin - 273.15;
    printf("%.2f Kelvin = %.2f Celsius\n", kelvin, celsius);
}

void kelvin_to_fahrenheit(float kelvin) {
    float fahrenheit = (kelvin - 273.15) * 9 / 5 + 32;
    printf("%.2f Kelvin = %.2f Fahrenheit\n", kelvin, fahrenheit);
}

int main() {
    int choice;
    float temperature;

    printf("\n===== Temperature Converter =====\n");
    
    do {
        printf("\nConversion Options:\n");
        printf("1. Celsius to Fahrenheit\n");
        printf("2. Celsius to Kelvin\n");
        printf("3. Fahrenheit to Celsius\n");
        printf("4. Fahrenheit to Kelvin\n");
        printf("5. Kelvin to Celsius\n");
        printf("6. Kelvin to Fahrenheit\n");
        printf("0. Exit\n");
        printf("Enter your choice (0-6): ");
        scanf("%d", &choice);
        
        if (choice >= 1 && choice <= 6) {
            printf("Enter the temperature value: ");
            scanf("%f", &temperature);
        }
        
        switch(choice) {
            case 1:
                celsius_to_fahrenheit(temperature);
                break;
            case 2:
                celsius_to_kelvin(temperature);
                break;
            case 3:
                fahrenheit_to_celsius(temperature);
                break;
            case 4:
                fahrenheit_to_kelvin(temperature);
                break;
            case 5:
                kelvin_to_celsius(temperature);
                break;
            case 6:
                kelvin_to_fahrenheit(temperature);
                break;
            case 0:
                printf("Exiting temperature converter. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
    
    return 0;
}
