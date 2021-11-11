#include <stdio.h>
#include <stdlib.h>
#include "stud.h"


student **create_class_list(char *filename, int *sizePtr){

	FILE *students = fopen(filename, "r");//opens and reads text file
	fscanf(students, "%d", sizePtr);//goes through the file and grabs the number of students in class

	student **class_list = (student**)calloc(*sizePtr, sizeof(student*));//memory allocation to store student list


	for(int i=0; i <*sizePtr; i++){// for loop that goes through all students
				class_list[i] =  (student*) calloc(1, sizeof(student));//allocated memory for each students first/last name and student #
				fscanf(students, "%d", &(class_list[i]-> student_id)); //store student's student # in the structure student under Studentid
				fscanf(students, "%s", &(class_list[i] -> first_name)); //store student's first name in the structure student under Firstname
				fscanf(students, "%s", &(class_list[i] -> last_name)); //store student's last name in the structure student under Lastname
			}



	fclose(students);//close file

	return class_list; //return class list
}

int find(int idNo, student **list, int size){

	for(int i =0; i<size;i++){//for loop going through entire array of class list
			if(idNo == list[i]-> student_id){//if statement that returns array elements if student number is equal to it
				return i;
			}
		}

	return -1;// return -1 

}

void input_grades(char *filename, student **list, int size)
{
	int idNumber, index; //initialize

		FILE *grades = fopen(filename, "r");//open and read grades file
		for(int i=0; i<size; i++){
			fscanf(grades, "%d", &idNumber);//store student's student # in the variable idNumber
			index = find(idNumber, list, size );//call find function
			if(index!= -1){
				fscanf(grades, "%d", &(list[index] -> project1_grade)); //stores project 1 grades into index
				fscanf(grades, "%d", &(list[index] -> project2_grade));//stores project 2 grades into index

			}
		}
	fclose(grades); //close file

}

void compute_final_course_grades(student **list, int size)
{
	double avg;   //initialize variable

		for(int i=0; i<size;i++){// goes through all students in the list
			//calculates avg of projects of each student
			avg = (((list[i]-> project1_grade) + (list[i]->project2_grade))/2.0);
			list[i] ->final_grade = avg; //places avg back into structure member final grade

		}
}

void output_final_course_grades(char *filename, student **list, int size)

	FILE *finalGrade = fopen(filename, "w");//opens a new file in writing mode

	fprintf(finalGrade, "%d \n", size); //prints size of class into the file
	for(int i =0; i<size; i++){// iterates through all students in array
		//adds student number and final grade to the opened file on separate lines and properly spaced out
		fprintf(finalGrade, "%d %f \n", list[i]-> student_id, list[i] ->final_grade);

	}

	fclose(finalGrade); //close file
}


void withdraw(int idNo, student **list, int* sizePtr)


	int index;
	
    index = find(idNo, list, *sizePtr);//use find function to find student with idNumber value
	free(list[index]); //deletes student with idNumber value

	for(int i= index; i<*sizePtr-1; i++){//loop through list and ensure we are pointing only at existing students
		list[i] = list[i+1];//Changing address of each student by one to ensure no memory is being wasted
	} //deletes any extra memory that's not in use anymore and updates its size
	list = (student**)	realloc(list, --(*sizePtr));

}


void destroy_list(student **list, int *sizePtr){

	for(int i=0; i<*sizePtr; i++){// iterates through all students
		free(list[i]);//deletes all students from file
	}

	free(list);//deallocates memory
	*sizePtr = 0;//update size of class

}