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
int getValidatedInteger() {
  int input;
  while (true) {
    cin >> input;
    if (cin.fail()) // User entered a non-integer input
    {
      cin.clear(); // Clears the error flag
      cin.ignore(numeric_limits<streamsize>::max(),
                 '\n'); // Ignores the rest of the line, effectively discarding
                        // the invalid input.
      cout << "Invalid input. Please enter a number: ";
    } else {
      cin.ignore(numeric_limits<streamsize>::max(),
                 '\n'); // Ignores any extra input on the same line to prevent
                        // issues with subsequent input operations.eturn input;
      break;
    }
  }
  return input;
}

bool isValidUsername(const string &username) {
  if (username.length() < USERNAME_MIN_LENGTH ||
      username.length() > USERNAME_MAX_LENGTH) {
    return false;
  }

  bool lastWasPeriod = false;

  for (int i = 0; i < username.length(); ++i) {
    char c = username[i];

    if (isalnum(c)) {
      lastWasPeriod = false; // Reset period flag
      continue;              // Allow letters and numbers
    } else if (c == '.') {
      if (lastWasPeriod)
        return false;       // No consecutive periods
      lastWasPeriod = true; // Set period flag
    } else
      return false; // Disallow any other characters
  }

  return true;
}

bool isValidPassword(const string &password) {
  if (password.length() < PASSWORD_MIN_LENGTH ||
      password.length() > PASSWORD_MAX_LENGTH)
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
  return name.length() >= COURSE_NAME_MIN_LENGTH &&
         name.length() <= COURSE_NAME_MAX_LENGTH;
}

bool isValidCourseCode(const string &code) {
  if (code.length() > COURSE_CODE_MAX_LENGTH) {
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
