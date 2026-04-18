#include<iostream>
#include<vector>
#include<tuple>
#include<fstream>
#include<algorithm>
#include<iomanip>
using namespace std;

/*
tuple:
0 = Subject Name
1 = Marks
2 = Teacher Initial
*/

struct Student{
    string id,name;
    vector<tuple<string,double,string>> info;
};

vector<Student> students;

string fileName="student_mark.txt";
string adminPass="admin";

// ---------- Average ----------
double avg(Student s){

    double sum=0;

    for(auto x:s.info)
        sum+=get<1>(x);

    return s.info.empty()?0:sum/s.info.size();
}

// ---------- Find Student ----------
int getIndex(string key){

    for(int i=0;i<students.size();i++)
        if(students[i].id==key)
            return i;

    return -1;
}

// ---------- Save ----------
void saveFile(){

    ofstream fout(fileName);

    for(auto s:students){

        fout<<s.id<<"|"<<s.name<<"|"<<s.info.size();

        for(auto x:s.info)
            fout<<"|"
                <<get<0>(x)<<"|"
                <<get<1>(x)<<"|"
                <<get<2>(x);

        fout<<endl;
    }
}

// ---------- Load ----------
void loadFile(){

    ifstream fin(fileName);
    if(!fin) return;

    string line;

    while(getline(fin,line)){

        vector<string> data;
        string temp="";

        for(char ch:line){

            if(ch=='|'){
                data.push_back(temp);
                temp="";
            }
            else temp+=ch;
        }

        data.push_back(temp);

        if(data.size()<3) continue;

        Student s;

        s.id=data[0];
        s.name=data[1];

        int n=stoi(data[2]),idx=3;

        for(int i=0;i<n;i++){

            if(idx+2>=data.size()) break;

            string sub=data[idx++];
            double mark=stod(data[idx++]);
            string teacher=data[idx++];

            s.info.push_back(
                {sub,mark,teacher}
            );
        }

        students.push_back(s);
    }
}

// =================================================
// ADMIN PANEL
// =================================================

void addStudent(){

    Student s;
    int n;

    cout<<"\nEnter ID: ";
    cin>>s.id;

    if(getIndex(s.id)!=-1){
        cout<<"ID Already Exists!\n";
        return;
    }

    cin.ignore();

    cout<<"Enter Name: ";
    getline(cin,s.name);

    cout<<"How Many Subjects: ";
    cin>>n;

    for(int i=1;i<=n;i++){

        string sub,teach;

        cin.ignore();

        cout<<"\nSubject "<<i<<" Name    : ";
        getline(cin,sub);

        cout<<"Teacher Initial : ";
        getline(cin,teach);

        s.info.push_back(
            {sub,0,teach}
        );
    }

    students.push_back(s);
    saveFile();

    cout<<"\nStudent Added Successfully!\n";
}

void showAll(){

    if(students.empty()){
        cout<<"No Data Found!\n";
        return;
    }

    cout<<"\n========== ALL STUDENTS ==========\n";

    for(auto s:students){

        cout<<"\nID   : "<<s.id;
        cout<<"\nName : "<<s.name;
        cout<<"\nSubjects:\n";

        for(auto x:s.info)
            cout<<"   "
                <<setw(15)<<left
                <<get<0>(x)
                <<get<1>(x)
                <<" ("
                <<get<2>(x)
                <<")\n";

        cout<<"Average : "
            <<fixed<<setprecision(2)
            <<avg(s)<<endl;

        cout<<"---------------------------------\n";
    }
}

void searchStudent(){

    string id;
    cout<<"Enter ID: ";
    cin>>id;

    int idx=getIndex(id);

    if(idx==-1){
        cout<<"Not Found!\n";
        return;
    }

    Student s=students[idx];

    cout<<"\nID   : "<<s.id;
    cout<<"\nName : "<<s.name;
    cout<<"\nSubjects:\n";

    for(auto x:s.info)
        cout<<"   "
            <<setw(15)<<left
            <<get<0>(x)
            <<get<1>(x)
            <<" ("
            <<get<2>(x)
            <<")\n";

    cout<<"Average : "<<avg(s)<<endl;
}

void deleteStudent(){

    string id;
    cout<<"Enter ID: ";
    cin>>id;

    int idx=getIndex(id);

    if(idx==-1){
        cout<<"Not Found!\n";
        return;
    }

    students.erase(students.begin()+idx);
    saveFile();

    cout<<"Deleted Successfully!\n";
}

void sortStudent(){

    sort(students.begin(),students.end(),
        [](Student a,Student b){
            return avg(a)>avg(b);
        });

    showAll();
}
// ---------- Update Student ----------
void updateStudent(){

    string id;
    cout<<"Enter Student ID: ";
    cin>>id;

    int idx=getIndex(id);

    if(idx==-1){
        cout<<"Student Not Found!\n";
        return;
    }

    int ch;

    do{
        cout<<"\n====== UPDATE STUDENT ======\n";
        cout<<"1. Change Name\n";
        cout<<"2. Change ID\n";
        cout<<"3. Change Subject Name\n";
        cout<<"4. Change Teacher Initial\n";
        cout<<"5. Add New Subject\n";
        cout<<"0. Back\n";
        cout<<"Choice: ";
        cin>>ch;

        // 1 Change Name
        if(ch==1){

            cin.ignore();

            cout<<"Enter New Name: ";
            getline(cin,students[idx].name);

            saveFile();
            cout<<"Name Updated!\n";
        }

        // 2 Change ID
        else if(ch==2){

            string newID;

            cout<<"Enter New ID: ";
            cin>>newID;

            if(getIndex(newID)!=-1){
                cout<<"ID Already Exists!\n";
            }
            else{
                students[idx].id=newID;
                saveFile();
                cout<<"ID Updated!\n";
            }
        }

        // 3 Change Subject Name
        else if(ch==3){

            for(int i=0;i<students[idx].info.size();i++)
                cout<<i+1<<". "
                    <<get<0>(students[idx].info[i])
                    <<endl;

            int op;
            cout<<"Choose Subject: ";
            cin>>op;

            if(op>=1 && op<=students[idx].info.size()){

                string sub;
                cin.ignore();

                cout<<"Enter New Subject Name: ";
                getline(cin,sub);

                get<0>(students[idx].info[op-1])=sub;

                saveFile();
                cout<<"Subject Updated!\n";
            }
        }

        // 4 Change Teacher Initial
        else if(ch==4){

            for(int i=0;i<students[idx].info.size();i++)
                cout<<i+1<<". "
                    <<get<0>(students[idx].info[i])
                    <<" ("
                    <<get<2>(students[idx].info[i])
                    <<")\n";

            int op;
            cout<<"Choose Subject: ";
            cin>>op;

            if(op>=1 && op<=students[idx].info.size()){

                string ini;
                cout<<"Enter New Initial: ";
                cin>>ini;

                get<2>(students[idx].info[op-1])=ini;

                saveFile();
                cout<<"Teacher Initial Updated!\n";
            }
        }

        // 5 Add New Subject
        else if(ch==5){

            string sub,ini;

            cin.ignore();

            cout<<"Enter Subject Name: ";
            getline(cin,sub);

            cout<<"Enter Teacher Initial: ";
            getline(cin,ini);

            students[idx].info.push_back(
                {sub,0,ini}
            );

            saveFile();
            cout<<"New Subject Added!\n";
        }

    }while(ch!=0);
}

void adminPanel(){

    string pass;

    cout<<"\nEnter Admin Password: ";
    cin>>pass;

    if(pass!=adminPass){
        cout<<"Wrong Password!\n";
        return;
    }

    int ch;

    do{
        cout<<"\n========== ADMIN PANEL ==========\n";
        cout<<"1. Add Student\n";
        cout<<"2. Show All Students\n";
        cout<<"3. Search Student\n";
        cout<<"4. Delete Student\n";
        cout<<"5. Sort By Average\n";
        cout<<"6. Update student\n";
        cout<<"0. Back\n";
        cout<<"Choice: ";
        cin>>ch;

        switch(ch){

            case 1:addStudent(); break;
            case 2:showAll(); break;
            case 3:searchStudent(); break;
            case 4:deleteStudent(); break;
            case 5:sortStudent(); break;
            case 6:updateStudent(); break;
        }

    }while(ch!=0);
}

// =================================================
// FACULTY PANEL
// =================================================

void facultyPanel(){

    string ini,pass;

    cout<<"\nEnter Faculty Initial : ";
    cin>>ini;

    cout<<"Enter Password        : ";
    cin>>pass;

    if(pass!=ini+to_string(123)){
        cout<<"Wrong Password!\n";
        return;
    }

    int ch;

    do{
        cout<<"\n========== FACULTY PANEL ==========\n";
        cout<<"Login As : "<<ini<<endl;
        cout<<"1. Add / Update Marks\n";
        cout<<"2. Show My Students\n";
        cout<<"3. Ranking\n";
        cout<<"4. pass student\n";
        cout<<"5. Failed student\n";
        cout<<"0. Back\n";
        cout<<"Choice: ";
        cin>>ch;

        // 1.Add Marks
        if(ch==1){

            string id;
            cout<<"Enter Student ID: ";
            cin>>id;

            int idx=getIndex(id);

            if(idx==-1){
                cout<<"Student Not Found!\n";
                continue;
            }

            bool found=false;

            for(auto &x:students[idx].info){

                if(get<2>(x)==ini){

                    cout<<get<0>(x)
                        <<" Marks: ";

                    cin>>get<1>(x);

                    if(get<1>(x)<0 ||
                       get<1>(x)>100){

                        cout<<"Invalid Marks!\n";
                        break;
                    }

                    found=true;
                }
            }

            if(found){
                saveFile();
                cout<<"Marks Updated!\n";
            }
            else cout<<"No Subject Assigned!\n";
        }

        // 2.Show My Students
        else if(ch==2){
            cout<<"\nAssigned Students:\n";

            for(auto s:students)
                for(auto x:s.info){
                    if(get<2>(x)==ini)
                        cout<<setw(20)<<left
                            <<s.name
                            <<" "
                            <<'\n'<< "Mark: "
                            <<get<1>(x)
                            <<endl;
                }
        }

        // 3.Ranking
        else if(ch==3){

            vector<pair<string,double>> list;
            string sub="";

            for(auto s:students)
                for(auto x:s.info)
                    if(get<2>(x)==ini){

                        list.push_back(
                            {s.name,get<1>(x)}
                        );

                        sub=get<0>(x);
                    }

            sort(list.begin(),list.end(),
                [](auto a,auto b){
                    return a.second>b.second;
                });

            cout<<"\n===== "<<sub<<" Ranking =====\n";

            for(int i=0;i<list.size();i++)
                cout<<i+1<<". "
                    <<setw(30)<<left
                    <<list[i].first
                    <<"Mark:"
                    <<list[i].second
                    <<endl;
        }
         // 4 Pass List
        else if(ch==4){
            cout<<"\n===== Pass Student List =====\n";

            bool found=false;

            for(auto s:students)
                for(auto x:s.info)
                    if(get<2>(x)==ini &&
                       get<1>(x)>=40){

                            cout<<setw(30)<<left
                            <<s.name
                            <<"Mark:"
                            <<get<1>(x)
                            <<endl;

                        found=true;
                    }

            if(!found)
                cout<<"No Pass Student Found!\n";
        }

        // 5 Fail List
        else if(ch==5){
            cout<<"\n===== Fail Student List =====\n";

            bool found=false;

            for(auto s:students)
                for(auto x:s.info)
                    if(get<2>(x)==ini &&
                       get<1>(x)<40){

                        cout<<setw(30)<<left
                            <<s.name
                            <<"Mark:"
                            <<get<1>(x)
                            <<endl;

                        found=true;
                    }

            if(!found)
                cout<<"No Fail Student Found!\n";
        }

    }while(ch!=0);
}

// =================================================
// STUDENT PANEL
// =================================================

void studentPanel(){

    string id;
    cout<<"\nEnter Student ID: ";
    cin>>id;

    int idx=getIndex(id);

    if(idx==-1){
        cout<<"Invalid ID!\n";
        return;
    }

    int ch;

    do{
        cout<<"\n========== STUDENT PANEL ==========\n";
        cout<<"Welcome, "<<students[idx].name<<endl;
        cout<<"1. Show My Result\n";
        cout<<"2. Subject Performance\n";
        cout<<"0. Back\n";
        cout<<"Choice: ";
        cin>>ch;

        Student s=students[idx];

        if(ch==1){

            cout<<"\nID   : "<<s.id;
            cout<<"\nName : "<<s.name;
            cout<<"\nSubjects:\n";

            for(auto x:s.info)
                cout<<"   "
                    <<setw(15)<<left
                    <<get<0>(x)
                    <<get<1>(x)
                    <<endl;

            cout<<"Average : "<<avg(s)<<endl;
        }

        else if(ch==2){

            string best="",low="";
            double mx=-1,mn=101;

            for(auto x:s.info){

                if(get<1>(x)>mx){
                    mx=get<1>(x);
                    best=get<0>(x);
                }

                if(get<1>(x)<mn){
                    mn=get<1>(x);
                    low=get<0>(x);
                }
            }

            cout<<"\nHighest Subject : "
                <<best<<" = "<<mx<<endl;

            cout<<"Lowest Subject  : "
                <<low<<" = "<<mn<<endl;
        }

    }while(ch!=0);
}

// =================================================
// MAIN
// =================================================

int main(){

    loadFile();

    int ch;

    do{
        cout<<"\n====================================\n";
        cout<<"   STUDENT MARK ORGANIZER SYSTEM\n";
        cout<<"====================================\n";
        cout<<"1. Admin Panel\n";
        cout<<"2. Faculty Panel\n";
        cout<<"3. Student Panel\n";
        cout<<"0. Exit\n";
        cout<<"------------------------------------\n";
        cout<<"Enter Choice: ";
        cin>>ch;

        switch(ch){

            case 1:adminPanel(); break;
            case 2:facultyPanel(); break;
            case 3:studentPanel(); break;
            case 0:cout<<"Program Ended.\n"; break;
            default:cout<<"Invalid Choice!\n";
        }

    }while(ch!=0);

    return 0;
}


