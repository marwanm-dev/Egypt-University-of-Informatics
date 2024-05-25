#include "../include/Student.h"
#include "../include/Administrator.h"
#include "../include/CONSTANTS.h"
#include "../include/Course.h"
#include "swapIndices.cpp"
#include <iomanip>

Student::Student()
    : numCourses(0), ADMIN(nullptr), MAX_COURSES(STUDENT_MAX_COURSES) {}

Student::Student(const string &username, const string &password,
                 const Administrator &admin)
    : User(username, password), numCourses(0), ADMIN(&admin),
      MAX_COURSES(STUDENT_MAX_COURSES) {
  courses = new Course[MAX_COURSES];
  grades = new double[MAX_COURSES];
  if (username ==
      "") // Due to the User constructor failed to set invalid credentials
    cout << "Student can not be created due to invalid credentials." << endl;
}

Student::~Student() {
  delete[] courses;
  delete[] grades;
}

void Student::registerCourse(const string &code, const double &grade = -1) {
  if (numCourses < MAX_COURSES) {
    Course *course = ADMIN->getCourse(code);
    if (course) {
      courses[numCourses] = *course;
      grades[numCourses++] = grade;
      course->addStudentId(getId(), grade);
      cout << course->getName() << " is registered successfully." << endl;
    } else
      cout << "Course with this specified code is not found in the system."
           << endl;
  } else
    cout << "Failed to register a course exceeding the maximum number of "
            "courses. "
            "Please remove a course and add later."
         << endl;
}

void Student::dropCourse(const string &code) {
  if (numCourses == 0)
    cout << "No courses to remove." << endl;

  int initialNumCourses = numCourses;
  for (int i = 0; i < numCourses; ++i) {
    if (courses[i].getCode() == code) {
      swapIndices(courses[i], courses[numCourses - 1]);
      swapIndices(grades[i], grades[numCourses - 1]);
      courses[i].removeStudentId(getId());
      numCourses--;
    }
  }

  if (initialNumCourses == numCourses)
    cout << INVALID_CODE;
}

void Student::setGrade(const string &code, const double &grade) {
  bool courseFound = false;
  for (int i = 0; i < numCourses; ++i) {
    cout << courses[i].getName() << endl;
    if (courses[i].getCode() == code) {
      courseFound = true;
      grades[i] = grade;
      courses[i].addStudentId(getId(), grade);
      Course *course = ADMIN->getCourse(code);
      course->addStudentId(getId(), grade);
    }
  }
  if (!courseFound) {
    cout << "Student is not registered in that course yet.\nRegistering.."
         << endl;
    registerCourse(code);
    setGrade(code, grade);
  }
}

double Student::getGrade(const string &code) {
  for (int i = 0; i < numCourses; ++i) {
    if (courses[i].getCode() == code) {
      int numStudents = courses[i].getNumStudents();
      for (int j = 0; j < numStudents; ++j) {
        if (courses[i].getStudentIds()[j] == getId()) {
          return courses[i].getStudentGrades()[j];
        }
      }
    }
  }
  return -1;
}
double Student::getStats(const string &type) {
  if (type == "avg") {
    double sum = 0;
    for (int i = 0; i < numCourses; ++i) {
      double grade = courses[i].getGrade(getId());
      if (grade >= 0) // Grade is -1 when when it is not set by the instructor
        sum += grade;
    }
    return sum / numCourses;
  } else if (type == "max") {
    double max = 0.0;
    for (int i = 0; i < numCourses; ++i) {
      double grade = courses[i].getGrade(getId());
      if (grade > max)
        max = grade;
    }
    return max;
  } else if (type == "min") {
    double min = MAX_GRADE;
    for (int i = 0; i < numCourses; ++i) {
      double grade = courses[i].getGrade(getId());
      if (grade < min &&
          grade != -1) // Grade is -1 when when it is not set by the instructor
        min = grade;
    }
    return min;
  } else {
    cout << "Invalid statistics' type. Please enter 'avg', 'max', or 'min'."
         << endl;
    return -1;
  }
}
void Student::display() const {
  User::display();

  // Display header for Courses and Grades
  cout << "Students' Courses/Grades" << endl;
  cout << left << setw(COURSE_CODE_MAX_LENGTH + SPACE) << "Code"
       << setw(COURSE_NAME_MAX_LENGTH + SPACE) << "Name"
       << setw(COURSE_CREDITS_MAX_LENGTH + 2 * SPACE) << "Credits"
       << setw(GRADE_MAX_LENGTH + SPACE) << "Grade" << endl;
  cout << DIVIDER;
  for (int i = 0; i < numCourses; ++i)
    cout << left << setw(COURSE_CODE_MAX_LENGTH + SPACE) << courses[i].getCode()
         << setw(COURSE_NAME_MAX_LENGTH + SPACE) << courses[i].getName()
         << setw(COURSE_CREDITS_MAX_LENGTH + 2 * SPACE)
         << courses[i].getCredits() << setw(GRADE_MAX_LENGTH + SPACE)
         << grades[i] << endl;
  cout << endl;
}
void Student::operator=(const Student &student) {
  User::operator=(student);
  numCourses = student.numCourses;
  ADMIN = student.ADMIN;
  delete[] courses;
  delete[] grades;
  courses = new Course[MAX_COURSES];
  grades = new double[MAX_COURSES];
  for (int i = 0; i < numCourses; ++i) {
    courses[i] = student.courses[i];
    grades[i] = student.grades[i];
  }
}
void Student::handleMenu() {
  int choice;
  do {
    cout << "1. Enroll in a new Course\n2. Drop a Course\n3. View Grade in a "
            "Specific Course\n4. Get statistics in all courses\n"
         << "5. Display All Information\n6. Logout\n";
    cin >> choice;

    switch (choice) {
    case 1: {
      if (ADMIN->getNumCourses() == 0) {
        cout << "No courses yet." << endl;
        break;
      }
      string *codes = ADMIN->getCourseCodes();
      string code;
      cout << "Available courses to register in:" << endl;
      for (int i = 0; i < ADMIN->getNumCourses(); ++i) {
        cout << codes[i];
        if (i != ADMIN->getNumCourses() - 1)
          cout << ", ";
        else
          cout << endl;
      }
      cout << "Type the course code: ";
      cin >> code;
      registerCourse(code);
      delete[] codes;
      break;
    }
    case 2: {
      string code;
      cout << "Enter the course code to drop: ";
      cin >> code;
      dropCourse(code);
      break;
    }
    case 3: {
      string code;
      cout << "Enter the course code to view: ";
      cin >> code;
      double grade = getGrade(code);
      if (grade == -1)
        cout << "Your grade in the course with the specified code was not "
                "found."
             << endl;
      else
        cout << "Your grade in " << code << " is: " << getGrade(code) << endl;
      break;
    }
    case 4: {
      cout << "1. Get the average grade\n2. Get the maximum grade\n3. Get the "
              "minimum grade\n";
      cin >> choice;
      if (choice == 1)
        cout << getStats("avg");
      else if (choice == 2)
        cout << getStats("max");
      else if (choice == 3)
        cout << getStats("min");
      else
        cout << "Invalid input.";
      cout << endl;
      break;
    }
    case 5:
      display();
      break;
    case 6:
      // Logout
      return;
    default:
      cout << "Invalid choice!\n";
    }
  } while (choice != 6);
}
