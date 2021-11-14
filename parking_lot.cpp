//============================================================================
// Name        : parking_lot.cpp
// Author      : Chinmay
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

enum VehicleType {CAR, BIKE, TRUCK};

class Vehicle {
public:
	const string& getColor() const {
		return color;
	}

	void setColor(const string &color) {
		this->color = color;
	}

	const string& getRegNumber() const {
		return reg_number;
	}

	void setRegNumber(const string &regNumber) {
		reg_number = regNumber;
	}

	VehicleType getType() const {
		return type;
	}

	void setType(VehicleType type) {
		this->type = type;
	}


private:
	VehicleType type;
	string reg_number;
	string color;
};

class Slot{
public:
	bool getIsAvailable() const {
		return isAvailable;
	}

	void setIsAvailable(bool isAvailable) {
		this->isAvailable = isAvailable;
	}

	const Vehicle& getVehicle() const {
		return vehicle;
	}

	void setVehicle(const Vehicle &vehicle) {
		this->vehicle = vehicle;
	}

private:
	bool isAvailable;
	Vehicle vehicle;

};

class Floor  {
public:
	int getNumSlots() const {
		return num_slots;
	}

	void setNumSlots(int numSlots) {
		num_slots = numSlots;
	}

	vector<Slot> getSlots() const {
		return slots;
	}

	void setSlots(vector<Slot> slots) {
		this->slots = slots;
	}
    Floor() {

    }
	Floor (int num_slots){
		this->num_slots = num_slots;
		vector<Slot> s(num_slots);
		for (int j = 0;j<num_slots;j++){
			s[j].setIsAvailable(true);
			Vehicle v;
			if (j == 0){
				v.setType(TRUCK);
				s[j].setVehicle(v);
			}
			else if (j == 1 or j == 2){
				v.setType(BIKE);
				s[j].setVehicle(v);
			}else {
				v.setType(CAR);
				s[j].setVehicle(v);
			}

		}
		this->slots = s;
	}

private:
	int num_slots;
	vector<Slot> slots;
};

class ParkingLot  {
public:
	vector<Floor> getFloors() const {
		return floors;
	}

	void setFloors(vector<Floor> floors) {
		this->floors = floors;
	}

	int getNumFloors() const {
		return num_floors;
	}

	void setNumFloors(int numFloors) {
		num_floors = numFloors;
	}

	ParkingLot (int num_floors,int slots_per_floor){

		this->num_floors = num_floors;
		this->floors.resize(num_floors);
		for (int i = 0;i<num_floors;i++){
			this->floors[i].setNumSlots(slots_per_floor);
			vector<Slot> s(slots_per_floor);
			for (int j = 0;j<slots_per_floor;j++){
				s[j].setIsAvailable(true);
				Vehicle v;
				if (j == 0){
					v.setType(TRUCK);
					s[j].setVehicle(v);
				}
				else if (j == 1 or j == 2){
					v.setType(BIKE);
					s[j].setVehicle(v);
				}else {
					v.setType(CAR);
					s[j].setVehicle(v);
				}

			}
			this->floors[i].setSlots(s);
		}

		cout<<"chinmay"<<endl;


	}
	void addFloor(int num_slots) {
		Floor floor(num_slots);
		num_floors++;
		floors.push_back(floor);


	}
	void addSlot(int floor_number,VehicleType v){
		int numSlots = floors[floor_number].getNumSlots();
		floors[floor_number].setNumSlots(numSlots+1);
		Slot slot;
		slot.setIsAvailable(true);
		Vehicle vehicle ;
		vehicle.setType(v);
		slot.setVehicle(vehicle);
		vector<Slot> s = floors[floor_number].getSlots();
		s.push_back(slot);
		floors[floor_number].setSlots(s);
	}

	void freeSlots(VehicleType v){
		for (int i = 0;i<floors.size();i++){
			vector<Slot> slots = floors[i].getSlots();
			int count = 0;
			string freeSlots="";
			for (int j = 0;j<slots.size();j++){
				Vehicle vehicle = slots[j].getVehicle();
				if (vehicle.getType() == v and slots[j].getIsAvailable()){
					count++;
					freeSlots+=": ";
					freeSlots+=to_string(j);
				}
			}
			cout<<"No. of slots for "<<to_string(v)<<" on floor "<<i<<" : "<<count<<" "<<freeSlots<<endl;
		}
	}

	pair<int,int> findFirstSlot(VehicleType v){
		for (int i = 0;i<floors.size();i++){
			vector<Slot> slots = floors[i].getSlots();
			for (int j = 0;j<slots.size();j++){
				Vehicle vehicle = slots[j].getVehicle();
				if (vehicle.getType() == v and slots[j].getIsAvailable()){
					return make_pair(i,j);
				}
			}
		}
		cout<<"No Slots available"<<endl;
		return make_pair(-1,-1);
	}

	string createTicket(string registration,int floor_number,int slot_number){
		string ticket = registration + "_" + to_string(floor_number) + "_" + to_string(slot_number);
		return ticket;
	}

	string parkVehicle(VehicleType v,string registration,string color){
		pair<int,int> first_slot = findFirstSlot(v);
		int f = first_slot.first;
		int s = first_slot.second;
		vector<Slot> slots_on_floor = floors[f].getSlots();
		slots_on_floor[s].setIsAvailable(false);
		Vehicle vehicle;
		vehicle.setType(v);
		vehicle.setRegNumber(registration);
		vehicle.setColor(color);
		slots_on_floor[s].setVehicle(vehicle);
		floors[f].setSlots(slots_on_floor);
		string ticket = createTicket(registration,f,s);
		cout<<"Vehicle Parked at "<<f<<" floor "<<s<<" slot"<<endl;
		return ticket;
	}

	void unParkVehicle(string ticket){
		string reg = ticket.substr(0,5);
		char f = ticket.substr(6,1)[0];
		char s = ticket.substr(8,1)[0];
		int fl = f-'0';
		int sl = s - '0';
		vector<Slot> slots = floors[fl].getSlots();
		slots[sl].setIsAvailable(false);

	}



private:

	int num_floors;
	vector<Floor> floors;
};




int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	string input = "create 5 9";

	/*
	for (int i = 0;i<input.size();i++){
		if (input[i] == ' '){
			pref = input.substr(0,i);
			break;
		}
	}
	*/

	    /*
		string floors = input.substr(7,1);
		stringstream f(floors);
		int num_floors = 0;
		f >> num_floors;
		string slots = input.substr(9,1);
		stringstream s(slots);
		int num_slots = 0;
		s >> num_slots;

		*/

	ParkingLot lot(5,9);
	lot.freeSlots(VehicleType::CAR);
	cout<<lot.parkVehicle(CAR,"12345","Red")<<endl;
	cout<<lot.parkVehicle(CAR,"23456","Green")<<endl;
	cout<<lot.parkVehicle(TRUCK,"56342","Black")<<endl;
	cout<<lot.parkVehicle(BIKE,"56342","Blue")<<endl;
	cout<<lot.parkVehicle(BIKE,"56342","Black")<<endl;
	cout<<lot.parkVehicle(BIKE,"56342","red")<<endl;
	cout<<lot.parkVehicle(BIKE,"56342","orange")<<endl;
	lot.freeSlots(VehicleType::CAR);
	lot.freeSlots(VehicleType::TRUCK);
	lot.freeSlots(VehicleType::BIKE);


	return 0;
}
