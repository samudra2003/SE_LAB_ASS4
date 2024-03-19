#include <stdio.h>
#include <stdlib.h>

struct Student {
    int rollno;
    char name[50];
    int marks1;
    int marks2;
    int marks3;
    int marks4;
    int marks5;
    int totalmarks;
};

void add_student() {
    FILE *fp;
    struct Student st;

    fp = fopen("student.txt", "ab");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    printf("Enter name: ");
    scanf("%s", st.name);

    printf("Enter rollno: ");
    scanf("%d", &st.rollno);

    printf("Enter marks of Maths-IV: ");
    scanf("%d", &st.marks1);
    printf("Enter marks of Computer Networks: ");
    scanf("%d", &st.marks2);
    printf("Enter marks of Graph Theory: ");
    scanf("%d", &st.marks3);
    printf("Enter marks of OOS: ");
    scanf("%d", &st.marks4);
    printf("Enter marks of Software Engineering: ");
    scanf("%d", &st.marks5);

    st.totalmarks = st.marks1 + st.marks2 + st.marks3 + st.marks4 + st.marks5;

    printf("Student added successfully...\n");
    fwrite(&st, sizeof(st), 1, fp);
    fclose(fp);
}

void update_marks() {
    FILE *fp;
    struct Student st;
    int roll_no, found = 0;

    printf("\n-----Update marks-----\n");
    printf("Enter rollno to update: ");
    scanf("%d", &roll_no);

    fp = fopen("student.txt", "rb+");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    while (fread(&st, sizeof(st), 1, fp) == 1) {
        if (roll_no == st.rollno) {
            found = 1;
            printf("Enter the new set of marks\n");
            printf("Enter marks of Maths-IV: ");
            scanf("%d", &st.marks1);
            printf("Enter marks of Computer Networks: ");
            scanf("%d", &st.marks2);
            printf("Enter marks of Graph Theory: ");
            scanf("%d", &st.marks3);
            printf("Enter marks of OOS: ");
            scanf("%d", &st.marks4);
            printf("Enter marks of Software Engineering: ");
            scanf("%d", &st.marks5);
            st.totalmarks = st.marks1 + st.marks2 + st.marks3 + st.marks4 + st.marks5;

            fseek(fp, -sizeof(st), SEEK_CUR);
            fwrite(&st, sizeof(st), 1, fp);
            fclose(fp);
            printf("\nMarks updated successfully...\n");
            break;
        }
    }

    if (!found) {
        printf("\nStudent not found...\n");
    }
}

void display() {
    FILE *fp;
    struct Student st;

    printf("\n---Student details----\n");
    printf("%-10s %-30s %-15s %-20s %-20s %-20s %-20s %-20s\n", "Rollno", "Name",
           "Maths-IV", "Computer Networks", "Graph Theory", "OOS", "Software Engineering", "Total Marks");

    fp = fopen("student.txt", "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    while (fread(&st, sizeof(st), 1, fp) == 1) {
        printf("%-10d %-30s %-15d %-20d %-20d %-20d %-20d %-20d\n", st.rollno, st.name,
               st.marks1, st.marks2, st.marks3, st.marks4, st.marks5, st.totalmarks);
    }

    fclose(fp);
}

void sort_by_marks() {
    // Sorting the students in the file based on total marks
    struct Student students[100]; // Assuming a maximum of 100 students
    int i, j, count = 0;
    FILE *fp;

    fp = fopen("student.txt", "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    while (fread(&students[count], sizeof(struct Student), 1, fp) == 1) {
        count++;
    }

    fclose(fp);

    // Bubble sort based on total marks
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (students[j].totalmarks < students[j + 1].totalmarks) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    // Displaying sorted students
    printf("\n---Students sorted by total marks---\n");
    printf("%-10s %-30s %-20s\n", "Rollno", "Name", "Total Marks");
    for (i = 0; i < count; i++) {
        printf("%-10d %-30s %-20d\n", students[i].rollno, students[i].name, students[i].totalmarks);
    }
}

void teacher() {
    int val;
    printf("\n1. Add student\n");
    printf("2. Update marks\n");
    printf("3. Display marks\n");
    printf("4. Sort students by marks\n");

    printf("Enter choice: ");
    scanf("%d", &val);

    switch (val) {
        case 1:
            add_student();
            break;
        case 2:
            update_marks();
            break;
        case 3:
            display();
            break;
        case 4:
            sort_by_marks();
            break;
        default:
            printf("Invalid input\n");
    }
}

void student() {
    display();
}

int main() {
    int val;

    while (1) {
        printf("\n1. Teacher\n");
        printf("2. Student\n");
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &val);

        switch (val) {
            case 1:
                teacher();
                break;
            case 2:
                student();
                break;
            case 0:
                exit(0);
            default:
                printf("Invalid input\n");
        }
    }
    return 0;
}

