#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

        switch (choice)
        {
        case 1:
            printf("Teacher Login\n");
            break;
        case 2:
            printf("Student Login\n");
            break;
        case 3:
            printf("Exiting system...\n");
            break;
        default:
            printf("\nInvalid choice! \nTry again.\n");
        }
    } while (choice != 3);
}
