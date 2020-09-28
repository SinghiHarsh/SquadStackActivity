#include<bits/stdc++.h>
using namespace std;
/*

Following are the definitions to perform specific tasks.

Create_parking_lot - Allocation of slots based on the available space.
Park               - Allocation of the nearest slot available which the vehicle registration number.
Leave              - Free up space for the particular vehicle based on the vehicle registration number,check has to performed if the slot is vacant or occupied. 

Following are the definitions to retrieve information collected while making space for parking.

NOTE: 
Following information cannot be generated 
if above commands (Create_parking_lot, Park, Leave) 
are not created.

Slot_number_for_car_with_number - Returns the vehicle slot number parked based on the vehicle registration number.
Slot_numbers_for_driver_of_age - Returns the slot numbers based on the drivers age.
Vehicle_registration_number_for_driver_of_age - Returns all the parked vehicles registration number parked based on age.

Following are the definitions used,

getUserInfoBasedOnInput() - This mehtod translates the input 
							command into the required data form in a list.

getDriverSlotInfoAge() - This method is used to check if slots are allocated, 
						 if allocated based on the command "Slot_numbers_for_driver_of_age" 
						 or "Vehicle_registration_number_for_driver_of_age" fetches result.

getRegistrationInfo() - This method is used to find the slot number based on the 
						registration number provided.

removeRegisteredSlotInfo() - This method removes the slot blocked if available 
						and updates all the required data structures to keep them in 
						sync with the application.

*/


vector<string> getUserInfoBasedOnInput(string &value) {
	vector<string> resultInfo;
	string build;

	for(int i = 1; i < value.size(); ++i){
		if(isspace(value[i])){
			resultInfo.push_back(build);
			build = "";
		}
		else {
				build += value[i];
		}
	}
	resultInfo.push_back(build);
	return resultInfo;
}

vector<pair<int,string>> getDriverSlotInfoAge(int age, unordered_map<int,vector<pair<int,string>>> &driverSlots){
	if(driverSlots.count(age) == 0){
		return {};
	}
	else {
		return driverSlots[age];
	}
}

int getRegistrationInfo(string registrationNumber, vector<pair<string,int>>& slots){
	for(int i = 1; i < slots.size(); ++i){
		if(slots[i].first == registrationNumber){
			return i;
		}
	}
	return -1;
}
bool removeRegisteredSlotInfo(unordered_map<int,vector<pair<int,string>>> & driverSlots,int age, string registrationNumber){
	if(driverSlots.count(age) == 1){
		auto &slots = driverSlots[age];
		auto removeIndex = -1;
		for(int i = 0; i < slots.size(); ++i){
			if(slots[i].second == registrationNumber){
				removeIndex = i;
				break;
			}
		}
		if(removeIndex == -1){
			return false;
		}
		else {
			slots.erase(slots.begin() + removeIndex);
			return true;
		}
	}
	else return false;

}

int main(){
	freopen("input.txt", "r",stdin);
	freopen("output.txt","w",stdout);

	string command;

	/* Define data-structures for 
		1. allocation of slots
		2. retrieving information based on slots booked
		3. Unallocation of slots.
	*/
	
	/* Allocate available slots,
		Each slot represents Vehicle number and driver age.	
	*/
	vector<pair<string,int>> totalSlots;
	totalSlots.push_back({"-1",-1});
	/*
		Allocate driver age as the key,with the values being stored 
		in a list containing pair which holds slot allocated and Vehicle number. 
	*/
	unordered_map<int,vector<pair<int,string>>> driverSlots;

	while(cin>>command){
		if(command == "Create_parking_lot"){
			string slots;
			getline(cin,slots);
			int k = stoi(slots);

			for(int i = 0; i < k; ++i){
				totalSlots.push_back({"-1",-1});
			}
			cout<<"Created parking of "<<k<<" slots"<<endl;
		}
		else if(command == "Park"){

			string userInformation;
			getline(cin,userInformation);

			vector<string> userData = getUserInfoBasedOnInput(userInformation);
			if(userData.size() > 3){
				cout<<"command instructions not followed, please try again!"<<endl;
				break;
			}

			for(int i = 1; i < totalSlots.size(); ++i){
				if(totalSlots[i].first == "-1" && totalSlots[i].second == -1){
					int driverAge = stoi(userData[2]);
					totalSlots[i] = {userData[0], driverAge};
					driverSlots[driverAge].push_back({i,userData[0]});
					cout<<"Car with vehicle registration number "<<userData[0]<<" has been parked at slot "<<i<<endl;
					break;
				}
			}
		}
		else if(command == "Slot_numbers_for_driver_of_age"){
			string driverAge;
			getline(cin,driverAge);

			int age = stoi(driverAge);

			vector<pair<int,string>> getSlots = getDriverSlotInfoAge(age,driverSlots);
			if(getSlots.size() > 0){

				for(auto i : getSlots){
					cout<<i.first<<" ";
				}
				cout<<endl;
			}
			else {
				cout<<"No slot information available for the driver age provided"<<endl;
			}
		}
		else if(command == "Slot_number_for_car_with_number"){
			string registrationNumber;
			getline(cin,registrationNumber);

			// Triming for leading spaces.
			registrationNumber = registrationNumber.substr(1, registrationNumber.size()-1);

			if(totalSlots.size() > 0){
				int available = getRegistrationInfo(registrationNumber,totalSlots);
				if(available == -1){
					cout<<"No vehicles found!"<<endl;
				}
				else {
					cout<<available<<endl;
				}
			}
			else {
				cout<<"No slots has been created for the parking"<<endl;
			}
		}
		else if(command == "Vehicle_registration_number_for_driver_of_age"){
			string driverAge;
			getline(cin,driverAge);

			int age = stoi(driverAge);

			vector<pair<int,string>> getSlots = getDriverSlotInfoAge(age,driverSlots);
			if(getSlots.size() > 0){

				for(auto i : getSlots){
					cout<<i.second<<" ";
				}
				cout<<endl;
			}
			else {
				cout<<"No slot information available for the driver age provided"<<endl;
			}
		}
		else if(command == "Leave"){
			string slot;
			getline(cin,slot);
			int k = stoi(slot);

			if(k > totalSlots.size()){
				cout<<"Invalid slot number"<<endl;
			}
			if(totalSlots[k].first == "-1" && totalSlots[k].second == -1){
				cout<<"The slot,which you are trying to remove is not allocated"<<endl;
			}
			else {
				string registrationNumber = totalSlots[k].first;
				int age = totalSlots[k].second;
				bool removed = removeRegisteredSlotInfo(driverSlots,age,registrationNumber);
				if(removed){
					cout<<"Slot number "<<k<<" vacated, the car with vehicle registration number "<<registrationNumber<<" left the space, the driver of the car was of age "<<age<<endl;
					totalSlots[k] = {"-1",-1};

				}
			}

		}
		else {
			cout<<"Invalid command found, please try again!"<<endl;
		}
	}

	return 0;
}