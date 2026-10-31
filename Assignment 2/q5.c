#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 4
#define MAX_BORROW 3

void displayMenu();

void registerMember(char name[], int *studentID, int *memberType);

void displayBooks(int bookIDs[], char bookTitles[][50],
                  int availableCopies[], int totalBooks);

void borrowBook(int bookIDs[], char bookTitles[][50],
                int availableCopies[], int totalBooks,
                int borrowedBookIDs[], int *borrowedCount,
                int memberType);

float returnBook(int bookIDs[], int availableCopies[],
                 int totalBooks, int borrowedBookIDs[],
                 int *borrowedCount, int memberType,
                 float *totalFine);

void displayMemberRecord(char name[], int studentID, int memberType,
                         int borrowedBookIDs[], int borrowedCount,
                         float totalFine, float fineAfterWaiver);

int main()
{
    int bookIDs[MAX_BOOKS] = {101, 102, 103, 104};

    char bookTitles[MAX_BOOKS][50] = {
        "Programming in C",
        "Data Structures",
        "Database Systems",
        "Computer Networks"
    };

    int availableCopies[MAX_BOOKS] = {5, 3, 0, 4};

    char name[50] = "";
    int studentID = 0;
    int memberType = 0;
    int registered = 0;

    int borrowedBookIDs[MAX_BORROW];
    int borrowedCount = 0;
    int totalBooks = MAX_BOOKS;
    int choice;

    float totalFine = 0;
    float fineAfterWaiver = 0;

    do
    {
        displayMenu();

        printf("Enter your choice: ");

        if(scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            return 1;
        }

        switch(choice)
        {
            case 1:
                if(registered == 0)
                {
                    registerMember(name, &studentID, &memberType);

                    if(memberType == 1 || memberType == 2)
                    {
                        registered = 1;
                    }
                }
                else
                {
                    printf("Member already registered.\n");
                }
                break;

            case 2:
                displayBooks(bookIDs, bookTitles,
                             availableCopies, totalBooks);
                break;

            case 3:
                if(registered == 1)
                {
                    borrowBook(bookIDs, bookTitles,
                               availableCopies, totalBooks,
                               borrowedBookIDs, &borrowedCount,
                               memberType);
                }
                else
                {
                    printf("Please register first.\n");
                }
                break;

            case 4:
                if(registered == 1)
                {
                    fineAfterWaiver += returnBook(
                        bookIDs, availableCopies, totalBooks,
                        borrowedBookIDs, &borrowedCount,
                        memberType, &totalFine);
                }
                else
                {
                    printf("Please register first.\n");
                }
                break;

            case 5:
                if(registered == 1)
                {
                    displayMemberRecord(name, studentID, memberType,
                                        borrowedBookIDs, borrowedCount,
                                        totalFine, fineAfterWaiver);
                }
                else
                {
                    printf("No member record found.\n");
                }
                break;

            case 6:
                printf("Program ended.\n");
                break;

            default:
                printf("Invalid menu choice!\n");
        }

    } while(choice != 6);

    return 0;
}

void displayMenu()
{
    printf("1. Register Member\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
}

void registerMember(char name[], int *studentID, int *memberType)
{
    int type;

    printf("Enter member name: ");
    scanf(" %49[^\n]", name);

    printf("Enter student ID: ");
    if(scanf("%d", studentID) != 1)
    {
        printf("Invalid student ID.\n");
        name[0] = '\0';
        *studentID = 0;
        *memberType = 0;
        return;
    }

    printf("1. Student\n");
    printf("2. Faculty\n");
    printf("Enter membership type: ");

    if(scanf("%d", &type) != 1 || (type != 1 && type != 2))
    {
        printf("Invalid membership type!\n");
        name[0] = '\0';
        *studentID = 0;
        *memberType = 0;
        return;
    }

    *memberType = type;
    printf("Member registered successfully.\n");
}

void displayBooks(int bookIDs[], char bookTitles[][50],
                  int availableCopies[], int totalBooks)
{
    int i;

    printf("\nID\tTitle\t\t\tCopies\n");

    for(i = 0; i < totalBooks; i++)
    {
        printf("%d\t%-24s %d\n",
               bookIDs[i], bookTitles[i], availableCopies[i]);
    }
}

void borrowBook(int bookIDs[], char bookTitles[][50],
                int availableCopies[], int totalBooks,
                int borrowedBookIDs[], int *borrowedCount,
                int memberType)
{
    int id, days, i;
    int found = -1;
    int allowedDays;

    if(*borrowedCount >= MAX_BORROW)
    {
        printf("Maximum limit of 3 books reached.\n");
        return;
    }

    printf("Enter book ID: ");
    if(scanf("%d", &id) != 1)
    {
        printf("Invalid book ID.\n");
        return;
    }

    printf("Enter number of days: ");
    if(scanf("%d", &days) != 1 || days <= 0)
    {
        printf("Days must be a positive number.\n");
        return;
    }

    for(i = 0; i < totalBooks; i++)
    {
        if(bookIDs[i] == id)
        {
            found = i;
            break;
        }
    }

    if(found == -1)
    {
        printf("Invalid book ID!\n");
        return;
    }

    if(availableCopies[found] <= 0)
    {
        printf("No copies available for this book.\n");
        return;
    }

    if(memberType == 1)
        allowedDays = 14;
    else
        allowedDays = 30;

    borrowedBookIDs[*borrowedCount] = id;
    (*borrowedCount)++;
    availableCopies[found]--;

    printf("Book borrowed successfully: %s\n", bookTitles[found]);

    if(days > allowedDays)
    {
        printf("Warning: You entered more than %d days.\n",
               allowedDays);
    }
    else
    {
        printf("Allowed borrowing period: %d days.\n", allowedDays);
    }
}

float returnBook(int bookIDs[], int availableCopies[],
                 int totalBooks, int borrowedBookIDs[],
                 int *borrowedCount, int memberType,
                 float *totalFine)
{
    int id, days, i;
    int borrowedIndex = -1;
    int found = -1;
    int allowedDays;
    float fine = 0;
    float payable;
    char code[30];

    if(*borrowedCount == 0)
    {
        printf("You have no borrowed books.\n");
        return 0;
    }

    printf("Enter book ID to return: ");
    if(scanf("%d", &id) != 1)
    {
        printf("Invalid book ID.\n");
        return 0;
    }

    for(i = 0; i < *borrowedCount; i++)
    {
        if(borrowedBookIDs[i] == id)
        {
            borrowedIndex = i;
            break;
        }
    }

    if(borrowedIndex == -1)
    {
        printf("You have not borrowed this book.\n");
        return 0;
    }

    printf("Enter actual days kept: ");
    if(scanf("%d", &days) != 1 || days <= 0)
    {
        printf("Days must be a positive number.\n");
        return 0;
    }

    if(memberType == 1)
        allowedDays = 14;
    else
        allowedDays = 30;

    if(days > allowedDays)
    {
        if(memberType == 1)
            fine = (days - allowedDays) * 20.0;
        else
            fine = (days - allowedDays) * 10.0;
    }

    printf("Fine before waiver: Rs. %.2f\n", fine);

    payable = fine;

    if(fine > 0)
    {
        printf("Enter membership code: ");
        scanf("%29s", code);

        if(strcmp(code, "LIB2026") == 0)
        {
            payable = fine * 0.50;
            printf("Correct code! 50%% waiver applied.\n");
        }
        else
        {
            printf("Wrong code. No waiver applied.\n");
        }
    }

    for(i = 0; i < totalBooks; i++)
    {
        if(bookIDs[i] == id)
        {
            found = i;
            break;
        }
    }

    if(found != -1)
        availableCopies[found]++;

    for(i = borrowedIndex; i < *borrowedCount - 1; i++)
    {
        borrowedBookIDs[i] = borrowedBookIDs[i + 1];
    }

    (*borrowedCount)--;

    *totalFine += fine;

    printf("Book returned successfully.\n");
    printf("Fine payable after waiver: Rs. %.2f\n", payable);

    return payable;
}

void displayMemberRecord(char name[], int studentID, int memberType,
                         int borrowedBookIDs[], int borrowedCount,
                         float totalFine, float fineAfterWaiver)
{
    int i;

    printf("\nMEMBER RECORD\n");
    printf("Name: %s\n", name);
    printf("Student ID: %d\n", studentID);

    if(memberType == 1)
        printf("Membership: Student\n");
    else
        printf("Membership: Faculty\n");

    printf("Currently borrowed book IDs: ");

    if(borrowedCount == 0)
    {
        printf("None");
    }
    else
    {
        for(i = 0; i < borrowedCount; i++)
        {
            printf("%d ", borrowedBookIDs[i]);
        }
    }

    printf("\nTotal fine before waiver: Rs. %.2f\n", totalFine);
    printf("Final fine payable: Rs. %.2f\n", fineAfterWaiver);
}
