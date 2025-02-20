//
// Created by titus and david on 2025-02-12.
//
/**
Project Title: Student Information Management System

Objective:
- Develop a simple C-based application to manage student information,
including adding, displaying, searching, and deleting student records for two groups of students.

Technical Requirements:
    - Implement using the C programming language.
    - Use arrays to store student information for both groups.
    - Provide a simple menu-driven interface using printf and scanf.
    - Ensure proper input validation and error handling.

Constraints:
    - The maximum number of students stored in memory should be limited (50 students per group).
    - The program should handle invalid inputs gracefully.
    - No struct nor union is used.
    - No file storage is used.
    - No late submission will be accepted.

Expected Outcome:
    - A console-based application that allows users to manage student records
    efficiently while categorizing them into two groups.
*/
#include <ctype.h>
#include <stdio.h>
#include <string.h>ad
#include <stdlib.h>

// The maximum number of students the database can store
#define MAX_SIZE 50

// The indexes of student attributes
#define ID_INDEX 0
#define NAME_INDEX 1
#define AGE_INDEX 2
#define PROGRAM_INDEX 3
#define GPA_INDEX 4
#define GROUP_INDEX 5

// Command codes
#define ADD 0
#define DISPLAY 1
#define SEARCH 2
#define DELETE 3
#define LIST 4
#define EXIT 5

// The database
void* STUDENT_DATABASE [MAX_SIZE][6];
// The number of students currently stored in the database
size_t entries = 0;

// Number of commands
const static unsigned short NUM_COMMANDS = 6;
// An array containing all valid commands
const static char* COMMANDS[6] = {"add", "display", "search", "delete", "list", "exit"};


// Takes a null-terminated string and replaces all uppercase letters with lowercase
void lowerString(char* string) {
    for (int i = 0; string[i] != '\0'; i++) {
        if ('A' <= string[i] && string[i] <= 'Z') { string[i] = string[i] + 32;}
    }
}

/**
* Finds the student by ID
*
* @param: id an int
* @return: int the row the student is in the 2D array, or -1 if the student was not found
*/
int findStudent(const int id) {
    for (int i = 0; i < entries; i++) {
        printf("%d",(*(int*) STUDENT_DATABASE[i][ID_INDEX] == id));
        if (*(int*) STUDENT_DATABASE[i][ID_INDEX] == id) {
            return i;
        }
    }
    return 0;
}

/**
* see if it only contains numbers
*
* @param: string a string
* @return: 1 true if it's an integer else 0 false
*/
int isInt(const char* string) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (!isdigit(string[i])){
            return 0;
        }
    }
    return 1;
}

/**
* see if it only contains characters
*
* @param: string a string
* @return: 1 true if it's a string else 0 false
*/
int isString(const char* string) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (!isalpha(string[i])) {
            return 0;
        }
    }
    return 1;
}

/**
 * REQUIRED
 * Allow users to enter a student's name, ID, age, program, GPA, and group
 */
void addStudent(int id, char name, int age, char program,
                double gpa, char group) {
    if (entries >= MAX_SIZE) {
      printf("Error: Database full!\n");
    }
    size_t row = entries++;

    STUDENT_DATABASE[row][ID_INDEX] = &id;
    STUDENT_DATABASE[row][NAME_INDEX] = &name;
    STUDENT_DATABASE[row][AGE_INDEX] = &age;
    STUDENT_DATABASE[row][PROGRAM_INDEX] = &program;
    STUDENT_DATABASE[row][GPA_INDEX] = &gpa;
    STUDENT_DATABASE[row][GROUP_INDEX] = &group;
}

/**
* Display the request and validates the user input before calling addStudent.
*
* -- Constraints --
* ID: unique, int
* Name: char
* Age: int
* Program: char array
* GPA: float (0.00 - 5.00 only take in 2 decimal place)
* Group: char array
*/
void addStudentPrompt() {
    char id[100], name[100], age[10], program[40], gpa[10], group;
    printf("To add a new student, please enter the following:\n");

    printf("Student ID: ");
    scanf("%s", id);
    if (!isInt(id)) {
        printf("ERROR: That is a invalid ID\n");
        return;
    }
    int idNum = atoi(id);
    if (findStudent(idNum)) {
        printf("ERROR: Student ID already exist\n");
        return;
    }

    printf("Name: ");
    scanf("%s", name);
    if (!isString(name)) {
      printf("ERROR: Name can only contain characters\n");
      return;
    }

    printf("Age: ");
    scanf("%s", age);
    if (!isInt(age)){
        printf("ERROR: Age must be an integer\n");
        return;
    }
    int ageNum = atoi(age);

    printf("Program:");
    scanf("%s", program);
    if (!isString(program)) {
        printf("ERROR: Program must only contain characters \n");
        return;
    }

    printf("GPA:");
    scanf("%s", gpa);
    char* endptr;
    double gpaValue = strtod(gpa, &endptr);
    if (*endptr != '\0') {
        printf("ERROR: GPA must be a double \n");
        return;
    }
    if (gpaValue < 0 || gpaValue > 5) {
        printf("ERROR: GPA must be between 0 and 5 \n");
        return;
    }
    gpaValue = (double)((int) gpaValue*100)/100;

    printf("Group [D]-Downtown campus [B]-Burnaby campus:");
    scanf(" %c", &group);
    if (tolower(group) != 'd' && tolower(group) != 'b') {
        printf("ERROR: Group can only be [D]-Downtown or [B]-Burnaby\n");
        return;
    }
    addStudent(idNum, name, ageNum, program, gpaValue, group);
    printf("Student added with these values:\n ID: %d,\n Name: %s,\n Age: %d,\n Program: %s,\n GPA: %f,\n Group: %c\n\n", idNum, name, ageNum, program, gpaValue, group);
}

/**
 * REQUIRED
 * Show all stored student records, categorized by group.
 */
void displayStudent() {
    printf("  ID  | Name | Age | Program | GPA | Group\n");
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%p", &STUDENT_DATABASE[i][ID_INDEX]);
        printf("%p", &STUDENT_DATABASE[i][NAME_INDEX]);
        printf("%p", &STUDENT_DATABASE[i][AGE_INDEX]);
        printf("%p", &STUDENT_DATABASE[i][GPA_INDEX]);
        printf("%p", &STUDENT_DATABASE[i][PROGRAM_INDEX]);
        printf("%p", &STUDENT_DATABASE[i][GROUP_INDEX]);
    }
}

/**
 * REQUIRED
 * Find a student by ID and display their group.
 */
void searchStudent(const int id) {
    for (int i = 0; i < MAX_SIZE; i++) {
        if (*(int*)STUDENT_DATABASE[i][ID_INDEX] == id) {
            printf("The student with id %d is at group: %s", id, (char*)STUDENT_DATABASE[i][GROUP_INDEX]);
        }
    }
}

/**
 * Display the prompt and validates the input before displaying the student's group.
 */
void searchStudentPrompt() {
    char id[100];
    printf("To find a student's group please enter their ID");
    scanf("%s", id);
    if (!isInt(id)) {
        printf("ERROR: That is a invalid ID\n");
    } else {
        int idNum = atoi(id);
        searchStudent(idNum);
    }
}

void shiftDatabase(const size_t row) {
    for (int i = row + 1; i < entries; i++) {
        for (int j = 0; j < 6; j++) {
            STUDENT_DATABASE[i-1][j] = STUDENT_DATABASE[i][j];
        }
    }

    // Null out the last entry
    for (int i = 0; i < 6; i++) {
        STUDENT_DATABASE[entries][i] = NULL;
    }
    entries--;
}

/**
 * REQUIRED
 * Removes a student record by ID
 */
void deleteStudent(const int id) {
    size_t row = findStudent(id);
    if (row == -1) {
        printf("Student with id %d not found\n", id);
        return;
    }
    shiftDatabase(row);
}

/**
 * Display the prompt for deleting and validates input before calling the delete function.
 */
void deleteStudentPrompt() {
    char id[100];
    printf("To delete a student, please enter their student ID:");
    scanf("%s", id);
    if (!isInt(id)) {
        printf("That is a invalid ID");
    }
    const int idNum = atoi(id);
    deleteStudent(idNum);
}

/**
 * REQUIRED
 * Display all students in a specified group
 */
void listByGroup(char group) {}

/**
 * Display prompt for listing groups and validates user input before calling listByGroup.
 */
void listByGroupPrompt() {
    char group[100];
    printf("Group [D]-Downtown campus [B]-Burnaby campus:");
    scanf(" %c", &group);
    if (tolower(group) != 'd' && tolower(group) != 'b') {
        printf("ERROR: Group can only be [D]-Downtown or [B]-Burnaby\n");
    } else {
        listByGroup(group);
    }
}

void runCommand(const int commandNum) {
    switch (commandNum) {
        case ADD:
            addStudentPrompt();
            break;
        case DISPLAY:
            printf("Display not yet implemented\n");
            break;
        case SEARCH:
            printf("Search not yet implemented\n");
            break;
        case DELETE:
            deleteStudentPrompt();
            break;
        case LIST:
            printf("List not yet implemented\n");
            break;
        default:
            break;
    }
}

void parseCommand(const char* command) {
    for (int i = 0; i < NUM_COMMANDS; i++) {
        if (strcmp(command, COMMANDS[i]) == 0) {
            runCommand(i);
            return;
        }
    }
}

char isValid(const char* command) {
    for (int i = 0; i < NUM_COMMANDS; i++) {
        if (strcmp(command, COMMANDS[i]) == 0) {
            return 1;
        }
    }
    printf("Invalid command \"%s\" \n", command);
    return 0;
}

void promptCommand(char* shouldExit) {
      char command[256] = "";
      do {
          printf("Please enter a valid command: ");
          scanf("%s", command);
          lowerString(command);
      } while (!isValid(command));

      if (strcmp(command, "exit") == 0 ) *shouldExit = 1;
      else parseCommand(command);
}

int main() {

  char shouldExit = 0;
  while (!shouldExit) {
      promptCommand(&shouldExit);
  }
    printf("Exiting...");
  return 0;
}