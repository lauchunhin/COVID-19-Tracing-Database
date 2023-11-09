#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>

const int MAX_MONTH = 24;
const int MAX_NUMBER_OF_DATA = 3000;

enum STATUS{
    ACTIVE, RECOVERED, DECEASED
};
enum DISTRICT{
    CW, EA, IS, KC, KI, KU, NO, SK, SS, ST, SO, TP, TW, TM, WC, WT, YT, YL
};

struct Patient{
    int ID;
    int date_of_infection;
    STATUS current_status;
    int date_of_recovery_or_death;
    DISTRICT location;
    Patient *next;
    Patient *infectees;
};

const char STATUS_NAME[][10] = {"ACTIVE", "RECOVERED", "DECEASED"};

const char DISTRICT_NAMES[][30] = { // Present as full name
    "Central and Western",
    "Eastern",
    "Islands",
    "Kowloon City",
    "Kwai Tsing",
    "Kwun Tong",
    "North",
    "Sai Kung",
    "Sham Shui Po",
    "Sha Tin",
    "Southern",
    "Tai Po",
    "Tsuen Wan",
    "Tuen Mun",
    "Wan Chai",
    "Wong Tai Sin",
    "Yau Tsim Mong",
    "Yuen Long"
};

 // Return the root pointer.
Patient* buildChainInfection(const char filename[]);
// Print brief information of a given patient
void printPatientID(const Patient* patient);
// Print detailed information of a given patient, including the total count of following cases which are epidemiologically linked to him/her
void printPatientDetails(const Patient* patient);
// Print tree view of Patient Database. 
void printPatientDatabase(const Patient* root, int vertical_alignment = 0);
// Print the number of newly confirmed cases for a given day
int printDailyStat(const Patient* root, int day);
// Search Patient by the given ID. Returns 3 pointers by reference.
void searchPatientByID(int ID, Patient*& current, Patient*& previous, Patient*& parent);

// Remove all cases who have recovered or deceased
void removeInactive(Patient* &root);
// Remove all cases
void deleteAllPatients(Patient* &root);

Patient* findroot(Patient* current);
#endif
