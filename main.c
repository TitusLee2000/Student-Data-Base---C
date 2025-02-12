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

// Takes a null-terminated string and replaces all uppercase letters with lowercase
void lowerString(char* string) {
    for (int i = 0; string[i] != '\0'; i++) {
        if ('A' <= string[i] && string[i] <= 'Z') { string[i] = string[i] + 32;}
    }
}

// Number of commands
const static unsigned short NUM_COMMANDS = 6;

// An array containing all valid commands
const static char* COMMANDS[6] = {"add", "display", "search", "delete", "list", "exit"};

//Allow users to enter a student's name, ID, age, program,
//GPA, and group (Group BBY or Group DTC).
void addStudent(char* name, int id, int age, char* program,
                double gpa, char* group, int row) {}

//Show all stored student records, categorized by group.
void displayStudent() {}

// finds the student by ID
// return: int the row the student is in the 2D array
int findStudent(int id) {}

// Find a student by ID and display their group.
void searchStudent(int id) {
  //not for marks but would make life easy
}

// Remove a student record by ID.
void deleteStudent(int id) {}

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

int main(){
  void* studentDataBase [50][6];
  char shouldExit = 0;
  while (!shouldExit) {
      promptCommand(&shouldExit);
  }
    printf("Exiting...");
  return 0;
}