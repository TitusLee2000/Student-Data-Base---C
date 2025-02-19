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

const int NUMBER_OF_STUDENTS = 50;
const void* STUDENT_DATABASE [NUMBER_OF_STUDENTS][6];
const int ID_INDEX      = 0;
const int NAME_INDEX    = 1;
const int AGE_INDEX     = 2;
const int PROGRAM_INDEX = 3;
const int GPA_INDEX     = 4;
const int GROUP_INDEX   = 5;

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

//Allow users to enter a student's name, ID, age, program,
//GPA, and group (Group BBY or Group DTC).
void addStudent(int id, char* name, int age, char* program,
                double gpa, char group) {
    if (entries >= NUMBER_OF_STUDENTS) {
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
* -- Constraints --
* ID: unique, int
* Name: char
* Age: int
*
*/
void addStudentPrompt() {
      int id, age;
      double gpa;
      char* name[100], program[40], group;
      printf("To add a new student, please enter the following:\nStudent ID:");
      scanf("%d", &id);
      // CALL Find ID see if its in it
      if (!isdigit(id)){
          printf("That is a invalid ID");
          return;
      }

      printf("Name:");
      scanf("%s", *name);
      for (int i = 0; i < strlen(*name); i++){
        if (!isalpha(*name[i])) {
          printf("Name can only contain characters");
          return;
        }
      }

      printf("Age:");
      scanf("%d", &age);
      if (!isdigit(age)){
        printf("Age must be an integer");
        return;
      }

      printf("Program:");
      scanf("%s", program);
      if (!isalpha(*program)){
        printf("Program must only conatin characters");
        return;
      }

      printf("Gpa:");
      scanf("%lf", &gpa);
      if (!isdigit(*program)){
        printf("Gpa must be an integer");
        return;
      }

      printf("Group [D]: Downtown campus [B]: Burnaby campus");
      scanf("%c", group);
      if (tolower(group) != 'd' || tolower(group) != 'b') {
        printf("Group can only be D - downtown or B - Burnaby");
        return;
      }
      addStudent(id, *name, age, program, gpa, group);
}

//Show all stored student records, categorized by group.
void displayStudent() {}

// finds the student by ID
// personal helper funciton
// return: int the row the student is in the 2D array
int findStudent(int id) {

}

// Find a student by ID and display their group.
void searchStudent(int id) {
}

// Remove a student record by ID.
void deleteStudent(int id) {

}

//Display all students in a specified group.
void listByGroup() {}

void runCommand(const int commandNum) {
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
            runCommand(i);
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