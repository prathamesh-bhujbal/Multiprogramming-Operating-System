#include<bits/stdc++.h>
using namespace std;

class OS{
    private:
    char Memory[100][4];
    unsigned char R[4];
    unsigned char IR[4];
    unsigned int IC;
    bool C;
    int SI;
    char buffer[200];

    public:
    void INIT();
    void LOAD();
    void EXECUTE();
    void MOS();
    void Start();
    int OppAdd();
    void READ();
    void WRITE();
    void HALT();

    fstream inputfile;
    fstream outputfile;
};

void OS ::INIT(){
    for(int i=0;i<100;i++){
        for(int j=0;j<4;j++){
            Memory[i][j]=' ';
        }
    }
    IR[3]=' ';
    R[3]=' ';
    C = false;
    IC =0;
}
void OS:: Start(){
    IC =0;
    EXECUTE();
}
int OS::OppAdd(){
    int add = IR[2]-'0';
    add = add*10+(IR[3]-'0');
    return add;
}
void OS:: READ(){
    inputfile.getline(buffer,42);
    IR[3] ='0';
    int k =0;
    int loc = OppAdd();
    for(int l=0;l<10;l++){
        for(int j=0;j<4;j++){
            Memory[loc][j] = buffer[k];
            k++;
        }
        if (Memory[loc][0] == '$' && Memory[loc][1] == 'E' && Memory[loc][2] == 'N' && Memory[loc][3] == 'D')
            return;

        loc++;
    }
}
void OS::HALT()
{
    outputfile << "\n\n";
}

void OS::WRITE(){
    int k =0;
    IR[3]='0';
    int loc = OppAdd();
    int i=0;

    for (int l = 0; l < 10; ++l)
    {
        for (int j = 0; j < 4; ++j)
        {
            outputfile << Memory[loc][j];
            k++;
        }
        loc++;
    }
    outputfile << "\n";
}
void OS::MOS(){
    switch(SI){
        case 1:
        for(int i=0;i<=40;i++){
            buffer[i]=' ';
        }
        READ();
        break;
        
        case 2:
        WRITE();
        break;

        case 3:
        HALT();
        break;

        default:
        break;
    }
}
void OS::EXECUTE(){
    while(true){
        for(int i=0;i<4;i++){
            IR[i] = Memory[IC][i];
        }
        IC++;
        int loc = OppAdd();
        if(IR[0]=='G' && IR[1]=='D'){
            SI =1;
            MOS();
        }
        else if(IR[0]=='P' && IR[1]=='D'){
            SI=2;
            MOS();
        }
        else if(IR[0]=='H'){
            SI = 3;
            MOS();
            break;
        }
        else if(IR[0]=='L'&& IR[1]=='R'){
            for(int j=0;j<4;j++){
                R[j] = Memory[loc][j];
            }
        }
        else if(IR[0]=='S'&& IR[1]=='R'){
            for(int j=0;j<4;j++){
                Memory[loc][j] =R[j];
            }
        }
        else if(IR[0]=='C' && IR[1]=='R'){
            int count =0;
            for(int j=0;j<4;j++){
                if(Memory[loc][j] == R[j])count++;
            }
            if(count==4)C = true;
            else C = false;
        }
        else if(IR[0]=='B' && IR[1]=='T'){
            if(C){
                IC = loc;
                C=false;
            }
        }
    }
}
void OS:: LOAD(){
    cout<<"Reading Data..."<<endl;
    int x =0;
    for(int i=0;i<100;i++){
        for(int j=0;j<4;j++){
            Memory[i][j]=' ';
        }
    }
    do{
        for(int i=0;i<=100;i++){
            buffer[i]=' ';
        }
        inputfile.getline(buffer,42);

        if(buffer[0]=='$'&&buffer[1]=='A'&&buffer[2]=='M'&& buffer[3]=='J'){
            INIT();
        }
        else if(buffer[0]=='$'&&buffer[1]=='D'&&buffer[2]=='T'&& buffer[3]=='A'){
            Start();
        }
        else if(buffer[0]=='$'&&buffer[1]=='E'&&buffer[2]=='N'&&buffer[3]=='D'){
            for(int i=0;i<100;i++){
                cout<< "M["<<i<<"]\t";
                for(int j=0;j<4;j++){
                    cout<<Memory[i][j];
                }
                cout<<endl;
                if(i%10==9)cout<<endl;
            }
            cin.get();
            continue;
        }
        else{
            int k =0;
            int limit = x+10;
            for(;x<limit;++x){
                for(int j=0;j<4;j++){
                    Memory[x][j] = buffer[k];
                    k++;
                }
                if(buffer[k]==' '|| buffer[k]=='\n'){
                    break;
                }
            }
        }
    }while(!inputfile.eof());
}


int main(){

    unsigned x;
    OS os;
    cout << "Implemented by Prathamesh Bhujbal- OS:Phase-01\n";
    cout << "Press any key to continue...\n";
    cin.get();

    os.inputfile.open("input.txt",ios::in);
    os.outputfile.open("output3.txt", ios::out);

     if (!os.inputfile)
        cout << "File doesn't exist" << endl;
    else
        cout << "File Exist" << endl;

    os.LOAD();
    os.inputfile.close();
    os.outputfile.close();
    return 0;
}