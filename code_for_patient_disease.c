#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct disease {
    int pid;
    char pname[100];
    char dis[200];
    char therapy[200];
    char dosha[50];
};

void addDisease() {
    FILE *fp;
    struct disease d;
    fp = fopen("patient_disease.txt", "a");
    if(fp == NULL){
        printf("File can't open\n");
        return;
    }
    printf("\nEnter Patient Id: ");
    scanf("%d",&d.pid);
    getchar();
    printf("Enter Name: ");
    fgets(d.pname,100,stdin);
    d.pname[strcspn(d.pname,"\n")] = '\0';
    printf("Enter Disease: ");
    fgets(d.dis,200,stdin);
    d.dis[strcspn(d.dis,"\n")] = '\0';
    printf("Enter Therapy: ");
    fgets(d.therapy,200,stdin);
    d.therapy[strcspn(d.therapy,"\n")] = '\0';
    printf("Enter Dosha Type: ");
    fgets(d.dosha,50,stdin);
    d.dosha[strcspn(d.dosha,"\n")] = '\0';

    fprintf(fp,"Patient ID: %d\n", d.pid);
    fprintf(fp,"Name: %s\n", d.pname);
    fprintf(fp,"Disease: %s\n", d.dis);
    fprintf(fp,"Therapy: %s\n", d.therapy);
    fprintf(fp,"Dosha: %s\n", d.dosha);
    fprintf(fp,"------------------------------\n\n");

    fclose(fp);
    printf("\nRecord Added Successfully...\n");
}

void viewDisease() {
    FILE *fp;
    char ch;
    fp = fopen("patient_disease.txt","r");
    if(fp == NULL){
        printf("No Records Found...\n");
        return;
    }
    printf("\n----- All Disease Records -----\n\n");
    while((ch=fgetc(fp))!=EOF){
        putchar(ch);
    }
    fclose(fp);
}

void searchDisease(){
    FILE *fp;
    int id;
    char line[200];
    int found = 0;

    printf("\nEnter Patient ID To Search: ");
    scanf("%d",&id);

    fp = fopen("patient_disease.txt","r");
    if(fp == NULL){
        printf("File not available\n");
        return;
    }

    sprintf(line,"Patient ID: %d",id);
    char str[300];

    while(fgets(str,300,fp)){
        if(strstr(str,line)){
            found = 1;
            printf("\nRecord Found:\n");
            printf("%s",str);
            for(int i=0;i<5;i++){
                fgets(str,300,fp);
                printf("%s",str);
            }
            break;
        }
    }

    if(found==0){
        printf("\nNo Record For This ID...\n");
    }

    fclose(fp);
}

void deleteDisease(){
    FILE *fp, *temp;
    int id;
    char str[300];
    int skip = 0;

    printf("\nEnter Patient ID To Delete: ");
    scanf("%d",&id);

    fp = fopen("patient_disease.txt","r");
    temp = fopen("temp.txt","w");

    if(fp==NULL || temp==NULL){
        printf("Error opening file\n");
        return;
    }

    while(fgets(str,300,fp)){
        if(strstr(str,"Patient ID: ")){
            int cid = atoi(str + 12);
            if(cid == id){
                skip = 1;
                for(int i=0;i<6;i++)
                    fgets(str,300,fp);
                continue;
            }
        }
        if(skip == 0){
            fputs(str,temp);
        }
        skip = 0;
    }

    fclose(fp);
    fclose(temp);

    remove("patient_disease.txt");
    rename("temp.txt","patient_disease.txt");

    printf("\nRecord Deleted...\n");
}

void updateDisease(){
    FILE *fp, *temp;
    int id;
    char str[300];
    int found = 0;
    struct disease d;

    printf("\nEnter Patient ID To Update: ");
    scanf("%d",&id);
    getchar();

    fp = fopen("patient_disease.txt","r");
    temp = fopen("temp.txt","w");

    if(fp==NULL || temp==NULL){
        printf("File not opening\n");
        return;
    }

    while(fgets(str,300,fp)){
        if(strstr(str,"Patient ID: ")){
            int cid = atoi(str + 12);

            if(cid == id){
                found = 1;

                printf("\nEnter New Name: ");
                fgets(d.pname,100,stdin);
                d.pname[strcspn(d.pname,"\n")] = '\0';

                printf("Enter New Disease: ");
                fgets(d.dis,200,stdin);
                d.dis[strcspn(d.dis,"\n")] = '\0';

                printf("Enter New Therapy: ");
                fgets(d.therapy,200,stdin);
                d.therapy[strcspn(d.therapy,"\n")] = '\0';

                printf("Enter New Dosha: ");
                fgets(d.dosha,50,stdin);
                d.dosha[strcspn(d.dosha,"\n")] = '\0';

                fprintf(temp,"Patient ID: %d\n", cid);
                fprintf(temp,"Name: %s\n", d.pname);
                fprintf(temp,"Disease: %s\n", d.dis);
                fprintf(temp,"Therapy: %s\n", d.therapy);
                fprintf(temp,"Dosha: %s\n", d.dosha);
                fprintf(temp,"------------------------------\n\n");

                for(int i=0;i<5;i++)
                    fgets(str,300,fp);

                continue;
            }
        }
        fputs(str,temp);
    }

    fclose(fp);
    fclose(temp);

    remove("patient_disease.txt");
    rename("temp.txt","patient_disease.txt");

    if(found)
        printf("\nRecord Updated!\n");
    else
        printf("\nRecord Not Found!\n");
}

void diseaseMenu(){
    int ch;
    do{
        printf("\n=== Disease Management Menu ===\n");
        printf("1. Add Disease Record\n");
        printf("2. View All Records\n");
        printf("3. Search Record\n");
        printf("4. Update Record\n");
        printf("5. Delete Record\n");
        printf("0. Exit\n");
        printf("Enter Choice: ");
        scanf("%d",&ch);

        switch(ch){
            case 1: addDisease(); break;
            case 2: viewDisease(); break;
            case 3: searchDisease(); break;
            case 4: updateDisease(); break;
            case 5: deleteDisease(); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Wrong Choice!\n");
        }
    }while(ch!=0);
}

int main(){
    diseaseMenu();
    return 0;
}
