/* 
Student: Gianna Binder
Class: ICS4U-2A
Assignment: Lab 5.3.4 Gym membership management system
Teacher: Dr. Noukhovitch
Date: March 21, 2022
*/

/********************************************
description: GYM MEMBERSHIP SYSTEM
********************************************/

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//initialize class
class GymMembership {
public:
  GymMembership();
  void printMembership();
  int getID() { return id; }
  int vectorID[10];
  void create(int id, string name);
  void del(int id);
  void add(int id, int months);
  void cancel(int id, int months);

private: 
  int months;
  int id;
  string name;
  int years;
};

//contructor - initialize variables
GymMembership::GymMembership(){
  id = 0; name = ' '; months = 0;
}

void GymMembership::printMembership(){

  //determine number of years
  years = months / 12 ;

  //if gym membership valid for more than a year
  if (years > 0){
    cout << "Member " << id << ": " << name << ", subscription valid for " << years << " years";
      
    //if the membership has additional months on top of the year
    if (months % 12 > 0)
      cout << " and " << months % 12 << " months" << endl;

    // if the membership length is a set amount of years
    else
      cout << endl;
  }
  
  else
    cout << "Member " << id << ": " << name << ", subscription valid for " << months << " months" << endl;
}

//creates membership and saves values
void GymMembership::create(int id, string name){
  
  //saves values
  this-> id = id; this-> name = name;

  printMembership(); //prints membership information
}

//deletes a memberhsip
void GymMembership::del(int id){

  //resets values
  this-> id = 0; this-> name = ' '; this-> months = 0;

  //tell user the membership was deleted
  cout << "Membership " << id << " has been deleted." << endl; 
}

//add months to membership
void GymMembership::add(int id, int months){

  ///cancels reserved seats if the int is valid
  if(months > 0)
    
    //saves value
    this-> months += months;

  //tell user if the input is not valid
  else
    cout << "INVALID INPUT" << endl;
  
  printMembership(); //print membership status
}

//cancels months from memberhsip
void GymMembership::cancel(int id, int months){

  //cancels reserved seats if the int is valid
  if(months > 0 && months <= this-> months)
    //saves value
    this-> months -= months;

  //tell user if the input is not valid
  else
    cout << "INVALID INPUT" << endl;
  
  printMembership(); // print membership status
}

int main() {
  
 //initialize the array
  GymMembership member[10];

  // tell user how to use the program
  cout << endl << "**************************************" << endl << endl;
  cout << "GYM MEMBERSHIP SYSTEM" << endl << endl;
   cout << "Create up to 10 memberships" << endl << endl;
  cout << "To modify memberships, input the following commands following the syntax without the brakets:" << endl << endl;
  cout << "- Create a membership: \'create [id] [name]\': creates a membership id attached to the member's name, there are 0 months initially." << endl << endl;
  cout <<  "- Delete a membership: \'delete [id]\': deletes the membership" << endl << endl;
  cout << "- Add months to memberhsip: \'add [id] [months]\': adds number of months to memberhsip" << endl << endl;
  cout << "- Cancel months from mebership: \'cancel [id] [months]\': cancels months from membership" << endl << endl;
  cout << "**************************************" << endl << endl;

  //initialize variables
  string command = " ";
  int memberships = 0;

  //ask user what they would like to do
  while (command != "quit")
  {
    
    //tell user if there are no memberships in the system
    if (memberships == 0)
      cout << "No members in the system." << endl << endl;

    //tell user if they cannot create any more memberships
    else if (memberships == 10)
      cout << "System capacity reached, no more members can be added." << endl;

    //initialize variable
    int goTo;
    int find = 0;
    int id = 0;
    string function ="";
    string name = "";
    int months = 0;
    

    //ask user what they would like to do
    cout << "What would you like to do? ";
    getline(cin, command); //receive user's command

    //break up command
    //find command
    function = command.substr(0, command.find_first_of(" "));
    command = command.erase(0, command.find_first_of(" ") + 1);
    
    //find id
    if (function == "create" || function == "add" || function == "cancel"  || function == "delete"){
      id = stoi(command.substr(0, command.find_first_of (" ")));
      command = command.erase(0, command.find_first_of (" ")+ 1);

      //find name
        if (function == "create"){

          //if the id is already in use
          for (int u = 0; u < 10; u++){
            if (member[u].getID() == id){
              cout << "ID already in use - INVALID INPUT" << endl;
              function = " ";
            }
          }

          name = command;
        }  
  
        //find months
        else
          months = stoi(command);
    }  

    //if they want to create a membership
    if (function == "create"){

      //store it in the array by finding a free spot
      for (int i = 0; i < 10; i++){

        //create the membership when an empty spot in the array is found
        if (member[i].getID() == 0){
          member[i].create(id, name);
          break;
        }
      }

      //increase counter
      memberships++;
    }

    //if the user would like to exit the program
    else if (command == "quit"){

      //thank the user
      cout << "Thank you for using our gym membership system!" << endl;
      break;
    }

    else if (function != " ") {

      //declare variable
      int IDnum = -1;
      
      //if id is not created
      for (int i = 0; i < 10; i++){
        if (member[i].getID() == id){
          IDnum = i;
          i = 30;
        }
      }
   
      //if id is invalid
      if (IDnum < 0)
        cout << "ID not found - INVALID INPUT" << endl;
      
      //if months is invalid
      else if (months < 0)
        cout << "Improper number of months - INVALID INPUT" << endl;

      //if command is valid
      else{
        
        //if they want to delete a membership
        if (function == "delete"){
  
          //delete the membership
          member[IDnum].del(id);

          //update counter
          memberships--;
        }  
    
        //if they want to add months to a membership
        else if (function == "add"){
  
          //call function
          member[IDnum].add(id, months);
        }
    
        //if they want to delete months from a membership
        else if (function == "cancel"){
  
          //call function
          member[IDnum].cancel(id, months); 
        }  

        //improper function called
        else
          cout << "Improper command - INVALID INPUT" << endl;
      }
    }

    cout << endl;
  } 

  return 0;
}