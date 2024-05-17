#ifndef USER_H
#define USER_H

#include <iostream>
#include <limits.h>
#include <string>

using namespace std;

class User {
  int id;
  string username, password;

public:
  User();
  User(const string &username_, const string &password_);
  bool checkAuth(const string &username_, const string &password_) const;
  int getId() const { return id; }
  virtual void display() const;
};

#endif
