// Write a program to implement an address book with options given below: a) Create address book. b) View address book. c) Insert a record. d) Delete a record. e) Modify a record. f) Exit

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[30];
    char phone[15];
    char email[30];
} Address;

Address book[MAX];
int count = 0;

void createAddressBook() {
    count = 0;
    printf("Address book created!\n");
}

void viewAddressBook() {
    if (count == 0) {
        printf("Address book is empty!\n");
    } else {
        for (int i = 0; i < count; i++) {
            printf("Name: %s, Phone: %s, Email: %s\n", book[i].name, book[i].phone, book[i].email);
        }
    }
}

void insertRecord() {
    if (count < MAX) {
        printf("Enter name: ");
        scanf("%s", book[count].name);
        printf("Enter phone: ");
        scanf("%s", book[count].phone);
        printf("Enter email: ");
        scanf("%s", book[count].email);
        count++;
    } else {
        printf("Address book is full!\n");
    }
}

void deleteRecord() {
    char name[30];
    printf("Enter name to delete: ");
    scanf("%s", name);

    for (int i = 0; i < count; i++) {
        if (strcmp(book[i].name, name) == 0) {
            for (int j = i; j < count - 1; j++) {
                book[j] = book[j + 1];
            }
            count--;
            printf("Record deleted!\n");
            return;
        }
    }
    printf("Record not found!\n");
}

void modifyRecord() {
    char name[30];
    printf("Enter name to modify: ");
    scanf("%s", name);

    for (int i = 0; i < count; i++) {
        if (strcmp(book[i].name, name) == 0) {
            printf("Enter new phone: ");
            scanf("%s", book[i].phone);
            printf("Enter new email: ");
            scanf("%s", book[i].email);
            printf("Record modified!\n");
            return;
        }
    }
    printf("Record not found!\n");
}

int main() {
    int choice;
    while (1) {
        printf("\n1. Create Address Book\n2. View Address Book\n3. Insert Record\n4. Delete Record\n5. Modify Record\n6. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                createAddressBook();
                break;
            case 2:
                viewAddressBook();
                break;
            case 3:
                insertRecord();
                break;
            case 4:
                deleteRecord();
                break;
            case 5:
                modifyRecord();
                break;
            case 6:
                exit(0);
                break;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
