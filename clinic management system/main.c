#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------------------------------
// Structure to hold patient data
// -------------------------------
struct Patient {
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[50];
};

// -------------------------------
// Function declarations
// -------------------------------
void addPatient();
void viewPatients();
void searchPatient();
void deletePatient();

// -------------------------------
// Main Function
// -------------------------------
int main() {
    int choice;

    while (1) {
        printf("\n====== Clinic Management System ======\n");
        printf("1. Add Patient\n");
        printf("2. View All Patients\n");
        printf("3. Search Patient\n");
        printf("4. Delete Patient\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                viewPatients();
                break;
            case 3:
                searchPatient();
                break;
            case 4:
                deletePatient();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

// -------------------------------
// Function: Add a new patient
// -------------------------------
void addPatient() {
    struct Patient p;
    FILE *fp = fopen("patients.dat", "ab");

    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Patient ID: ");
    scanf("%d", &p.id);

    printf("Enter Name: ");
    scanf("%s", p.name);

    printf("Enter Age: ");
    scanf("%d", &p.age);

    printf("Enter Gender: ");
    scanf("%s", p.gender);

    printf("Enter Disease: ");
    scanf("%s", p.disease);

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);

    printf("Patient record added successfully!\n");
}

// -------------------------------
// Function: View all patients
// -------------------------------
void viewPatients() {
    struct Patient p;
    FILE *fp = fopen("patients.dat", "rb");

    if (!fp) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- Patient Records ---\n");

    while (fread(&p, sizeof(p), 1, fp)) {
        printf("ID: %d | Name: %s | Age: %d | Gender: %s | Disease: %s\n",
               p.id, p.name, p.age, p.gender, p.disease);
    }

    fclose(fp);
}

// -------------------------------
// Function: Search a patient by ID
// -------------------------------
void searchPatient() {
    struct Patient p;
    FILE *fp = fopen("patients.dat", "rb");
    int id, found = 0;

    if (!fp) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Patient ID to search: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            printf("Record Found!\n");
            printf("ID: %d | Name: %s | Age: %d | Gender: %s | Disease: %s\n",
                   p.id, p.name, p.age, p.gender, p.disease);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Patient not found!\n");
    }

    fclose(fp);
}

// -------------------------------
// Function: Delete a patient by ID
// -------------------------------
void deletePatient() {
    struct Patient p;
    FILE *fp = fopen("patients.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    int id, found = 0;

    if (!fp) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id != id) {
            fwrite(&p, sizeof(p), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("patients.dat");
    rename("temp.dat", "patients.dat");

    if (found) {
        printf("Patient record deleted successfully!\n");
    } else {
        printf("Patient not found!\n");
    }
}
