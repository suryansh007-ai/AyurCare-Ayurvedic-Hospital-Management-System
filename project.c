#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int id;
    char name[50];
    int exp;
    int stock;
}med;

struct patient
{
    int patient_id;
    char name[100];
    char address[300];
    long long int phone_no;
};
void patientMenu()
{
    int choice,count=0,store;
    long long int temp;
    static int imp=0;
    printf("\n--- Patient Management ---\n");
    printf("1.Add new patient details\n2.Edit patient detials\n3.Delete Patient Detials\nEnter your choice:");
    scanf("%d",&choice);
    struct patient p[1000];
    switch(choice)
        {
          case 1:
          {FILE *fp=fopen("patient.txt","a");
          printf("Enter patient ID:");
          scanf("%d",&p[imp].patient_id);
          printf("Enter patient NAME:");
          getchar();
          fgets(p[imp].name,100,stdin);
          printf("Enter Address:");
          fgets(p[imp].address,300,stdin);
          temp=p[imp].phone_no;
          while (count!=10)
            {
                printf("Enter phone number: ");
                scanf("%lld",&p[imp].phone_no);
                temp=p[imp].phone_no;
                while(temp!=0)
                {
                    temp/=10;
                    count++;
                }
                if (count!=10)
                {
                    printf("Invalid phone number!Must be 10 digits.\n");
                }
            }
          if(fp==NULL)
          {
              printf("Error opening file:(");
          }
          fprintf(fp,"%d %s %s %lld",p[imp].patient_id,p[imp].name,p[imp].address,p[imp].phone_no);
          fclose(fp);
          printf("\nPatient details saved successfully:)\n");
          imp++;
          break;
          }
          case 2:
          {
              FILE *fp=fopen("patient.txt","a");
              printf("Enter patient ID:");
              scanf("%d",&store);

          }
        }
    }

void doctorMenu()
{
    printf("\n--- Doctor & Therapist Management ---\n");
    // you will add code here later
}

void inventoryMenu()
{
     printf("\n--- Medicine Inventory ---\n");
    printf("1. Add item\n2. View all\n3. Delete item\n4. Back to main menu\n");
    int ch;
    printf("Enter you Choice: ");
    scanf("%d",&ch);
    switch(ch){
        case 1: addmed(); break;
        case 2: viewmed(); break;
        case 3: delmed(); break;
        case 4: return;
        default: printf("Invalid choice.\n");
    }
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





