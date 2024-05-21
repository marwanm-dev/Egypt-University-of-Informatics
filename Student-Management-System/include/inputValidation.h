#ifndef INPUTVALIDATION_H
#define INPUTVALIDATION_H

#include <string>

using namespace std;

// Helper Functions
inline bool isUpperCase(const char &);

inline bool isLowerCase(const char &);

inline bool isDigit(const char &);

inline bool isSpecialChar(const char &);

inline bool isAlphanumeric(const char &);

// Input Validation

inline bool isValidUsername(const string &);

inline bool isValidPassword(const string &);

inline bool isValidCourseName(const string &);

inline bool isValidCourseCode(const string &);

inline bool isValidCourseCredits(const int &);

#endif