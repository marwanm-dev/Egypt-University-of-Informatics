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
  User(const string &, const string &);
  virtual ~User();
  bool checkAuth(const string &, const string &) const;
  void operator=(const User &);
  void display() const;
  virtual void handleMenu();
  int getId() const { return id; }
  string getUsername() const { return username; }
};

#endif
