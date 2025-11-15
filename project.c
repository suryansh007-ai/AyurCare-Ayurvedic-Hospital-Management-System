#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int id;
    char name[50];
    int exp;
    int stock;
}med;

void patientMenu()
{
    printf("\n--- Patient Management ---\n");
    // you will add code here later
}

void doctorMenu()
{
    printf("\n--- Doctor & Therapist Management ---\n");
    // you will add code here later
}

void inventoryMenu()
{
    printf("\n--- Medicine Inventory ---\n");
    // you will add code here later
}

void therapyMenu()
{
    printf("\n--- Panchkarma Therapy Schedule ---\n");
    // you will add code here later
}

void billingMenu()
{
    printf("\n--- Billing Section ---\n");
    int total;
    
}

void reportsMenu()
{
    printf("\n--- Reports Section ---\n");
    // you will add code here later
}

int main()
{
    int choice;

    while(1)
    {
        printf("\n=============================\n");
        printf("      AYURCARE SYSTEM\n");
        printf("=============================\n");
        printf("1. Patient Management\n");
        printf("2. Doctor and Therapist Management\n");
        printf("3. Medicine Inventory\n");
        printf("4. Panchkarma Therapy Schedule\n");
        printf("5. Billing\n");
        printf("6. Reports\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                patientMenu();
                break;

            case 2:
                doctorMenu();
                break;

            case 3:
                inventoryMenu();
                break;

            case 4:
                therapyMenu();
                break;

            case 5:
                billingMenu();
                break;

            case 6:
                reportsMenu();
                break;

            case 7:
                printf("\nExiting program...\n");
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}



