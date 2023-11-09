# COVID-19 Tracing Database
This C++ program manages a database of patients infected with COVID-19. The database is implemented as a linked list of Patient objects, where each Patient represents an individual patient. Several functionalities for managing and visualizing the patient database are provided.


## Patient Structure
Each Patient object has the following properties:

`ID`: The patient’s unique identifier.

`date_of_infection`: The date the patient was infected.

`current_status`: The patient’s current status (active, recovered, or deceased).

`date_of_recovery_or_death`: The date the patient recovered or died.

`location`: The district where the patient is located.

`next`: A pointer to the next patient in the list.

`infectees`: A pointer to the first patient infected by this patient.


## Functions
The program includes several functions for managing the patient database:

`buildChainInfection`: Reads data from a file and builds the patient database using a linked list of `Patient` objects

`printPatientID` and `printPatientDetails`: Print a given patient's ID and detailed information, respectively.

`printPatientDatabase`: Prints a tree view of the patient database.

`printDailyStat`: Prints the number of new cases for a given day.

`searchPatientByID`: Searches for a patient by their ID and returns pointers to the patient, the previous patient in the list, and the patient who infected them.

`removeInactive`: Removes all patients who have recovered or are deceased from the database.

`deleteAllPatients`: Removes all patients from the database.


## Input Data
1. Data Format: The data for each patient is organized in the following format:
```
ID	InfectionDate	Status	Recovery/DeathDate	District	Infector
```
2. ID: This is a unique identifier for each patient.
3. InfectionDate: This represents the date when the patient was infected.
4. Status: This represents the current status of the patient. It can have one of the following values:
- 0: ACTIVE
- 1: RECOVERED
- 2: DECEASED
5. Recovery/DeathDate: This represents the date when the patient either recovered or died. If the patient is still active (i.e., has not yet recovered or died), this field will have a value of -1.
6. District: This represents the district where the patient is located.
7. Infector: This represents the ID of the patient who infected this patient. If this field has a value of -1, it means that the patient is the root of the infection chain, i.e., they were not infected by any other patient.

## Usage
1. Compile the program with the following command: g++ -std=c++11 main.cpp given.cpp patient.cpp -o main
2. Run the resulting executable with ./main
3. The program will display a menu with the following options:
- 10: Load a file to the system. You will be prompted to enter the filename. The file should be in the correct format as described in the program documentation.
- 88: Quit the program.
4. Enter the number corresponding to the option you want to choose and press Enter.


## Examples
#### Main Menu]
![Main Menu](https://github.com/lauchunhin/COVID-19-Tracing-Database/blob/main/menu_0.png)

#### Patient Detailed Information
![Patient Detailed Information](https://github.com/lauchunhin/COVID-19-Tracing-Database/blob/main/funct_3.png)

#### Infection Chain Tree Graph of data in `c.txt`
![Infection Chain Tree Graph](https://github.com/lauchunhin/COVID-19-Tracing-Database/blob/main/function_42.png)

