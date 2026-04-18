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



