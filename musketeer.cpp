#include "musketeer.h"
/* Start block: DO NOT CHANGE
    * Please do not change anything in this code block (including whitespace, empty lines)
    * If changes, your submission is marked as zero.
*/

/*
    * Default constructor for MemoryManager class
*/
MemoryManager::MemoryManager() {
    this->numOfAllocation = 0;
}

/*
    * Method: get the number of allocation used in this battle
    * Input: None
    * Output:
    * - Returns the number of allocation used in this battle
*/
int MemoryManager::getNumOfAllocation() {
    return this->numOfAllocation;
}

/*
    * Method: allocate to the pointer, increase the number of allocation by 1
    * Input: pointer which needs to be allocated
    * Output: None
*/
void MemoryManager::allocate(int* &pointer) {
    pointer = new int;
    this->numOfAllocation++;
}

/*
    * Method: deallocate to the pointer, decrease the number of allocation by 1
    * Input: pointer which needs to be deallocated
    * Output: None
*/
void MemoryManager::deallocate(int* pointer) {
    if (pointer != NULL) {
        delete pointer;
        this->numOfAllocation--;
    }
}

/*
    * Default constructor for Musketeer class
*/
Musketeer::Musketeer() {
    this->HP = 0;
    this->pC1 = this->pC2 = this->pC3 = NULL;
    this->manager = NULL;
}

/*
    * Default destructor for Musketeer class
*/
Musketeer::~Musketeer() {
    this->finalize();
}

/*
    * Method: set the memory manager for this musketeer
    * Input: the memory manager which currently manages the battle
    * Output: None
*/
void Musketeer::setMemoryManger(MemoryManager* manager) {
    this->manager = manager;
}

/*
    * Method: set the team of this musketeer
    * Input: the team of this musketeer
    * Output: None
*/
void Musketeer::setTeam(Musketeer* team) { 
    this->team = team;
}

/*
    * Method: set the pointer to value of respective cystal of this musketeer
    * Input:
    * - index: the index of cystal
    * - pointer: the address to memory location in which value stores
    * Output: None
*/
void Musketeer::setCystalPointer(int index, int* pointer) {
    switch(index) {
        case 1:
            this->pC1 = pointer;
            break;
        case 2:
            this->pC2 = pointer;
            break;
        case 3:
            this->pC3 = pointer;
            break;
        default:
            break;
    }
}

/*
    * Method: get the pointer to value of respective cystal of this musketeer
    * Input:
    * - index: the index of cystal
    * Output: the address to memory location in which value stores
*/
int* Musketeer::getCystalPointer(int index) {
    switch(index) {
        case 1:
            return this->pC1;
        case 2:
            return this->pC2;
        case 3:
            return this->pC3;
        default:
            return NULL;
    }
}

/*
    * Method: get the HP of this musketeer
    * Input: None
    * Output: the HP of this musketeer
*/
int Musketeer::getHP() {
    return this->HP;
}

/*
    * Method: assign value to the HP of this musketeer
    * Input: the HP value needs to be assigned
    * Output: None
*/
void Musketeer::setHP(int HP) {
    this->HP = HP;
}
/* End block: DO NOT CHANGE */

/* Start block: TO DO
    * You can write anything in this block (make sure there is no errors) and complete below methods
*/
void Musketeer::taoCystal(int cystal,int preMus,int chisoCystal){
    int *cystalPointer;
    manager->allocate(cystalPointer); //Tao vung nho moi cho cystal
    *cystalPointer = cystal; //Level cua cystal moi nhat duoc
    team[preMus].setCystalPointer(chisoCystal, cystalPointer); //Thiet lap gia tri cho vung nho cua cystal
}
void Musketeer::thayCystal(int cystal,int preMus,int chisoCystal,bool dungChung[4][3]){
    if(dungChung[preMus][chisoCystal]==true){
        int *cystalPointer;
        manager->allocate(cystalPointer); //Tao vung nho moi cho cystal
        *cystalPointer = cystal; //Level cua cystal moi nhat duoc
        team[preMus].setCystalPointer(chisoCystal,cystalPointer); //Thiet lap gia tri cho vung nho cua cystal
    }
    else{
        int *cystalPointer;
        *cystalPointer = cystal; //Level cua cystal moi nhat duoc
        team[preMus].setCystalPointer(chisoCystal,cystalPointer); //Thiet lap gia tri cho vung nho cua cystal
    }
}





bool Musketeer::timCystal(int chisoCystal,int HP[4]){
    if(team[3].getCystalPointer(1)!=NULL || team[3].getCystalPointer(2)!=NULL || team[3].getCystalPointer(3)!=NULL){
        if(tim(chisoCystal,HP,3)){ //Tim thay
            return true;
        }
    }
    if(team[0].getCystalPointer(1)!=NULL || team[0].getCystalPointer(2)!=NULL || team[0].getCystalPointer(3)!=NULL){
        if(tim(chisoCystal,HP,0)){ //Tim thay
            return true;
        }
    }
    if(team[1].getCystalPointer(1)!=NULL || team[1].getCystalPointer(2)!=NULL || team[1].getCystalPointer(3)!=NULL){
        if(tim(chisoCystal,HP,1)){ //Tim thay
            return true;
        }
    }
    if(team[2].getCystalPointer(1)!=NULL || team[2].getCystalPointer(2)!=NULL || team[2].getCystalPointer(3)!=NULL){
        if(tim(chisoCystal,HP,2)){ //Tim thay
            return true;
        }
    }
    return false;
}

bool Musketeer::tim(int chisoCystal,int HP[4],int NLQ){ //Tim xem NLQ (co chi so NLQ) co cystal de doi thanh cystal thich hop ko
    int mus1=NLQ+1; if(mus1>=4) mus1-=4; 
    int mus2=NLQ+2; if(mus2>=4) mus2-=4;
    int mus3=NLQ+3; if(mus3>=4) mus3-=4;
    for(int i=1;i<4;i++){
        if(i!=chisoCystal){
            if(team[NLQ].getCystalPointer(i)!=NULL){
                if(*(team[NLQ].getCystalPointer(i))>1 && (*(team[3].getCystalPointer(i)))*10<HP[3]){
                    HP[NLQ]=HP[NLQ]-(*(team[NLQ].getCystalPointer(i)))*10;
                    int* cystalPointer;
                    manager->allocate(cystalPointer);
                    *cystalPointer=*(team[NLQ].getCystalPointer(i))-1;
                    team[3].setCystalPointer(i, cystalPointer);
                    if(team[mus1].getCystalPointer(i)==team[NLQ].getCystalPointer(i)){
                        manager->deallocate(team[mus1].getCystalPointer(i));
                        team[mus1].setCystalPointer(i,NULL);
                    }
                    if(team[mus2].getCystalPointer(i)==team[NLQ].getCystalPointer(i)){
                        manager->deallocate(team[mus2].getCystalPointer(i));
                        team[mus2].setCystalPointer(i,NULL);
                    }
                    if(team[mus3].getCystalPointer(i)==team[NLQ].getCystalPointer(i)){
                        manager->deallocate(team[mus3].getCystalPointer(i));
                        team[mus3].setCystalPointer(i,NULL);
                    }
                    manager->deallocate(team[NLQ].getCystalPointer(i));
                    team[NLQ].setCystalPointer(i,NULL);
                    return true;
                }
            }
        }
    }
    return false;
}

void Musketeer::muonNgoc(int muon,int choMuon,int chisoCystal,bool dungChung[4][3]){ //Cho ngu la quan hien tai muon cystal
    int mus1=choMuon+1; if(mus1>=4) mus1-=4; 
    int mus2=choMuon+2; if(mus2>=4) mus2-=4;
    int mus3=choMuon+3; if(mus3>=4) mus3-=4;
    int* cystalPointer;
    *cystalPointer=*(team[choMuon].getCystalPointer(chisoCystal))-1; //Dung 1 cystal de chien dau
    if(*cystalPointer==0) {
        if(team[mus1].getCystalPointer(chisoCystal)==team[choMuon].getCystalPointer(chisoCystal)){
            manager->deallocate(team[mus1].getCystalPointer(chisoCystal));
            team[mus1].setCystalPointer(chisoCystal,NULL);
        }
        if(team[mus2].getCystalPointer(chisoCystal)==team[choMuon].getCystalPointer(chisoCystal)){
            manager->deallocate(team[mus2].getCystalPointer(chisoCystal));
            team[mus2].setCystalPointer(chisoCystal,NULL);
        }
        if(team[mus3].getCystalPointer(chisoCystal)==team[choMuon].getCystalPointer(chisoCystal)){
            manager->deallocate(team[mus3].getCystalPointer(chisoCystal));
            team[mus3].setCystalPointer(chisoCystal,NULL);
        }
        manager->deallocate(team[choMuon].getCystalPointer(chisoCystal));
        team[choMuon].setCystalPointer(chisoCystal,NULL);
    }
    else {
        team[muon].setCystalPointer(chisoCystal, cystalPointer); //Dung chung so cystal con lai
        dungChung[choMuon][chisoCystal]=true;
        dungChung[muon][chisoCystal]=true;
    }
}

void Musketeer::finalize() {
    // TO-DO
    for(int i=0;i<3;i++){
        this->manager->deallocate(this->getCystalPointer(i));
    }


    
}
/* End block: TO DO */