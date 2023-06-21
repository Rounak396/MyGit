namespace mygitlog{
    #include <iostream>
    #include <string>
    #include <unistd.h>
    #include <stdio.h>
    #include <limits.h>
    #include <dirent.h>
    #include <sys/types.h>
    #include <fcntl.h>
    #include <errno.h>
    #include <time.h>
    #include <vector>
    #include <map>
    #include <fstream>
    #include <algorithm>
    #include <sys/stat.h>


    using namespace std;


    string log_path;
    string get_cwd();
    string get_sha(string);
    vector<string> get_files(string);
    string convert_to_sha(string);
    string currenttime();

    void log_print(){
        log_path = get_cwd(); // get_cwd() returns the absolute path of the current working directory
        log_path += "/.mygit/log.txt"; //path is goto .mygit and then log.txt file
        string version_no_path = get_cwd() + "/.mygit/version_no.txt";

        string s;
        ifstream ifile(log_path.c_str()); // log_path.c_str() converts the string log_path to a const char* which is the required argument for ifstream constructor.
        ifstream ifile(version_no_path.c_str()); // ifstream is used to read from files. Here ifile is the object of ifstream class. version_no_path.c_str() converts the string version_no_path to a const char* which is the required argument for ifstream constructor.
        int version;
        ifile >> version;

        ifile.open(log_path,ios::in);//open log file by providing its path in read mode

        while(ifile){
           getline(ifile , s);//read it line by line
           cout<<s<<endl;//print it line by line
        } 

        ifile.close();//close the file
    }


    void log_write(){
        log_path = get_cwd();
        log_path += "/.mygit/log.txt"; //path is goto .mygit and then log.txt file
        string version_no_path = get_cwd() + "/.mygit/version_no.txt";

        string s;
        ifstream ifile(log_path.c_str()); // log_path.c_str() converts the string log_path to a const char* which is the required argument for ifstream constructor.
        ifstream ifile(version_no_path.c_str()); // ifstream is used to read from files. Here ifile is the object of ifstream class. version_no_path.c_str() converts the string version_no_path to a const char* which is the required argument for ifstream constructor.
        int version;
        ifile >> version;

        ifile.open(log_path,ios::in);//open log file by providing its path in read mode
        while(ifile){
           getline(ifile , s);//read it line by line
           cout<<s<<endl;//print it line by line
        } 

        ifile.close();//close the file

        string commit_message;
        cout << "Enter commit message: ";
        getline(cin, commit_message);

        ofstream ofile(log_path, ios::app); // ios::app is used to append to the file. Here ofile is the object of ofstream class. log_path.c_str() converts the string log_path to a const char* which is the required argument for ofstream constructor.
        ofile << "commit " << version << endl;
        ofile << "Author: " << get_sha("user.name") << endl;
        ofile << "Date: " << currenttime() << endl;
        ofile << endl;
        ofile << "    " << commit_message << endl;
        ofile << endl;
        ofile.close();

        cout << "Commit successful" << endl;
    }


    string currenttime(){
        time_t current_time;
        current_time = time(NULL);
        tm *tm_local = localtime(&current_time);
        string time ="";
        string timehour =  to_string(tm_local->tm_hour);
        string timemin = to_string(tm_local->tm_min);
        string timesec = to_string(tm_local->tm_sec);
        time += timehour+":"+timemin + ":"+timesec;
        return time;//returning the current time

    }

    string get_cwd(){
       char cwd_path[PATH_MAX]; 
       string current_path;
       if (getcwd(cwd_path, sizeof(cwd_path)) != NULL)  current_path = cwd_path;
    
       else{
            perror("unable to get current working directory");
            exit(1);
       }
       return current_path;
    }

}
    