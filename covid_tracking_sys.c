#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define PASSWORD  100100 // program password as a macro

// the maximum capacity of four isolation hospitals .
int hospital_1 = 1000, hospital_2 = 500, hospital_3 = 100, hospital_4 = 10; 
// total number of covid-19 patients in all hospitals .
int  patients_num=0;
// patient stucture 
struct patient_data {
	char name[50];
	int age;
	char address[50];
	int hospital_id;
	char reason[250];};
// non-initializing pointer of patient struct type  
struct patient_data *ptr;


void showMainMenue(struct patient_data *ptr);
void storePatientData(struct patient_data *ptr);
void AssignHospitalID(struct patient_data *ptr, char search_name[]);
void displayAllData(struct patient_data *ptr);
void deletePatient(struct patient_data *ptr, char search_name[]);
void displayHospitalData(struct patient_data *ptr, int hospital_id);
int search(struct patient_data *ptr, char search_name[]);
void printHeader();

int main(void){
	char temp;
	int password;
	struct patient_data *newptr; // helping pointer to reallocating our array

	ptr = (struct patient_data*) malloc(5 * sizeof(struct patient_data));	
	
	for (int i = 1; i <= 3; i++){
		printf("Enter program password : ");
		scanf("%d", &password);
		printf("%d\n", password);
		if(password == PASSWORD) {
			while(1){
				printf("\n");
				showMainMenue(ptr);

				// if the reallocation of array pionter succeed
			    if(newptr = realloc(ptr, (patients_num+2) * sizeof (struct patient_data))) {
			    	ptr = newptr;
			    } 
			    else { // allocation Faild
			    	printf("FAILD TO RELLOC");
			    	exit(0);
			    }
			}
		} 
		else if (password != PASSWORD && i == 3) {
			printf("Wrong PASSWORD for three times...\n");
			exit(0);
		}
	}
	return 0;
};

void showMainMenue(struct patient_data *ptr){
	int choice, num_patient, hospital_id;
	char search_name[50];
	char temp;

	printf("\n");
	printf("Please select from the following options  : \n");
	printf("1: Store patinet data\n");
	printf("2: Assign hospital ID to patient\n");
	printf("3: Delete patient data\n");
	printf("4: Print All data in Table\n");
	printf("5: Print hospital Data\n");
	printf("6: Exit\n");
	printf("\n");
	scanf("%d", &choice);


	switch(choice){
		case 1: // store patient's data
			storePatientData(ptr);
			break;
		case 2: // assign hospital id to patient
			printf("Enter the name of The patient to assign Hospital id : ");
			scanf("%c",&temp); // temp statement to clear buffer
			scanf("%[^\n]", search_name);
			AssignHospitalID(ptr, search_name);
			break;
		case 3: // delete specific patient
		    printf("Enter The name you want Delete\n");
		    scanf("%c",&temp); // temp statement to clear buffer
			scanf("%[^\n]", search_name);
			deletePatient(ptr, search_name);
			break;
		case 4: // display all patients' data
			displayAllData(ptr);
			break;
		case 5: // display all patients in specific hospital
			printf("Enter hospital id : ");
			scanf("%d", &hospital_id);
			displayHospitalData(ptr, hospital_id);
			break;
		case 6: // Exit program
			exit(0);;
			break;
	};
};

void storePatientData(struct patient_data *ptr){
	char temp, name[30];
	int boolean, is_exist;

	for (int i = (patients_num+1); i < (patients_num + 1 + 1); i++){
		
		printf("====== Storing Patient Data.... ======\n");
		printf("patient Name : ");
		scanf("%c",&temp); // temp statement to clear buffer
		scanf("%[^\n]", name);
		is_exist = search(ptr, name);
		if (!is_exist) { // if patient does not exist .. so we store the rest of his data
			
			// string copy function that compy from name var to patient's structs
			strcpy((ptr+i)->name , name);

			printf("patient Age : ");
			scanf("%d", &(ptr+i)->age);

			printf("patient Address : ");
			scanf("%c",&temp);
			scanf("%[^\n]", (ptr+i)->address);

			printf("patient Infection Reason : ");
			scanf("%c",&temp);
			scanf("%[^\n]", (ptr+i)->reason);

		} else{
			printf("This patient exists ..\n");
			continue;
		}
	};
	
	// increase patients total  number by one .
	patients_num++;	
};

void AssignHospitalID(struct patient_data *ptr, char search_name[]){
	int patient_indx, hospital_id;
	patient_indx = search(ptr, search_name); // get patient index in array
	if (patient_indx > 0) { // paient exists
		patient_indx--; // search function return index plus one, so we subtract it
		printf("Enter hospital ID : \n");
		scanf("%d", &hospital_id);

		// if hospital_id of patients is 0 or we need to change the hospital_id to another one 
		if ((ptr+patient_indx)->hospital_id != hospital_id) {
			// switch case to decrese the maximum capacity of hospital
			switch((ptr+patient_indx)->hospital_id){
				case 1:
					hospital_1++;
					break;
				case 2:
					hospital_2++;
					break;
				case 3:
					hospital_3++;
					break;
				case 4:
					hospital_4++;
					break;
			};

			// increase the capacity of the hospital we transport the patient from
			switch(hospital_id){
				case 1:
					(ptr+patient_indx)->hospital_id = hospital_id;
					hospital_1--;
					break;
				case 2:
					(ptr+patient_indx)->hospital_id = hospital_id;
					hospital_2--;
					break;
				case 3:
					(ptr+patient_indx)->hospital_id = hospital_id;
					hospital_3--;
					break;
				case 4:

					(ptr+patient_indx)->hospital_id = hospital_id;
					hospital_4--;
					break;
			};
			
		}
		
        
	}
};

void displayAllData(struct patient_data *ptr){
	printf("Displaying Information:\n");
   	for(int i = 1; i < (patients_num+1); ++i)
       	printf("Name: %s\tAge: %d \thos: %d \n", (ptr+i)->name, (ptr+i)->age, (ptr+i)->hospital_id);
};

void deletePatient(struct patient_data *ptr, char search_name[]){
     for(int  i=0; i<= patients_num; i++){
         if( strcmp( (ptr+i)->name ,search_name ) ==0 ){ // if this patient exists
             for(int j=i;j<patients_num;j++){
                 *(ptr+j)=*(ptr+j+1);
             }
             // decrese the total number of patients
             patients_num--;

             // switch case to decrese the maximum capacity of hospital
             switch((ptr+i)->hospital_id){
             	case 1:
             		hospital_1++;
             		break;
             	case 2:
             		hospital_2++;
             		break;
             	case 3:
             		hospital_3++;
             		break;
             	case 4:
             		hospital_4++;
             		break;
             }
             break;
         }
     }};

int search(struct patient_data *ptr, char search_name[]) {
	// serch for patient in patients array and if it exists return his index plus one otherwise return 0 .
    for(int i =0; i<=patients_num; i++){
      if( strcmp(search_name,(ptr+i)->name) == 0 ){
      	return i+1;
      }
    }

    return 0;  
};

void displayHospitalData(struct patient_data *ptr, int hospital_id){
	printHeader(); // print the table header
	for (int i = 1; i < (patients_num+1); i++){
		if ((ptr+i)->hospital_id == hospital_id) {
			printf("Name: %s\t | Age: %d\t | address: %s\t | date of infection: %s \n", (ptr+i)->name, (ptr+i)->age, (ptr+i)->address, (ptr+i)->reason);
			printf("-----------------------------------------------------------\n");
		}
	}
};

void printHeader(){
	printf("Name \t\t | Age \t\t | Address \t | Date of infection \n");
	printf("==============================================================\n");
};