#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char name[50];
    char author[50];
    int issued;
};

void addBook() {
    struct Book b;
    FILE *fp = fopen("library.txt", "ab");

    printf("Enter Book ID: ");
    scanf("%d", &b.id);

    printf("Enter Book Name: ");
    scanf(" %s[^\n]", b.name);

    printf("Enter Author Name: ");
    scanf(" %s[^\n]", b.author);

    b.issued = 0;

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);

    printf("Book Added Successfully!\n");
}

void displayBooks() {
    struct Book b;
    FILE *fp = fopen("library.txt", "rb");

    printf("\nID\tName\t\tAuthor\t\tStatus\n");
    printf("-----------------------------------------\n");

    while (fread(&b, sizeof(b), 1, fp)) {
        printf("%d\t%s\t\t%s\t\t%s\n",
               b.id, b.name, b.author,
               b.issued ? "Issued" : "Available");
    }

    fclose(fp);
}

void searchBook() {
    struct Book b;
    int id, found = 0;

    FILE *fp = fopen("library.txt", "rb");

    printf("Enter Book ID to search: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id) {
            printf("Book Found!\n");
            printf("Name: %s\n", b.name);
            printf("Author: %s\n", b.author);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Book not found\n");

    fclose(fp);
}

void issueBook() {
    struct Book b;
    int id;

    FILE *fp = fopen("library.txt", "rb+");

    printf("Enter Book ID to issue: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id) {
            if (b.issued == 1) {
                printf("Book already issued!\n");
            } else {
                b.issued = 1;
                fseek(fp, -sizeof(b), SEEK_CUR);
                fwrite(&b, sizeof(b), 1, fp);
                printf("Book issued successfully!\n");
            }
            fclose(fp);
            return;
        }
    }

    printf("Book not found\n");
    fclose(fp);
}

int main(void) {
    int choice;

    while (1) {
        printf("\n--- Library Management System ---\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book\n");
        printf("4. Issue Book\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addBook();
            break;

        case 2:
            displayBooks();
            break;

        case 3:
            searchBook();
            break;

        case 4:
            issueBook();
            break;

        case 5:
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
