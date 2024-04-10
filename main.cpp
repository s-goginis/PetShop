//Shreya Gogini
//hw1.cpp

//Purpose: This program is a shelter management systems. The user can
//         choose to add a dog or cat to the shelter. The user can choose
//         to adopt a dog or cat from the shelter.

#include <iostream>
#include <queue>
#include <string>

using namespace std;

//creating a struct with the necessary information for the pet
struct Pet{
  string animal_name;//name of the pet
  int duration;//time-stamp for the pet in the shelter
};

class Petshop{
  public:
  //creating two queues, one for each pet type at the shelter
  queue <Pet*> dog;
  queue <Pet*> cat;

  //desc : adds a pet of a certain type to the corresponding queue
  //pre : queue exists and all the parameters of function are satisfied
  //post : the new pet is added to the corresponding queue
  void addPet(string animal_name, string type, int duration){
    //creates a new pew with name and a number signifying time spent
    Pet *new_pet = new Pet{animal_name, duration};
    //depending on the choice that the user made, adds either dog or cat
    if(type == "dog"){
      dog.push(new_pet);
    }
    if(type == "cat"){
      cat.push(new_pet);
    }
  }

  //desc : the user can adopt the pet based on their choice
  //pre : both queues exist 
  //post : prints out the adoption result, and returns true if success
  //       otherwise false if the queue is empty
  bool getPet(queue<Pet*> &pet){
      //if the queue is empty, returns false to eliminate out of bounds errors
      if (pet.empty()){
        return false;
      }
      else{
        //if the chosen pet is a dog
        if(pet == dog){
          //pointer saves the front pointer
          Pet *front = dog.front();
          //get the name of the dog
          string name = front->animal_name;
          //removes the dog from the queue
          dog.pop();
          //deletes the memory
          delete front;
          cout<< "Congrats on adopting a dog, their name is: "<< name << endl;
        }
        //if the chosen pet is a cat
        else if (pet == cat){
          //pointer saves the front pointer
          Pet *front = cat.front();
          //gets the name of the cat
          string name = front->animal_name;
          //removes the cat from the queue
          cat.pop();
          //deletes the memory
          delete front;
          cout<< "Congrats on adopting a cat, their name is: "<< name << endl;
        }
    }
    //once the actions are completed, returns true
    return true;
  }
  
  //desc : gets the oldest pet in the pet shop
  //pre : both queues exists and have pets
  //post : calls the getPet function, returns true if completed successfully
  bool getOldest(){
    //checks if both queues are empty, returns false
    if(cat.empty() && dog.empty()){
      return false;
    }
    //starts the comparisons of the queues
    //if there are dogs, but no cats
    if(cat.empty() && !dog.empty()){
      getPet(dog);
    }
    //if there are cats, but no dogs
    else if(dog.empty() && !cat.empty()){
      getPet(cat);
    }
    else{
      //gets the front pet of each queue to compare
      //and see which one is older
      Pet *old_cat = cat.front();
      Pet *old_dog = dog.front();
      if(old_cat->duration > old_dog->duration){
        //gets the pet using the getPet function
        getPet(dog);
      }
      else{
        getPet(cat);
      }
    }
    //returns true upon success
    return true;
  }

  //desc : destructor of the Pet
  //pre : queues exist
  //post : memory is deallocated correctly and no memeory leak
  ~Petshop(){
    //deallocating the cat queue and the front pointers
    while(!cat.empty()){
      delete cat.front();
      cat.pop();
    }
    //deallocating the dog queue and the front pointers
    while(!dog.empty()){
      delete dog.front();
      dog.pop();
    }
  }
    
};

//desc : main function that runs the program
//pre : Petshop class exists
//post : none
int main(){
  //creates an instance of the petshop class
  Petshop shelter;
  //variable to check if user wants to continue
  bool repeat = true;
  //keeps track of pet order
  int count = 1;
  do{
    //variable for user's choice in the options below
    int choice;
    //prints out the options
    cout << "\nWelcome to the animal shelter." 
        <<" What would you like to do?" << endl;
    cout << "1. Add a CAT to the shelter" << endl;
    cout << "2. Add a DOG to the shelter" << endl;
    cout << "3. Adopt a CAT from the shelter" << endl;
    cout << "4. Adopt a DOG from the shelter" << endl;
    cout << "5. Adopt any animal from the shelter" << endl;
    cout << "6. Exit" << endl;
    //asks the user for their choice based on the options
    cin >> choice;
    //variables that hold the pet names
    string cat_name;
    string dog_name;
    
    //switch statement to account for all the choices 
    switch (choice){
      //if the user wants to add a cat
      case 1:
        //gets the name and calls the addPet function
        cout << "Enter the name of the cat:" << endl;
        cin >> cat_name;
        shelter.addPet(cat_name, "cat", count);
        //increments count
        count ++;
        break;
      //if the user wants to add a dog
      case 2:
        //gets the name and calls the addPet function
        cout <<"Enter the name of the dog:" << endl;
        cin >> dog_name;
        shelter.addPet(dog_name, "dog", count);
        //increments count
        count ++;
        break;
      //if the user wants to adopt a cat
      case 3:
        //calls the getPet function, runs as long as there are pets to adopt
        if(!shelter.getPet(shelter.cat)){
          cout << "There are no cats to adopt" << endl;
        }
        break;
      //if the user wants to adopt a dog
      case 4:
        //calls the getPet functions, runs as long as there are pets to adopt
        if(!shelter.getPet(shelter.dog)){
          cout << "There are no dogs to adopt" << endl;
        }
        break;
      //if the user wants to adopt any pet
      case 5:
        //gets the oldest pet in the shelter, if there are any
        if(!shelter.getOldest()){
          cout << "There are no pets to adopt." << endl;
        }
        break;
      //if the user wants to quit
      case 6:
        //ends program
        repeat = false;
        cout << "Thank you for visiting the pet shelter. Goodbye!" << endl;
        break;
      //in case of invalid input, ends program with output
      default:
        cout << "Error. Invalid input " << endl;
        repeat = false;
        break;
      }
  //continues as long as user doesn't exit
  }while(repeat); 

}



