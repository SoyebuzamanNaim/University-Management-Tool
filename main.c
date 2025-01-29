#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define STUDENT_USERNAME "Student"
#define STUDENT_PASSWORD "Student"

#define TEACHER_USERNAME "Teacher"
#define TEACHER_PASSWORD "Teacher"

typedef struct
{
    long long int roll;
    char name[50];
    int batch;
    char contact[15];
} Student;

void flushInputBuffer();
int studentLogin();
int teacherLogin();
void studentModule();
void teacherModule();

void initializeStudentQueue();
void addStudentToQueue();
void removeStudentFromQueue();
void showAllStudents();
void searchStudentByRoll();
void searchStudentByName();
void updateStudentInfo();
void sortStudentsByRoll();
int isQueueEmpty();
int isQueueFull();

void libraryModule();
void displayBookInfo();
void listBooksByAuthor();
void displayBookCount();
void borrowBook();
void returnBook();
void buyBook();

#define MAX_BOOK_STACK 100
#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 50

typedef struct
{
    int id;
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    int available;
    char borrower[50];
} Book;

Book bookStack[MAX_BOOK_STACK];
int bookStackTop = -1;

void initializeBookStack();
int isBookStackEmpty();
int isBookStackFull();
void pushToBookStack(Book book);
Book popFromBookStack();

#define MAX_QUEUE_SIZE 100
Student studentQueue[MAX_QUEUE_SIZE];
int queueFront = -1, queueRear = -1, queueSize = 0;

int main()
{

    int choice;
    printf("\n\nWelcome to University Management System\n");
    do
    {
        printf("\nMain Menu:\n");
        printf("1. Teacher Login\n");
        printf("2. Student Login\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        flushInputBuffer();

        switch (choice)
        {
        case 1:
            if (teacherLogin() || 1)
                teacherModule();

            break;
        case 2:
            if (studentLogin() || 1)
                studentModule();

            break;
        case 3:
            printf("Exiting system...\n");
            break;
        default:
            printf("\nInvalid choice! \nTry again.\n");
        }
    } while (choice != 3);
}

void flushInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int studentLogin()
{
    char username[50], password[50];

    printf("\nStudent Login\n");

    printf("Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if (strcmp(username, STUDENT_USERNAME) == 0 && strcmp(password, STUDENT_PASSWORD) == 0)
    {
        printf("Welcome Student!\n");
        return 1;
    }

    printf("Invalid Password or Username!\n");
    return 0;
}

int teacherLogin()
{
    char username[50], password[50];
    printf("\nTeacher Login\n");
    printf("Username: ");
    fgets(username, 50, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Password: ");
    fgets(password, 50, stdin);
    password[strcspn(password, "\n")] = '\0';

    if (strcmp(username, TEACHER_USERNAME) == 0 &&
        strcmp(password, TEACHER_PASSWORD) == 0)
    {
        printf("Welcome Teacher!\n");
        return 1;
    }
    printf("Invalid Password or Username!\n");
    return 0;
}

void teacherModule()
{
    int choice;
    initializeStudentQueue();

    do
    {
        printf("\nTeacher Module\n");
        printf("1. Add Student\n");
        printf("2. Find Student by Roll\n");
        printf("3. Find Student by Name\n");
        printf("4. Total Students\n");
        printf("5. Delete Student\n");
        printf("6. Update Student\n");
        printf("7. Display All Students\n");
        printf("8. Sort by Roll\n");
        printf("9. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        flushInputBuffer();

        switch (choice)
        {
        case 1:
            addStudentToQueue();
            break;
        case 2:
            searchStudentByRoll();
            break;
        case 3:
            searchStudentByName();
            break;
        case 4:
            printf("\nTotal Students: %d\n", queueSize);
            break;
        case 5:
            removeStudentFromQueue();
            break;
        case 6:
            updateStudentInfo();
            break;
        case 7:
            showAllStudents();
            break;
        case 8:
            sortStudentsByRoll();
            showAllStudents();
            break;
        case 9:
            printf("\nExiting Teacher Module...\n\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 9);
}

void initializeStudentQueue()
{
    Student sample[5] = {
        {2023200000066, "Naim", 65, "0123456789"},
        {10, "Bob", 23, "0171234567"},
        {43, "Charlie", 24, "0182345678"},
        {32L, "David", 24, "0193456789"},
        {10L, "Emma", 25, "0154567890"}};
    for (int i = 0; i < 5; i++)
    {
        queueRear = (queueRear + 1) % MAX_QUEUE_SIZE;
        studentQueue[queueRear] = sample[i];
        queueSize++;
    }
    queueFront = 0;
}

int isQueueEmpty()
{
    return queueSize == 0;
}

int isQueueFull()
{
    return queueSize == MAX_QUEUE_SIZE;
}

void addStudentToQueue()
{
    if (isQueueFull())
    {
        printf("Queue is full! Cannot add more students.\n");
        return;
    }
    if (queueFront == -1)
        queueFront = 0;

    queueRear = (queueRear + 1) % MAX_QUEUE_SIZE;
    printf("Enter Roll Number: ");
    scanf("%lld", &studentQueue[queueRear].roll);
    getchar();
    printf("Enter Name: ");
    fgets(studentQueue[queueRear].name, sizeof(studentQueue[queueRear].name), stdin);
    studentQueue[queueRear].name[strcspn(studentQueue[queueRear].name, "\n")] = '\0';

    printf("Enter Batch Number: ");
    scanf("%d", &studentQueue[queueRear].batch);
    printf("Enter Contact Number: ");
    scanf("%s", studentQueue[queueRear].contact);

    queueSize++;
    printf("Student added successfully!\n");
}

void removeStudentFromQueue()
{
    if (isQueueEmpty())
    {
        printf("No students in the queue!\n");
        return;
    }
    printf("Removing Student: Roll: %lld, Name: %s\n", studentQueue[queueFront].roll, studentQueue[queueFront].name);
    queueFront = (queueFront + 1) % MAX_QUEUE_SIZE;
    queueSize--;
}

void showAllStudents()
{
    if (isQueueEmpty())
    {
        printf("No students in the queue.\n");
        return;
    }
    printf("\n--- Student List ---\n");
    int i, index;
    for (i = 0; i < queueSize; i++)
    {
        index = (queueFront + i) % MAX_QUEUE_SIZE;
        printf("Roll: %lld | Name: %s | Batch: %d | Contact: %s\n",
               studentQueue[index].roll, studentQueue[index].name, studentQueue[index].batch, studentQueue[index].contact);
    }
}

void searchStudentByRoll()
{
    long long int roll;
    int i, index;
    printf("Enter Roll Number to search: ");
    scanf("%lld", &roll);

    for (i = 0; i < queueSize; i++)
    {
        index = (queueFront + i) % MAX_QUEUE_SIZE;
        if (studentQueue[index].roll == roll)
        {
            printf("Student Found: %s (Roll: %lld, Batch: %d, Contact: %s)\n",
                   studentQueue[index].name, studentQueue[index].roll, studentQueue[index].batch, studentQueue[index].contact);
            return;
        }
    }
    printf("Student with Roll %lld not found.\n", roll);
}

void searchStudentByName()
{
    char name[50];
    int i, index;
    printf("Enter Name to search: ");

    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    for (i = 0; i < queueSize; i++)
    {
        index = (queueFront + i) % MAX_QUEUE_SIZE;
        if (strcasecmp(studentQueue[index].name, name) == 0)
        {
            printf("Student Found: %s (Roll: %lld, Batch: %d, Contact: %s)\n",
                   studentQueue[index].name, studentQueue[index].roll, studentQueue[index].batch, studentQueue[index].contact);
            return;
        }
    }
    printf("Student with Name '%s' not found.\n", name);
}

void updateStudentInfo()
{
    long long int roll;
    int i, index;
    printf("Enter Roll Number to update: ");
    scanf("%lld", &roll);

    for (i = 0; i < queueSize; i++)
    {
        index = (queueFront + i) % MAX_QUEUE_SIZE;
        if (studentQueue[index].roll == roll)
        {
            printf("Updating Student: %s (Roll: %lld)\n", studentQueue[index].name, studentQueue[index].roll);
            printf("Enter New Name: ");
            getchar();
            fgets(studentQueue[index].name, sizeof(studentQueue[index].name), stdin);
            studentQueue[index].name[strcspn(studentQueue[index].name, "\n")] = '\0';

            printf("Enter New Batch Number: ");
            scanf("%d", &studentQueue[index].batch);
            printf("Enter New Contact Number: ");
            scanf("%s", studentQueue[index].contact);

            printf("Student updated successfully!\n");
            return;
        }
    }
    printf("Student with Roll %lld not found.\n", roll);
}

void sortStudentsByRoll()
{
    if (isQueueEmpty())
    {
        printf("No students to sort.\n");
        return;
    }
    int i, j, index1, index2;
    Student temp;

    for (i = 0; i < queueSize - 1; i++)
    {
        for (j = 0; j < queueSize - i - 1; j++)
        {
            index1 = (queueFront + j) % MAX_QUEUE_SIZE;
            index2 = (queueFront + j + 1) % MAX_QUEUE_SIZE;

            if (studentQueue[index1].roll > studentQueue[index2].roll)
            {
                temp = studentQueue[index1];
                studentQueue[index1] = studentQueue[index2];
                studentQueue[index2] = temp;
            }
        }
    }
    printf("Students sorted by Roll Number successfully!\n");
}

void studentModule()
{
    int choice;
    do
    {
        printf("\nStudent Module\n");
        printf("1. Library\n");
        printf("2. Quiz\n");
        printf("3. Tuition fees calculator\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        flushInputBuffer();

        switch (choice)
        {
        case 1:
            libraryModule();
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 3);
}

void libraryModule()
{
    initializeBookStack();
    int choice;
    do
    {
        printf("\nWelcome  to \nLibrary Management System \n");
        printf("1. Display All Book Information\n");
        printf("2. List All Books by a Given Author\n");
        printf("3. List the Count of Books in the Library\n");
        printf("4. Borrow a Book\n");
        printf("5. Return a Book\n");
        printf("6. Buy a Book\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        flushInputBuffer();

        switch (choice)
        {
        case 1:
            displayBookInfo();
            break;
        case 2:
            listBooksByAuthor();
            break;
        case 3:
            displayBookCount();
            break;
        case 4:
            borrowBook();
            break;
        case 5:
            returnBook();
            break;
        case 6:
            buyBook();
            break;
        case 7:
            printf("Exiting Library Module...\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 7);
}

void initializeBookStack()
{
    Book initialBooks[] = {
        {1, "The C Programming Language", "Dennis Ritchie", 1, ""},
        {2, "Data Structures in C", "Robert Sedgewick", 1, ""},
        {3, "Clean Code", "Robert Martin", 1, ""},
        {4, "Introduction to Algorithms", "Thomas Cormen", 1, ""},
        {5, "Design Patterns", "Erich Gamma", 1, ""}};

    for (int i = 0; i < 5; i++)
    {
        pushToBookStack(initialBooks[i]);
    }
}

int isBookStackEmpty()
{
    return bookStackTop == -1;
}

int isBookStackFull()
{
    return bookStackTop == MAX_BOOK_STACK - 1;
}

void pushToBookStack(Book book)
{
    if (!isBookStackFull())
    {
        bookStack[++bookStackTop] = book;
    }
}

Book popFromBookStack()
{
    Book emptyBook = {0, "", "", 0, ""};
    if (!isBookStackEmpty())
    {
        return bookStack[bookStackTop--];
    }
    return emptyBook;
}

void displayBookInfo()
{
    if (isBookStackEmpty())
    {
        printf("No books in library!\n");
        return;
    }

    printf("\n--- Book Information ---\n");
    for (int i = 0; i <= bookStackTop; i++)
    {

        printf("Book ID: %d\n", bookStack[i].id);
        printf("Title: %s\n", bookStack[i].title);
        printf("Author: %s\n", bookStack[i].author);
        printf("Status: %s\n", bookStack[i].available ? "Available" : "Borrowed");
        if (!bookStack[i].available)
        {
            printf("Borrowed or Purchased by: %s\n", bookStack[i].borrower);
        }
        printf("------------------------\n");
    }
}

void listBooksByAuthor()
{
    if (isBookStackEmpty())
    {
        printf("No books in library!\n");
        return;
    }

    char author[MAX_AUTHOR_LENGTH];
    int found = 0;

    printf("Enter Author Name: ");
    fgets(author, MAX_AUTHOR_LENGTH, stdin);
    author[strcspn(author, "\n")] = '\0';

    printf("\nBooks by %s:\n", author);
    for (int i = 0; i <= bookStackTop; i++)
    {
        if (strcasecmp(bookStack[i].author, author) == 0)
        {
            printf("Book ID: %d. %s (%s)\n", bookStack[i].id, bookStack[i].title,
                   bookStack[i].available ? "Available" : "Borrowed");
            found++;
        }
    }
    if (!found)
    {
        printf("No books found by this author.\n");
    }
}

void displayBookCount()
{
    if (isBookStackEmpty())
    {
        printf("No books in library!\n");
        return;
    }

    Book tempStack[MAX_BOOK_STACK];
    int tempTop = -1;
    int availableInStack = 0;
    int borrowedFromStack = 0;

    while (!isBookStackEmpty())
    {
        Book currentBook = popFromBookStack();
        if (currentBook.available)
        {
            availableInStack++;
        }
        else
        {
            borrowedFromStack++;
        }
        tempStack[++tempTop] = currentBook;
    }

    // Restore books to original stack
    while (tempTop >= 0)
    {
        pushToBookStack(tempStack[tempTop--]);
    }

    printf("\nLibrary Stack Statistics:\n");
    printf("Total Books in Stack: %d\n", availableInStack + borrowedFromStack);
    printf("Available Books in Stack: %d\n", availableInStack);
    printf("Borrowed Books from Stack: %d\n", borrowedFromStack);
}

void borrowBook()
{
    if (isBookStackEmpty())
    {
        printf("No books in library!\n");
        return;
    }

    int bookId;
    printf("Enter Book ID to borrow: ");
    scanf("%d", &bookId);
    flushInputBuffer();

    for (int i = 0; i <= bookStackTop; i++)
    {
        if (bookStack[i].id == bookId)
        {
            if (bookStack[i].available)
            {
                printf("Enter your name: ");
                fgets(bookStack[i].borrower, 50, stdin);
                bookStack[i].borrower[strcspn(bookStack[i].borrower, "\n")] = '\0';

                bookStack[i].available = 0;
                printf("Book borrowed successfully from stack!\n");
            }
            else
            {
                printf("Book is already borrowed by %s\n", bookStack[i].borrower);
            }
            return;
        }
    }
    printf("Book not found in stack!\n");
}

void returnBook()
{
    if (isBookStackEmpty())
    {
        printf("No books in library!\n");
        return;
    }

    int bookId;
    printf("Enter Book ID to return to stack: ");
    scanf("%d", &bookId);
    flushInputBuffer();

    for (int i = 0; i <= bookStackTop; i++)
    {
        if (bookStack[i].id == bookId)
        {
            if (!bookStack[i].available)
            {
                bookStack[i].available = 1;
                strcpy(bookStack[i].borrower, "");
                printf("Book returned successfully to stack!\n");
            }
            else
            {
                printf("This book is not borrowed!\n");
                printf("Do you want to give this book to library? (y/n): ");
                char choice;
                scanf("%c", &choice);
                flushInputBuffer();

                if (choice == 'y' || choice == 'Y')
                {
                    Book newBook;
                    newBook.id = bookStackTop + 2; // New ID will be last ID + 1
                    printf("Enter Book Title: ");
                    fgets(newBook.title, MAX_TITLE_LENGTH, stdin);
                    newBook.title[strcspn(newBook.title, "\n")] = '\0';

                    printf("Enter Book Author: ");
                    fgets(newBook.author, MAX_AUTHOR_LENGTH, stdin);
                    newBook.author[strcspn(newBook.author, "\n")] = '\0';

                    newBook.available = 1;
                    strcpy(newBook.borrower, "");

                    pushToBookStack(newBook);
                    printf("Book added to library successfully!\n");
                }
            }
            return;
        }
    }

    // If book not found, ask if they want to add a new book
    printf("Book not found in library!\n");
    printf("Do you want to give this book to library? (y/n): ");
    char choice;
    scanf("%c", &choice);
    flushInputBuffer();

    if (choice == 'y' || choice == 'Y')
    {
        Book newBook;
        newBook.id = bookStackTop + 2; // New ID will be last ID + 1
        printf("Enter Book Title: ");
        fgets(newBook.title, MAX_TITLE_LENGTH, stdin);
        newBook.title[strcspn(newBook.title, "\n")] = '\0';

        printf("Enter Book Author: ");
        fgets(newBook.author, MAX_AUTHOR_LENGTH, stdin);
        newBook.author[strcspn(newBook.author, "\n")] = '\0';

        newBook.available = 1;
        strcpy(newBook.borrower, "");

        pushToBookStack(newBook);
        printf("Book added to library successfully!\n");
    }
}

void buyBook()
{
    if (isBookStackEmpty())
    {
        printf("No books available to buy!\n");
        return;
    }

    printf("\nAvailable books to buy:\n");
    Book tempStack[MAX_BOOK_STACK];
    int tempTop = -1;

    while (!isBookStackEmpty())
    {
        Book currentBook = popFromBookStack();
        if (currentBook.available)
        {
            printf("ID: %d, Title: %s, Author: %s\n",
                   currentBook.id, currentBook.title, currentBook.author);
        }
        tempStack[++tempTop] = currentBook;
    }

    // Restore books to original stack
    while (tempTop >= 0)
    {
        pushToBookStack(tempStack[tempTop--]);
    }

    int bookId;
    printf("\nEnter Book ID to buy: ");
    scanf("%d", &bookId);
    flushInputBuffer();

    tempTop = -1;
    int found = 0;

    while (!isBookStackEmpty())
    {
        Book currentBook = popFromBookStack();
        if (currentBook.id == bookId && currentBook.available)
        {
            printf("Enter your name: ");
            fgets(currentBook.borrower, 50, stdin);
            currentBook.borrower[strcspn(currentBook.borrower, "\n")] = '\0';
            currentBook.available = 0;
            printf("Book '%s' has been purchased successfully by %s!\n",
                   currentBook.title, currentBook.borrower);
            found = 1;
        }
        tempStack[++tempTop] = currentBook;
    }

    // Restore all books to original stack
    while (tempTop >= 0)
    {
        pushToBookStack(tempStack[tempTop--]);
    }

    if (!found)
    {
        printf("Book not found or not available for purchase!\n");
    }
}
