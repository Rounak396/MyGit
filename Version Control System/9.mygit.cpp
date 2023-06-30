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
#include <sstream>
#include <map>


#include "1.add.cpp"
#include "2.commit.cpp"
#include "3.log.cpp"
#include "4.merge.cpp"
#include "5.pull.cpp"
#include "6.push.cpp"
#include "7.rollback.cpp"
#include "8.status.cpp"


using namespace std;
using namespace mygitadd;
using namespace mygitCommit;
using namespace mygitlog;
using namespace mygitmerge;
using namespace mygitpull;
using namespace mygitpush;
using namespace mygitrollback;
using namespace mygitstatus;


int init();
string retrieve_version_no();
void retrieve_sha(string , string );
void retrieve_filename(string , string );



int main(int argc, char* argv[]){
    
    string str;
    char * p=argv[1];
    str=p;

    if (str == "init"){    
        if (init() == 0)
        {
            string s = "Mygit successfully initialised!!";
            mygitlog::log_write(s);
            cout << s << endl;
            exit(EXIT_SUCCESS);
        }
        else
        {
            string s = "Error in initialisation!!";
            mygitlog::log_write(s);
            cout << s << endl;
            exit(EXIT_SUCCESS);
        }
    }

    else if (str == "add"){
        if (argc == 3)
        {
            string s = "File added successfully!!";
            mygitlog::log_write(s);
            cout << s << endl;
            add(argv[2]);
            exit(EXIT_SUCCESS);
        }
        else
        {
             string s = "Error in adding file!!";
            mygitlog::log_write(s);
            cout << s << endl;
            exit(EXIT_SUCCESS);
        }
    }

    else if (str == "commit"){
        if (argc == 3)
        {
            string s = "Commit successful!!";
            mygitlog::log_write(s);
            cout << s << endl;
            commit(argv[2]);
            exit(EXIT_SUCCESS);
        }
        else
        {
            string s = "Error in commit!!";
            mygitlog::log_write(s);
            cout << s << endl;
            exit(EXIT_SUCCESS);
        }
    }

    else if (str == "log"){
        if (argc == 2)
        {
            string s = "Log successful!!";
            mygitlog::log_write(s);
            cout << s << endl;
            log();
            exit(EXIT_SUCCESS);
        }
        else
        {
            string s = "Error in log!!";
            mygitlog::log_write(s);
            cout << s << endl;
            exit(EXIT_SUCCESS);
        }
    }

    else if (str == "merge"){
        if (argc == 3)
        {
            string s = "Merge successful!!";
            mygitlog::log_write(s);
            cout << s << endl;
            merge(argv[2]);
            exit(EXIT_SUCCESS);
        }
        else
        {
            string s = "Error in merge!!";
            mygitlog::log_write(s);
            cout << s << endl;
            exit(EXIT_SUCCESS);
        }
    }

    else if (str == "pull"){
        if (argc == 3)
        {
            string s = "Pull successful!!";
            mygitlog::log_write(s);
            cout << s << endl;
            pull(argv[2]);
            exit(EXIT_SUCCESS);
        }
        else
        {
            string s = "Error in pull!!";
            mygitlog::log_write(s);
            cout << s << endl;
            exit(EXIT_SUCCESS);
        }
    }

    else if (str == "push"){
        if (argc == 3)
        {
            string s = "Push successful!!";
            mygitlog::log_write(s);
            cout << s << endl;
            push(argv[2]);
            exit(EXIT_SUCCESS);
        }
        else
        {
            string s = "Error in push!!";
            mygitlog::log_write(s);
         cout << s << endl;
            exit(EXIT_SUCCESS);
        }
    }

    else if (str == "rollback"){
        if (argc == 3)
        {
            string s = "Rollback successful!!";
            mygitlog::log_write(s);
            cout << s << endl;
            rollback(argv[2]);
            exit(EXIT_SUCCESS);
        }
        else
        {
            string s = "Error in rollback!!";
            mygitlog::log_write(s);
            cout << s << endl;
            exit(EXIT_SUCCESS);
        }
    }

    else if (str == "status"){
        if (argc == 2)
        {
            string s = "Status successful!!";
            mygitlog::log_write(s);
            cout << s << endl;
            status();
            exit(EXIT_SUCCESS);
        }
        else
        {
            string s = "Error in status!!";
            mygitlog::log_write(s);
            cout << s << endl;
            exit(EXIT_SUCCESS);
        }
    }

    else if (str== "retrieve_version_no"){
        if (argc == 2)
        {
            string s = "Version number retrieved successfully!!";
            mygitlog::log_write(s);
            cout << s << endl;
            retrieve_version_no();
            exit(EXIT_SUCCESS);
        }
        else
        {
            string s = "Error in retrieving version number!!";
            mygitlog::log_write(s);
            cout << s << endl;
            exit(EXIT_SUCCESS);
        }
    }

    else if (str== "retrieve_sha"){
        if (argc == 4)
        {
            string s = "SHA retrieved successfully!!";
            mygitlog::log_write(s);
            cout << s << endl;
            retrieve_sha(argv[2],argv[3]);
            exit(EXIT_SUCCESS);
        }
        else
        {
            string s = "Error in retrieving SHA!!";
            mygitlog::log_write(s);
            cout << s << endl;
            exit(EXIT_SUCCESS);
        }
    }

    else if (str== "retrieve_filename"){
        if (argc == 4)
        {
            string s = "Filename retrieved successfully!!";
            mygitlog::log_write(s);
            cout << s << endl;
            retrieve_filename(argv[2],argv[3]);
            exit(EXIT_SUCCESS);
        }
        else
        {
            string s = "Error in retrieving filename!!";
            mygitlog::log_write(s);
            cout << s << endl;
            exit(EXIT_SUCCESS);
        }
    }
        
    else{
        cout  << str << " is not a git command. " << endl;
        cout   << "These are common Git commands :"<<endl;
        cout << "1.) ./mygit init \n2.) ./mygit status\n3.) ./mygit add\n4.) ./mygit commit\n5.) ./mygit log\n6.) ./mygit rollback\n7.) ./mygit pull\n8.) ./mygit push\n9.) ./mygit merge\n10.) ./mygit retrieve_version_no\n11.) ./mygit retrieve_sha filename version_no\n12.) ./mygit retrieve_filename sha version_no\n" << endl;  
    }

    return 0;
}


int init(){
    bool createmygitdir = false,chdirmygit = false,createversion0dir = false,chdirversion0 = false,createindexversion0 = false;
    
    //getting current version directory
    string current_path = mygitstatus::get_cwd();


    //create .mygit folder
    if (mkdir(".mygit", 0777) == -1)
    {   
        cerr <<  strerror(errno) << endl;
        //display error in making .git folder
        return 0;
    }
    else
    {
        createmygitdir = true;
        // .Mygit directory created
    }

    if (chdir(".mygit") == -1)
    {
        cerr <<  strerror(errno) << endl;
        //display error in changing directory to .mygit
        
        return 0;
    }
    else
    {
        chdirmygit = true;
        // Moved to .mygit directory!!;
    }

    //make version_no.txt file
    ofstream fout;
    fout.open("version_no.txt", ios::out);
    if (fout)
    {
        string num = "0";//initially version no is 0;
        fout << num << endl;
    }
    fout.close();

    //make log.txt file
    ofstream fout2;
    fout2.open("log.txt", ios::out);
    fout2.close();


    if (mkdir("0", 0777) == -1)
    {
        cerr << strerror(errno) << endl;//display error in creating 0 version
        return 0;
    }
    else
    {
        createversion0dir = true;
        // 0 version folder created
    }

    if (chdir("0") == -1)
    {
        cerr << strerror(errno) << endl;//display error in changing to 0 version folder
        return 0;
    }
    else
    {
        chdirversion0 = true;
        // Moved to 0 version folder
    }

    //  create 0 version index file;
    ofstream fout3;
    fout3.open("index.txt");
    createindexversion0 = true;
    fout3.close();


    //return to .mygit folder
    string path = current_path + "/.mygit";
    if (chdir(path.c_str()) == -1)
    {
        cerr << strerror(errno) << endl;
        return 0;
    }

    //create a base folder
    if (mkdir("base", 0777) == -1)
    {
        cerr <<  strerror(errno) << endl;//display error in creating base folder
        return 0;
    }

    if (chdir("base") == -1)
    {
        cerr << strerror(errno) << endl;
        return 0;
    }


    //now transfer all the file from current path to this base folder
    vector<string> v = mygitstatus::get_files(current_path);
    for (int i = 0; i < v.size(); i++)
    {
        string file = v[i];
        string s = current_path + "/" + file;

        //geting current working directory
        string base_path = mygitstatus::get_cwd();;
        string path = base_path + "/" + file;

        //copy files from cwd_path to base
        ifstream fin;
        ofstream fout;

        fin.open(s, ios::in);//open that file in current path to read
        fout.open(path, ios::out);//open that file in base to write

        string line;

        while (fin)
        {
            getline(fin, line);//reading line by line
            fout << line << endl;//writing line by line
        }
        fin.close();
        fout.close();
        //files copied from cwd to base
    }

    path = current_path + "/.mygit";//return to .mygit folder
    if (chdir(path.c_str()) == -1)
    {
        cerr << strerror(errno) << endl;
        return 0;
    }
    
    //if everything is done then init is successfull
    if (createmygitdir && chdirmygit && createversion0dir && chdirversion0 && createindexversion0)
        return 1;
    else
        return 0;
};


string retrieve_version_no()
{   
    //getting current working directory
    string cwd_path = mygitstatus::get_cwd();
    string mygit_path = cwd_path + "/.mygit/";

    //reading version_no file to get current version number
    string version_no_file_path = mygit_path + "version_no.txt";
    fstream version_no_file(version_no_file_path, std::ios_base::in);
    string version_no;
    version_no_file >> version_no;
    version_no_file.close();

    return (version_no);
}


void retrieve_sha(string filename, string version_no)
{   
    //getting current working directory
    string cwd_path = mygitstatus::get_cwd();
    string mygit_path = cwd_path + "/.mygit/";
    
    string version_no_file_path = mygit_path + version_no + "/index.txt";
    
    map<string, string> files = mygitstatus::get_map(version_no_file_path);

    string sha = "";
    //retrieving sha of given file
    for (auto it : files)
    {
        if (it.first == filename)
        {
            sha = it.second;
            break;
        }
    }
    if (sha == "")
    {
        cout << "file with given filename not found in the given version...unable to retrieve sha" << endl;
    }
    else
    {
        cout <<"sha : "<< sha << endl;
    }
}


void retrieve_filename(string sha, string version_no)
{   
    //getting current working directory
    string cwd_path = mygitstatus::get_cwd();
    string mygit_path = cwd_path + "/.mygit/";
    
    string version_no_file_path = mygit_path + version_no + "/index.txt";
    
    map<string, string> files = mygitstatus::get_map(version_no_file_path);


    string filename = "";
    //retrieving filename of given file
    for (auto it : files)
    {
        if (it.second == sha)
        {
            filename = it.first;
            break;
        }
    }
    if (filename == "")
    {
        cout << "file with given sha not found in the given version...unable to retrieve filename" << endl;
    }
    else
    {
        cout << "filename : "<< filename << endl;
    }
}