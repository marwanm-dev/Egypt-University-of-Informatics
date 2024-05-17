#include "../include/User.h"

using namespace std;

User::User() {}

User::User(const string &username_, const string &password_)
    : username(username_), password(password_), id(1 + (rand() % INT_MAX)) {}

bool User::checkAuth(const string &username_, const string &password_) const {
  return username == username_ && password == password_;
}

void User::setId(int id) { this->id = id; }

void User::setUsername(string username) { this->username = username; }

void User::setPassword(string password) { this->password = password; }

void User::display() const {
  cout << "Id: " << id << endl;
  cout << "Username: " << username << endl;
}
