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


