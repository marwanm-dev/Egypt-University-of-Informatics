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
  void setId(const int &id);
  void setUsername(const string &password);
  void setPassword(const string &password);
  int getId() const { return id; }
  string getUsername() const { return username; }
  string getPassword() const { return password; }
  virtual void display() const;
};

#endif
