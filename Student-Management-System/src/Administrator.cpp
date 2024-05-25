#include "../include/Administrator.h"
#include "../include/CONSTANTS.h"
#include "../include/Instructor.h"
#include "../include/Student.h"
#include "../include/User.h"
#include "fstream"
#include "inputValidation.cpp"
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
  if (student.getUsername() == "")
  // A flag indicating that the User constructor failed to set invalid
  // credentials
  {
    cout << "Failed to add a student with invalid credentials." << endl;
    return;
  }
  bool studentFound = false;
  for (int i = 0; i < numStudents; ++i) {
    if (students[i].getUsername() == student.getUsername())
      studentFound = true;
  }
  if (!studentFound) {

    if (numStudents == studentCapacity)
      resizeStudents();
    students[numStudents++] = student;
    cout << student.getUsername() << " is added successfully." << endl;
  } else
    cout << "A student with the same username is found. Try again with "
            "different username."
         << endl;
}

void Administrator::removeStudent(const int &id) {
  if (numStudents == 0)
    cout << "No students to remove." << endl;

  int initialNumStudents = numStudents;
  for (int i = 0; i < numStudents; ++i) {
    if (students[i].getId() == id) {
      for (int i = 0; i < numCourses; ++i)
        courses[i].removeStudent(id);
      swapIndices(students[i], students[numStudents - 1]);
      numStudents--;
    }
  }

  if (initialNumStudents == numStudents) // Did not find the student
    cout << "A student with that id was not found" << endl;
  else
    cout << "Student removed successfully." << endl;
}

void Administrator::addInstructor(const Instructor &instructor) {
  if (instructor.getUsername() ==
      "") // A flag indicating that the User constructor failed to set invalid
          // credentials
  {
    cout << "Failed to add an instructor with invalid credentials." << endl;
    return;
  }
  bool instructorFound = false;
  for (int i = 0; i < numInstructors; ++i) {
    if (instructors[i].getUsername() == instructor.getUsername())
      instructorFound = true;
  }
  if (!instructorFound) {
    if (numInstructors == instructorCapacity)
      resizeInstructors();
    instructors[numInstructors++] = instructor;
    cout << instructor.getUsername() << " is added successfully." << endl;
  } else
    cout << "An instructor with the same username is found. Try again with "
            "different username."
         << endl;
}

void Administrator::removeInstructor(const int &id) {
  if (numInstructors == 0)
    cout << "No instructors to remove." << endl;

  int initialNumInstructors = numInstructors;
  for (int i = 0; i < numInstructors; i++) {
    if (instructors[i].getId() == id) {
      for (int i = 0; i < numCourses; ++i)
        courses[i].removeInstructorId(id);
      swapIndices(instructors[i], instructors[numInstructors - 1]);
      numInstructors--;
    }
  }

  if (initialNumInstructors == numInstructors) // Did not find the instructor
    cout << "An instructor with that id was not found" << endl;
  else
    cout << "Instructor removed successfully." << endl;
}

void Administrator::addCourse(const Course &course) {
  if (course.getName() == "") // A flag indicating that the Course constructor
                              // failed to set invalid information
  {
    cout << "Failed to add a course with invalid information." << endl;
    return;
  }
  bool courseFound = false;
  for (int i = 0; i < numCourses; ++i) {
    if (courses[i].getCode() == course.getCode())
      courseFound = true;
  }
  if (!courseFound) {
    if (numCourses == courseCapacity)
      resizeCourses();
    courses[numCourses++] = course;
    cout << course.getName() << " is added successfully." << endl;
  } else
    cout << "A course with the same code is found. Try again with "
            "different code."
         << endl;
}

void Administrator::removeCourse(const string &code) {
  if (numCourses == 0)
    cout << "No courses to remove." << endl;

  int initialNumCourses = numCourses;
  for (int i = 0; i < numCourses; i++) {
    if (courses[i].getCode() == code) {
      for (int i = 0; i < numStudents; ++i)
        students[i].dropCourse(code);
      for (int i = 0; i < numInstructors; ++i)
        instructors[i].removeCourse(code);

      swapIndices(courses[i], courses[numCourses - 1]);
      numCourses--;
    }
  }

  if (initialNumCourses == numCourses) // Did not find the course
    cout << "The course with the specified code was not found!" << endl;
  else
    cout << "Course removed successfully." << endl;
}

// Resizes dynamic arrays based on their current capacity
void Administrator::resizeStudents() {
  studentCapacity *= 2;
  Student *newStudents = new Student[studentCapacity];

  for (int i = 0; i < numStudents; ++i)
    newStudents[i] = students[i];

  delete[] students;
  students = newStudents;
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
    choice = getValidatedInteger();

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
      if (numStudents == 0) {
        cout << "No students you added yet." << endl;
        break;
      }

      cout << "Available students to remove:" << endl;
      for (int i = 0; i < numStudents; ++i) {
        cout << students[i].getUsername() << '(' << students[i].getId() << ')';
        if (i != numStudents - 1)
          cout << ", ";
        else
          cout << endl;
      }
      cout << "Student id: ";
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

      Instructor instructor(username, password, *this);
      addInstructor(instructor);
      break;
    }
    case 4: {
      int id;
      if (numInstructors == 0) {
        cout << "No instructors you hired yet." << endl;
        break;
      }
      cout << "Available instructors to remove:" << endl;
      for (int i = 0; i < numInstructors; ++i) {
        cout << instructors[i].getUsername() << '(' << instructors[i].getId()
             << ')';
        if (i != numInstructors - 1)
          cout << ", ";
        else
          cout << endl;
      }
      cout << "Instructor id: ";
      cin >> id;

      removeInstructor(id);
      break;
    }
    case 5: {
      string name, code;
      int credits;
      cout << "Course name: ";
      getline(cin, name);
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
      if (numCourses == 0) {
        cout << "No courses in the system yet." << endl;
        break;
      }

      cout << "Available courses to remove:" << endl;
      for (int i = 0; i < numCourses; ++i) {
        cout << courses[i].getName() << '(' << courses[i].getCode() << ')';
        if (i != numCourses - 1)
          cout << ", ";
        else
          cout << endl;
      }
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
      cout << "Logging out..\n";
      return;
    default:
      cout << "Invalid choice! Please try again.\n";
    }
  } while (choice != 8);
}
