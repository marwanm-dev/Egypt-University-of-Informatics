#include <iostream>
#include <limits.h>
#include <string>

using namespace std;

class User {
  int id;
  string username, password;

public:
  User(const string &username_, const string &password_);
  bool checkAuth(const string &username_, const string &password_);
  int getId() const { return id; }
};
