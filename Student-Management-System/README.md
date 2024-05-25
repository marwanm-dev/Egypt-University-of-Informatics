# Student Management System

## Team Members

- Marwan Mostafa (23-101165)
- Youssef Walid (23-101117)
- Abdelrahman Ahmed (23-101010)
- Abdelrahman Amr (23-101225)
- Saif Alaa Eldin (23-101113)

## Project Description

Student Management System is designed to streamline administrative tasks and enhance the learning experience within an educational institution. It provides a centralized platform where users, including instructors, students, and administrators, can interact with various functionalities tailored to their roles.

### Key Features

- User Authentication: Ensures secure access for all users.
  Administrative Privileges: Administrators can add/remove users and courses.
- Instructor Capabilities: Instructors can manage their courses and student grades.
- Student Functions: Students can enroll in courses, access materials, drop courses, and view their grades.

Overall, the system facilitates efficient communication, organization, and administration within an educational environment, supporting the institution's goals of delivering high-quality education.

### Implementation Guide

- User: A user has a user ID, username, and password to verify sign-ins.
- Administrator: Inherits from the User class. At the beginning of your program, there should be at least one admin with a known username and password. Can add or remove users (instructors or students) and courses from the system.
- Instructor: Inherits from the User class. Has an ID, name, and a list of up to 5 courses they teach. Can manage their courses and student grades, including adding/removing courses and updating grades.
  Can perform statistics on courses (e.g., maximum, minimum, and average grades).
- Student: Inherits from the User class. Has an ID, name, and a list of registered courses (up to 6) and their grades. Can register in new courses, drop courses, and view grades.
- Course: Stores information about the course, including its name, code, instructor IDs (up to 3), credits, and student grades.

## Instructions on Running and Using the Program

1. Compile the program using a C++ compiler: `g++ main.cpp ./src/*.cpp -o student_management_system`

2. Run the compiled program: ./student_management_system

3. On startup, log in as an administrator to add instructors or students using the appropriate credentials.

