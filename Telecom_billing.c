#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct customer {
    char name[20];
    char phone[20];
    float bill;
    int usage;
} cust;

void add_data() {
    int code1 = 0;

    FILE *file_1 = fopen("Telecom_Rec.txt", "a");
    if (file_1 == NULL) {
        printf("File not found");
        exit(1);
    }

    printf("Enter your name: ");
    scanf("%s", cust.name);

    while (code1 != 10) {
        printf("Enter your phone number: ");
        scanf("%s", cust.phone);
        code1 = strlen(cust.phone);
        if (code1 != 10) {
            printf("Invalid phone number!!!!\n");
        }
    }

    printf("Enter usage (in minutes): ");
    scanf("%d", &cust.usage);
    cust.bill = cust.usage * 0.5;

    fprintf(file_1, "%s\t%s\t%.2f\t%d\n", cust.name, cust.phone, cust.bill, cust.usage);
    printf("Record saved successfully....\n");
    fclose(file_1);
}

void view_list() {
    FILE *file_2 = fopen("Telecom_Rec.txt", "r");
    if (file_2 == NULL) {
        printf("File not found");
        exit(1);
    }

    char line[100];
    char name[20];
    char phone[20];
    float bill;
    int usage;

    printf("\nName\t\tPhone Number\tBill\tUsage(in minutes)\n");
    printf("-----------------------------------------------------------\n");

    while (fgets(line, sizeof(line), file_2)) {
        sscanf(line, "%19s\t%19s\t%f\t%d", name, phone, &bill, &usage);
        printf("%-10s\t%s\t%.2f\t%d\n", name, phone, bill, usage);
    }

    fclose(file_2);
}

void modify_rec() {
    FILE *file_3 = fopen("Telecom_Rec.txt", "r");
    if (file_3 == NULL) {
        printf("File not found");
        exit(1);
    }

    struct customer customers[100];
    int count = 0;

    while (fscanf(file_3, "%19s\t%19s\t%f\t%d", customers[count].name, customers[count].phone, &customers[count].bill, &customers[count].usage) == 4) {
        count++;
    }
    fclose(file_3);

    char targetName[20];
    printf("Enter the name of the customer to modify: ");
    scanf("%s", targetName);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(customers[i].name, targetName) == 0) {
            printf("Enter new usage (in minutes): ");
            scanf("%d", &customers[i].usage);
            customers[i].bill = customers[i].usage * 0.5;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Record not found.\n");
        return;
    }

    FILE *file_3_write = fopen("Telecom_Rec.txt", "w");
    if (file_3_write == NULL) {
        printf("File not found");
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        fprintf(file_3_write, "%s\t%s\t%.2f\t%d\n", customers[i].name, customers[i].phone, customers[i].bill, customers[i].usage);
    }
    fclose(file_3_write);
    
    printf("Record updated successfully.\n");
}

void view_pay() {
    FILE *file_4 = fopen("Telecom_Rec.txt", "r");
    if (file_4 == NULL) {
        printf("File not found");
        exit(1);
    }

    char name[20];
    char phone[20];
    float bill;
    int usage;
    char targetName[20];
    int found = 0;

    printf("Enter your name: ");
    scanf("%s", targetName);

    while (fscanf(file_4, "%19s\t%19s\t%f\t%d", name, phone, &bill, &usage) == 4) {
        if (strcmp(name, targetName) == 0) {
            printf("\nBill for %s: Rs %.2f\n", name, bill);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Record not found.\n");
    }

    fclose(file_4);
}

void delete_rec() {
    FILE *file_5 = fopen("Telecom_Rec.txt", "r");
    if (file_5 == NULL) {
        printf("File not found");
        exit(1);
    }

    struct customer customers[100];
    int count = 0;

    while (fscanf(file_5, "%19s\t%19s\t%f\t%d", customers[count].name, customers[count].phone, &customers[count].bill, &customers[count].usage) == 4) {
        count++;
    }
    fclose(file_5);

    char targetName[20];
    printf("Enter the name of the customer to delete: ");
    scanf("%s", targetName);
    printf("------------------------------------------------\n");
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(customers[i].name, targetName) == 0) {
            for (int j = i; j < count - 1; j++) {
                customers[j] = customers[j + 1];
            }
            count--;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Record not found.\n");
        return;
    }

    FILE *file_5_write = fopen("Telecom_Rec.txt", "w");
    if (file_5_write == NULL) {
        printf("File not found");
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        fprintf(file_5_write, "%s\t%s\t%.2f\t%d\n", customers[i].name, customers[i].phone, customers[i].bill, customers[i].usage);
    }
    fclose(file_5_write);

    printf("Record deleted successfully.\n");
}


//MAIN
int main() {
    printf("\nWelcome to Telecom!!!");
    char choice='y';
    while (choice=='Y' || choice=='y')
    {
    printf("\n1. Add data\n2. View list of records\n3. Modify Record\n4. View Payment\n5. Delete Record\n6. Exit\nEnter your choice: ");
    int ch;
    scanf("%d", &ch);   
    switch (ch){
        case 1:
            add_data();
            break;
        case 2:
            view_list();
            break;
        case 3:
            modify_rec();
            break;
        case 4:
            view_pay();
            break;
        case 5:
            delete_rec();
            break;
        case 6:
            printf("Goodbye!!");
            return 0;
        default:
            printf("Invalid choice!!!\n");
        }
    printf("\nDo you want to continue? (Y/N): ");
    scanf(" %c", &choice);
    printf("------------------------------------------------\n");
}
    return 0;
}
