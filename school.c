#include"school.h"

p_class_t init_class( int *num_of_clases) {
	int* all_id = NULL;
	p_class_t all_clases = NULL;
	system("cls");
	printf("ok! so lets create your school!\nhow many clases will you have? : ");
	scanf("%d", num_of_clases);

	all_id = (int*)malloc(sizeof(int) * (*num_of_clases));
	if (all_id == 0) {
		printf("malloc fail");
		return NULL;
	}
	all_clases = (p_class_t)malloc(sizeof(class_t) * (*num_of_clases));
	if (all_clases == 0) {
		printf("malloc fail");
		free(all_id);
		return NULL;
	}
	for (int i = 0; i < *num_of_clases; i++) {
		printf("\tplease enter id of class %d: ", i + 1);
		scanf("%d", (&(all_clases + i)->class_code));
		(all_clases[i]).head_student = NULL;
		for (int j = 0; j < i; j++) {
			if ((all_clases[i]).class_code == all_id[j]){
				printf("two clases can't have the same id - try again\n");
				system("pause");
				return NULL;
			}
		}
		all_id[i] = ((all_clases[i]).class_code);
		
	}
	free(all_id);
	return all_clases;

}

void add_student(p_class_t class, int id, char name[]) {
	p_student_t new_student = NULL, * pos = (*class).head_student;

	new_student = (student_t*)malloc(sizeof(student_t));
	new_student->id = id;
	new_student->name = (char*)malloc((strlen(name)+1)*sizeof(char));
	strcpy(new_student->name,name);
	new_student->head_grades = NULL;
	new_student->next = NULL;

	if (!((*class).head_student)) {
		(*class).head_student = new_student;
	}
	else {
		if ((*class).head_student->id == id) {
			printf("\n\t******EROR*****\n\tthis id is already in use by: %s.\n\ttwo students cant have the same id...\n\tplease find a new id for: %s and try to add him again :)\n\n ", (*class).head_student->name,name);
			return;
		}
		while ((*class).head_student->next) {
			((*class).head_student) = ((*class).head_student)->next;
			if ((*class).head_student->id == id) {
				printf("\n\t******EROR*****\n\tthis id is already in use by %s.\n\ttwo students cant have the same id...\n\tplease find a new id for %s and try to add him again\n\n ", (*class).head_student->name, name);
				return;
			}
		}
		((*class).head_student)->next = new_student;
		(*class).head_student = pos;
	}


}

void add_grade(p_student_t student, int id_test, int grade) {
	p_grades_t new_grade = NULL, * pos = (*student).head_grades;

	new_grade = (grades_t*)malloc(sizeof(grades_t));
	new_grade->id_test = id_test;
	new_grade->grade = grade;
	new_grade->next = NULL;
	

	if (!((*student).head_grades)) {
		(*student).head_grades = new_grade;
	}
	else {
		if ((*student).head_grades->id_test == id_test) {
			printf("\n\t******EROR*****\n\tthis tets_id already has a grade: %d.\n\n ", (*student).head_grades->grade);
			return;
		}
		while ((*student).head_grades->next) {
			(*student).head_grades = (*student).head_grades->next;
			if ((*student).head_grades->id_test == id_test) {
				printf("\n\t******EROR*****\n\tthis tets_id already has a grade: %d.\n\n ", (*student).head_grades->grade);
				return;
			}
		}
		((*student).head_grades)->next = new_grade;
		(*student).head_grades = pos;
	}


}

int print_students(p_class_t class) {
	p_student_t temp = class->head_student;
	if (!temp) {
		printf("\n\t****ERROR****\n\tthere are no students in this class.\n\n");
		return 0;
	}
	else {
		printf("\n\tall students in class %d: \n",class->class_code);
		while (temp) {
			printf("\t* id: %d name: %s\n", temp->id, temp->name);
			temp = temp->next;
		}
	}
}

int print_students_grades(p_student_t student) {
	p_grades_t temp = student->head_grades;
	if (!temp) {
		printf("\n\t\t****ERROR****\n\t\tno grades to show for this student\n");
		return 0;
	}
	else {
		printf("\t\t\nall grades of %s \n",student->name);
		while (temp) {
			printf("\t\t\ttest id: %d grade: %d\n", temp->id_test, temp->grade);
			temp = temp->next;
		}
	}
}

void delete_student(p_class_t class, int id) {
	p_student_t temp = class->head_student,stud = NULL;
	if (class->head_student->id == id) {
		stud = class->head_student;
		class->head_student = class->head_student->next;
		delete_all_grades(stud);
		free(stud);
		return 1;
	}
	while (class->head_student->next->id != id) {
		class->head_student = class->head_student->next;
	}
	stud = class->head_student->next;
	class->head_student->next = class->head_student->next->next;
	delete_all_grades(stud);
	free(stud);
	class->head_student = temp;
	
}

void delete_grade(p_student_t student, int test_id) {
	p_grades_t temp = student->head_grades, grade = NULL;
	if (student->head_grades->id_test == test_id) {
		grade = student->head_grades;
		student->head_grades = student->head_grades->next;
		free(grade);
		return 1;
	}
	while (student->head_grades->next->id_test != test_id) {
		student->head_grades = student->head_grades->next;
	}
	grade = student->head_grades->next;
	student->head_grades->next = student->head_grades->next->next;
	free(grade);
	student->head_grades = temp;

}

void delete_all_grades(p_student_t student) {
	p_grades_t temp = student->head_grades;
	if (temp) {
		while (temp->next) {
			student->head_grades = temp;
			temp = temp->next;
			free(student->head_grades);
		}
	}

}

void delete_all_students(p_class_t class) {
	p_student_t temp = class->head_student;
	if (temp) {
		while (temp->next) {
			class->head_student = temp;
			temp = temp->next;
			delete_all_grades(class->head_student);
			free(class->head_student);
		}
	}
}

void delete_school(p_class_t all_clases,int num_of_clases) {
	
	
	for (int i = 0; i < num_of_clases - 1; i++) {
		delete_all_students(&all_clases[i]);
	}
	free(all_clases);

}

void save_data(p_class_t clases, int num_of_clases) {
	int len,student_num,grades_num;
	int temp_int = 3;

	p_class_t temp = clases;
	FILE* file = fopen("C:\\Users\\nataly\\Desktop\\h.w - spedtech\\c\\linked_list\\school.txt", "wb");

	if (file == NULL) {
		printf("eror loading file");
		return 0;
	}
	fwrite(&num_of_clases, sizeof(int), 1, file);

	for (int i = 0; i < num_of_clases; i++) {
		fwrite(&((clases)->class_code), sizeof(int), 1, file);
		student_num = student_count((*clases).head_student);
		printf("%d students saved\n", student_num);
		fwrite(&student_num, sizeof(int), 1, file);
		while ((*clases).head_student) {
			fwrite(&((*clases).head_student->id), sizeof(int), 1, file);
			len = strlen((*clases).head_student->name)+1;
			fwrite(&len, sizeof(int), 1, file);
			fwrite((*clases).head_student->name, sizeof(char), len, file);
			grades_num = grades_count((*clases).head_student->head_grades);
			printf("%d grades saved\n", grades_num);
			fwrite(&grades_num, sizeof(int), 1, file);
			while ((*clases).head_student->head_grades) {
				
				fwrite(&((*clases).head_student->head_grades->id_test), sizeof(int), 1, file);
				fwrite(&((*clases).head_student->head_grades->grade), sizeof(int), 1, file);
				(*clases).head_student->head_grades = (*clases).head_student->head_grades->next;
			}
			(clases)->head_student = (clases)->head_student->next;
		
		}

		clases++;
		
	}
	fclose(file);
}

p_class_t load_data(int *num_of_clases) {
	p_class_t all_clases = NULL;
	int len, student_num, grades_num=0;
	int id_stud, id_test, grade;
	char *name;
	p_class_t temp = all_clases;

	FILE *file= fopen("C:\\Users\\nataly\\Desktop\\h.w - spedtech\\c\\linked_list\\school.txt", "rb");
	if (file == NULL) {
		printf("eror loading file");
		return 0;
	}

	system("cls");
	printf("\t\t\******your school: *******\n\n");

	fread(num_of_clases, sizeof(int), 1, file);
	printf("%d clases loaded: \n", *num_of_clases);
	(all_clases) = (p_class_t)malloc(sizeof(class_t) * (*num_of_clases));
	for (int i = 0; i < *num_of_clases; i++) {
		fread(&((all_clases+i)->class_code), sizeof(int), 1, file);
		(all_clases + i)->head_student = NULL;
		fread(&student_num, sizeof(int), 1, file);
		printf("\t%d students in class %d: \n", student_num,i+1);
		for (int j = 0; j < student_num; j++) {
			fread(&(id_stud), sizeof(int), 1, file);
			fread(&len, sizeof(int), 1, file);
			name = (char*)malloc(sizeof(char) * (len));
			fread(name, sizeof(char), len, file);
			printf("\t\tid: %d ,name: %s\n", id_stud, name);
			add_student((all_clases+i), id_stud, "abc");
			fread(&grades_num, sizeof(int), 1, file);
			printf("\t\t\t%d grades for student %d: \n", grades_num,id_stud);
			for (int k = 0; k < grades_num; k++) {
				fread(&id_test, sizeof(int), 1, file);
				fread(&grade, sizeof(int), 1, file);
				printf("\t\t\t\ttest id: %d grade: %d\n",id_test,grade);
				add_grade((all_clases + i)->head_student, id_test, grade);
			}
			printf("\n");
			
		}
		
	}
	fclose(file);
	return all_clases;


}

int student_count(p_student_t student) {
	p_student_t temp = student;
	int count = 0;
	while (temp) {
		temp = temp->next;
		count++;
	}
	return count;
}

int grades_count(p_grades_t grade) {
	p_grades_t temp = grade;
	int count = 0;
	while (temp) {
		temp = temp->next;
		count++;
	}
	return count;
}
