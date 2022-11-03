# University Management System

Design and implement a program to manage university courses, teachers, and students.

All the classes must belong to the package university. 


## R1. University

The user interface (not part of this assignment) interacts through the class University, whose constructor accepts as argument the name of the university. 

The name of the university can be retrieved through method getName().

It is possible to assign the name of the Rector by means of the method setRector() that accepts as arguments the first and last name of the Rector. 

The method getRector() returns the first and last name of the Rector concatenated and separated by a blank space (" "). 

## R2. Students

It is possible to enter information concerning a new student thought the method enroll() of class University, that accepts as arguments first and last name of the student; the method returns the ID number that has been assigned to the student. ID numbers are are assigned progressively in each university starting from number 10000. 

To retrieve the information about a student we can use the method student() that accepts as an argument the ID number and returns a string made up of ID, first, and last name separated by blank spaces, e.g. "10000 Donald Duck". 

💡We can assume that each university has at most 1000 enrolled students. 

## R3. Courses

To define a new course we can use the method activate() that accepts as arguments the title of the course and the name of the responsible teacher. The method returns an integer that corresponds to the course code. Course codes are assigned progressively starting from 10. 

To retrieve the information about a course we can use the method course() that accepts the course's code and returns a string containing code, title, and teacher separated by commas, e.g., "10,Object Oriented Programming,James Gosling". 

💡We can safely assume that any university offers no more than 50 courses. 

## R4. Course attendance

Students that wish to attend a course must be registered through the method register() that accepts as arguments the ID of the student and the course's code. 

To get the list of students attending a course we can use the method listAttendees() that accepts the code of the course and returns a string containing the list of attendees.
 The students appear one per row (rows are terminated by a new-line character '\n') and each row is formatted as describe in requirement R2. 

Given the ID of a student, it is possible to get the list of courses she is attending through the method studyPlan(). The courses are described one per row and formatted as described in requirement R3. 

💡We can safely assume that no course has more than 100 attendees and that each student can attend no more that 25 distinct courses. 
