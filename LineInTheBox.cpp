#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

void output(vector<string> box, string inp){
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for(int i=0;i<box.size();i++){
        if(i==box.size()-2){
            SetConsoleTextAttribute(hConsole, 15);
                cout<<box[i][0]; 

            SetConsoleTextAttribute(hConsole, 9);
                cout<<box[i][1];
            bool swi=false;
            for(int j=2;j<box[i].size()-1;j+=2){
                if(swi){
                    SetConsoleTextAttribute(hConsole, 9);
                    cout<<box[i][j]<<box[i][j+1];
                    swi=false;
                }
                else{
                    SetConsoleTextAttribute(hConsole, 12);
                        cout<<box[i][j]<<box[i][j+1];
                    swi=true;
                }
            }
            SetConsoleTextAttribute(hConsole, 15);
                cout<<box[i][box[i].size()-1];
        }
        else{
            for(int j=0;j<box[i].size();j++){
                if(box[i][j]=='\\' || box[i][j]=='|' || box[i][j]=='/' || box[i][j]=='#'){
                    SetConsoleTextAttribute(hConsole, 10);
                        cout<<box[i][j];
                }
                else{
                    SetConsoleTextAttribute(hConsole, 15);
                        cout<<box[i][j];
                }
            }
        }
        cout<<"\n";
    }
}

void display(string inp, int* w,int* h){
    int hk=*h,wk=*w;
    vector<string> box(hk+3);    //CREATING THE BOX
    box[0].insert(0,2*wk+1,'=');    box[hk+2].insert(0,2*wk+1,'='); //first and lat rows with '='

    for(int i=1;i<hk+1;i++){    //middle of the box edges is ':'
        box[i].push_back(':');
        box[i].insert(1,2*wk-1,' ');
        box[i].push_back(':');
    }

    int temp=1; //numbers in bottom
    box[hk+1].push_back('='); 
    for(int i=0;i<2*wk-1;i++){
        if(i%2==0 || temp>9){
            string tempp=to_string(temp);
            if(tempp.size()==3){
                box[hk+1]+=tempp.substr(0,2);
                box[hk+2][i+1]=tempp[2];
            }
            else if(tempp.size()==4){
                box[hk+1]+=tempp.substr(0,2);
                box[hk+2][i+1]=tempp[2];
                box[hk+2][i+2]=tempp[3];
            }
            else{
                box[hk+1]+=tempp;
            }
            temp++;
            if(temp>9)i++;}
        else{
            box[hk+1].push_back(' ');}}
    box[hk+1].push_back('=');    //IT IS END

    if(inp=="") {
        output(box,inp);
        return;
    }
        
    int k=stoi(inp);    vector<pair<int,int>> positions;
    double hkk=hk,wkk=wk;
    for(int i=1;i<hk+1;i++){   
        int x=floor((-1*i*((double)(wkk+1)/2-k))/((double)hkk/2)+wkk+0.5);
        box[i][x]='#';
        positions.emplace_back(i,x);
    } 

    if(positions.size()==1){
        box[positions[0].first][positions[0].second]='|';
    }
    else{
        for(int i=0;i<positions.size()-1;i++){
            if(positions[i].second==positions[i+1].second) box[positions[i].first][positions[i].second]='|';
            else if(positions[i].second>positions[i+1].second) box[positions[i].first][positions[i].second]='/';
            else if(positions[i].second<positions[i+1].second) box[positions[i].first][positions[i].second]='\\';
            temp=i;
        }
        if(positions[temp+1].second==positions[temp].second) box[positions[temp+1].first][positions[temp+1].second]='|';
        else if(positions[temp+1].second>positions[temp].second) box[positions[temp+1].first][positions[temp+1].second]='\\';
        else if(positions[temp+1].second<positions[temp].second) box[positions[temp+1].first][positions[temp+1].second]='/';
    }
    output(box,inp);
}

string rig(string inp,int* w){
    while(inp!="box" && inp!="stop" && (!isdigit(inp[0]) || stoi(inp)>*w || stoi(inp)<1)){
        cout<<"Wrong input!\n";
        if(!isdigit(inp[0]) || stoi(inp)>*w || stoi(inp)<1) cout<<"Diapason is: "<<1<<'-'<<*w;
        cout<<"\nWrite again: ";
        cin>>inp;
    }
    return inp;
}

string input(int* w,int* h){
    string inp="";
    
    cout<<"Write stop for \"stop\" the program.\nIf you want to create a box write \"box\".\nInput number in diapason: 1-"<<*w<<". For draw line.\nInput: ";
    cin>>inp;
    inp=rig(inp,w);
    if(inp.substr(0,3)=="box"){
        toomuch:{}
        cout<<"Write Weight and Height with space(max size of box is 9999x2^32): ";
        cin>>*w>>*h;
        if(*w>9999){
            cout<<"It is too much!!\n";
            goto toomuch;
        }
    }
    return inp; 
}

int main(){
    string inp="";  int w=5,h=7;
    while(inp!="stop"){
        display(inp,&w,&h);
        inp = input(&w,&h);
        if(inp=="box") inp="";
    }
    cout<<"\nSoft ended.";
}