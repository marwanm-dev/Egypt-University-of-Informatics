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
  virtual ~User();
  User(const string &, const string &);
  bool checkAuth(const string &, const string &) const;
  int getId() const { return id; }
  string getUsername() const { return username; }
  void operator=(const User &);
  virtual void display() const;
  virtual void handleMenu();
};

#endif
