

#include<stdio.h> 
#include <string.h>

#pragma warning(disable : 4996)
#define MAXSTUDENTS 10

struct Student {
	int id;
	char Name[50];
	int Age : 7;
	int Grade : 4;
	float GradePointAv;

};


int main()
{
	// Struct declaration
	struct Student MyStudents[MAXSTUDENTS];
	struct Student* pMyStudents = MyStudents;
	struct Student* pMyStudentsTemp = MyStudents;
	struct Student* pMyStudentsTempBase = MyStudents;

	// adding student 1
	MyStudents[0].id = 1;
	strcpy(MyStudents[0].Name, "Gaëtan Rabier");
	MyStudents[0].Age = 37;
	MyStudents[0].Grade = 1;
	MyStudents[0].GradePointAv = 1.5;

	// adding student 2
	MyStudents[1].id = 2;
	strcpy(MyStudents[1].Name, "Barack Obama");
	MyStudents[1].Age = 57;
	MyStudents[1].Grade = 4;
	MyStudents[1].GradePointAv = 3.85;

	// adding student 3
	MyStudents[2].id = 3;
	strcpy(MyStudents[2].Name, "Eminem");
	MyStudents[2].Age = 48;
	MyStudents[2].Grade = 8;
	MyStudents[2].GradePointAv = 9.65;

	// adding student 4
	MyStudents[3].id = 4;
	strcpy(MyStudents[3].Name, "Bob Marley");
	MyStudents[3].Age = 62;
	MyStudents[3].Grade = 6;
	MyStudents[3].GradePointAv = 6.38;

	int choice1;
	char tempChar[50];
	int tempInt;
	float tempFloat;
	int tempInt2;
	int exit = 0;
	printf("What do you want to do ?\n1.Show the information about the students\n2.Add a new student\n3.Search a student by entering an ID\n4.Show the average GPA of all students\n5.Find the student with the highest GPA\n");
	scanf_s("%d", &choice1);
	while (exit == 0)
	{
		switch (choice1)
		{
		case 1:
			for (int i = 0; i < MAXSTUDENTS; i++)
			{
				printf("The Student is %s, would like to see all information ? \n1 for yes, 2 for next Student, 3 to quit the program\n", pMyStudents->Name);
				scanf_s("%d", &choice1);
				switch (choice1)
				{
				case 1:
					printf("Here is the information for student %s:\nId:%d\nAge:%d\nGrade:%d\nGrade Point Average:%f\n\n", pMyStudents->Name, pMyStudents->id, pMyStudents->Age, pMyStudents->Grade, pMyStudents->GradePointAv);
					printf("Do you want to\n1.Modify those information\n2.See the next student\n3.quit the program\n");
					scanf_s("%d", &choice1);
					switch (choice1)
					{
					case 1:
						printf("Which info would you like to modify ?\n1.Name\n2.ID\n3.Age\n4.Grade\n5.Grade Point Average\n\n");
						scanf_s("%d", &choice1);
						switch (choice1)
						{
						case 1:
							printf("Please enter the new name of the student.\n");

							scanf_s("%s\0", &tempChar, 50);
							strcpy(pMyStudents->Name, tempChar);
							printf("The student name is now %s\n", pMyStudents->Name);
							break;
						case 2:
							printf("Sorry it's not possible to modify the ID of a student\n");
							break;
						case 3:
							printf("What is the new age of the student ? I guess i should say Happy Birthday ?\n");
							scanf_s("%d", &tempInt);
							pMyStudents->Age = tempInt;
							printf("The new age of %s is now %d\n", pMyStudents->Name, pMyStudents->Age);
							break;
						case 4:
							printf("What is the new grade of the student ?\n");
							scanf_s("%d", &tempInt);
							pMyStudents->Grade = tempInt;
							printf("The new grade of %s is now %d\n", pMyStudents->Name, pMyStudents->Grade);
							break;
						case 5:
							printf("What is the new Grade Point Average of the student ?\n");
							scanf_s("%f", &tempFloat);
							pMyStudents->GradePointAv = tempFloat;
							printf("The new grade of %s is now %f\n", pMyStudents->Name, pMyStudents->GradePointAv);
							break;
						}
						break;
					case 2:
						pMyStudents++;
						break;
					case 3:
						i = 10;
						break;
					}
					break;
				case 2:
					pMyStudents++;
					break;
				case 3:
					i = 10;
					break;
				}

			}
			break;
		case 2:
			for (int i = 0; i < MAXSTUDENTS; i++)
			{
				if (pMyStudents->id >= 0 & pMyStudents->id < 10)
				{
					pMyStudents++;
				}
			}
			printf("Enter the information for the new student :\nName?\n");
			scanf_s("%s", tempChar, 50);
			strcpy(pMyStudents->Name, tempChar);
			printf("Id?\n");
			scanf_s("%d", &tempInt);
			for (int i = 0; i < MAXSTUDENTS; i++)
			{
				if (pMyStudentsTemp->id == tempInt)
				{
					printf("You have chosen an Id already used. Please choose another one.\n");
					tempInt2 = 0;
					pMyStudentsTemp = pMyStudentsTempBase;
					i = 0;
					scanf_s("%d", &tempInt);
				}
				else
				{
					pMyStudentsTemp++;
				}
			}
			pMyStudents->id = tempInt;
			printf("Age?");
			scanf_s("%d", &tempInt);
			while (!(tempInt > 18 & tempInt < 99))
			{
				printf("This person cannot be a student. The age is should be between 18 and 99.\nPlease reenter the age.\n");
				scanf_s("%d", &tempInt);
			}
			pMyStudents->Age = tempInt;
			printf("Grade?\nIt should be between 1 and 12\n");
			scanf_s("%d", &tempInt);
			while (!(tempInt >= 1 & tempInt <= 12))
			{
				printf("This grade is not correct.\nIt should be between 1 and 12.\nPlease reenter the grade.\n");
				scanf_s("%d", &tempInt);
			}
			pMyStudents->Grade = tempInt;
			printf("Grade Point Average?\n");
			scanf_s("%f", &tempFloat);
			while (!(tempInt >= 1 & tempInt <= 12))
				pMyStudents->GradePointAv = tempFloat;
			printf("Thank you.\n\n");
			printf("Here is the information for student %s:\nId:%d\nAge:%d\nGrade:%d\nGrade Point Average:%f\n\n", pMyStudents->Name, pMyStudents->id, pMyStudents->Age, pMyStudents->Grade, pMyStudents->GradePointAv);

			break;

		case 3:
			printf("Enter the ID of the student you are looking for\n");
			scanf_s("%d", &tempInt);
			pMyStudents = pMyStudentsTempBase;
			for (int i = 0; i < MAXSTUDENTS; i++)
			{
				if (pMyStudents->id == tempInt)
				{
					printf("Here is the information for student %s:\nId:%d\nAge:%d\nGrade:%d\nGrade Point Average:%f\n\n", pMyStudents->Name, pMyStudents->id, pMyStudents->Age, pMyStudents->Grade, pMyStudents->GradePointAv);
					break;
				}
				else
				{
					pMyStudents++;
				}
			}
			break;
		case 4:
			tempInt = 0;
			tempFloat = 0;
			pMyStudents = pMyStudentsTempBase;
			for (int i = 0; i < MAXSTUDENTS; i++)
			{
				if (pMyStudents->id >= 0 & pMyStudents->id < 10)
				{
					tempInt++;
					tempFloat = tempFloat + pMyStudents->GradePointAv;
					pMyStudents++;
				}
			}
			tempFloat = tempFloat / tempInt;
			printf("The average GPA of all students is %f.\n", tempFloat);

			break;
		case 5:
			tempFloat = 0;
			pMyStudents = pMyStudentsTempBase;
			for (int i = 0; i < MAXSTUDENTS; i++)
			{
				if (pMyStudents->id >= 0 & pMyStudents->id < 10)
				{
					if (tempFloat < pMyStudents->GradePointAv)
					{
						pMyStudentsTemp = pMyStudents;
						tempFloat = pMyStudents->GradePointAv;
					}
					pMyStudents++;
				}
			}
			printf("The student with the highest GPA is %s with %f.\n", pMyStudentsTemp->Name, pMyStudentsTemp->GradePointAv);
			break;
		}
	}
}

/*
struct myStructTypeName {
	dataType member1;
	dataType member2;
	dataType member3;
	.
		.
		dataType memberN;
};

Age:%d\nGrade:%d\nGrade Point Average:%f\n

*/

