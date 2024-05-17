#include "include/Administrator.h"
#include "include/Course.h"
#include "include/Instructor.h"
#include "include/Student.h"
#include "include/User.h"

using namespace std;
int main() {
  Student s("mama", "pass");
  Course c("Physics", "C-PH112", 3);
  s.registerCourse(c);
  s.display();
}
/* int main() { */
/*   Administrator admin("admin", "admin"); */
/*   string username, password; */
/*   cout << "Welcome User!" << endl; */
/**/
/*   bool loggedIn = false; */
/*   while (!loggedIn) { */
/*     // Add input validation */
/*     cout << "Please login to your account" << endl; */
/*     cout << "Username: "; */
/*     cin >> username; */
/*     cout << "Password: "; */
/*     cin >> password; */
/**/
/*     if (admin.checkAuth(username, password)) { */
/*       loggedIn = true; */
/*       cout << "Login successful! You are logged in as " << username << endl;
 */
/*       // list available member functions for the Administrator class and an
 */
/*       // option to log out */
/*     } */
/*     for (int i = 0; i < admin.numInstructors && !loggedIn; ++i) { */
/*       if (admin.instructors[i].checkAuth(username, password)) { */
/*         loggedIn = true; */
/*         cout << "Login successful! You are logged in as " << username <<
 * endl; */
/*         // list available member functions for the Administrator class and an
 */
/*         // option to log out */
/*       } */
/*     } */
/*     for (int i = 0; i < admin.numOfStudents && !loggedIn; ++i) { */
/*       if (admin.students[i].checkAuth(username, password)) { */
/*         loggedIn = true; */
/*         cout << "Login successful! You are logged in as " << username <<
 * endl; */
/*         // list available member functions for the Administrator class and an
 */
/*         // option to log out */
/*       } */
/*     } */
/*   } */
/**/
/*   return 0; */
/* } */
