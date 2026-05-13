#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SEMESTERS 100

//Structure to score semester data
struct Semester {
    char name [10];
    int year;
    int hours;
    float quality_points;
};

//Convert letter grade to GPA points
float grade_to_points(char grade) {
    grade = toupper(grade);
    switch (grade){
        case 'A': return 4.0;
        case 'B': return 3.0;
        case 'C': return 2.0;
        case 'D': return 1.0;
        case 'F': return 0.0;
        default: return -1.0; // invalid
    }
}
//Normalize semster name (SPRING, SUMMER, FALL)
void normalize_semester(char *s){
    for (int i = 0; s[i]; i++)
    s[i] = toupper(s[i]);
}

int find_semester(struct Semester sems[], int count, char *name, int year){
    for (int i = 0; i < count; i++){
        if (strcmp(sems[i].name, name) == 0 && sems[i].year == year)
        return i;
    }
    return -1;
}

int main() {
    struct Semester sems[MAX_SEMESTERS];
    int sem_count = 0;

    printf("----> To quit entering grades, enter a blank line.\n");

    while (1) {
        char line[100];
        printf("Enter a letter grade and hours for a course with its year and semester: ");

        if (!fgets(line, sizeof(line), stdin))
        break;

        if (line[0] == '\n')
        break;

        char grade;
        int hours, year;
        char semester[20];

        if (sscanf(line, " %c %d %19s %d", &grade, &hours, semester, &year) != 4) {
            printf("Invalid input. Try again.\n");
            continue;
        }

    float points = grade_to_points(grade);
        if (points < 0) {
            printf("Invalid grade. Use A, B, C, D, or F.\n");
            continue; 
        }  
        
        if (hours <= 0) {
            printf("Invalid credit hours.\n");
            continue;
        }

        normalize_semester(semester);
        if (strcmp(semester, "SPRING") != 0 &&
            strcmp(semester, "SUMMER") != 0 &&
            strcmp(semester, "FALL") != 0) {
            printf("Invalid semester. Use SPRING, SUMMER, or FALL.\n");
            continue;
        }

        if (year < 1900 || year > 2100) {
            printf("Invalid year.\n");
            continue;
        }

        int idx = find_semester(sems, sem_count, semester, year);
        if (idx == -1) {
            idx = sem_count++;
            strcpy(sems[idx].name, semester);
            sems[idx].year = year;
            sems[idx].hours = 0;
            sems[idx].quality_points = 0.0;
        }

        sems[idx].hours += hours;
        sems[idx].quality_points += points * hours;
    }
    printf("-------------------------------------\n");
    printf("Unofficial Transcript\n");

    int total_hours = 0;
    float total_qp = 0.0;

    for (int i = 0; i < sem_count; i++) {
        float gpa = sems [i].quality_points/ sems[i].hours;
        printf("%-6s %d (%d hours) %.3f\n",
            sems[i].name, sems[i].year, sems[i].hours, gpa);

        total_hours += sems[i].hours;
        total_qp += sems[i].quality_points;
    }

    printf("\n--\n");
    printf("Total credit hours: %d\n", total_hours);

    if (total_hours > 0) {
        float overall_gpa = total_qp / total_hours;
        printf("Overall GPA: %.3f\n", overall_gpa);
    } else {
        printf("Overall GPA: N/A\n");
    }

    printf("-------------------------------------\n");
    
    return 0;
}
