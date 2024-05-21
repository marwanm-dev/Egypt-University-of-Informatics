#include "../include/inputValidation.h"
#include "../include/CONSTANTS.h"

// Helper Functions
bool isUpperCase(const char &c) { return c >= 'A' && c <= 'Z'; }

bool isLowerCase(const char &c) { return c >= 'a' && c <= 'z'; }

bool isDigit(const char &c) { return c >= '0' && c <= '9'; }

bool isSpecialChar(const char &c) {
  string specialChars = "!@#$%^&*_";
  for (int i = 0; i < specialChars.length(); ++i) {
    if (c == specialChars[i])
      return true;
  }
  return false;
}

bool isAlphanumeric(const char &c) {
  return isUpperCase(c) || isLowerCase(c) || isDigit(c);
}

// Input Validation
bool isValidUsername(const string &username) {
  if (username.length() < 5 || username.length() > USERNAME_MAX_LENGTH)
    return false;

  for (char c : username) {
    if (!isAlphanumeric(c))
      return false;
  }

  return true;
}

bool isValidPassword(const string &password) {
  if (password.length() < 8 || password.length() > 32)
    return false;

  bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;

  for (char c : password) {
    if (isUpperCase(c))
      hasUpper = true;
    else if (isLowerCase(c))
      hasLower = true;
    else if (isDigit(c))
      hasDigit = true;
    else if (isSpecialChar(c))
      hasSpecial = true;
  }

  return hasUpper && hasLower && hasDigit && hasSpecial;
}

bool isValidCourseName(const string &name) {
  return name.length() >= 8 && name.length() <= COURSE_NAME_MAX_LENGTH;
}

bool isValidCourseCode(const string &code) {
  if (code.length() > 10) {
    return false;
  }
  int dashCount = 0;
  bool hasDigit = false;

  // Ensure the code contains exactly one dash and is in uppercase
  for (char c : code) {
    if (c == '-') {
      dashCount++;
    } else if (isdigit(c)) {
      hasDigit = true;
    } else if (!isupper(c)) {
      return false;
    }
  }

  // Ensure there is exactly one dash and at least one number
  if (dashCount != 1 || !hasDigit) {
    return false;
  }

  return true;
}

bool isValidCourseCredits(const int &credits) {
  return credits > 0 && credits < COURSE_CREDITS_MAX_LENGTH;
}