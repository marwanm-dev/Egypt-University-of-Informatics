#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

using namespace std;

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "Admin123!";

// Array sizes
const int STUDENT_MAX_COURSES = 5;
const int INSTRUCTOR_MAX_COURSES = 6;
const int COURSE_MAX_INSTRUCTORS = 3;
const int INITIAL_CAPACITY = 1;

// Input Validation and Display
const string DIVIDER =
    "------------------------------------------------------------"
    "------------------\n";
const string LONG_DIVIDER =
    "------------------------------------------------------------"
    "------------------------------------------------------------\n";
const int SPACE = 2;
const int ID_MAX_LENGTH = 10;   // INT_MAX
const int GRADE_MAX_LENGTH = 3; // e.g., 100
const int USERNAME_MAX_LENGTH = 20;
const int PASSWORD_MAX_LENGTH = 32;
const int COURSE_CODE_MAX_LENGTH = ID_MAX_LENGTH;
const int COURSE_NAME_MAX_LENGTH = 50;
const int COURSE_CREDITS_MAX_LENGTH = 6;
const int COURSE_NAME_MIN_LENGTH = 8;
const int USERNAME_MIN_LENGTH = 4;
const int PASSWORD_MIN_LENGTH = 8;

#endif