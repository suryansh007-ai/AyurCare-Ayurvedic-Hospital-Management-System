#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char name[50];
    int expr;
    int stock;
    float price;
}med;

struct patient {
    int patient_id;
    char name[100];
    char address[300];
    long long int phone_no;
};

struct doctor {
    int doc_id;
    char doc_name[100];
    char spec[100];
    long long int phone;
    float fee;
    char timing[100];
};

void adddoctor() {
    FILE *fp = fopen("doctor.txt","a");
    struct doctor doc;
    static int id = 0;
    int count = 0;
    long long temp;

    if(fp == NULL) {
        printf("Error opening file.");
        return;
    }

    doc.doc_id = id;
    printf("Enter Therapist/Doctor's Name:");
    getchar();
    fgets(doc.doc_name,100,stdin);
    printf("Enter Therapist/Doctor's Specialization:");
    fgets(doc.spec,200,stdin);

    while (1) {
        printf("Enter Therapist/Doctor's Phone Number:");
        scanf("%lld",&doc.phone);
        temp = doc.phone;
        count = 0;
        while(temp != 0) {
            temp /= 10;
            count++;
        }
        if (count == 10)
            break;
        else
            printf("Invalid Phone number\n");
    }

    printf("Enter Consultation Fee:");
    scanf("%f",&doc.fee);
    printf("Enter available timings:");
    getchar();
    fgets(doc.timing,50,stdin);

    fprintf(fp,"%d|%s|%s|%lld|%f|%s\n",
            doc.doc_id, doc.doc_name, doc.spec, doc.phone, doc.fee, doc.timing);

    fclose(fp);
    printf("\n%s's details have been successfully saved\nHis ASSIGNED ID is %d",doc.doc_name,doc.doc_id);
    id++;
}

void editdoctor() {
    struct doctor doc;
    int id, flag = 0, store;
    printf("Enter doctor/therapist ID whose details you wish to change?");
    scanf("%d",&id);

    FILE *fp = fopen("doctor.txt","r");
    FILE *fpw = fopen("temp1.txt","w");
    if(fp == NULL || fpw == NULL) {
        printf("Error in opening file,it does not exist\n");
        return;
    }

    while (fscanf(fp,"%d|%99[^|]|%99[^|]|%lld|%f|%49[^\n]\n",
                  &doc.doc_id, doc.doc_name, doc.spec,
                  &doc.phone, &doc.fee, doc.timing) == 6)
    {
        if (doc.doc_id == id) {
            flag = 1;
            printf("\nCurrent Detials:\n");
            printf("Doctor/Therapist ID:%d\nName:%s\nSpecilization:%s\nPhone:%lld\nConsultation FEE:%f\nTimings:%s\n",
                   doc.doc_id, doc.doc_name, doc.spec, doc.phone, doc.fee, doc.timing);

            printf("1.Change Doctor/Therapist name\n2.Change Specilization\n3.Change Doctor/Therapist's Phone Number\n4.Change consultation fee amount\n5.Change Timings\nEnter your choice:");
            scanf("%d",&store);

            switch(store) {
                case 1:
                    printf("Enter NEW Name:");
                    getchar();
                    fgets(doc.doc_name,100,stdin);
                    break;
                case 2:
                    printf("Enter NEW Specilization:");
                    getchar();
                    fgets(doc.spec,300,stdin);
                    break;
                case 3:
                    printf("Enter new phone number:");
                    scanf("%lld",&doc.phone);
                    break;
                case 4:
                    printf("Enter NEW Consultation FEE:");
                    scanf("%f",&doc.fee);
                    break;
                case 5:
                    printf("Enter NEW Timings:");
                    getchar();
                    fgets(doc.timing,100,stdin);
                    break;
                default:
                    printf("Wrong Choice");
            }
        }

        fprintf(fpw,"%d|%s|%s|%lld|%f|%s\n",
                doc.doc_id, doc.doc_name, doc.spec, doc.phone, doc.fee, doc.timing);
    }

    fclose(fp);
    fclose(fpw);

    if(!flag) {
        printf("\nDoctor/Therapist ID does not exist\n");
        remove("temp1.txt");
    } else {
        remove("doctor.txt");
        rename("temp1.txt","doctor.txt");
        printf("\nDetails Updated Successfully\n");
    }
}

void deletedoctor() {
    int id;
    printf("Enter Doctor/Therapist ID to delete:");
    scanf("%d",&id);

    FILE *fp = fopen("doctor.txt","r");
    FILE *temp = fopen("temp1.txt","w");
    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct doctor doc;
    int found = 0;

    while(fscanf(fp,"%d|%99[^|]|%99[^|]|%lld|%f|%49[^\n]\n",
                 &doc.doc_id, doc.doc_name, doc.spec, &doc.phone, &doc.fee, doc.timing) == 6)
    {
        if (doc.doc_id == id) {
            found = 1;
            continue;
        }

        fprintf(temp,"%d|%s|%s|%lld|%f|%s\n",
                doc.doc_id, doc.doc_name, doc.spec, doc.phone, doc.fee, doc.timing);
    }

    fclose(fp);
    fclose(temp);

    if(!found) {
        printf("\nDoctor/Therapist ID %d not found.\n",id);
        remove("temp1.txt");
    } else {
        remove("doctor.txt");
        rename("temp1.txt", "doctor.txt");
        printf("\nDoctor/Therapist ID %d deleted successfully.\n",id);
    }
}

void searchdoc() {
    int found = 0;
    FILE *fp = fopen("doctor.txt","r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct doctor doc;
    int id;
    printf("Enter Doctor/Therapist's ID:");
    scanf("%d",&id);

    while(fscanf(fp,"%d|%99[^|]|%99[^|]|%lld|%f|%49[^\n]\n",
                 &doc.doc_id, doc.doc_name, doc.spec,
                 &doc.phone, &doc.fee, doc.timing) == 6)
    {
        if (doc.doc_id == id) {
            found = 1;
            printf("-----Doctor/Therapist Found-----");
            printf("\n%d",doc.doc_id);
            printf("\n%s",doc.doc_name);
            printf("\n%s",doc.spec);
            printf("\n%lld",doc.phone);
            printf("\n%f",doc.fee);
            printf("\n%s",doc.timing);
            break;
        }
    }
    if (!found)
        printf("Record not found");

    fclose(fp);
}

void trim(char *s) {
    int len = strlen(s);
    while(len > 0 && (s[len-1]=='\n' || s[len-1]=='\r' || s[len-1]==' '))
    {
        s[len-1] = 0;
        len--;
    }
}

void displaydocs() {
    struct doctor doc;
    char searchSpec[100];
    int found = 0;

    FILE *fp = fopen("doctor.txt","r");
    if (!fp) {
        printf("Error opening doctor file!\n");
        return;
    }

    getchar();
    printf("Enter specialization to search:");
    fgets(searchSpec,100,stdin);
    trim(searchSpec);

    printf("\n---Doctors/Therapists with Specialization:%s---\n",searchSpec);

    while(fscanf(fp,"%d|%99[^|]|%99[^|]|%lld|%f|%49[^\n]\n",
                 &doc.doc_id, doc.doc_name, doc.spec,
                 &doc.phone, &doc.fee, doc.timing) == 6)
    {
        trim(doc.spec);
        if (strcasecmp(doc.spec,searchSpec)==0)
        {
            found = 1;
            printf("Doctor/Therapist ID:%d|Doctor's NAME:%s|Therapist's Specilization:%s|Doctor/Therapist's Phone No.:%lld|Consultation Fee:%f|Timings:%s\n",
                   doc.doc_id,doc.doc_name,doc.spec,doc.phone,doc.fee,doc.timing);
        }
    }

    fclose(fp);

    if(!found)
        printf("\nNo doctor/therapist found for specialization:%s\n",searchSpec);

    printf("\n\n");
}

/* ------------------ PATIENT FUNCTIONS ------------------ */

void deletePatient() {
    int id;
    printf("Enter patient ID to delete:");
    scanf("%d",&id);

    FILE *fp = fopen("patient_profile.txt","r");
    FILE *temp = fopen("temp.txt","w");
    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct patient p;
    int found = 0;

    while(fscanf(fp,"%d|%99[^|]|%299[^|]|%lld\n",
                 &p.patient_id,p.name,p.address,&p.phone_no)==4)
    {
        if (p.patient_id==id) {
            found=1;
            continue;
        }

        fprintf(temp,"%d|%s|%s|%lld\n",
                p.patient_id,p.name,p.address,p.phone_no);
    }

    fclose(fp);
    fclose(temp);

    if(!found) {
        printf("\nPatient ID %d not found.\n",id);
        remove("temp.txt");
    } else {
        remove("patient_profile.txt");
        rename("temp.txt", "patient_profile.txt");
        printf("\nPatient ID %d deleted successfully.\n",id);
    }
}

void search() {
    int n;
    printf("You want to search by?\n1.Patient ID\n2.Phone Number\nEnter Choice:");
    scanf("%d",&n);

    int found = 0;
    FILE *fp = fopen("patient_profile.txt","r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    switch (n) {
    case 1: {
        struct patient p;
        int id;
        printf("Enter Patient's ID:");
        scanf("%d",&id);

        while(fscanf(fp,"%d|%99[^|]|%299[^|]|%lld\n",
                     &p.patient_id,p.name,p.address,&p.phone_no)==4)
        {
            if (p.patient_id==id) {
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

    case 2: {
        long long int no;
        struct patient p;
        printf("Enter Patient's Phone Number:");
        scanf("%lld",&no);

        while(fscanf(fp,"%d|%99[^|]|%299[^|]|%lld\n",
                     &p.patient_id,p.name,p.address,&p.phone_no)==4)
        {
            if (p.phone_no==no) {
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

    default:
        printf("You entered wrong choice");
    }

    if (!found)
        printf("Record not found");

    fclose(fp);
}

void patientMenu() {
    int choice, count = 0;
    long long int temp;
    static int imp = 0;

    printf("\n--- Patient Management ---\n");
    printf("1.Add new patient details\n2.Edit patient details\n3.Delete Patient Details\n4.Search Patient\nEnter your choice:");
    scanf("%d",&choice);

    struct patient p[1000];

    switch(choice)
    {
    case 1: {
        FILE *fp=fopen("patient_profile.txt","a");

        printf("Enter patient NAME:");
        getchar();
        fgets(p[imp].name,100,stdin);

        printf("Enter Address:");
        fgets(p[imp].address,300,stdin);

        while (1) {
            printf("Enter phone number: ");
            scanf("%lld",&p[imp].phone_no);
            temp = p[imp].phone_no;
            count = 0;

            while(temp != 0) {
                temp /= 10;
                count++;
            }

            if (count == 10) break;
            else printf("Invalid phone number! Must be 10 digits.\n");
        }

        if(fp==NULL) {
            printf("Error opening file:(");
            return;
        }

        p[imp].patient_id = imp;
        fprintf(fp,"%d|%s|%s|%lld\n",
                p[imp].patient_id,p[imp].name,p[imp].address,p[imp].phone_no);

        fclose(fp);
        printf("Patient ID:%d",imp);
        printf("\nPatient details saved successfully:)\n");
        imp++;

        break;
    }

    case 2: {
        int id, flag = 0, ig = 0, store;
        printf("Enter patient ID whose details you wish to edit:");
        scanf("%d",&id);

        FILE *fp = fopen("patient_profile.txt","r");
        FILE *fpw = fopen("temp.txt","w");
        if(fp == NULL || fpw == NULL) {
            printf("Error in opening file,it does not exist\n");
            return;
        }

        while (fscanf(fp, "%d|%99[^|]|%299[^|]|%lld\n",
                      &p[ig].patient_id,p[ig].name,p[ig].address,
                      &p[ig].phone_no) == 4)
        {
            if (p[ig].patient_id == id) {
                flag = 1;
                printf("\nCurrent Detials:\n");
                printf("Patient ID:%d\nName:%s\nAddress:%s\nPhone:%lld\n",
                       p[ig].patient_id,p[ig].name,p[ig].address,p[ig].phone_no);

                printf("1.Change Patient name\n2.Change Patient Address\n3.Change Patient's Phone Number\nEnter your choice:");
                scanf("%d",&store);

                switch(store)
                {
                case 1:
                    printf("Enter NEW Name:");
                    getchar();
                    fgets(p[ig].name,100,stdin);
                    break;
                case 2:
                    printf("Enter NEW Address:");
                    getchar();
                    fgets(p[ig].address,300,stdin);
                    break;
                case 3:
                    printf("Enter new phone number:");
                    scanf("%lld",&p[ig].phone_no);
                    break;
                default:
                    printf("Wrong Choice");
                }
            }

            fprintf(fpw,"%d|%s|%s|%lld\n",
                    p[ig].patient_id,p[ig].name,p[ig].address,p[ig].phone_no);
            ig++;
        }

        fclose(fp);
        fclose(fpw);

        if(!flag) {
            printf("\nPatient ID does not exist\n");
            remove("temp.txt");
        } else {
            remove("patient_profile.txt");
            rename("temp.txt","patient_profile.txt");
            printf("\nDetails Updated Successfully\n");
        }
        break;
    }

    case 3:
        deletePatient();
        break;

    case 4:
        search();
        break;

    default:
        printf("Wrong Choice");
    }
}
void doctorMenu()
{   int n;
    printf("\n---Doctor and Therapist Management---\n");
    printf("1.Add Doctor/Therapist\n2.Edit Doctor's/Therapist's Details\n3.Delete Doctor's/Therapist's details\n4.Search Doctor/Therapist\n5.Display list of doctors/Therapists\n6.Assign Doctor/Therapist to patient\n7.Doctor Availability/Scheduling");
    printf("\nEnter your choice:");
    scanf("%d",&n);
    switch (n)
    {
    case 1:
        {
          adddoctor();
        }
    case 2:
        {
          editdoctor();
        }
    case 3:
    {
        deletedoctor();
    }
    case 4:
        {
           searchdoc();
        }
    case 5:
        {
           displaydocs();
        }
    case 6:
        {
            //assign();
        }
    case 7:
        {
           // availability();
        }
    }
}

/* ------------------ MEDICINE FUNCTIONS ------------------ */

void addmed(){  // AVI NEGI
    med m;
    FILE *f=fopen("medicine.txt","a");
    if (f==NULL){
        printf("Error opening file!\n");
    }
    printf("Enter Name of Medicine: ");
    scanf(" %[^\n]",&m.name);
    printf("Enter Expiration Date(YYYY): ");
    scanf(" %d",&m.expr);
    printf("Enter Amount: ");
    scanf(" %d",&m.stock);
    printf("Enter Price: ");
    scanf(" %f",&m.price);
    fprintf(f, "%s|%d|%d|%f\n", m.name, m.expr, m.stock,m.price);
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
    while(fscanf(f," %49[^|]|%d|%d|%f\n",&m.name,&m.expr,&m.stock,&m.price)==4){
        printf("%d) Name: %s | Expiration: %d | Stock: %d | Price: %f\n",++pos,m.name,m.expr,m.stock,m.price);
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
    scanf(" %d",&amt);
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
     while(fscanf(f," %49[^|]|%d|%d|%f\n",m.name,&m.expr,&m.stock,&m.price)==4){
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
            printf("\nUpdated Stock of %s: %d",m.name,m.stock);

            if(m.stock>0) fprintf(temp,"%s|%d|%d|%f\n",m.name,m.expr,m.stock,m.price);
            continue;
        }
    
        fprintf(temp,"%s|%d|%d|%f\n",m.name,m.expr,m.stock,m.price);
    }
    fclose(f);
    fclose(temp);

    if(found==0){
        printf("Medicine Not Found!\n");
        remove("temp_med.txt");        
    } else{
        remove("medicine.txt");
        rename("temp_med.txt","medicine.txt");
        printf("\nAmount Deducted Successfully");
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

void billingMenu(){
    struct doctor doc;
    med m;    
    printf("\n--- Billing Section ---\n");
    int q,id,con;
    float total=0.0;
    char medname[50];

    FILE* f1=fopen("doctor.txt","r");
    FILE* f2=fopen("medicine.txt","r");
    if (f1 == NULL) {
        printf("Error: cannot open doctor file.\n");
        if (f2) fclose(f2);
        return;
    }
    if (f2 == NULL) {
        printf("Error: cannot open medicine file.\n");
        fclose(f1);
        return;
    }
    do{
        printf("Enter ID of Doctor: ");
        scanf(" %d",&id);
        printf("Enter Name of Medicine(In Small Letters): ");
        scanf(" %[^\n]",medname);
        printf("Enter Quantity of Medicine: ");
        scanf("%d",&q);
        printf("If you want bill press '1',If you want to change Something press '0'\n");
        scanf("%d",&con);
    } while(con==0);
    int docf=0;
    while(fscanf(f1,"%d|%99[^|]|%199[^|]|%lld|%f|%49[^\n]\n",&doc.doc_id,&doc.doc_name,&doc.spec,&doc.phone,&doc.fee,&doc.timing)==6){
        if (doc.doc_id==id){
            docf=1;
            total+=doc.fee;
            break;
        }       
    }
    if(docf==0){
        printf("Doctor with ID %d Not Found\n",id);
        fclose(f1);fclose(f2);
        return;
    }

int medf=0;
    while(fscanf(f2," %49[^|]|%d|%d|%f\n",&m.name,&m.expr,&m.stock,&m.price)==4){
        if(strcmp(m.name,medname)==0){
            medf=1;
            if(q>m.stock){
                printf("Only %d units in stock\n",m.stock);
                fclose(f1);
                fclose(f2);
                return;
            }
            total+=(m.price)*q;
            m.stock-=q;
            break;        
        }
    }
    if(medf==0){
        printf("Medicine %s not Found\n",medname);
        fclose(f1); fclose(f2);
        return;
    }

    printf("--- Bill Summary ---\n");
    printf("Doctor: %s (Fee: %.2f)\n", doc.doc_name, doc.fee);
    printf("Medicine: %s | Unit price: %f | Qty: %d | Subtotal: %.2f\n",
           m.name, m.price, q, m.price * q);
    printf("-----------------------------\n");
    printf("Total payable: %.2f\n", total);
    fclose(f1);
    fclose(f2);    
}

void reportsMenu() {
    printf("\n--- Reports Section ---\n");
}

int main() {
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


