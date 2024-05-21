#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

using namespace std;

const string DIVIDER =
    "------------------------------------------------------------"
    "------------------\n";
const int SPACE = 2;
const int ID_MAX_LENGTH = 10;   // INT_MAX
const int GRADE_MAX_LENGTH = 3; // e.g., 100
const int USERNAME_MAX_LENGTH = 20;
const int COURSE_CODE_MAX_LENGTH = ID_MAX_LENGTH;
const int COURSE_NAME_MAX_LENGTH = 50;
const int COURSE_CREDITS_MAX_LENGTH = 5;

const int INSTRUCTOR_MAX_COURSES = 6;
const int STUDENT_MAX_COURSES = 5;
const int COURSE_MAX_INSTRUCTORS = 3;
const int INITIAL_CAPACITY = 1;

const string ADMIN_USERNAME = "admin";

const string ADMIN_PASSWORD = "Admin123!";

const string INVALID_USERNAME =
    "Username is invalid. It must be 5-20 characters long and contain only "
    "letters and digits.\n";

const string INVALID_PASSWORD =
    "Password is invalid. It must be 8-32 characters long and contain at least "
    "one uppercase letter, one lowercase letter, one digit, and one special "
    "character.\n";

const string INVALID_ID = "Id was not found!\n";

const string INVALID_CODE =
    "The course with the specified code was not found!\n";

const string INVALID_COURSE_CODE =
    "Course code is invalid. It must be all uppercase letters with at least "
    "one number and one dash.";

const string INVALID_COURSE_NAME =
    "Course name is invalid. It must 8-50 characters.\n";

const string INVALID_COURSE_CREDITS =
    "Credits is invalid. It must be between 0 and 5.\n";

#endif