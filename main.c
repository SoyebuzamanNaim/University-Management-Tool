#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*This are for password verification */
#define STUDENT_USERNAME "Student"
#define STUDENT_PASSWORD "Student"

#define TEACHER_USERNAME "Teacher"
#define TEACHER_PASSWORD "Teacher"



// Naim
void flushInputBuffer();
int studentLogin();
int teacherLogin();

//Samir,Taz,Naim
void studentModule();

//Abid,Shawon,Sami
void teacherModule();


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

// Naim
void flushInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}



//Naim
int studentLogin() {
    char username[50], password[50];

    printf("Student Login\n");

    printf("Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove trailing newline

    printf("Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove trailing newline

    if (strcmp(username, STUDENT_USERNAME) == 0 && strcmp(password, STUDENT_PASSWORD) == 0) {
        printf("Welcome Student!\n");
        return 1;
    }

    printf("Invalid Password or Username!\n");
    return 0;
}

//Naim
int teacherLogin() {
    char username[50], password[50];
    printf("Teacher Login\n");
    printf("Username: ");
    fgets(username, 50, stdin);
    username[strcspn(username, "\n")] = '\0';
    
    printf("Password: ");
    fgets(password, 50, stdin);
    password[strcspn(password, "\n")] = '\0';
    
    if(strcmp(username, TEACHER_USERNAME) == 0 && 
       strcmp(password, TEACHER_PASSWORD) == 0) {
        printf("Welcome Teacher!\n");
        return 1;
    }
    printf("Invalid Password or Username!\n");
    return 0;
}

//Abid,Shawon,Sami

   void teacherModule() {
    int choice;
    do {
        printf("\nTeacher Module\n");
        printf("1. Add Student\n");
        printf("2. Find Student by Roll\n");
        printf("3. Find Student by Name\n");
        printf("4. Total Admitted Students\n");
        printf("5. Delete Student\n");
        printf("6. Update Student\n");
        printf("7. Display All Students\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        flushInputBuffer();

        switch(choice) {
            case 1: printf("Student added successfully\n"); break;
            
            default: printf("Invalid choice!\n");
        }
    } while(choice != 8);
}

//Samir,Taz,Naim
void studentModule() {
    int choice;
    do {
        printf("\nStudent Module\n");
        printf("1. Library\n");
        printf("2. Quiz\n");
        printf("3. Tuition fees calculator\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        flushInputBuffer();

        switch(choice) {
            case 1: printf("Library Module\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 3);
}
