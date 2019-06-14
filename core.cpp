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
    for(int i=n-1;i>1;i--){
        if(soNguyenTo(i)==true) return i;
    }
}

float luyThua(float coSo,int mu){
    int result=1;
    for(int i=1;i<=mu;i++){
        result*=coSo;
    }
    return result;
}
void Musketeer::help(int preMus,int chisoCystal,float chisoQuai,bool pause[4],int event,int HP[4],bool dungChung[4][3]){ //Giup do preMus chien dau voi doi thu
    int mus1=preMus+1; if(mus1>=4) mus1-=4;
    int mus2=preMus+2; if(mus2>=4) mus2-=4;
    int mus3=preMus+3; if(mus3>=4) mus3-=4;
    if(preMus==0 && team[0].getHP()<HP[0] && pause[0]==true) { //d'Artagnan hoi phuc HP
        if(team[0].getHP()+200>HP[0]) {
            team[preMus].setHP(HP[0]); //Da hoi phuc HP ban dau
            pause[preMus]=false;
        }
        else{
            this->team[preMus].setHP(this->team[preMus].getHP()+200); //Neu chua hoi phuc HP ban dau thi tiep tuc +200
        }
    }
    if(preMus==1 && team[1].getHP()<HP[1] && pause[1]==true) { //Athos hoi phuc HP
        if(team[1].getHP()+150>HP[1]) {
            team[preMus].setHP(HP[1]); //Da hoi phuc HP ban dau
            pause[preMus]=false;
        }
        else{
            this->team[preMus].setHP(this->team[preMus].getHP()+150); //Neu chua hoi phuc HP ban dau thi tiep tuc +150
        }
    }
    if(preMus==2 && team[2].getHP()<HP[2] && pause[2]==true) { //Porthos hoi phuc HP
        if(team[2].getHP()+100>HP[2]) {
            team[preMus].setHP(HP[2]); //Da hoi phuc HP ban dau
            pause[preMus]=false;
        }
        else{
            this->team[preMus].setHP(this->team[preMus].getHP()+100); //Neu chua hoi phuc HP ban dau thi tiep tuc +100
        }
    }
    if(preMus==3 && team[3].getHP()<HP[3] && pause[3]==true) { //Aramis hoi phuc HP
        if(team[3].getHP()+50>HP[3]) {
            team[preMus].setHP(HP[3]); //Da hoi phuc HP ban dau
            pause[preMus]=false;
        }
        else{
            this->team[preMus].setHP(this->team[preMus].getHP()+50); //Neu chua hoi phuc HP ban dau thi tiep tuc +50
        }
    }
    if(this->team[mus1].getCystalPointer(chisoCystal) != NULL && pause[mus1]==false){ //Neu mus1 co cystal thich hop va ko nghi ngoi
        int* cystalPointer;
        *cystalPointer=*team[mus1].getCystalPointer(chisoCystal)-1;
        if(*cystalPointer==0) {
            manager->deallocate(team[mus1].getCystalPointer(chisoCystal));
            team[mus1].setCystalPointer(chisoCystal,NULL);
        }
        else{
            team[mus1].setCystalPointer(chisoCystal,cystalPointer);
        }
    }
    else{
        if(this->team[mus2].getCystalPointer(chisoCystal)!=NULL && pause[mus2]==false){ //Neu mus2 co cystal thich hop va khong nghi ngoi
            helpMus(mus2,mus1,chisoCystal,dungChung); //mus 1 dung chung cystal cua mus2
            helpMus(mus2,preMus,chisoCystal,dungChung); //preMus dung chung cystal cua mus3
        }
        else {
            if(this->team[mus3].getCystalPointer(chisoCystal)!=NULL && pause[mus3]==false){ //Neu mus3 co cystal thich hop va khong nghi ngoi
                helpMus(mus3,mus1,chisoCystal,dungChung); //mus1 dung chung cystal cua mus3
                helpMus(mus3,preMus,chisoCystal,dungChung); //preMus dung chung cystal cua mus3
            }
            else{
                if(mus1!=3){
                    if((-(event))%100==11){ //Neu doi thu la Quezacolt va 4 NLQ ko co cystal thich hop
                        pause[mus1]=true; //NLQ bi te liet
                    }
                    else{
                        int dam ,hp;
                        dam = (int)(-event*chisoQuai+(int)(luyThua(chisoQuai,mus1+1)*sntNhoHon(-event))%100);
                        hp=this->team[mus1].getHP()-dam;
                        if(hp<1){
                            HP=0; //Neu HP ngu lam quan giam xuong nho hon 1 thi HP=0 va ngu lam quan phai nghi
                            pause[mus1]=true;
                        }
                        this->team[mus1].setHP(hp); //Set HP cho ngu lam quan
                    }
                }
                else{
                    if(timCystal(chisoCystal,HP)==false){
                        int dam ,hp;
                        dam = (int)(-event*chisoQuai+(int)(luyThua(chisoQuai,mus1+1)*sntNhoHon(-event))%100);
                        hp=this->team[mus1].getHP()-dam;//HP bi giam 1 luong dam
                        if(hp<1){
                            hp=0; //Neu HP ngu lam quan giam xuong nho hon 1 thi HP=0 va ngu lam quan phai nghi
                            pause[mus1]=true;
                        }
                        this->team[mus1].setHP(hp); //Set HP cho ngu lam quan
                    }
                    else{
                        team[3].setHP(HP[3]);
                    }
                }          
            }
        }
    }
}
void Musketeer::attack(int preMus,int chisoCystal,float chisoQuai,bool pause[4],int event,int HP[4],bool dungChung[4][3]){
    int mus1=preMus+1; if(mus1>=4) mus1-=4; 
    int mus2=preMus+2; if(mus2>=4) mus2-=4;
    int mus3=preMus+3; if(mus3>=4) mus3-=4;
    if(this->team[preMus].getCystalPointer(chisoCystal)!=NULL){ //Ngu lam quan hien tai co cystal thich hop de chien dau
        int* cystalPointer;
        *cystalPointer=*team[preMus].getCystalPointer(chisoCystal)-1;
        if(*cystalPointer==0) {
            manager->deallocate(team[preMus].getCystalPointer(chisoCystal));
            team[preMus].setCystalPointer(chisoCystal,NULL);
        }
        else this->team[preMus].setCystalPointer(chisoCystal, cystalPointer);
    }
    else{
        if(this->team[mus1].getCystalPointer(chisoCystal)!=NULL && !pause[mus1]){ //Ngu lam quan tiep theo thu 1 co cystal thich hop de chien dau
            helpMus(mus1,preMus,chisoCystal,dungChung); //Ngu lam quan mus1 cho ngu lam quan hien tai muon cystal thich hop
        }
        else {
            if(this->team[mus2].getCystalPointer(chisoCystal)!=NULL && !pause[mus2]){ //Ngu lam quan tiep theo thu 2 co cystal thich hop de chien dau
                helpMus(mus2,preMus,chisoCystal,dungChung); //Ngu lam quan mus2 cho ngu lam quan hien tai muon cystal thich hop
            }
            else{
                if(this->team[mus3].getCystalPointer(chisoCystal)!=NULL && !pause[mus3]){ //Ngu lam quan tiep theo thu 3 co cystal thich hop de chien dau
                    helpMus(mus3,preMus,chisoCystal,dungChung); //Ngu lam quan mus3 cho ngu lam quan hien tai muon cystal thich hop
                }
                else{
                    if(-(event)%100==11){ //Neu doi thu la Quezacolt va ca 4 ngu lam quan deu khong co cystal thich hop
                        pause[preMus]=true; //Ngu lam quan bi te liet
                    }
                    else{
                        if(preMus!=3){
                            if((-(event))%100==11){ //Neu doi thu la Quezacolt va 4 NLQ ko co cystal thich hop
                                pause[preMus]=true; //NLQ bi te liet
                            }
                            else{
                                int dam ,hp;
                                dam = (int)(-event*chisoQuai+(int)(luyThua(chisoQuai,preMus+1)*sntNhoHon(-event))%100);
                                hp=this->team[preMus].getHP()-dam;
                                if(hp<1){
                                    HP=0; //Neu HP ngu lam quan giam xuong nho hon 1 thi HP=0 va ngu lam quan phai nghi
                                    pause[preMus]=true;
                                }
                                this->team[preMus].setHP(hp); //Set HP cho ngu lam quan
                            }
                        }
                        else{
                            if(!timCystal(chisoCystal,HP)){
                                int dam ,hp;
                                dam = (int)(-event*chisoQuai+(int)(luyThua(chisoQuai,preMus+1)*sntNhoHon(-event))%100);
                                hp=this->team[preMus].getHP()-dam;//HP bi giam 1 luong dam
                                if(hp<1){
                                    hp=0; //Neu HP ngu lam quan giam xuong nho hon 1 thi HP=0 va ngu lam quan phai nghi
                                    pause[preMus]=true;
                                }
                                this->team[preMus].setHP(hp); //Set HP cho ngu lam quan
                            }
                            else{
                                team[3].setHP(HP[3]);
                            }
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
    musketeers[0].setHP(999);
    musketeers[1].setHP(900);
    musketeers[2].setHP(888);
    musketeers[3].setHP(777);
    int HP[4];
    for(int i=0;i<4;i++){
        HP[i]=this->musketeers[i].getHP();
    }
    bool pause[4]; //Bien dung de xem ngu lam quan co bi te liet hay phai nghi ngoi ko
    for(int i=0;i<4;i++){
        pause[i]=false;
    }
    bool dungChung[NUM_OF_MUSKETEERS][NUM_OF_CYSTAL];
    for(int i=0;i<NUM_OF_MUSKETEERS;i++){
        for(int j=1;j<=NUM_OF_CYSTAL;j++){
            dungChung[i][j]=false;
        }
    }
    musketeers[0].setHP(999);
    musketeers[1].setHP(900);
    musketeers[2].setHP(888);
    musketeers[3].setHP(777);
    int preMus=this->firstMusketeer;
    int mus1=preMus+1; if(mus1>=4) mus1-=4;
    int mus2=preMus+2; if(mus2>=4) mus2-=4;
    int mus3=preMus+3; if(mus3>=4) mus3-=4;
    for(int i=0;i<this->numOfEvents;i++){
        if(events[i]>9 && events[i]<20){  //Nhat duoc Sapphire co level X
            int cystal=events[i]%10;
            if(this->musketeers[preMus].getCystalPointer(1)==NULL){ //Neu NLQ chua co cystal 1
                musketeers[preMus].taoCystal(cystal,preMus,1);
            }
            else{
                if(*(this->musketeers[preMus].getCystalPointer(1))<cystal){ //Level cua cystal moi lon hon level hat cu
                    musketeers[preMus].thayCystal(cystal,preMus,1,dungChung);
                }
            }

        }
        else{
            if(events[i]>19 && events[i]<30){  //Nhat duoc Emerald co level X
                int cystal=events[i]%10;
                if(this->musketeers[preMus].getCystalPointer(2)==NULL){//Neu NLQ chua co cystal 2
                    musketeers[preMus].taoCystal(cystal,preMus,2);
                }
                else{
                    if(*(this->musketeers[preMus].getCystalPointer(2))<cystal){ //Level cua cystal moi lon hon level hat cu
                        musketeers[preMus].thayCystal(cystal,preMus,2,dungChung);
                    }
                }

            }
            else{
                if(events[i]>29 && events[i]<40){  //Nhat duoc Aquamarine co level X
                    int cystal=events[i]%10;
                    if(this->musketeers[preMus].getCystalPointer(3)==NULL){ //Neu NLQ chua co cystal 3
                        musketeers[preMus].taoCystal(cystal,preMus,3);
                    }
                    else{
                        if(*(this->musketeers[preMus].getCystalPointer(3))<cystal){ //Level cua cystal moi lon hon level hat cu
                            musketeers[preMus].thayCystal(cystal,preMus,3,dungChung);
                        }
                    }

                }
                else{
                    int event=-events[i]%100;
                    switch(event){
                        case 11: //Quai vat Quezacolt tan cong
                            if(pause[preMus]==true){ //Neu NLQ hien tai bi te liet thi mus1 giup
                                if(pause[mus1]==true){ //Neu mus1 bi te liet thi mus2 giup
                                    if(pause[mus2]==true) { //Neu mus2 bi te liet thi mus3 giup
                                        musketeers[mus2].help(mus2,1,0.65f,pause,events[i],HP,dungChung); //mus3 giup mus2
                                    }
                                    else musketeers[mus1].help(mus1,1,0.65f,pause,events[i],HP,dungChung); //mus2 giup mus1
                                }
                                else musketeers[preMus].help(preMus,1,0.65f,pause,events[i],HP,dungChung); //mus1 giup preMus
                            }
                            else{
                                musketeers[preMus].attack(preMus,1,0.65f,pause,events[i],HP,dungChung); //preMus danh(neu ko co thi muon)
                            }
                            break;
                        case 12: //Quai vat Bahamut tan cong
                            if(pause[preMus]==true){
                                if(pause[mus1]==true){ //Neu mus1 bi te liet thi mus2 giup
                                    if(pause[mus2]==true) { //Neu mus2 bi te liet thi mus3 giup
                                        musketeers[mus2].help(mus2,1,0.95f,pause,events[i],HP,dungChung); //mus3 giup mus2
                                    }
                                    else musketeers[mus1].help(mus1,1,0.95f,pause,events[i],HP,dungChung); //mus2 giup mus1
                                }
                                else musketeers[preMus].help(preMus,1,0.95f,pause,events[i],HP,dungChung); //mus1 giup preMus
                            }
                            else{
                                musketeers[preMus].attack(preMus,1,0.95f,pause,events[i],HP,dungChung);
                            }
                            break;
                        case 21: //Quai vat Cerberus tan cong
                            if(pause[preMus]==true){
                                if(pause[mus1]==true){ //Neu mus1 bi te liet thi mus2 giup
                                    if(pause[mus2]==true) { //Neu mus2 bi te liet thi mus3 giup
                                        musketeers[mus2].help(mus2,2,0.85f,pause,events[i],HP,dungChung); //mus3 giup mus2
                                    }
                                    else musketeers[mus1].help(mus1,2,0.85f,pause,events[i],HP,dungChung); //mus2 giup mus1
                                }
                                else musketeers[preMus].help(preMus,2,0.85f,pause,events[i],HP,dungChung); //mus1 giup preMus
                            }
                            else{
                                musketeers[preMus].attack(preMus,2,0.85f,pause,events[i],HP,dungChung);
                            }
                            break;
                        case 22: //Quai vat Ifrit tan cong
                            if(pause[preMus]==true){
                                if(pause[mus1]==true){ //Neu mus1 bi te liet thi mus2 giup
                                    if(pause[mus2]==true) { //Neu mus2 bi te liet thi mus3 giup
                                        musketeers[mus2].help(mus2,2,0.9f,pause,events[i],HP,dungChung); //mus3 giup mus2
                                    }
                                    else musketeers[mus1].help(mus1,2,0.9f,pause,events[i],HP,dungChung); //mus2 giup mus1
                                }
                                else musketeers[preMus].help(preMus,2,0.9f,pause,events[i],HP,dungChung); //mus1 giup preMus
                            }
                            else{
                                musketeers[preMus].attack(preMus,2,0.9f,pause,events[i],HP,dungChung);
                            }
                            break;
                        case 31: //Quai vat Siren tan cong
                            if(pause[preMus]==true){
                                if(pause[mus1]==true){ //Neu mus1 bi te liet thi mus2 giup
                                    if(pause[mus2]==true) { //Neu mus2 bi te liet thi mus3 giup
                                        musketeers[mus2].help(mus2,3,0.4f,pause,events[i],HP,dungChung); //mus3 giup mus2
                                    }
                                    else musketeers[mus1].help(mus1,3,0.4f,pause,events[i],HP,dungChung); //mus2 giup mus1
                                }
                                else musketeers[preMus].help(preMus,3,0.4f,pause,events[i],HP,dungChung); //mus1 giup preMus
                            }
                            else{
                                musketeers[preMus].attack(preMus,3,0.4f,pause,events[i],HP,dungChung);
                            }
                            break;
                        case 32: //Quai vat Leviathan tan cong
                            if(pause[preMus]==true){
                                if(pause[mus1]==true){ //Neu mus1 bi te liet thi mus2 giup
                                    if(pause[mus2]==true) { //Neu mus2 bi te liet thi mus3 giup
                                        musketeers[mus2].help(mus2,3,1,pause,events[i],HP,dungChung); //mus3 giup mus2
                                    }
                                    else musketeers[mus1].help(mus1,3,1,pause,events[i],HP,dungChung); //mus2 giup mus1
                                }
                                else musketeers[preMus].help(preMus,3,1,pause,events[i],HP,dungChung); //mus1 giup preMus
                            }
                            else{
                                musketeers[preMus].attack(preMus,3,1,pause,events[i],HP,dungChung);
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
    delete[] events;
    for(int i=0;i<NUM_OF_MUSKETEERS;i++){
        musketeers[i].finalize();
    }
    delete[] musketeers;


}
/* End block: TO DO */
