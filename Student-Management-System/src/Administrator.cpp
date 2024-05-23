#include "../include/Administrator.h"
#include "../include/CONSTANTS.h"
#include "../include/Instructor.h"
#include "../include/Student.h"
#include "../include/User.h"
#include "swapIndices.cpp"
#include <iomanip>

Administrator::Administrator()
    : numInstructors(0), numStudents(0), numCourses(0),
      instructorCapacity(INITIAL_CAPACITY), studentCapacity(INITIAL_CAPACITY),
      courseCapacity(INITIAL_CAPACITY) {
  instructors = new Instructor[instructorCapacity];
  students = new Student[studentCapacity];
  courses = new Course[courseCapacity];
}

Administrator::Administrator(const string &username, const string &password)
    : User(username, password), numInstructors(0), numStudents(0),
      numCourses(0), instructorCapacity(INITIAL_CAPACITY),
      studentCapacity(INITIAL_CAPACITY), courseCapacity(INITIAL_CAPACITY) {
  instructors = new Instructor[instructorCapacity];
  students = new Student[studentCapacity];
  courses = new Course[courseCapacity];
}

Administrator::~Administrator() {
  delete[] instructors;
  delete[] students;
  delete[] courses;
}

void Administrator::addStudent(const Student &student) {
  if (student.getUsername() ==
      "") // Due to the User constructor failed to set invalid credentials
  {
    cout << "Failed to add a student with invalid credentials." << endl;
    return;
  }
  if (numStudents == studentCapacity)
    resizeStudents();
  students[numStudents++] = student;
  cout << student.getUsername() << " is added successfully." << endl;
}

void Administrator::removeStudent(const int &id) {
  if (numStudents == 0)
    cout << "No students to remove." << endl;

  int initialNumStudents = numStudents;
  for (int i = 0; i < numStudents; ++i) {
    if (students[i].getId() == id) {
      swapIndices(students[i], students[numStudents - 1]);
      numStudents--;
    }
  }

  if (initialNumStudents == numStudents)
    cout << INVALID_ID;
}

void Administrator::addInstructor(const Instructor &instructor) {
  if (instructor.getUsername() ==
      "") // Due to the User constructor failed to set invalid credentials
  {
    cout << "Failed to add an instructor with invalid credentials." << endl;
    return;
  }
  if (numInstructors == instructorCapacity)
    resizeInstructors();
  instructors[numInstructors++] = instructor;
  cout << instructor.getUsername() << " is added successfully." << endl;
}

void Administrator::removeInstructor(const int &id) {
  if (numInstructors == 0)
    cout << "No instructors to remove." << endl;

  int initialNumInstructors = numInstructors;
  for (int i = 0; i < numInstructors; i++) {
    if (instructors[i].getId() == id) {
      swapIndices(instructors[i], instructors[numInstructors - 1]);
      numInstructors--;
    }
  }

  if (initialNumInstructors == numInstructors)
    cout << INVALID_ID;
}

void Administrator::addCourse(const Course &course) {
  if (course.getName() ==
      "") // Due to the Course constructor failed to set invalid information
  {
    cout << "Failed to add a course with invalid information." << endl;
    return;
  }
  if (numCourses == courseCapacity)
    resizeCourses();
  courses[numCourses++] = course;
  cout << course.getName() << " is added successfully." << endl;
}
void Administrator::removeCourse(const string &code) {
  if (numCourses == 0)
    cout << "No courses to remove." << endl;

  int initialNumCourses = numCourses;
  for (int i = 0; i < numCourses; i++) {
    if (courses[i].getCode() == code) {
      swapIndices(courses[i], courses[numCourses - 1]);
      numCourses--;
    }
  }

  if (initialNumCourses == numCourses)
    cout << INVALID_CODE;
}

void Administrator::resizeStudents() {
  studentCapacity *= 2;
  Student *newStudents = new Student[studentCapacity];

  for (int i = 0; i < numStudents; ++i)
    newStudents[i] = students[i];

  delete[] students;
  students = newStudents;
}

void Administrator::resizeInstructors() {
  instructorCapacity *= 2;
  Instructor *newInstructors = new Instructor[instructorCapacity];

  for (int i = 0; i < numInstructors; ++i)
    newInstructors[i] = instructors[i];

  delete[] instructors;
  instructors = newInstructors;
}

void Administrator::resizeCourses() {
  courseCapacity *= 2;
  Course *newCourses = new Course[courseCapacity];

  for (int i = 0; i < numCourses; ++i)
    newCourses[i] = courses[i];

  delete[] courses;
  courses = newCourses;
}

void Administrator::display() const {
  cout << endl;
  cout << "Your Ticket:" << endl;
  User::display();

  // Display header for instructors
  cout << "Instructors:\n";
  cout << LONG_DIVIDER;
  for (int i = 0; i < numInstructors; ++i)
    instructors[i].display();
  cout << LONG_DIVIDER;

  // Display header for students
  cout << "Students:\n";
  cout << LONG_DIVIDER;
  for (int i = 0; i < numStudents; ++i)
    students[i].display();
  cout << LONG_DIVIDER;

  // Display header for courses
  cout << "Courses:" << endl;
  cout << LONG_DIVIDER;
  for (int i = 0; i < numCourses; ++i)
    courses[i].display();
  cout << LONG_DIVIDER;
  cout << endl;
}

Course *Administrator::getCourse(const string &code) const {
  for (int i = 0; i < numCourses; ++i) {
    if (courses[i].getCode() == code) {
      return &courses[i];
    }
  }
  return nullptr;
}

string *Administrator::getCourseCodes() const {
  if (numCourses == 0)
    return nullptr;
  cout << numCourses << endl;
  string *codes = new string[numCourses];
  for (int i = 0; i < numCourses; ++i)
    codes[i] = courses[i].getCode();
  return codes;
}

void Administrator::handleMenu() {
  int choice;
  do {
    cout << "1. Add Student\n"
         << "2. Remove Student\n"
         << "3. Add Instructor\n"
         << "4. Remove Instructor\n"
         << "5. Add Course\n"
         << "6. Remove Course\n"
         << "7. Display All Information\n"
         << "8. Logout\n";
    cin >> choice;

    switch (choice) {
    case 1: {
      string username, password;
      cout << "Student username: ";
      cin >> username;
      cout << "Student password: ";
      cin >> password;

      Student student(username, password, *this);
      addStudent(student);
      break;
    }
    case 2: {
      int id;
      cout << "Student Id: ";
      cin >> id;

      removeStudent(id);
      break;
    }
    case 3: {
      string username, password;
      cout << "Instructor username: ";
      cin >> username;
      cout << "Instructor password: ";
      cin >> password;

      Instructor instructor(username, password);
      addInstructor(instructor);
      break;
    }
    case 4: {
      int id;
      cout << "Instructor Id: ";
      cin >> id;

      removeInstructor(id);
      break;
    }
    case 5: {
      string name, code;
      int credits;
      cout << "Course name: ";
      cin >> name;
      cout << "Course code: ";
      cin >> code;
      cout << "Course credits: ";
      cin >> credits;

      Course course(name, code, credits);
      addCourse(course);
      break;
    }
    case 6: {
      string code;
      cout << "Course code: ";
      cin >> code;

      removeCourse(code);
      break;
    }
    case 7: {
      display();
      break;
    }
    case 8:
      cout << "Logging out...\n";
      return;
    default:
      cout << "Invalid choice! Please try again.\n";
    }
  } while (choice != 8);
}
