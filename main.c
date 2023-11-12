/*  
* Title: Assignment #1 - Student Registration System  
* Course: CST8234 C Language 
* @Author: <<< firstname lastname (studentID) >>> 
* Lab Section: 011 
* Professor: Surbhi Bahri 
* Due date: MM/DD/YY 
* Submission date: MM/DD/YY  
*
*  
*  
* Demo malloc(), memset(), calloc() and free() in C, Ansi-style*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "table.h"

int *studentIDs;
int numberOfStudents;
int numberOfCourses;
char **courseIDs;
int** registrationTable;


int isValid(const char *id){
    if (strlen(id) == 7) {
        for (int i = 0; i < 3; i++) {
            if (!isalpha(id[i]))
                return 0;
        }
        for (int i = 3; i < 7; i++) {
            if (!isdigit(id[i]))
                return 0;
        }
        return 1;
    }
    return 0;
}
void welcome(){ 
    printf("Welcome to Student Registration System.\n\n");
    printf("Enter the number of students to register: ");
    scanf("%d", &numberOfStudents);

    studentIDs = (int *)malloc(numberOfStudents * sizeof(int));

    for (int i = 0; i < numberOfStudents; i++){
        printf("Enter the student index[%d] student id [5-digits]: ", (i));
        while (scanf("%d", &studentIDs[i]) != 1 || studentIDs[i] < 10000 || studentIDs[i] >= 100000) {
            printf("Student Id must be 5 digits\n");
            printf("Enter the student index[%d] student id [5-digits]: ", (i));
            while (getchar() != '\n');
        }
        
    }
    
    printf("\nEnter the number of courses available: ");
    scanf("%d", &numberOfCourses);

    courseIDs = (char **)malloc(numberOfCourses * sizeof(char *));

    for (int i = 0; i < numberOfCourses; i++) {
        courseIDs[i] = (char *)malloc(8 * sizeof(char));
        int valid = 0;
        while (!valid) {
            printf("Enter the course index[%d] course id [3-Alphas][4-digits]: ", i);
            scanf("%s", courseIDs[i]);

            if (!isValid(courseIDs[i])) {
                if (strlen(courseIDs[i]) != 7) {
                    printf("Incorrect Course ID length [7-character Id]\n");
                } else {
                    printf("Incorrect Course ID input [3-Alphas][4-digits]\n");
                }
            } else {
                valid = 1;
            }
        }
    }

}


void addInTable(int numStd, int numCou) {
    registrationTable = (int**)malloc(numStd * sizeof(char*));
    for (int i = 0; i < numStd; ++i) {
        registrationTable[i] = (int*)calloc(numCou, sizeof(char));
    }
}


void registerStudent() {
    int studentToRegister;
    char courseToRegister[8];

    // List of Student Ids
    printf("List of Student Ids\n");
    for (int i = 0; i < numberOfStudents; i++) {
        printf("Index %d \t\t %d\n", i, studentIDs[i]);
    }

    printf("Enter the Student's Id to register a course: ");
    scanf("%d", &studentToRegister);

    // Find the student index based on the provided ID
    int studentIndex = -1;
    for (int i = 0; i < numberOfStudents; i++) {
        if (studentIDs[i] == studentToRegister) {
            studentIndex = i;
            break;
        }
    }

    if (studentIndex == -1) {
        printf("Student Id must be 5 digits\n");
        return;
    }

    // List of Available Course Id
    printf("List of Available Course Id\n");
    for (int i = 0; i < numberOfCourses; i++) {
        printf("Index %d \t\t %s\n", i, courseIDs[i]);
    }

    printf("Enter the course id [3-Alphas][4-digits]: ");
    scanf("%s", courseToRegister);

    // Find the course index based on the provided ID
    int courseIndex = -1;
    for (int i = 0; i < numberOfCourses; i++) {
        if (strcmp(courseIDs[i], courseToRegister) == 0) {
            courseIndex = i;
            break;
        }
    }

    if (courseIndex == -1) {
        printf("Course with ID %s not found.\n", courseToRegister);
        return;
    }

    // Register the student into the course
    registrationTable[studentIndex][courseIndex] = 'R';
    printf("Registration Successful\n");
}

typedef struct {
    int studentID;
    char* courseID;
} RegistrationEntry;

void displayTable() {
    int ind = 0;
    printf("\n");
    printf("\t\tRegistration Table\n");
    printf("Registration Index\tStudent ID\tCourse ID\tRegistration Status\n");

    RegistrationEntry* entries = (RegistrationEntry*)malloc(numberOfStudents * numberOfCourses * sizeof(RegistrationEntry));
    
    for (int i = 0; i < numberOfStudents; ++i) {
        for (int j = 0; j < numberOfCourses; ++j) {
            char status = registrationTable[i][j];
            if (status == 'R' || status == 'D') {
                entries[ind].studentID = studentIDs[i];
                entries[ind].courseID = courseIDs[j];
                printf("\t%d\t\t%d\t\t%s\t\t%c\n", ind++, entries[ind].studentID, entries[ind].courseID, status);
            
            }
        }
    }

    // Free the dynamically allocated array
    free(entries);
}

void dropStudent() {
    int indexToDrop;

    displayTable();
    printf("Please select Registration Index to Drop: ");
    scanf("%d", &indexToDrop);
    if (indexToDrop < 0 || indexToDrop >= numberOfStudents * numberOfCourses) {
        printf("Invalid Registration Index.\n");
        return;
    }

    if (registrationTable[indexToDrop / numberOfCourses][indexToDrop % numberOfCourses] == 'R') {
        registrationTable[indexToDrop / numberOfCourses][indexToDrop % numberOfCourses] = 'D';
        printf("Drop course successful.\n");
    } else {
        printf("The student is not registered for this course.\n");
    }

    displayTable();
}




int main(){ 
    welcome();
    addInTable(numberOfStudents,numberOfCourses);
    
    while (true){
        int choice=-1;
        menu();
        scanf("%d", &choice);
        
        switch (choice){ 
        case 0:
            return 0;
        break;

        case 1:
            registerStudent();
        break;

        case 2: 
            dropStudent();
        break;

        case 3:  
            displayTable();
        break;
        
        case 4:
            printf("Exiting...\n");
            free(studentIDs);
            for (int i = 0; i < numberOfCourses; i++) {
                free(courseIDs[i]);
                free(registrationTable[i]);
            }
            free(courseIDs);
            return 0;
        break;
        default:
            printf("Invalid Option.");
        break;
        }
    }
    
}    

    
