#include <stdio.h>
#include <string.h>

#define max_employees 100
#define FILE_NAME "employees.txt"

struct Employee {
    int id;
    char name[50];
    char department[50];
    float salary;
    char contact[20];
};

struct Employee employees[max_employees];
int numEmployees = 0;

void loadEmployees() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL)
        return;

    while (numEmployees < max_employees &&
           fscanf(file, "%d|%49[^|]|%49[^|]|%f|%19s\n",
                  &employees[numEmployees].id,
                  employees[numEmployees].name,
                  employees[numEmployees].department,
                  &employees[numEmployees].salary,
                  employees[numEmployees].contact) == 5) {
        numEmployees++;
    }

    fclose(file);
}

void saveEmployees() {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Error\n");
        return;
    }

    int i;
    for (i = 0; i < numEmployees; i++) {
        fprintf(file, "%d|%s|%s|%.2f|%s\n",
                employees[i].id,
                employees[i].name,
                employees[i].department,
                employees[i].salary,
                employees[i].contact);
    }

    fclose(file);
}

int isUniqueID(int id) {
    int i;
    for (i = 0; i < numEmployees; i++)
        if (employees[i].id == id)
            return 0;
    return 1;
}

int isValidContact(char *c) {
    int i;
    if (strlen(c) != 11)
        return 0;
    for (i = 0; i < 11; i++)
        if (c[i] < '0' || c[i] > '9')
            return 0;
    return 1;
}

void addEmployee() {
    if (numEmployees >= max_employees) {
        printf("Maximum employees reached\n");
        return;
    }

    struct Employee emp;

    printf("Enter ID: ");
    scanf("%d", &emp.id);
    if (emp.id < 100 || emp.id > 999) {
        printf("ID must be of 3 digits\n");
        return;
    }
    if (!isUniqueID(emp.id)) {
        printf("ID already exists\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", emp.name);

    printf("Enter Department: ");
    scanf(" %[^\n]", emp.department);

    printf("Enter Salary: ");
    scanf("%f", &emp.salary);
    if (emp.salary <= 0) {
        printf("Salary must be positive!\n");
        return;
    }

    printf("Enter Contact: ");
    scanf("%19s", emp.contact);
    if (!isValidContact(emp.contact)) {
        printf("Invalid contact number\n");
        return;
    }

    employees[numEmployees++] = emp;
    saveEmployees();
    printf("Employee added successfully\n");
}

void updateEmployee() {
    int id, i;
    printf("Enter ID to update: ");
    scanf("%d", &id);

    for (i = 0; i < numEmployees; i++) {
        if (employees[i].id == id) {
            printf("Enter new Name: ");
            scanf(" %[^\n]", employees[i].name);

            printf("Enter new Department: ");
            scanf(" %[^\n]", employees[i].department);

            printf("Enter new Salary: ");
            scanf("%f", &employees[i].salary);
            if (employees[i].salary <= 0) {
                printf("Salary must be positive!\n");
                return;
            }

            printf("Enter new Contact: ");
            scanf("%19s", employees[i].contact);
            if (!isValidContact(employees[i].contact)) {
                printf("Invalid contact number\n");
                return;
            }

            saveEmployees();
            printf("Employee updated successfully\n");
            return;
        }
    }

    printf("Employee not found\n");
}

void deleteEmployee() {
    int id, i, j;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    for (i = 0; i < numEmployees; i++) {
        if (employees[i].id == id) {
            for (j = i; j < numEmployees - 1; j++) {
                employees[j] = employees[j + 1];
            }
            numEmployees--;
            saveEmployees();
            printf("Employee deleted successfully\n");
            return;
        }
    }

    printf("Employee not found\n");
}

void displayAll() {
    int i;
    if (numEmployees == 0) {
        printf("No employees to display\n");
        return;
    }

    printf("%-5s %-20s %-15s %-10s %-15s\n",
           "ID", "Name", "Department", "Salary", "Contact");

    for (i = 0; i < numEmployees; i++) {
        printf("%-5d %-20s %-15s %-10.2f %-15s\n",
               employees[i].id,
               employees[i].name,
               employees[i].department,
               employees[i].salary,
               employees[i].contact);
    }
}

void sortByDepartment() {
    char dep[50];
    int i;
    printf("Enter department: ");
    scanf(" %[^\n]", dep);

    printf("%-5s %-20s %-15s %-10s %-15s\n",
           "ID", "Name", "Department", "Salary", "Contact");

    int found = 0;
    for (i = 0; i < numEmployees; i++) {
        if (strcmp(employees[i].department, dep) == 0) {
            found = 1;
            printf("%-5d %-20s %-15s %-10.2f %-15s\n",
                   employees[i].id,
                   employees[i].name,
                   employees[i].department,
                   employees[i].salary,
                   employees[i].contact);
        }
    }

    if (!found)
        printf("No employees found\n");
}


void sortBySalary() {
    if (numEmployees == 0) {
        printf("No employees to display\n");
        return;
    }

  
    struct Employee temp[max_employees];
    int i, j;
    for (i = 0; i < numEmployees; i++)
        temp[i] = employees[i];


    for (i = 0; i < numEmployees - 1; i++) {
        int min_idx = i;
        for (j = i + 1; j < numEmployees; j++) {
            if (temp[j].salary < temp[min_idx].salary)
                min_idx = j;
        }
        if (min_idx != i) {
            struct Employee t = temp[i];
            temp[i] = temp[min_idx];
            temp[min_idx] = t;
        }
    }

    printf("%-5s %-20s %-15s %-10s %-15s\n",
           "ID", "Name", "Department", "Salary", "Contact");

    for (i = 0; i < numEmployees; i++) {
        printf("%-5d %-20s %-15s %-10.2f %-15s\n",
               temp[i].id,
               temp[i].name,
               temp[i].department,
               temp[i].salary,
               temp[i].contact);
    }
}


void searchByID() {
    if (numEmployees == 0) {
        printf("No employees available\n");
        return;
    }

    int id, i;
    printf("Enter ID to search: ");
    scanf("%d", &id);

    for (i = 0; i < numEmployees; i++) {
        if (employees[i].id == id) {
            printf("%-5s %-20s %-15s %-10s %-15s\n",
                   "ID", "Name", "Department", "Salary", "Contact");
            printf("%-5d %-20s %-15s %-10.2f %-15s\n",
                   employees[i].id,
                   employees[i].name,
                   employees[i].department,
                   employees[i].salary,
                   employees[i].contact);
            return;
        }
    }

    printf("Employee not found\n");
}

int main() {
    int choice;
    loadEmployees();

    do {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Update Employee\n");
        printf("3. Delete Employee\n");
        printf("4. Display All Employees\n");
        printf("5. Search by Department\n");
        printf("6. Sort by Salary \n");
        printf("7. Search by ID\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: updateEmployee(); break;
            case 3: deleteEmployee(); break;
            case 4: displayAll(); break;
            case 5: sortByDepartment(); break;
            case 6: sortBySalary(); break;
            case 7: searchByID(); break;
            case 8: break;
            default: printf("Invalid choice\n");
        }

    } while (choice != 8);

    return 0;
}


