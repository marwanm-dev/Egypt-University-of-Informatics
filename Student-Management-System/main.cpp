#include "fstream"
#include "include/Administrator.h"
#include "include/CONSTANTS.h"
#include "include/Instructor.h"
#include "include/Student.h"
#include "include/User.h"
#include <limits.h>
using namespace std;

int main() {
  Administrator admin(ADMIN_USERNAME, ADMIN_PASSWORD);
  int choice;
  string username, password;

  Student s("mazen", "Mazen123!", admin);
  Student s2("mazen2", "Mazen123!", admin);
  Instructor i("marwan", "Marwan123!", admin);
  Course c("calculus", "C-MA112", 3);
  admin.addStudent(s);
  admin.addStudent(s2);
  admin.addInstructor(i);
  admin.addCourse(c);

  i.addCourse("C-MA112");
  i.setGrade("C-MA112", 846930887, 55);
  i.setGrade("C-MA112", 1681692778, 82);
  c.display();

  while (true) {
    cout << "1. Login\n2. Exit\n";
    cin >> choice;

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
      loggedInUser = nullptr;
    } else if (choice == 2) {
      /* cout << "do u want to save ?\n"; */
      /* cout << "1. yes\n2. no\n"; */
      /* cin >> choice; */
      /* if (choice == 1) { */
      /*   ofstream save("save.txt", ios::app); */
      /**/
      /*   save << admin.getNumInstructors() << endl; */
      /*   save << admin.getNumStudents() << endl; */
      /*   for (int i = 0; i < admin.getNumInstructors(); i++) { */
      /*     save << admin.getInstructors()[i].getUsername() << "    "; */
      /*     save << admin.getInstructors()[i].getId() << endl; */
      /*   } */
      /**/
      /*   for (int i = 0; i < admin.getNumStudents(); i++) { */
      /*     save << admin.getStudents()[i].getUsername() << "    "; */
      /*     save << admin.getStudents()[i].getId() << endl; */
      /*   } */
      /**/
      /* save << admin.getCourseCodes(); */
      /**/
      /*   save.close(); */
      /*   break; */
      /* } */
      /* break; */
      break;
    } else {
      cout << "Invalid input!" << endl;
    }
  }

  return 0;
}
