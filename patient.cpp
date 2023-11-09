#include <iostream>
#include <cstring>
#include "patient.h"
using namespace std;


bool exist(const Patient* root, int id)
{
    if (root == nullptr) {return false;};
    if (root->ID == id) {return true;};
    bool indirect = exist(root->next, id);
    if(indirect) {return true;};
    bool direct = exist(root->infectees, id);
    return direct;
}


bool deletion(const Patient* root)
{
    if (root == nullptr) {return false;};
    if (root->current_status > 0) {return true;};
    bool indirect = deletion(root->next);
    if(indirect) {return true;};
    bool direct = deletion(root->infectees);
    return direct;
}

int next_id(const Patient* root)
{
    if (root == nullptr) {return 0;};
    if (root->current_status > 0) {return root->ID;};
    int indirect = next_id(root->next);
    if(indirect > 0) {return indirect;};
    int direct = next_id(root->infectees);
    if(direct > 0) {return direct;}
    else {return 0;}
}

void cases(Patient* &root, Patient* &previous, Patient* &parent){
    Patient* temp = nullptr;

    if (previous && !parent && !root->infectees) {
        temp = root;
        Patient* prev_patient = previous;
        Patient* next_patient = root->next;
        prev_patient->next = next_patient;
        root = root->next;
        delete temp;
        temp = nullptr;
        return;
    }

    else if (previous && !parent && root->infectees) {
        Patient* prev_patient = previous;
        temp = root;
        Patient* direct_infectee = root->infectees;
        Patient* next_patient = root->next;
        Patient* direct_temp = direct_infectee;
        prev_patient->next = direct_infectee;
        while (direct_temp->next){
            direct_temp = direct_temp->next;
        }
        direct_temp->next = next_patient;
        root = root->infectees;
        delete temp;
        temp = nullptr;
        return;
    }

    else if (previous && parent && !root->infectees) {
        Patient* prev_patient = previous;
        Patient* next_patient = root->next;
        temp = root;
        prev_patient->next = next_patient;
        root = root->next;
        delete temp;
        temp = nullptr;
        prev_patient = nullptr;
        return;
    }

    else if (previous && parent && root->infectees) {
        Patient* prev_patient = previous;
        Patient* direct_infectee = root->infectees;
        Patient* next_patient = root->next;
        Patient* direct_temp = root->infectees;
        temp = root;
        prev_patient->next = direct_infectee;
        while (direct_temp->next){
            direct_temp = direct_temp->next;
        }
        direct_temp->next = next_patient;
        root = root->next;
        delete temp;
        temp = nullptr;
        return;
    }

    else if (!previous && !parent && !root->infectees) {
        Patient* next_patient = root->next;
        temp = root;
        root = next_patient;
        delete temp;
        temp = nullptr;
        return;
    }

    else if (!previous && !parent && root->infectees) {
        Patient* direct_infectee = root->infectees;
        Patient* direct_temp = direct_infectee;
        Patient* next_patient = root->next;
        temp = root;
        root->next = direct_infectee;
        while (direct_temp->next){
            direct_temp = direct_temp->next;
        }
        direct_temp->next = next_patient;
        root = direct_infectee;
        delete temp;
        temp = nullptr;
        return;
    }

    else if (!previous && parent && !root->infectees) {
        Patient* infector = parent;
        Patient* next_patient = root->next;
        temp = root;
        infector->infectees = next_patient;
        root = root->next;
        delete temp;
        temp = nullptr;
        return;
    }

    else if (!previous && parent && root->infectees) {
        Patient* infector = parent;
        Patient* next_patient = root->next;
        Patient* direct_infectee = root->infectees;
        Patient* direct_temp = direct_infectee;
        temp = root;
        infector->infectees = direct_infectee;
        while(direct_temp->next){
            direct_temp = direct_temp->next;
        }
        direct_temp->next = next_patient;
        delete temp;
        temp->next = nullptr;
        temp = nullptr;
        direct_infectee = nullptr;
        return;
    }

    else {
        return;
    }
}

int total_infectees(const Patient* patient, int count = 0){
    if (!patient) {return 0;}
    if (patient->ID > 0) {count ++;}
    else if (!patient || (!patient->infectees && !patient->next)) {return count;}
    if (patient->infectees && !patient->next) {return count + total_infectees(patient->infectees, 0);}
    else if (!patient->infectees && patient->next) { return count + total_infectees(patient->next, 0);}
    else if (patient->next && patient->infectees) { return count + total_infectees(patient->next, 0) + total_infectees(patient->infectees, 0);}
    else {return count;}
}

int daycount(const Patient* root, int day, int count = 0){
    if (root->date_of_infection == day) {count ++;}
    else if (!root || (!root->infectees && !root->next)) {return count;}
    if (root->infectees && !root->next) {return count + daycount(root->infectees, day, 0);}
    else if (!root->infectees && root->next) {return count + daycount(root->next, day, 0);}
    else if (root->next && root->infectees) {return count + daycount(root->next, day, 0) + daycount(root->infectees, day, 0);}
    else {return count;}
};

int lastnode(const Patient* root){
    if (!root->infectees && !root->next) {return root->ID;}
    if (root->infectees) {return lastnode(root->infectees);}
    else {return lastnode(root->next);}
}

void tabspacing(int level){
    for (int i = 0; i < level; ++i){
        cout << "\t" ;
    }
}

void execution(Patient* &root, Patient* &direction){
    Patient* rootstore = root;
    Patient* current = root;
    Patient* previous = nullptr;
    Patient* parent = nullptr;
    int last_ID = lastnode(direction);
    searchPatientByID(last_ID, current, previous, parent);
    if (current->current_status > 0) {cases(current, previous, parent);}
    else {
        bool checked = false;
        do{
            if (checked){
                current = rootstore;
                previous = nullptr;
                parent = nullptr;
                searchPatientByID(last_ID, current, previous, parent);
            }
            checked = true;
            bool next_check = deletion(current->next);
            int tbd = next_id(current->next);
            if (next_check){
                while(current->current_status == 0){
                    next_check = deletion(current->next);
                    if (next_check) {current = current->next;}
                    else {current = current->infectees;}
                }
                last_ID = current->ID;
            }
            else if (previous){
                last_ID = previous->ID;
                current = previous;
            }
            else {
                last_ID = parent->ID;
                current = parent;
            }
        }
        while (current->current_status == 0);

        current = rootstore;
        previous = nullptr;
        parent = nullptr;
        searchPatientByID(last_ID, current, previous, parent);
        cases(current, previous, parent);
    }
}

// Print detailed information of a given patient, including the total count of following cases which are epidemiologically linked to him/her
void printPatientDetails(const Patient* patient){
    printPatientID(patient); cout << endl;
    cout <<"Date of Infection:" << patient->date_of_infection << endl;
    cout << STATUS_NAME[patient->current_status] << endl;
    cout <<"Date of Recovery or Death:" << patient->date_of_recovery_or_death << endl;
    cout <<"Location:" << DISTRICT_NAMES[patient->location] << endl;
    cout <<"Total infectees:" << total_infectees(patient->infectees) << endl;
};

// Print tree view of Patient Database. 
void printPatientDatabase(const Patient* root, int vertical_alignment){
    if (!root) {return;}
    tabspacing(vertical_alignment);
    printPatientID(root);
    cout << endl;
    if (root->infectees){
        printPatientDatabase(root->infectees, vertical_alignment+1);
    }
    if (root->next){
        printPatientDatabase(root->next, vertical_alignment);
    }
    if (!root->infectees && !root->next) {return;}
};

// Print the number of newly confirmed cases for a given day
int printDailyStat(const Patient* root, int day){
    if(!root) {return 0;}
    else{
        Patient* next_direct_infectee =  root->infectees;
        Patient* next_indirect_infectee =  root->next;
        int direct_count = 0, indirect_count = 0, total_count = 0;
        if (root->date_of_infection == day) {total_count ++;}
        if (next_direct_infectee){
            direct_count += daycount(next_direct_infectee, day, 0);
        }
        if (next_indirect_infectee){
            while(!next_direct_infectee && next_indirect_infectee && next_indirect_infectee->date_of_infection <= day){
                if (next_indirect_infectee->date_of_infection == day) {indirect_count ++;}
                next_direct_infectee = next_indirect_infectee->infectees;
                next_indirect_infectee = next_indirect_infectee->next;
            }
            indirect_count += daycount(next_indirect_infectee, day, 0);
        }
        return total_count + direct_count + indirect_count;
    }
};

// Search Patient by the given ID. Returns 3 pointers by reference.
void searchPatientByID(int ID, Patient*& current, Patient*& previous, Patient*& parent){
    bool direct = exist(current->infectees, ID);
    bool indirect = exist(current->next, ID);
    if (current->ID == ID || !current) {return;}
    if (!direct && !indirect){
        current = nullptr;
        parent = nullptr;
        previous = nullptr;
        return;
    }
    if (indirect && current->next){
        previous = current;
        current = current->next;
        searchPatientByID(ID, current, previous, parent);
    }
    if (current->ID == ID || !current) {return;}
    if (direct && current->infectees && current->infectees){
        parent = current;
        current = current->infectees;
        previous = nullptr;
        searchPatientByID(ID, current, previous, parent);
    }
    if (!current->infectees && !current->next) {return;} 
    return;
};

// Remove all cases who have recovered or deceased
void removeInactive(Patient* &root){
    bool direct = deletion(root->infectees);
    bool indirect = deletion(root->next);
    bool invalidroot = (root->current_status > 0);
    // Deletion Done
    if (!direct && !indirect && !invalidroot) {return;}
    // NEXT / INDIRECT DELETION IN PROGRESS
    if (indirect && root->next){
        execution(root, root->next);
        return removeInactive(root);
    }
    // INFECTEES / DIRECT DELETION IN PROGRESS
    if (direct && root->infectees){
        execution(root, root->infectees);
        return removeInactive(root);
    }
    // ROOT DELETION IN PROGRESS
    if (!direct && !indirect && invalidroot) {
        Patient* previous = nullptr;
        Patient* parent = nullptr;
        cases(root, previous, parent);
    }
    return;
}

// Remove all cases
void deleteAllPatients(Patient* &root){
    if (root == nullptr) {return;}
    deleteAllPatients(root->next);
    deleteAllPatients(root->infectees);
    delete root;
    root = nullptr;  
}