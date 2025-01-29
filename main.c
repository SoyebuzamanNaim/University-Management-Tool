#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
            printf("Library Module\n");
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 3);
}
