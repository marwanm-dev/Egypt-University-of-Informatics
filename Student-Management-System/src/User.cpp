#include "../include/User.h"
#include "../include/CONSTANTS.h"
#include "./inputValidation.cpp"
#include <iomanip>

using namespace std;

User::User() : id(0), username(""), password("") {}

User::~User() {}

User::User(const string &username, const string &password)
    : id(1 + (rand() % INT_MAX)) {
  if (isValidUsername(username) && isValidPassword(password)) {
    this->username = username;
    this->password = password;
  } else {
    this->username = "";
    if (!isValidUsername(username))
      cout << INVALID_USERNAME;
    else
      cout << INVALID_PASSWORD;
  }
}

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
