#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct{
    char name[50];
    int expr;
    int stock;
}med;

//SURYANSH SIROHI
struct patient
{
    int patient_id;
    char name[100];
    char address[300];
    long long int phone_no;
};
void deletePatient() //SURYANSH SIROHI
{
    int id;
    printf("Enter patient ID to delete:");
    scanf("%d",&id);
    FILE *fp=fopen("patient.txt","r");
    FILE *temp=fopen("temp.txt","w");
    if (fp==NULL||temp==NULL)
    {
        printf("Error opening file!\n");
    }
    struct patient p;
    int found=0;
    while(fscanf(fp,"%d|%99[^|]|%299[^|]|%lld\n",&p.patient_id,p.name,p.address,&p.phone_no)==4)
    {
        if (p.patient_id==id)
        {
            found=1;
            continue;
        }
        fprintf(temp,"%d|%s|%s|%lld\n",p.patient_id,p.name,p.address,p.phone_no);
    }
    fclose(fp);
    fclose(temp);
    if(!found)
    {
        printf("\nPatient ID %d not found.\n",id);
        remove("temp.txt");
    }
    else
    {
        remove("patient.txt");
        rename("temp.txt", "patient.txt");
        printf("\nPatient ID %d deleted successfully.\n",id);
    }
}
void search() //SURYANSH SIROHI
{
    int n;
    printf("You want to search by?\n1.Patient ID\n2.Phone Number\nEnter Choice:");
    scanf("%d",&n);
    int found=0;
    FILE *fp=fopen("patient.txt","r");
    if (fp==NULL)
    {
        printf("Error opening file!\n");
    }
    switch (n)
    {
    case 1:
        {

            struct patient p;
            int id;
            printf("Enter Patient's ID:");
            scanf("%d",&id);
            while(fscanf(fp,"%d|%99[^|]|%299[^|]|%lld\n",&p.patient_id,p.name,p.address,&p.phone_no)==4)
            {
              if (p.patient_id==id)
              {
                  found=1;
                  printf("-----Patient Found-----");
                  printf("\n%d",p.patient_id);
                  printf("\n%s",p.name);
                  printf("\n%s",p.address);
                  printf("\n%lld",p.phone_no);
                  break;
              }
            }
            break;
        }
    case 2:
            {
                long long int no;
                struct patient p;
            printf("Enter Patient's Phone Number:");
            scanf("%lld",&no);
            while(fscanf(fp,"%d|%99[^|]|%299[^|]|%lld\n",&p.patient_id,p.name,p.address,&p.phone_no)==4)
            {
              if (p.phone_no==no)
              {
                  found=1;
                  printf("-----Patient Found-----");
                  printf("\n%d",p.patient_id);
                  printf("\n%s",p.name);
                  printf("\n%s",p.address);
                  printf("\n%lld",p.phone_no);
                  break;
              }
            }
        }
    default:
        {if (found==0)
        printf("Record not found");
        else{
            printf("You entered wrong choice");
        }
        break;}
    fclose(fp);
}
}
void patientMenu() //SURYANSH SIROHI
{
    int choice,count=0,store;
    long long int temp;
    static int imp=0;
    printf("\n--- Patient Management ---\n");
    printf("1.Add new patient details\n2.Edit patient detials\n3.Delete Patient Details\n4.Search Patient\nEnter your choice:");
    scanf("%d",&choice);
    struct patient p[1000];
    switch(choice)
        {
          case 1:
          {FILE *fp=fopen("patient.txt","a");
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
          p[imp].patient_id=imp;
          fprintf(fp,"%d|%s|%s|%lld\n",p[imp].patient_id,p[imp].name,p[imp].address,p[imp].phone_no);
          fclose(fp);
          printf("Patient ID:%d",imp);
          printf("\nPatient details saved successfully:)\n");
          imp++;
          break;
          }
          case 2:
          {
              int id,flag=0,ig=0,store;
              printf("Enter patient ID whose details you wish to edit:");
              scanf("%d",&id);
              FILE *fp=fopen("patient.txt","r");
              FILE *fpw=fopen("temp.txt","w");
              if(fp==NULL||fpw==NULL)
              {
               printf("Error in opening file,it does not exist\n");
              }
             while (fscanf(fp, "%d|%99[^|]|%299[^|]|%lld\n",&p[ig].patient_id,p[ig].name,p[ig].address,&p[ig].phone_no) == 4)
              {
                  if (p[ig].patient_id==id)
                  {
                      flag=1;
                      printf("\nCurrent Detials:\n");
                      printf("Patient ID:%d\nName:%s\nAddress:%s\nPhone:%lld\n",p[ig].patient_id,p[ig].name,p[ig].address,p[ig].phone_no);
                      printf("1.Change Patient name\n2.Change Patient Address\n3.Change Patient's Phone Number\nEnter your choice:");
                      scanf("%d",&store);
                      switch(store)
                      {
                      case 1:
                       {
                        printf("Enter NEW Name:");
                        getchar();
                        fgets(p[ig].name,100,stdin);
                        break;}
                      case 2:
                        {printf("Enter NEW Address:");
                        getchar();
                        fgets(p[ig].address,300,stdin);
                        break;}
                      case 3:
                        {printf("Enter new phone number:");
                        scanf("%lld",&p[ig].phone_no);
                        break;}
                      default:
                        {printf("Wrong Choice");
                        break;}
                      }
                  }
                  fprintf(fpw,"%d|%s|%s|%lld\n",p[ig].patient_id,p[ig].name,p[ig].address,p[ig].phone_no);
                  ig++;
              }
              fclose(fp);
              fclose(fpw);
              if(!flag)
              {
                  printf("\nPatient ID does not exist\n");
                  remove("temp.txt");
              }
              else{
                remove("patient.txt");
                rename("temp.txt","patient.txt");
                printf("\nDetails Updated Successfully\n");
              }
          }
        case 3:
        {
            deletePatient();
        }
        case 4:
        {
            search();
        }
        default:
            {printf("Wrong Choice");
        break;}}
}
void doctorMenu() //SURYANSH SIROHI
{
    printf("\n--- Doctor & Therapist Management ---\n");
    // you will add code here later
}

void addmed(){  // AVI NEGI
    med m;
    FILE *f=fopen("medicine.txt","a");
    if (f==NULL){
        printf("Error opening file!\n");
    }
    printf("Enter Name of Medicine: ");
    scanf(" %[^\n]",&m.name);
    printf("Enter Expiration Date(MM YYYY): ");
    scanf("%d",&m.expr);
    printf("Enter Amount: ");
    scanf("%d",&m.stock);
    fprintf(f, "%s|%d|%d\n", m.name, m.expr, m.stock);
    fclose(f);
    printf("Medicine added successfully with Name %s\n", m.name);
}
void viewmed(){  // AVI NEGI
    FILE* f=fopen("medicine.txt","r");
    if(f==NULL){
        printf("No Medicine Found\n");
        return;
    }
    med m;
    int pos=0;
    printf("-------MEDICINES-------\n");
    while(fscanf(f," %50[^|]|%d|%d\n",&m.name,&m.expr,&m.stock)==3){
        printf("%d) Name: %s | Expiration: %d | Stock: %d\n",++pos,m.name,m.expr,m.stock);
    }
    if(pos==0) printf("Inventory Is Empty\n");
    fclose(f);
}
void delmed(){     // AVI NEGI
    char aim[50];
    int amt;
    printf("Enter the name of medicine: ");
    scanf(" %[^\n]",aim);
    printf("Enter Amount:");
    scanf("%d",&amt);
    FILE* f=fopen("medicine.txt","r");
    FILE* temp=fopen("temp_med.txt","w");
    if (f==NULL||temp==NULL)
    {
        printf("Error opening file!\n");
        if (f) fclose(f);
        if (temp) fclose(temp);
        if (temp) remove("temp_med.txt");
        return;
    }
    med m;
    int found=0;
     while(fscanf(f," %49[^|]|%d|%d\n",m.name,&m.expr,&m.stock)==3){
        if(strcmp(m.name,aim)==0&&found==0){
            found=1;
            if(amt>m.stock){
                printf("Only %d units in stock",m.stock);
                fclose(f);
                fclose(temp);
                remove("temp_med.txt");
                return;
            }
            m.stock-=amt;
            printf("Updated Stock of %s: %d",m.name,m.stock);

            if(m.stock>0) fprintf(temp,"%s|%d|%d\n",m.name,m.expr,m.stock);
            continue;
        }
    
        fprintf(temp,"%s|%d|%d\n",m.name,m.expr,m.stock);
    }
    fclose(f);
    fclose(temp);

    if(found==0){
        printf("Medicine Not Found!\n");
        remove("temp_med.txt");        
    } else{
        remove("medicine.txt");
        rename("temp_med.txt","medicine.txt");
        printf("Amount Deducted Successfully");
    }
}

void inventoryMenu() //AVI NEGI
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








