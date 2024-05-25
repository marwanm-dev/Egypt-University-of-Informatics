#include "../include/Instructor.h"
#include "../include/Administrator.h"
#include "../include/CONSTANTS.h"
#include "../include/Course.h"
#include "./swapIndices.cpp"
#include <iomanip>
#include <string>

Instructor::Instructor()
    : numCourses(0), ADMIN(nullptr), MAX_COURSES(INSTRUCTOR_MAX_COURSES) {
  courses = new Course[MAX_COURSES];
}

Instructor::Instructor(const string &username, const string &password,
                       const Administrator &admin)
    : User(username, password), numCourses(0), ADMIN(&admin),
      MAX_COURSES(INSTRUCTOR_MAX_COURSES) {
  courses = new Course[MAX_COURSES];
  if (username == "") // invalid credentials validated by the User constructor
    cout << "Instructor can not be created due to invalid credentials." << endl;
}

Instructor::~Instructor() { delete[] courses; }

void Instructor::addCourse(const string &code) {
  if (numCourses < MAX_COURSES) {
    Course *course = ADMIN->getCourse(code);
    if (course) {
      courses[numCourses++] = *course;
      course->addInstructorId(getId());
      cout << course->getName() << " is added successfully." << endl;
    } else
      cout << "Course with this specified code is not found in the system."
           << endl;
  } else
    cout << "Failed to add a course exceeding the maximum number of courses. "
            "Please remove a course and add later."
         << endl;
}

void Instructor::removeCourse(const string &code) {
  if (numCourses == 0)
    cout << "No courses to remove." << endl;

  int initialNumCourses = numCourses;
  for (int i = 0; i < numCourses; i++) {
    if (courses[i].getCode() == code) {
      swapIndices(courses[i], courses[numCourses - 1]);
      courses[i].removeInstructorId(getId());
      numCourses--;
    }
  }

  if (initialNumCourses == numCourses)
    cout << INVALID_CODE;
}

void Instructor::setGrade(const string &code, const int &id,
                          const double &grade) {
  bool courseFound = false;
  for (int i = 0; i < numCourses; i++) {
    if (courses[i].getCode() == code) {
      courseFound = true;
      courses[i].addStudentId(id, grade);
      Student *students = ADMIN->getStudents();
      for (int j = 0; j < ADMIN->getNumStudents(); ++j) {
        if (students[j].getId() == id)
          students[j].setGrade(code, grade);
      }
    }
  }
  if (!courseFound)
    cout << "Sorry you are not teaching that course with the specified code."
         << endl;
  else
    cout << "Student id and grade are saved." << endl;
}

double Instructor::performStats(const string &code, const string &type) {
  for (int i = 0; i < numCourses; i++) {
    if (courses[i].getCode() == code) {
      if (type == "max")
        return courses[i].getMaxGrade();
      if (type == "min")
        return courses[i].getMinGrade();
      if (type == "avg")
        return courses[i].getAvgGrade();
    }
  }
};

void Instructor::operator=(const Instructor &instructor) {
  User::operator=(instructor);
  numCourses = instructor.numCourses;
  ADMIN = instructor.ADMIN;
  delete[] courses;
  courses = new Course[MAX_COURSES];
  for (int i = 0; i < numCourses; ++i)
    courses[i] = instructor.courses[i];
}

void Instructor::display() const {
  User::display();

  // Display header for Courses
  cout << "Instructor Courses:" << endl;
  cout << left << setw(COURSE_CODE_MAX_LENGTH + SPACE) << "Code"
       << setw(COURSE_NAME_MAX_LENGTH + SPACE) << "Name"
       << setw(COURSE_CREDITS_MAX_LENGTH + SPACE) << "Credits" << endl;
  cout << DIVIDER;
  for (int i = 0; i < numCourses; i++)
    cout << left << setw(COURSE_CODE_MAX_LENGTH + SPACE) << courses[i].getCode()
         << setw(COURSE_NAME_MAX_LENGTH + SPACE) << courses[i].getName()
         << setw(COURSE_CREDITS_MAX_LENGTH + SPACE) << courses[i].getCredits()
         << endl;
  cout << endl;
}

void Instructor::handleMenu() {
  int choice;
  do {
    cout << "1. Add Course\n2. Remove Course\n3. Add/Update Student Grade\n"
         << "4. Perform Course Statistics\n5. Display All Information\n6. "
            "Logout\n";
    cin >> choice;

    switch (choice) {
    case 1: {
      if (ADMIN->getNumCourses() == 0) {
        cout << "No courses in the system yet." << endl;
        break;
      }
      string *codes = ADMIN->getCourseCodes();
      string code;
      cout << "Available courses to teach:" << endl;
      for (int i = 0; i < ADMIN->getNumCourses(); ++i) {
        cout << codes[i];
        if (i != ADMIN->getNumCourses() - 1)
          cout << ", ";
        else
          cout << endl;
      }
      cout << "Type the course code: ";
      cin >> code;
      addCourse(code);
      delete[] codes;
      break;
    }
    case 2: {
      string code;
      cout << "Enter the course code to remove: ";
      cin >> code;
      removeCourse(code);
      break;
    }
    case 3: {
      string code;
      int id;
      double grade;
      if (numCourses == 0) {
        cout << "You are not teaching any courses yet." << endl;
        break;
      }
      cout << "courses you teach:" << endl;
      for (int i = 0; i < numCourses; ++i) {
        cout << courses[i].getCode();
        if (i != numCourses - 1)
          cout << ", ";
        else
          cout << endl;
      }
      cout << "Enter the course code: ";
      cin >> code;
      cout << "Available students:" << endl;
      Student *students = ADMIN->getStudents();
      for (int i = 0; i < ADMIN->getNumStudents(); ++i) {
        cout << students[i].getId() << " - " << students[i].getUsername();
        if (i != ADMIN->getNumStudents() - 1)
          cout << ", ";
        else
          cout << endl;
      }
      cout << "Enter the student id: ";
      cin >> id;
      cout << "Enter the new student grade: ";
      cin >> grade;
      setGrade(code, id, grade);
      break;
    }
    case 4: {
      string code;
      cout << "Enter the course code: ";
      cin >> code;
      cout << "1. Get the average grade\n2. Get the maximum grade\n3. Get the "
              "minimum grade\n";
      cin >> choice;
      if (choice == 1)
        cout << performStats(code, "avg");
      else if (choice == 2)
        cout << performStats(code, "max");
      else if (choice == 3)
        cout << performStats(code, "min");
      else
        cout << "Invalid input.";
      cout << endl;
      break;
    }
    case 5: {
      display();
      break;
    }
    case 6:
      // Logout
      return;
    default:
      cout << "Invalid choice!\n";
    }
  } while (choice != 6);
}
