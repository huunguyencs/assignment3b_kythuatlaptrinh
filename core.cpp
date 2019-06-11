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
bool soNguyenTo(int n){
    for(int i=2;i<n;i++){
        if(n%i==0) return false;
    }
    return true;
}
int sntNhoHon(int n){
    for(int i=n;i>1;i--){
        if(soNguyenTo(i)==true) return i;
    }
}
void Musketeer::helpMus(int giup,int duocGiup,int quai){
    int* cystalPointer;
    team[duocGiup].setCystalPointer(quai,this->team[giup].getCystalPointer(quai));
    *cystalPointer=*team[duocGiup].getCystalPointer(quai)-1;
    if(*cystalPointer==0) manager->deallocate(team[duocGiup].getCystalPointer(quai));
    else team[duocGiup].setCystalPointer(quai, cystalPointer);
}

void Musketeer::help(int preMus,int chisoCystal,float chisoQuai,bool pause[4],int event,int HP[4]){
    int mus1=preMus+1; if(mus1>=4) mus1-=4;
    int mus2=preMus+2; if(mus2>=4) mus2-=4;
    int mus3=preMus+3; if(mus3>=4) mus3-=4;
    if(preMus==0 && team[0].getHP()<HP[0]) {
        if(team[0].getHP()+200>HP[0]) team[preMus].setHP(HP[0]);
        else{
            this->team[preMus].setHP(this->team[preMus].getHP+200);
        }
    }
    if(preMus==1 && team[1].getHP()<HP[1]) {
        if(team[1].getHP()+150>HP[1]) team[preMus].setHP(HP[1]);
        else{
            this->team[preMus].setHP(this->team[preMus].getHP+150);
        }
    }
    if(preMus==2 && team[2].getHP()<HP[2]) {
        if(team[2].getHP()+100>HP[2]) team[preMus].setHP(HP[2]);
        else{
            this->team[preMus].setHP(this->team[preMus].getHP+100);
        }
    }
    if(preMus==3 && team[3].getHP()<HP[3]) {
        if(team[3].getHP()+50>HP[0]) team[preMus].setHP(HP[3]);
        else{
            this->team[preMus].setHP(this->team[preMus].getHP+50);
        }
    }
    if(this->team[mus1].getCystalPointer(chisoCystal) != NULL && !pause[mus1]){
        int* cystalPointer;
        *cystalPointer=*team[mus1].getCystalPointer(chisoCystal)-1;
        if(*cystalPointer==0) manager->deallocate(team[mus1].getCystalPointer(chisoCystal));
        else{
            team[mus1].setCystalPointer(chisoCystal,cystalPointer);
        }
    }
    else{
        if(this->team[mus2].getCystalPointer(chisoCystal)!=NULL && !pause[mus2]){
            helpMus(mus2,mus1,chisoCystal);
            helpMus(mus2,preMus,chisoCystal);
        }
        else {
            if(this->team[mus3].getCystalPointer(chisoCystal)!=NULL && !pause[mus3]){
                helpMus(mus3,mus1,chisoCystal);
                helpMus(mus3,preMus,chisoCystal);
            }
            else{
                if(-(event)%100==11){
                    pause[mus1]=true;
                }
                else{
                    if(!(mus1==3 && timCystal(chisoCystal,HP)==true)){
                        int dam ,hp;
                        dam = floor(-event*chisoQuai+(int)(pow(chisoQuai,mus1+1)*sntNhoHon(-event))%100);
                        hp=this->team[mus1].getHP()-dam;
                        if(hp<1){
                            HP=0;
                            pause[mus1]=true;
                        }
                        this->team[mus1].setHP(hp);
                    }
                }
                    
            }
        }
    }
}
bool Musketeer::timCystal(int chisoCystal,int HP[4]){
    if(*(team[3].getCystalPointer(1))>1 || *(team[3].getCystalPointer(2))>1 || *(team[3].getCystalPointer(3))>1){
        for(int i=1;i<4;i++){
            if(*(team[3].getCystalPointer(i))>1 && (*(team[3].getCystalPointer(i)))*10<HP[3]){
                HP[3]=HP[3]-(*(team[3].getCystalPointer(i)))*10;
                int* cystalPointer;
                manager->allocate(cystalPointer);
                *cystalPointer=*team[3].getCystalPointer(i)-1;
                team[3].setCystalPointer(chisoCystal, cystalPointer);
                manager->deallocate(team[3].getCystalPointer(i));
                return true;
            }
        }
    }
    if(*(team[0].getCystalPointer(1))>1 || *(team[0].getCystalPointer(2))>1 || *(team[0].getCystalPointer(3))>1){
        for(int i=1;i<4;i++){
            if(*(team[0].getCystalPointer(i))>1 && (*(team[0].getCystalPointer(i)))*10<HP[3]){
                HP[3]=HP[3]-(*(team[3].getCystalPointer(i)))*10;
                int* cystalPointer;
                manager->allocate(cystalPointer);
                *cystalPointer=*team[0].getCystalPointer(i)-1;
                team[3].setCystalPointer(chisoCystal, cystalPointer);
                manager->deallocate(team[0].getCystalPointer(i));
                return true;
            }
        }
    }
    if(*(team[1].getCystalPointer(1))>1 || *(team[1].getCystalPointer(2))>1 || *(team[1].getCystalPointer(3))>1){
        for(int i=1;i<4;i++){
            if(*(team[1].getCystalPointer(i))>1 && (*(team[1].getCystalPointer(i)))*10<HP[3]){
                HP[3]=HP[3]-(*(team[3].getCystalPointer(i)))*10;
                int* cystalPointer;
                manager->allocate(cystalPointer);
                *cystalPointer=*team[1].getCystalPointer(i)-1;
                team[3].setCystalPointer(chisoCystal, cystalPointer);
                manager->deallocate(team[1].getCystalPointer(i));
                return true;
            }
        }
    }
    if(*(team[2].getCystalPointer(1))>1 || *(team[2].getCystalPointer(2))>1 || *(team[2].getCystalPointer(3))>1){
        for(int i=1;i<4;i++){
            if(*(team[2].getCystalPointer(i))>1 && (*(team[2].getCystalPointer(i)))*10<HP[3]){
                HP[3]=HP[3]-(*(team[3].getCystalPointer(i)))*10;
                int* cystalPointer;
                manager->allocate(cystalPointer);
                *cystalPointer=*team[2].getCystalPointer(i)-1;
                team[3].setCystalPointer(chisoCystal, cystalPointer);
                manager->deallocate(team[2].getCystalPointer(i));
                return true;
            }
        }
    }
    return false;
}
void Musketeer::attack(int preMus,int chisoCystal,float chisoQuai,bool pause[4],int event,int HP[4]){
    int mus1=preMus+1; if(mus1>=4) mus1-=4;
    int mus2=preMus+2; if(mus2>=4) mus2-=4;
    int mus3=preMus+3; if(mus3>=4) mus3-=4;
    if(this->team[preMus].getCystalPointer(chisoCystal)!=NULL){
        int* cystalPointer;
        *cystalPointer=*team[preMus].getCystalPointer(chisoCystal)-1;
        if(*cystalPointer==0) manager->deallocate(team[preMus].getCystalPointer(chisoCystal));
        else this->team[preMus].setCystalPointer(chisoCystal, cystalPointer);
    }
    else{
        if(this->team[mus1].getCystalPointer(chisoCystal)!=NULL && !pause[mus1]){
            helpMus(mus1,preMus,chisoCystal);
        }
        else {
            if(this->team[mus2].getCystalPointer(chisoCystal)!=NULL && !pause[mus2]){
                helpMus(mus2,preMus,chisoCystal);
            }
            else{
                if(this->team[mus3].getCystalPointer(chisoCystal)!=NULL && !pause[mus3]){
                    helpMus(mus3,preMus,chisoCystal);
                }
                else{
                    if(-(event)%100==11){
                        pause[preMus]=true;
                    }
                    else{
                        if(!(preMus==3 && timCystal(chisoCystal,HP)==true)){
                            int dam ,hp;
                            dam = floor(-event*chisoQuai+(int)(pow(chisoQuai,preMus+1)*sntNhoHon(-event))%100);
                            hp=this->team[preMus].getHP()-dam;
                            if(hp<1){
                                HP=0;
                                pause[preMus]=true;
                            }
                            this->team[preMus].setHP(hp);
                        }
                    }
                        
                }
            }
        }
        
    }
}

/*
    * Method: Emulate this battle
    * Input: None
    * Output: None
*/
void Battle::struggle() {
    // TO-DO
    int HP[4];
    for(int i=0;i<4;i++){
        HP[i]=this->musketeers[i].getHP();
    }
    bool pause[4];
    for(int i=0;i<4;i++){
        pause[i]=false;
    }
    int preMus=this->firstMusketeer;
    int mus1=preMus+1; if(mus1>=4) mus1-=4;
    int mus2=preMus+2; if(mus2>=4) mus2-=4;
    int mus3=preMus+3; if(mus3>=4) mus3-=4;
    for(int i=0;i<this->numOfEvents;i++){
        if(events[i]>9 && events[i]<20){  //Nhat duoc Sapphire co level X
            int cystal=events[i]%10;
            if(this->musketeers[preMus].getCystalPointer(1)==NULL){
                int *cystalPointer;
                manager->allocate(cystalPointer);
                *cystalPointer = cystal;
                this->musketeers[preMus].setCystalPointer(1, cystalPointer);
            }
            else{
                if(*(this->musketeers[preMus].getCystalPointer(1))<cystal){
                    manager->deallocate(this->musketeers[i].getCystalPointer(1));
                    int *cystalPointer;
                    manager->allocate(cystalPointer);
                    *cystalPointer = cystal;
                    this->musketeers[preMus].setCystalPointer(1,cystalPointer);
                }
            }

        }
        else{
            if(events[i]>19 && events[i]<30){  //Nhat duoc Emerald co level X
                int cystal=events[i]%10;
                if(this->musketeers[preMus].getCystalPointer(2)==NULL){
                    int *cystalPointer;
                    manager->allocate(cystalPointer);
                    *cystalPointer = cystal;
                    this->musketeers[preMus].setCystalPointer(2, cystalPointer);
                }
                else{
                    if(*(this->musketeers[preMus].getCystalPointer(2))<cystal){
                        manager->deallocate(this->musketeers[i].getCystalPointer(2));
                        int *cystalPointer;
                        manager->allocate(cystalPointer);
                        *cystalPointer = cystal;
                        this->musketeers[preMus].setCystalPointer(2,cystalPointer);
                    }
                }

            }
            else{
                if(events[i]>29 && events[i]<40){  //Nhat duoc Aquamarine co level X
                    int cystal=events[i]%10;
                    if(this->musketeers[preMus].getCystalPointer(3)==NULL){
                        int *cystalPointer;
                        manager->allocate(cystalPointer);
                        *cystalPointer = cystal;
                        this->musketeers[preMus].setCystalPointer(2, cystalPointer);
                    }
                    else{
                        if(*(this->musketeers[preMus].getCystalPointer(3))<cystal){
                            manager->deallocate(this->musketeers[i].getCystalPointer(3));
                            int *cystalPointer;
                            manager->allocate(cystalPointer);
                            *cystalPointer = cystal;
                            this->musketeers[preMus].setCystalPointer(3,cystalPointer);
                        }
                    }

                }
                else{
                    int event=-events[i]%100;
                    switch(event){
                        case 11: //Quai vat Quezacolt tan cong
                            if(pause[preMus]==true){
                                if(pause[mus1]==true){
                                    if(pause[mus2]==true) {
                                        musketeers[mus2].help(mus2,1,0.65f,pause,events[i],HP);
                                    }
                                    else musketeers[mus1].help(mus1,1,0.65f,pause,events[i],HP);
                                }
                                else musketeers[preMus].help(preMus,1,0.65f,pause,events[i],HP);
                            }
                            else{
                                musketeers[preMus].attack(preMus,1,0.65f,pause,events[i],HP);
                            }
                            break;
                        case 12: //Quai vat Bahamut tan cong
                            if(pause[preMus]==true){
                                musketeers[preMus].help(preMus,1,0.95f,pause,events[i],HP);
                            }
                            else{
                                musketeers[preMus].attack(preMus,1,0.95f,pause,events[i],HP);
                            }
                            break;
                        case 21: //Quai vat Cerberus tan cong
                            if(pause[preMus]==true){
                                musketeers[preMus].help(preMus,2,0.85f,pause,events[i],HP);
                            }
                            else{
                                musketeers[preMus].attack(preMus,2,0.85f,pause,events[i],HP);
                            }
                            break;
                        case 22: //Quai vat Ifrit tan cong
                            if(pause[preMus]==true){
                                musketeers[preMus].help(preMus,2,0.9f,pause,events[i],HP);
                            }
                            else{
                                musketeers[preMus].attack(preMus,2,0.9f,pause,events[i],HP);
                            }
                            break;
                        case 31: //Quai vat Siren tan cong
                            if(pause[preMus]==true){
                                musketeers[preMus].help(preMus,3,0.4f,pause,events[i],HP);
                            }
                            else{
                                musketeers[preMus].attack(preMus,3,0.4f,pause,events[i],HP);
                            }
                            break;
                        case 32: //Quai vat Leviathan tan cong
                            if(pause[preMus]==true){
                                musketeers[preMus].help(preMus,3,1,pause,events[i],HP);
                            }
                            else{
                                musketeers[preMus].attack(preMus,3,1,pause,events[i],HP);
                            }
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
