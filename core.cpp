#include "core.h"

/* Start block: DO NOT CHANGE
    * Please do not change anything in this code block (including whitespace, empty lines)
    * If changes, your submission is marked as zero.
*/

/*
    * Default constructor for Battle class
*/
Battle::Battle(MemoryManager* manager) {
    this->musketeers = NULL;
    this->events = NULL;
    this->manager = manager;
}

/*
    * Default destructor for Battle class
*/
Battle::~Battle() {
    this->finalize();
}

/*
    * Method: read data from input file and assign values to musketeers
    * Input:
    * - filename: the name of input file
    * Output:
    * - Returns true if read file successfully, otherwise returns false
*/
bool Battle::readDataFromFile(string filename) {
    fstream fs(filename, ios::in);

    if (!fs.is_open()) return false;

    this->musketeers = new Musketeer[NUM_OF_MUSKETEERS];

    int* cystalPointer = NULL;
    int cystal = 0;

    for (int i = 0; i < NUM_OF_MUSKETEERS; i++) {
        this->musketeers[i].setMemoryManger(this->manager);
        this->musketeers[i].setTeam(this->musketeers);
        
        for (int j = 0; j < NUM_OF_CYSTAL; j++) {
            fs >> cystal;

            if (cystal > 0) {
                manager->allocate(cystalPointer);
                *cystalPointer = cystal;
                this->musketeers[i].setCystalPointer(j + 1, cystalPointer);
            }
        }
    }
    
    fs >> this->firstMusketeer;

    string eventsInText = "";
    fs.ignore();
    getline(fs, eventsInText);

    int numOfSpaces = 0;
    for (int i = 0; i < eventsInText.length(); i++) {
        if (eventsInText.at(i) == ' ') numOfSpaces++;
    }

    int numOfEvents = numOfSpaces + 1;

    this->events = new int[numOfEvents];

    stringstream ss(eventsInText);

    for (int i = 0; i < numOfEvents; i++)
        ss >> this->events[i];
    
    this->numOfEvents = numOfEvents;
    
    return true;
}

void Battle::display() {
    for (int i = 0; i < NUM_OF_MUSKETEERS; i++) {
        cout << this->musketeers[i].getHP() << " ";

        for (int j = 0; j < NUM_OF_CYSTAL; j++) {
            if (this->musketeers[i].getCystalPointer(j + 1) != NULL)
                cout << *(this->musketeers[i].getCystalPointer(j + 1));
            else cout << 0;
            if (j < NUM_OF_CYSTAL - 1) cout << " ";
        }
    
        cout << endl;
    }

    cout << this->manager->getNumOfAllocation();
}
/* End block: DO NOT CHANGE */

/* Start block: TO DO
    * You have to complete only one method of Battle class
*/

/*
    * Method: Emulate this battle
    * Input: None
    * Output: None
*/
void Battle::struggle() {
    // TO-DO
    for(int i=0;i<this->numOfEvents;i++){
        int preMus=this->firstMusketeer;
        if(events[i]>9 && events[i]<20){  //Nhat duoc Sapphire co level X
            int levelX=events[i]%10;
            int *cystalPointer;
            int cystal=levelX;
            *cystalPointer = cystal;
            this->musketeers[preMus].setCystalPointer(1, cystalPointer);

        }
        else{
            if(events[i]>19 && events[i]<30){  //Nhat duoc Emerald co level X
                int levelX=events[i]%10;
                int *cystalPointer;
                int cystal=levelX;
                *cystalPointer = cystal;
                this->musketeers[preMus].setCystalPointer(2, cystalPointer);

            }
            else{
                if(events[i]>29 && events[i]<40){  //Nhat duoc Aquamarine co level X
                    int levelX=events[i]%10;
                    int *cystalPointer;
                    int cystal=levelX;
                    *cystalPointer = cystal;
                    this->musketeers[preMus].setCystalPointer(3, cystalPointer);

                }
                else{
                    int event=-events[i]%100;
                    switch(event){
                        case 11: //Quai vat Quezacolt tan cong
                            

                            break;
                        case 12: //Quai vat Bahamut tan cong


                            break;
                        case 21: //Quai vat Cerberus tan cong


                            break;
                        case 22: //Quai vat Ifrit tan cong


                            break;
                        case 31: //Quai vat Siren tan cong


                            break;
                        case 32: //Quai vat Leviathan tan cong



                            break;
                    }
                }
            }
        }
        










    }









}

/*
    * Method: finalize a battle, deallocate any dynamic memories. 
    * Input: None
    * Output: None
*/
void Battle::finalize() {
    // TO-DO















}
/* End block: TO DO */
