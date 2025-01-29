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

#define MAX_QUEUE_SIZE 100
Student studentQueue[MAX_QUEUE_SIZE];
int queueFront = -1, queueRear = -1, queueSize = 0;

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

void quizModule();
void dmQuiz();
void dsQuiz();
void addQuestion(const char *questionText, const char options[4][100], int correctOption);
void freeQuestions();
void initializeDM();

typedef struct dmQn
{
    char question[200];
    char options[4][100];
    int correctOption;
    struct dmQn *next;
} dmQn;

dmQn *head = NULL;

void addQuestion(const char *questionText, const char options[4][100], int correctOption);
void freeQuestions();

typedef struct dsQn
{
    char question[200];
    char options[4][100];
    int correctOption;
    struct dsQn *prev;
    struct dsQn *next;
} dsQn;
dsQn *dsHead = NULL, *dsTail = NULL;
void addDSQuestion(const char *questionText, const char options[4][100], int correctOption);
void freeDSQuestions();
void initializeDS();
void tuitionFeesCalculator();

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
            if (teacherLogin())
                teacherModule();

            break;
        case 2:
            if (studentLogin())
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
        case 2:
            quizModule();
            break;
        case 3:
            tuitionFeesCalculator();
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
        printf("5. Return a Book/Donate a Book\n");
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
    printf("Enter Book ID to return to stack/Enter '-1' to donate: ");
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
                    newBook.id = bookStackTop + 2;
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

    printf("Book not found in library!\n");
    printf("Do you want to give this book to library? (y/n): ");
    char choice;
    scanf("%c", &choice);
    flushInputBuffer();

    if (choice == 'y' || choice == 'Y')
    {
        Book newBook;
        newBook.id = bookStackTop + 2;
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

    while (tempTop >= 0)
    {
        pushToBookStack(tempStack[tempTop--]);
    }

    if (!found)
    {
        printf("Book not found or not available for purchase!\n");
    }
}

void quizModule()
{
    int choice;
    do
    {
        printf("\nQuiz Module\n");

        printf("1. Start Quiz in Discrete Mathmemtic\n");
        printf("2. Start Quiz in Data Structure\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        flushInputBuffer();

        switch (choice)
        {
        case 1:
            dmQuiz();
            break;
        case 2:
            dsQuiz();
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 3);
}

void dmQuiz()
{
    initializeDM();
    int score = 0;
    int answer;
    dmQn *current = head;

    if (current == NULL)
    {
        printf("No questions available for the quiz.\n");
        return;
    }

    printf("\n--- Discrete Mathematics Quiz ---\n");

    int questionCount = 0;
    while (current != NULL && questionCount < 5)
    {
        printf("%s\n", current->question);
        for (int i = 0; i < 4; i++)
        {
            printf("%d. %s\n", i + 1, current->options[i]);
        }
        printf("Enter your answer (1-4): ");
        scanf("%d", &answer);

        if (answer < 1 || answer > 4)
        {
            printf("Invalid input. Please enter a number between 1 and 4.\n");
            continue;
        }

        if (answer - 1 == current->correctOption)
        {
            score++;
            printf("Correct!\n");
        }
        else
        {
            printf("Incorrect. The correct answer was %d.\n", current->correctOption + 1);
        }

        current = current->next;
        questionCount++;
    }

    printf("Your total score: %d out of %d\n", score, questionCount);
    freeQuestions();
}

void dsQuiz()
{
    initializeDS();
    int score = 0;
    int answer;
    dsQn *current = dsHead;

    if (current == NULL)
    {
        printf("No questions available for the quiz.\n");
        return;
    }

    printf("\n--- Data Structures Quiz ---\n");

    int questionCount = 0;
    while (current != NULL && questionCount < 5)
    {
        printf("%s\n", current->question);
        for (int i = 0; i < 4; i++)
        {
            printf("%d. %s\n", i + 1, current->options[i]);
        }
        printf("Enter your answer (1-4): ");
        scanf("%d", &answer);

        if (answer < 1 || answer > 4)
        {
            printf("Invalid input. Please enter a number between 1 and 4.\n");
            continue;
        }

        if (answer - 1 == current->correctOption)
        {
            score++;
            printf("Correct!\n");
        }
        else
        {
            printf("Incorrect. The correct answer was %d.\n", current->correctOption + 1);
        }

        current = current->next;
        questionCount++;
    }

    printf("Your total score: %d out of %d\n", score, questionCount);
    freeDSQuestions();
}

void addQuestion(const char *questionText, const char options[4][100], int correctOption)
{
    dmQn *newQuestion = (dmQn *)malloc(sizeof(dmQn));
    strcpy(newQuestion->question, questionText);
    for (int i = 0; i < 4; i++)
    {
        strcpy(newQuestion->options[i], options[i]);
    }
    newQuestion->correctOption = correctOption;
    newQuestion->next = head;
    head = newQuestion;
}

void freeQuestions()
{
    dmQn *current = head;
    while (current != NULL)
    {
        dmQn *temp = current;
        current = current->next;
        free(temp);
    }
}

void initializeDM()
{
    char options1[4][100] = {"A set with no elements", "A set with one element", "A set with infinite elements", "A set with undefined elements"};
    addQuestion("What is an empty set?", options1, 0);

    char options2[4][100] = {"Union", "Intersection", "Difference", "Complement"};
    addQuestion("Which operation finds common elements in two sets?", options2, 1);

    char options3[4][100] = {"Subset", "Power set", "Proper subset", "Superset"};
    addQuestion("What is a set containing all subsets of a given set?", options3, 1);

    char options4[4][100] = {"P implies Q", "P and Q", "P or Q", "Not P"};
    addQuestion("In logic, what does 'P ^ Q' represent?", options4, 1);

    char options5[4][100] = {"3", "5", "7", "9"};
    addQuestion("How many edges does a complete graph with 4 vertices have?", options5, 1);
}
void addDSQuestion(const char *questionText, const char options[4][100], int correctOption)
{
    dsQn *newQuestion = (dsQn *)malloc(sizeof(dsQn));
    strcpy(newQuestion->question, questionText);
    for (int i = 0; i < 4; i++)
    {
        strcpy(newQuestion->options[i], options[i]);
    }
    newQuestion->correctOption = correctOption;
    newQuestion->next = NULL;
    newQuestion->prev = dsTail;

    if (dsTail != NULL)
    {
        dsTail->next = newQuestion;
    }
    else
    {
        dsHead = newQuestion;
    }
    dsTail = newQuestion;
}

void freeDSQuestions()
{
    dsQn *current = dsHead;
    while (current != NULL)
    {
        dsQn *temp = current;
        current = current->next;
        free(temp);
    }
    dsHead = dsTail = NULL;
}

void initializeDS()
{
    char options1[4][100] = {"Array", "Linked List", "Stack", "Queue"};
    addDSQuestion("Which data structure uses LIFO principle?", options1, 2);

    char options2[4][100] = {"O(1)", "O(log n)", "O(n)", "O(n^2)"};
    addDSQuestion("What is the time complexity of searching in a balanced BST?", options2, 1);

    char options3[4][100] = {"Breadth-first search", "Depth-first search", "Linear search", "Binary search"};
    addDSQuestion("Which algorithm is used for traversing a tree level by level?", options3, 0);

    char options4[4][100] = {"A stack", "A queue", "A linked list", "A heap"};
    addDSQuestion("Which data structure is used in recursion?", options4, 0);

    char options5[4][100] = {"Insertion sort", "Selection sort", "Merge sort", "Bubble sort"};
    addDSQuestion("Which sorting algorithm has the best worst-case time complexity?", options5, 2);
}

void tuitionFeesCalculator()
{
    printf("\n\nWelcome to Tuition Fees Calculator\n");
    const int perCreditFee = 3850;
    const int labFee = 2000;
    const int activityFee = 1500;

    int creditHours, waiverPercentage;
    printf("Total Credits: ");
    scanf("%d", &creditHours);

    char hasWaiver;
    printf("Do you have a waiver? (y/n): ");
    scanf(" %c", &hasWaiver);
    if (hasWaiver == 'y' || hasWaiver == 'Y')
    {
        printf("Enter Waiver Percentage: ");
        scanf("%d", &waiverPercentage);
    }
    else
    {
        waiverPercentage = 0;
    }
    double courseFee = perCreditFee * creditHours;
    double totalSemesterFee = courseFee + labFee + activityFee;

    double firstInstallment = totalSemesterFee * 0.4;
    double secondInstallment = totalSemesterFee * 0.3;
    double thirdInstallment = (totalSemesterFee * 0.3) - (courseFee * (waiverPercentage / 100.0));

    if (thirdInstallment < 0)
    {
        secondInstallment += thirdInstallment;
        thirdInstallment = 0;
    }
    if (secondInstallment < 0)
    {
        firstInstallment += secondInstallment;
        secondInstallment = 0;
    }

    double totalPayable = firstInstallment + secondInstallment + thirdInstallment;

    printf("\nTuition Fee Breakdown:\n");
    printf("Total Semester Fee (Before Waiver): %.2lf BDT\n", totalSemesterFee);
    printf("Total Payable After Waiver: %.2lf BDT\n", totalPayable);
    printf("1st Installment: %.2lf BDT\n", firstInstallment);
    printf("2nd Installment: %.2lf BDT\n", secondInstallment);
    printf("3rd Installment: %.2lf BDT\n", thirdInstallment);
}