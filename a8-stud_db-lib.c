#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "studdb.txt"

typedef struct {
    int roll;
    char name[50];
    int marks;
} Student;


void createStudent();
void displayStudents();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    while (1) {
        printf("\nStudent Data\n");
        printf("1. Add a student\n");
        printf("2. Display all students in database\n");
        printf("3. Modify a student\n");
        printf("4. Delete a student data\n");
        printf("5. Exit program\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                createStudent();
                break;
            case 2: 
                displayStudents();
                break;
            case 3: 
                updateStudent();
                break;
            case 4: 
                deleteStudent();
                break;
            case 5: 
                exit(0);
            default: 
                printf("Invalid choice!\n");
        }
    }
    return 0;
}


void createStudent() {
    FILE *file = fopen(FILE_NAME, "ab");  
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    Student s;
    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);  
    printf("Enter Marks: ");
    scanf("%d", &s.marks);

    fwrite(&s, sizeof(Student), 1, file);
    fclose(file);
    printf("Student added successfully!\n");
}


void displayStudents() {
    FILE *file = fopen(FILE_NAME, "rb");  
    if (!file) {
        printf("No student records found.\n");
        return;
    }

    Student s;
    printf("\nRoll\tName\t\tMarks\n");
    printf("--------------------------------\n");
    while (fread(&s, sizeof(Student), 1, file)) {
        printf("%d\t%s\t%d\n", s.roll, s.name, s.marks);
    }
    fclose(file);
}


void updateStudent() {
    FILE *file = fopen(FILE_NAME, "rb+");  
    if (!file) {
        printf("No student records found.\n");
        return;
    }

    int roll, found = 0;
    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);

    Student s;
    while (fread(&s, sizeof(Student), 1, file)) {
        if (s.roll == roll) {
            printf("Enter new Name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter new Marks: ");
            scanf("%d", &s.marks);

            fseek(file, -sizeof(Student), SEEK_CUR);  
            fwrite(&s, sizeof(Student), 1, file);
            found = 1;
            break;
        }
    }
    fclose(file);

    if (found)
        printf("Student record updated successfully.\n");
    else
        printf("Student with Roll No. %d not found.\n", roll);
}


void deleteStudent() {
    FILE *file = fopen(FILE_NAME, "rb");  
    if (!file) {
        printf("No student records found.\n");
        return;
    }

    FILE *tempFile = fopen("temp.dat", "wb");  
    if (!tempFile) {
        printf("Error creating temp file!\n");
        fclose(file);
        return;
    }

    int roll, found = 0;
    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    Student s;
    while (fread(&s, sizeof(Student), 1, file)) {
        if (s.roll == roll) {
            found = 1;  
        } else {
            fwrite(&s, sizeof(Student), 1, tempFile);
        }
    }
    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found)
        printf("Student record deleted successfully.\n");
    else
        printf("Student with Roll No. %d not found.\n", roll);
}
