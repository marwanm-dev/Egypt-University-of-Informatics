#include "../include/User.h"

using namespace std;

User::User(const string &username_, const string &password_)
    : username(username_), password(password_), id(1 + (rand() % INT_MAX)) {}

bool User::checkAuth(const string &username_, const string &password_) {
  return username == username_ && password == password_;
}
