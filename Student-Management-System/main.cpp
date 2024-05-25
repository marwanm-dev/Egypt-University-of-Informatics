#include "fstream"
#include "include/Administrator.h"
#include "include/CONSTANTS.h"
#include "include/Instructor.h"
#include "include/Student.h"
#include "include/User.h"
#include "src/inputValidation.cpp"
#include <limits.h>
using namespace std;

int main() {
  srand(time(0));
  Administrator admin(ADMIN_USERNAME, ADMIN_PASSWORD);
  int choice;
  string username, password;

  while (true) {
    cout << "1. Login\n2. Exit\n";
    choice = getValidatedInteger();

    if (choice == 1) {
      cout << "Username: ";
      cin >> username;
      cout << "Password: ";
      cin >> password;

      User *loggedInUser = nullptr;

      if (admin.checkAuth(username, password))
        loggedInUser = &admin;

      for (int i = 0; !loggedInUser && i < admin.getNumInstructors(); ++i) {
        Instructor &instructor = admin.getInstructors()[i];
        if (instructor.checkAuth(username, password))
          loggedInUser = &instructor;
      }

      for (int i = 0; !loggedInUser && i < admin.getNumStudents(); ++i) {
        Student &student = admin.getStudents()[i];
        if (student.checkAuth(username, password))
          loggedInUser = &student;
      }

      if (loggedInUser)
        loggedInUser->handleMenu();
      else
        cout << "Invalid credentials!" << endl;
    } else if (choice == 2)
      break;
    else
      cout << "Invalid input!" << endl;
  }

  return 0;
}
