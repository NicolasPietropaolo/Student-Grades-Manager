#include <stdio.h>
#include <stdlib.h>
#include "stud.h"


//definitions and prototypes
student **create_class_list(char *filename, int *sizePtr);
int find(int idNo, student **list, int size);
void input_grades(char *filename, student **list, int size);
void compute_final_course_grades(student **list, int size);
void output_final_course_grades(char *filename, student **list, int size);

void withdraw(int idNo, student **list, int *sizePtr);
void destroy_list(student **list, int *sizePtr);


