#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// define structure book
typedef struct Books
{
    char book_name[50];
    float price;
    int pages;
    int supplies;
} book;

// uppercase a string
void upper(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        str[i] = toupper(str[i]);
    }
}

// registers new book in library
void register_books(book *book_details, int num_books)
{
    // take all details for books
    for (int i = 0; i < num_books; i++)
    {
        printf("---------------------------\n");
        fflush(stdin);
        printf("Book name: ");
        gets((book_details + i)->book_name);
        // uppercase the book name
        upper((book_details + i)->book_name);
        printf("Book price: ");
        scanf("%f", &(book_details + i)->price);
        printf("Total pages: ");
        scanf("%d", &(book_details + i)->pages);
        printf("Total supplies: ");
        scanf("%d", &(book_details + i)->supplies);
        printf("---------------------------\n");
    }
}

// to search a specific book with name
int find_book(book *books, int total, char *match)
{
    upper(match); // uppercase the string because all book names are in uppercase
    printf("---------------------------\n");
    for (int i = 0; i < total; i++)
    {
        if (strcmp(((books + i)->book_name), match) == 0)
        {
            printf("Name of book: %s\n", books->book_name);
            printf("Price: %.2f\n", books->price);
            printf("Total pages: %d\n", books->pages);
            printf("Supplies available: %d\n", books->supplies);
            return i;
        }
    }
    printf("---------------------------\n");
    return -1;
}

// issue books
void issue_book(book *books, char *book_name, int total)
{
    signed int index = find_book(books, total, book_name);
    if (index != -1)
    {
        if ((books + index)->supplies != 0)
        {
            (books + index)->supplies--;
            printf("Book issued!");
        }
        else
        {
            printf("All copies have been issued.");
        }
    }
    else
    {
        printf("This books doesn't exist.");
    }
}

// shows all the books present
void show_all(book *books, int total)
{
    printf("---------------------------\n");
    printf("\nBook name\t\tBook Price\tTotal Pages\tCopies available\n");
    for (int i = 0; i < total; i++)
    {
        printf("%-15s \t%-6.2f \t\t%-4d \t\t%-3d\n", books[i].book_name, books[i].price, books[i].pages, books[i].supplies);
    }
    printf("---------------------------\n");
}

// main function
int main()
{
    // num_books is total number of books you wanna register
    int num_books;
    // declaring a pointer structure
    book *book_details;

    // inout for total number of books to register
    printf("Number of books you want to register: ");
    scanf("%d", &num_books);

    // dynamically allocate size of the pointer
    book_details = (book *)malloc(num_books * sizeof(book));

    // register some books for the first time
    register_books(book_details, num_books);
    int choice;
    // k is a count for total number of books present
    int k = num_books;
    // book name stores name of the book to find
    char book_name[50];

    // loop keeps going until you choose to exit
    while (1)
    {
        // take user decision for what action to perform
        printf("\n1. Register books\t2. Find book\t3. Issue a book\t4. Show all\t5. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            // inout for total number of books to register
            printf("Number of books you want to register: ");
            scanf("%d", &num_books);

            // dynamically allocate size of the pointer
            book_details = (book *)realloc(book_details, num_books);

            // call function to register books in library
            register_books((book_details + k), num_books);
            k++; // k is total number of books
        }
        else if (choice == 2)
        {
            // searches a specific book for you
            printf("\nName a book to search: ");
            fflush(stdin);
            // scanf("%[^\n]%*c", book_name);
            gets(book_name);
            // if there is no book found... it prints there is no book
            if (!find_book(book_details, num_books, book_name))
            {
                printf("We couldn't find any book with that name.\n");
            }
        }
        else if (choice == 3)
        {
            printf("Enter name of the book: ");
            fflush(stdin);
            gets(book_name);
            issue_book(book_details, book_name, num_books);
        }

        else if (choice == 4)
        { // shows all the book present
            show_all(book_details, num_books + k - 1);
        }
        else if (choice == 5)
        {
            // exits there loop
            break;
        }
        else
        {
            printf("Invalid option.\nTry again.\n\n");
        }
    }
    free(book_details);
    return 0;
}
