#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define FILE_NAME "studdb_sys.dat"

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
        printf("\nStudent Data (System Calls)\n");
        printf("1. Add a student\n");
        printf("2. Display all students in database\n");
        printf("3. Modify a student\n");
        printf("4. Delete a student data\n");
        printf("5. Exit program\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createStudent(); break;
            case 2: displayStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

void createStudent() {
    int fd = open(FILE_NAME, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }

    Student s;
    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Marks: ");
    scanf("%d", &s.marks);

    write(fd, &s, sizeof(Student));
    close(fd);

    printf("Student added successfully!\n");
}

void displayStudents() {
    int fd = open(FILE_NAME, O_RDONLY);
    if (fd < 0) {
        printf("No student records found.\n");
        return;
    }

    Student s;
    printf("\nRoll\tName\t\tMarks\n");
    printf("--------------------------------\n");

    while (read(fd, &s, sizeof(Student)) == sizeof(Student)) {
        printf("%d\t%s\t\t%d\n", s.roll, s.name, s.marks);
    }

    close(fd);
}

void updateStudent() {
    int fd = open(FILE_NAME, O_RDWR);
    if (fd < 0) {
        printf("No student records found.\n");
        return;
    }

    int roll, found = 0;
    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);

    Student s;
    off_t offset = 0;

    while (read(fd, &s, sizeof(Student)) == sizeof(Student)) {
        if (s.roll == roll) {
            printf("Enter new Name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter new Marks: ");
            scanf("%d", &s.marks);

            lseek(fd, offset, SEEK_SET);  // move back to start of this record
            write(fd, &s, sizeof(Student));
            found = 1;
            break;
        }
        offset += sizeof(Student);
    }

    close(fd);

    if (found)
        printf("Student record updated successfully.\n");
    else
        printf("Student with Roll No. %d not found.\n", roll);
}

void deleteStudent() {
    int fd = open(FILE_NAME, O_RDONLY);
    if (fd < 0) {
        printf("No student records found.\n");
        return;
    }

    int tempfd = open("temp_sys.dat", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (tempfd < 0) {
        perror("Error creating temp file");
        close(fd);
        return;
    }

    int roll, found = 0;
    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    Student s;
    while (read(fd, &s, sizeof(Student)) == sizeof(Student)) {
        if (s.roll == roll) {
            found = 1;
            continue;  // skip writing this record
        }
        write(tempfd, &s, sizeof(Student));
    }

    close(fd);
    close(tempfd);

    remove(FILE_NAME);
    rename("temp_sys.dat", FILE_NAME);

    if (found)
        printf("Student record deleted successfully.\n");
    else
        printf("Student with Roll No. %d not found.\n", roll);
}
