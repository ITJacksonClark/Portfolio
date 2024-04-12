// Implementation of the course class
// By Mary Elaine Califf
// Edited by Jackson Clark
// 3/13/19

#include "Course.h"
#include <fstream>
#include <iomanip>

// constructors
Course::Course(string courseName)
{
  name = courseName;
  numStudents = 0;
  quizzesGiven = 0;
  examsGiven = 0;
  papersGiven = 0;
  for (int i = 0; i<MAX_STUDENTS; i++)
  {
    studentList[i] = NULL;
  }
}

Course::Course(istream& infile)
{
  string junk;
  getline(infile, name);
  infile >> quizzesGiven >> examsGiven >> papersGiven;
  infile >> numStudents;
  getline(infile, junk);
  if(numStudents > MAX_STUDENTS)
  {
    numStudents = MAX_STUDENTS;
    cout<<"\nThe number of students you requested is over the specified limit. Students past the maximum number allowed have not been added in the list of students."<<endl;
  }
  for (int i = 0; i < numStudents; i++)
  {
    studentList[i] = new Student(infile);
  }
}

Course::Course(const Course& orig)
{
  this->name = orig.name;
  this->numStudents = orig.numStudents;
  this->quizzesGiven = orig.quizzesGiven;
  this->examsGiven = orig.examsGiven;
  this->papersGiven = orig.papersGiven;
  for (int i = 0; i < MAX_STUDENTS; i++)
    {
      if (orig.studentList[i])
	this->studentList[i] = new Student(*(orig.studentList[i]));
      else
	this->studentList[i] = NULL;
    }
}

// destructor
Course::~Course()
{
  for (int i = 0; i < numStudents; i++)
  {
    delete studentList[i];
  }
}

//assignment operator
Course& Course::operator=(const Course& rhs)
{
  if (this != &rhs) // assigning a different object
    {
      // clear out what is here now
      for (int i = 0; i < numStudents; i++)
	{
	  delete studentList[i];
	}
      // copy in the new
        this->name = rhs.name;
	this->numStudents = rhs.numStudents;
	this->quizzesGiven = rhs.quizzesGiven;
	this->examsGiven = rhs.examsGiven;
	this->papersGiven = rhs.papersGiven;
	for (int i = 0; i < MAX_STUDENTS; i++)
	  {
	    if (rhs.studentList[i])
	      this->studentList[i] = new Student(*(rhs.studentList[i]));
	    else
	      this->studentList[i] = NULL;
	  }

    }
  return *this;
}

void Course::addStudent(string id, string fName, string lName)
{
  if(numStudents < MAX_STUDENTS)
  {
    studentList[numStudents] = new Student(id, fName, lName);
    ++numStudents;
  }
  else
  {
    cout<<"\nYou have reached the limit for the number of students allowed."<<endl;
  }
}

void Course::recordExam(string fileName)
{
  ifstream infile;
  int score;
  infile.open(fileName);
  for (int i = 0; i < numStudents; i++)
  {
    infile >> score;
    studentList[i]->recordExam(score);
  }
  ++examsGiven;
  infile.close();
}

void Course::recordQuiz(string fileName)
{
  ifstream infile;
  int score;
  infile.open(fileName);
  for (int i = 0; i < numStudents; i++)
  {
    infile >> score;
    studentList[i]->recordQuiz(score);
  }
  ++quizzesGiven;
  infile.close();
}

void Course::recordPaper(string fileName)
{
  ifstream infile;
  int score;
  infile.open(fileName.c_str());
  for (int i = 0; i < numStudents; i++)
  {
    infile >> score;
    studentList[i]->recordPaper(score);
  }
  ++papersGiven;
  infile.close();
}

void Course::recordAbsence(string id)
{
  
  studentList[findStudent(id)]->recordAbsence();
  
}

// methods to correct scores for a particular student
void Course::correctExamScore(string id, int grade, int gradeIndex)
{
  
  studentList[findStudent(id)]->updateExamScore(grade, gradeIndex);
  
}

void Course::correctQuizScore(string id, int grade, int gradeIndex)
{
  studentList[findStudent(id)]->updateQuizScore(grade, gradeIndex);
}

void Course::correctPaperScore(string id, int grade, int gradeIndex)
{
  
  studentList[findStudent(id)]->updatePaperScore(grade, gradeIndex);
  
}

// get a particular student's current course grade
double Course::getCourseGrade(string id)
{
  
  return studentList[findStudent(id)]->calcGrade();
}

// returns a string containing a formatted reported with all
//  of the student's data
string Course::createStudentReport(string id)
{
  
  return studentList[findStudent(id)]->createReport();
}

// returns a string containing a formatted report of all
// students' ids, names, and current course grades
string Course::createCourseReport()
{
  stringstream report;
   report << name << "\n\nID\t\tName\t\tGrade\n";
  for (int i=0; i<numStudents; i++)
  {
    Student* stuPtr = studentList[i];
    report << stuPtr->getStudentID() << "\t" << stuPtr->getFirstName() << " "
        << stuPtr->getLastName() << "\t" << setprecision(3) << stuPtr->calcGrade()*100
        << "%\n\n";
  }
  return report.str();
}

void Course::writeData(ostream& outfile)
{
  outfile << name << "\n";
  outfile << quizzesGiven << "\n";
  outfile << papersGiven << "\n";
  outfile << examsGiven << "\n";
  outfile << numStudents << "\n";
  for (int i = 0; i < numStudents; i++)
  {
    studentList[i]->writeData(outfile);
  }
}

// helper method that determines index in studentList given student id
int Course::findStudent(string id)
{
  int index = 0;
  while (index < numStudents && id != studentList[index]->getStudentID())
  {
    index++;
  }
  if (index >= numStudents)
    index = -1;
  return index;
}
