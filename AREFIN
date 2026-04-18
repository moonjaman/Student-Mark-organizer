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





