#include "../include/User.h"
#include "../include/CONSTANTS.h"
#include "./inputValidation.cpp"
#include <iomanip>

using namespace std;

User::User() : id(0), username(""), password("") {}

User::User(const string &username, const string &password)
    : id(1 + (rand() % INT_MAX)) {
  if (isValidUsername(username) && isValidPassword(password)) {
    this->username = username;
    this->password = password;
  } else {
    this->username = "";
    if (!isValidUsername(username))
      cout << "Usernames must be 4-20 characters long and can contain letters "
              "(a-z), numbers (0-9), and periods (.). Usernames cannot contain "
              "an ampersand (&), equals sign (=), underscore (_), apostrophe "
              "('), dash (-), plus sign (+), comma (,), brackets (<,>), or "
              "more than one period (.)"
           << endl;
    else
      cout << "Password is invalid. It must be 8-32 characters long and "
              "contain at least one uppercase letter, one lowercase letter, "
              "one digit, and one special character."
           << endl;
  }
}

User::~User() {}

bool User::checkAuth(const string &username, const string &password) const {
  return this->username == username && this->password == password;
}

void User::operator=(const User &user) {
  this->id = user.id;
  this->username = user.username;
  this->password = user.password;
}

void User::display() const {
  cout << left << setw(ID_MAX_LENGTH + SPACE) << "ID"
       << setw(USERNAME_MAX_LENGTH + SPACE) << "Username" << endl;
  cout << DIVIDER;
  cout << left << setw(ID_MAX_LENGTH + SPACE) << id
       << setw(USERNAME_MAX_LENGTH + SPACE) << username << endl;

  cout << endl;
}

void User::handleMenu() { return; }