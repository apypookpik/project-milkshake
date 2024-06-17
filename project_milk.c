#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define BUFFER_SIZE 1000

struct milkmilk {
    int details[3];
    char name2[30];
} st;

char name[50], tel[50], adminID[4][11] = {"admin1", "admin2", "admin3", "admin4"};

void main() {
    system("cls");
    int choose1;
    printf("\n\n\t\t\tPOOKPIK  MILK  SHAKE\n\n");
    printf("\t\t\t 1.  ADMIN\n");
    printf("\t\t\t 2.  CUSTOMER\n");
    printf("\t\t\t 3.  EXIT\n\n");
    printf("\t\tPlease choose 1 or 2 and ENTER : ");
    scanf("%d", &choose1);
    switch(choose1) {
        case 1:
            admininputID();
            break;
        case 2:
            customerinputnametel();
            break;
        default:
            printf("\n\n\t\t\tTHANK YOU");
            getch();
            exit(0);
            break;
    }
}

void admininputID() {
    system("cls");
    char check[11], checkcheck[11];
    int i, j, loop = 0, checkim = 0;
    printf("\n\n\t\t\tPOOKPIK  MILK  SHAKE");
    printf("\n\n\t\t\t\tADMIN\n\n");
    printf("\n\n\tENTER YOUR ADMIN");
    printf("\n\tPRESS 'bk' to back\n\n");
    printf("\t:");
    scanf("%s", check);
    if(strcmp(check, "bk") == 0) {
        main();
    }
    for(i = 0; i < 4; i++) {
        for(j = 0; adminID[i][j] != '\0'; j++) {
            checkcheck[j] = adminID[i][j];
        }
        for(j = 0; adminID[j][i] != '\0'; j++) {
            if(check[j] != checkcheck[j]) {
                checkim++;
            }
        }
        if(checkim == 0) {
            loop = 1;
        }
        checkim = 0;
    }
    if(loop == 0) {
        printf("\n\n\tADMIN CODE IS WRONG PREASE TRY AGAIN\n");
        getch();
        admininputID();
    } else {
        printf("\n\t\tADMIN CODE IS CORRECT ");
        printf("\n\t\tWELCOME %s to ADMIN MANAGE", check);
        getch();
        adminmanage();
    }
}

void adminmanage() {
    system("cls");
    int choose;
    printf("\n\n\t\t\tPOOKPIK  MILK  SHAKE");
    printf("\n\n\t\t\t\tADMIN\n\n");
    printf("\t 1.insert stock\n");
    printf("\t 2.delete stock\n");
    printf("\t 3.back\n");
    printf("\t please choose 1 2 or 3 :");
    scanf("%d", &choose);
    switch(choose) {
        case 1:
            insert_stock();
            break;
        case 2:
            delete_stock();
            break;
        default:
            main();
            break;
    }
}

void insert_stock() {
    FILE *fp;
    system("cls");
    printf("\n\n\t\t\tPOOKPIK  MILK  SHAKE");
    printf("\n\n\t\t\t\tADMIN\n\n");
    char tmp[8];
    int ans;

    if((fp = fopen("product.txt", "ab")) == NULL) {
        perror("Error opening file for insert stock");
        getch();
        exit(1);
    }
    do {
        printf("\n\n\t\t\t   PLEASE INSERT STOCK\n");
        printf("\t\t\tmenu : ");
        fflush(stdin); // ใช้เพื่อเคลียร์ buffer ก่อนการรับ input
        gets(st.name2);
        printf("\n\t\t\tquality : ");
        gets(tmp);
        st.details[1] = atoi(tmp); // เปลี่ยน atof เป็น atoi
        fwrite(&st, sizeof(st), 1, fp);
        if(ferror(fp)) {
            printf("\t\t\tERROR FOR INSERT STOCK\n");
            getch();
            exit(1);
        }
        printf("\t\t\tcontinue (press C) or exit (press E) : ");
        ans = getch();
    } while(ans != 'E');
    fclose(fp);
    adminmanage();
}

void delete_stock() {
    FILE *fp;
    system("cls");
    int i = 0;
    char ans;
    char rec[5];
    printf("\n\n\t\t\tPOOKPIK  MILK  SHAKE");
    printf("\n\n\t\t\t\tADMIN\n\n");
    if((fp = fopen("product.txt", "rb+")) == NULL) {
        perror("Error opening file for delete stock");
        getch();
        exit(1);
    }
    printf("\n\n THIS IS STOCK FOR DELETE\n");
    do {
        while(1) {
            fread(&st, sizeof(st), 1, fp);
            if(ferror(fp)) {
                printf("ERROR TO READ STOCK FOR DELETE\n");
                getch();
                exit(1);
            }
            if(feof(fp))
                break;
            ++i;
            printf("%d.%s\t\t", i, st.name2);
        }
        printf("\nDo you want to delete stock (Y or N) : ");
        ans = getch();
        if(ans == 'Y') {
            printf("\nmenu : ");
            fflush(stdin); // ใช้เพื่อเคลียร์ buffer ก่อนการรับ input
            gets(rec);
            fseek(fp, ((atoi(rec) - 1) * sizeof(st)), SEEK_SET);
            strcpy(st.name2, "\0");
            fwrite(&st, sizeof(st), 1, fp);
            if(ferror(fp)) {
                printf("ERROR FOR DELETE STOCK\n");
                getch();
                exit(1);
            }
            printf("DELETE STOCK COMPLETE\n");
        }
        printf("\ncontinue (press C) or exit (press E) : ");
        ans = getche();
        printf("\n");
    } while(ans != 'E');
    fclose(fp);
    adminmanage();
}

void customerinputnametel() {
    system("cls");
    printf("\n\n\t\t\tPOOKPIK  MILK  SHAKE\n\n");
    printf("\t\t\t\tCUSTOMER\n\n");
    printf("\t\t\tNAME : ");
    fflush(stdin);
    gets(name);
    printf("\t\t\tTEL : ");
    gets(tel);
    User();
}

void User() {
    system("cls");
    char yn = '\0'; // เริ่มต้น yn เป็น '\0' แทนที่จะเป็นตัวอื่นที่ไม่แน่นอน
    FILE *fp1, *fptemp;
    struct milkmilk mk;
    struct milkmilk mk2;
    time_t orig_format;
    time(&orig_format);
    int code, quan, price;
    int total = 0, stotal = 0; // เริ่มต้น total และ stotal เป็น 0
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\tCUSTOMER\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("\n\t              welcome to MILK MILK :)");
    printf("\n\t       MENU                              PRICES");
    printf("\n\t 1. white malt                             60");
    printf("\n\t 2. matcha greentea                        60");
    printf("\n\t 3. strawberry milk shake                  60");
    printf("\n\t 4. orange yuzu milf shake                 60");
    while(yn != 'E') {
        printf("\n\nPlease input code product : ");
        scanf("%d", &code);
        printf("Please quantity : ");
        scanf("%d", &quan);
        if((fp1 = fopen("product.txt", "r")) == NULL) {
            perror("Error opening file for reading");
            exit(1);
        }
        while((fscanf(fp1, "%d %s %d %d", &mk.details[0], mk.name2, &mk.details[1], &mk.details[2])) != EOF) {
            if(code == mk.details[0]) {
                price = mk.details[2];
                total = price * quan;
                printf("\n product name : %s\n price per piece : %d\n quantity : %d\n", mk.name2, mk.details[2], quan);
                printf("\n\n price all : %d\n", total);
                break;
            }
        }
        fclose(fp1);

        FILE *fp2;
        if((fp2 = fopen("receipt.txt", "a")) == NULL) {
            perror("Error opening file for writing receipt");
            exit(1);
        }
        fprintf(fp2, "%d %s %d %d %d %s\n", mk.details[0], mk.name2, mk.details[1], mk.details[2], quan, total, asctime(gmtime(&orig_format)));
        fclose(fp2);

        userUpdateDatabase(mk.details[0], mk.name2, mk.details[1], mk.details[2], quan);
        addRecipt(mk.details[0], mk.name2, quan, total);
        printf("\nDo you want continue ? (Any Key = Yes / E = end and print receipt) : ");
        yn = getche();
    }

    printf("\n-----------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\tReceipt\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\tCode\t\tName\t\tQuantity\t\tPrice\n");
    if((fptemp = fopen("tempRecipt.txt", "r")) == NULL) {
        perror("Error opening tempRecipt.txt for reading");
        exit(1);
    }
    while((fscanf(fptemp, "%d %s %d %d", &mk2.details[0], mk2.name2, &mk2.details[1], &mk2.details[2])) != EOF) {
        printf("\t\t\t%d\t\t%s\t\t%d\t\t\t%d\n", mk2.details[0], mk2.name2, mk2.details[1], mk2.details[2]);
        stotal += mk2.details[2];
    }
    fclose(fptemp);

    printf("\n-----------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\tTotal is %d Bath\n", stotal);
    printf("\t\t\t\t\tTHANK YOU FOR SHOPPING WITH US.\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");

    if((fp1 = fopen("tempRecipt.txt", "w")) == NULL) {
        perror("Error opening tempRecipt.txt for writing");
        exit(1);
    }
    fclose(fp1);

    printf("Continue (Press Enter) or Exit (press E) : ");
    yn = getche();
    if(yn == 'E')
        main();
    else
        User();
}

void userUpdateDatabase(int no, char *name, int q, int p, int qUse) {
    char oldWord[100], newWord[100];
    char buffer[BUFFER_SIZE];

    FILE *fPtr;
    FILE *fTemp;

    snprintf(oldWord, 100, "%d %s %d %d", no, name, q, p);
    q = q - qUse;
    snprintf(newWord, 100, "%d %s %d %d", no, name, q, p);

    fPtr = fopen("product.txt", "r");
    fTemp = fopen("replace.tmp", "w");

    if(fPtr == NULL || fTemp == NULL) {
        perror("Error opening files for updating database");
        exit(EXIT_SUCCESS);
    }

    while((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL) {
        replaceAll(buffer, oldWord, newWord);
        fputs(buffer, fTemp);
    }
    fclose(fPtr);
    fclose(fTemp);

    remove("product.txt");
    rename("replace.tmp", "product.txt");
}

void addRecipt(int c, char *name, int q, int total) {
    FILE *fp2;
    if((fp2 = fopen("purchase_order.txt", "a")) == NULL) {
        perror("Error opening purchase_order.txt for writing receipt");
        exit(1);
    }
    fprintf(fp2, "%d %s %d %d\n", c, name, q, total);
    fclose(fp2);
}

void replaceAll(char *str, const char *oldWord, const char *newWord) {
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;

    owlen = strlen(oldWord);

    if(!strcmp(oldWord, newWord)) {
        return;
    }

    while((pos = strstr(str, oldWord)) != NULL) {
        strcpy(temp, str);
        index = pos - str;
        str[index] = '\0';
        strcat(str, newWord);
        strcat(str, temp + index + owlen);
    }
}
