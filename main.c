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
#include <string.h>
#include <stdlib.h>

// The maximum number of students the database can store
#define MAX_SIZE 50

// The number of attributes associated with each student
#define NUM_ATTRIBUTES 6

// Maximum size of a string attribute for this database
#define STRING_MAX 256

// The indexes of student attributes
#define ID_INDEX 0
#define NAME_INDEX 1
#define AGE_INDEX 2
#define PROGRAM_INDEX 3
#define GPA_INDEX 4
#define GROUP_INDEX 5

// The number of commands
#define NUM_COMMANDS 6

// Command codes
#define ADD 0
#define DISPLAY 1
#define SEARCH 2
#define DELETE 3
#define LIST 4
#define EXIT 5

// Columns in the database
int IDs[MAX_SIZE];
char names[MAX_SIZE][STRING_MAX];
int ages[MAX_SIZE];
char programs[MAX_SIZE][STRING_MAX];
double GPAs[MAX_SIZE];
char groups[MAX_SIZE];

// The database
void* STUDENT_DATABASE [NUM_ATTRIBUTES] = {IDs, names, ages, programs, GPAs, groups};

// The number of students currently stored in the database
size_t entries = 0;

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
        //printf("%d",(*(int*) STUDENT_DATABASE[ID_INDEX][i] == id));
        if (((int*)STUDENT_DATABASE[ID_INDEX])[i] == id) {
            return i;
        }
    }
    return -1;
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
void addStudent(int id, char* name, int age, char* program,
                double gpa, char group) {
    if (entries >= MAX_SIZE) {
      printf("Error: Database full!\n");
    }
    size_t row = entries++;

    ((int*)STUDENT_DATABASE[ID_INDEX])[row] = id;
    ((char**) STUDENT_DATABASE[NAME_INDEX])[row] = name;
    ((int*) STUDENT_DATABASE[AGE_INDEX])[row] = age;
    ((char**) STUDENT_DATABASE[PROGRAM_INDEX])[row] = program;
    ((double*) STUDENT_DATABASE[GPA_INDEX])[row] = gpa;
    ((char*) STUDENT_DATABASE[GROUP_INDEX])[row] = group;
}

char validateID (char* id) {
    if (!isInt(id)) {
        printf("ID must be numeric!\n");
        return 0;
    }

    int idAsInt = atoi(id);
    if (findStudent(idAsInt) != -1) {
        printf("Student with ID %d already exists!\n", idAsInt);
        return 0;
    }
    return 1;
}

char validateName(char* name) {
    if (name == NULL || name[0] == '\0' ) {
        printf("Name must not be empty!\n");
        return 0;
    }
    if (!isString(name)) {
        printf("Name can only contain characters!\n");
        return 0;
    }
    return 1;
}

char validateAge(char* age) {
    if (!isInt(age)) {
        printf("Age must be numeric!\n");
        return 0;
    }

    int ageAsInt = atoi(age);
    if (ageAsInt <= 18) {
        printf("Age must be greater than 18!\n");
        return 0;
    }
    return 1;
}

char validateProgram(char* program) {
    if (program == NULL || program[0] == '\0' ) {
        printf("Program must not be empty!\n");
        return 0;
    }
    if (!isString(program)) {
        printf("Program can only contain characters!\n");
        return 0;
    }
    return 1;
}

char validateGPA(char* gpa) {
    char* endptr;
    double gpaValue = strtod(gpa, &endptr);
    if (*endptr != '\0') {
        printf("GPA must be a double\n");
        return 0;
    }
    if (gpaValue < 0 || gpaValue > 5) {
        printf("GPA must be between 0 and 5\n");
        return 0;
    }
    return 1;
}

char validateGroup (char* group)
{
    if (group == NULL || group[0] == '\0' ) {
        printf("Group must not be empty!\n");
        return 0;
    }
    if (tolower(group[0]) != 'd' && tolower(group[0]) != 'b') {
        printf("Group must be Downtown or Burnaby\n");
        return 0;
    }
    return 1;
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
    printf("---------------------------------------------------\n");
    printf("To add a new student, please enter the following...\n\n");

    char id[256] = "";
    do {
        printf("Enter a valid Student ID:");
        scanf("%s", id);
    }
    while (!validateID(id));
    int idNum = atoi(id);

    char* name = malloc(sizeof(char) * STRING_MAX);
    do {
        printf("Enter student's name:");
        scanf("%s", name);
    } while (!validateName(name));

    char age[256] = "";
    do {
        printf("Enter student's age:");
        scanf("%s", age);
    } while (!validateAge(age));
    int ageNum = atoi(age);

    char* program = malloc(sizeof(char) * STRING_MAX);
    do {
        printf("Enter student's program:");
        scanf("%s", program);
    } while (!validateProgram(program));

    char gpa[256] = "";
    do {
        printf("Enter student's GPA:");
        scanf("%s", gpa);
    } while (!validateGPA(gpa));
    double gpaValue = strtod(gpa, NULL);
    gpaValue = (double)((int) gpaValue*100)/100;

    char group[256] = "";
    do {
        printf("[D]-Downtown [B]-Burnaby\n");
        printf("Enter student's group:");
        scanf("%s", group);
    } while (!validateGroup(group));
    char groupChar = tolower(group[0]);

    addStudent(idNum, name, ageNum, program, gpaValue, groupChar);
    printf("~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~\n");
    printf("Student added with these values:\n ID:      %d\n Name:    %s\n Age:     %d\n Program: %s"
        "\n GPA:     %f\n Group:   %c\n", idNum, name, ageNum, program, gpaValue, groupChar);
    printf("~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~\n\n");

}

int validateSearch(char* id) {
    if (!isInt(id)) {
        printf("ID must be an integer!\n");
        return 0;
    }

    return 1;
}

/**
 * REQUIRED
 * Find a student by ID and display their group.
 */
void searchStudent(const int id) {
    const int row = findStudent(id);
    if (row == -1) {
        printf("No student with ID %d\n", id);
        return;
    }

    char* group = "";
    char groupChar = ((char*)STUDENT_DATABASE[GROUP_INDEX])[row];
    switch (groupChar) {
        case 'd':
            group = "Downtown";
            break;
        case 'b':
            group = "Burnaby";
            break;
    }
    printf("Student with ID %d is in group %s\n", id, group);
}

/**
 * Display the prompt and validates the input before displaying the student's group.
 */
void searchStudentPrompt() {
    if (entries < 1) {
        printf("No students to search\n");
        return;
    }
    char id[STRING_MAX];
    do {
        printf("Search by ID:");
        scanf("%s", id);
    } while (!validateSearch(id));
    int idNum = atoi(id);
    searchStudent(idNum);
}

void shiftDatabase(const size_t row) {
    // free(((char**)STUDENT_DATABASE[NAME_INDEX])[row]);
    // free(((char**)STUDENT_DATABASE[PROGRAM_INDEX])[row]);

    for (size_t i = row; i < entries-1; i++) {
        int id = ((int*)STUDENT_DATABASE[ID_INDEX])[i+1];
        char* name = ((char**) STUDENT_DATABASE[NAME_INDEX])[i+1];
        int age = ((int*) STUDENT_DATABASE[AGE_INDEX])[i+1];
        char* program = ((char**) STUDENT_DATABASE[PROGRAM_INDEX])[i+1];
        double gpa = ((double*) STUDENT_DATABASE[GPA_INDEX])[i+1];
        char group = ((char*) STUDENT_DATABASE[GROUP_INDEX])[i+1];

        ((int*)STUDENT_DATABASE[ID_INDEX])[i] = id;
        ((char**) STUDENT_DATABASE[NAME_INDEX])[i] = name;
        ((int*) STUDENT_DATABASE[AGE_INDEX])[i] = age;
        ((char**) STUDENT_DATABASE[PROGRAM_INDEX])[i] = program;
        ((double*) STUDENT_DATABASE[GPA_INDEX])[i] = gpa;
        ((char*) STUDENT_DATABASE[GROUP_INDEX])[i] = group;
    }

    // Null out the last entry
    // ((int*)STUDENT_DATABASE[ID_INDEX])[entries] = NULL;
    // ((char**)STUDENT_DATABASE[NAME_INDEX])[entries] = NULL;
    // ((int*)STUDENT_DATABASE[AGE_INDEX])[entries] = NULL;
    // ((char**)STUDENT_DATABASE[PROGRAM_INDEX])[entries] = NULL;
    // ((double**)STUDENT_DATABASE[GPA_INDEX])[entries]  = NULL;
    // ((char**)STUDENT_DATABASE[GROUP_INDEX])[entries]  = NULL;

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
void listByGroup(char group) {
    printf("GROUP %c TABLE\n",toupper(group));
    printf("_________________________________________\n");
    printf("ID  - Name - Age - Program - GPA - Group\n");
    char foundAny = 0;
    for (size_t i = 0; i < entries; i++) {
        if (((char*)STUDENT_DATABASE[GROUP_INDEX])[i] == group) {
            foundAny = 1;
            printf("%d | ", ((int*) STUDENT_DATABASE[ID_INDEX])[i]);
            printf("%s | ", ((char**) STUDENT_DATABASE[NAME_INDEX])[i]);
            printf("%d | ", ((int*) STUDENT_DATABASE[AGE_INDEX])[i]);
            printf("%s | ", ((char**) STUDENT_DATABASE[PROGRAM_INDEX])[i]);
            printf("%f | ", ((double*) STUDENT_DATABASE[GPA_INDEX])[i]);
            printf("%c\n", ((char*) STUDENT_DATABASE[GROUP_INDEX])[i]);
        }
    }
    printf("_________________________________________\n\n");
    if (!foundAny) {
        printf("(No students in group %c)\n", group);
    }
}

/**
 * Display prompt for listing groups and validates user input before calling listByGroup.
 */
void listByGroupPrompt() {
    if (entries < 1) {
        printf("No students to list\n");
        return;
    }

    char group[STRING_MAX];
    printf("Group [D]-Downtown campus [B]-Burnaby campus:");
    scanf("%s", group);
    if (tolower(group[0]) != 'd' && tolower(group[0]) != 'b') {
        printf("ERROR: Group can only be [D]-Downtown or [B]-Burnaby\n");
    } else {
        listByGroup(group[0]);
    }
}

/**
 * REQUIRED
 * Show all stored student records, categorized by group.
 */
void displayStudent() {
    if (entries < 1) {
        printf("No students to display\n");
        return;
    }

    listByGroup('d');
    listByGroup('b');
}

void runCommand(const int commandNum) {
    switch (commandNum) {
        case ADD:
            addStudentPrompt();
            break;
        case DISPLAY:
            displayStudent();
            break;
        case SEARCH:
            searchStudentPrompt();
            break;
        case DELETE:
            deleteStudentPrompt();
            break;
        case LIST:
            listByGroupPrompt();
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
          printf("========================================\n");
          printf(" Add | Display | Search | Delete | List\n");
          printf("========================================\n");

          printf("Please enter a valid command:\n");

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