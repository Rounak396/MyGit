namespace mygitpull{
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
    #include <sstream>
    #include <iterator>

    using namespace std;
    
    string get_cwd();
    vector<string> pull_get_files(string);
    string get_sha(string);

    int pull(){
        // removes files from current working directory and move  files from push folder to current working directory
        // (if there is a conflict, then it will not remove the file from current working directory) (also
        // removes file from push after copying)

        // get the current working directory
        string cwd_path = get_cwd();
        string my_git_path = cwd_path ;
        my_git_path += "/.mygit/";

        // retrieving version number
        string version_no="";
        string version_no_file_path = my_git_path + "/version_no.txt";
        fstream version_no_file(version_no_file_path.c_str()); // .c_str() converts string to char*. It can be also done by version_no_file.open(version_no_file_path,ios::in);
        version_no_file >> version_no;
        version_no_file.close();

        // copy files from current working directory to pull folder
        string src_path = my_git_path + version_no;
        string des_path = my_git_path + "/pull";

        cout << "copying all files from " << src_path << endl;
        vector<string> files = pull_get_files(src_path);

        // creating pull folder
        if (mkdir(des_path.c_str(), 0777) == -1 && errno != EEXIST)
        {
            cerr << "unable to make pull directory " << strerror(errno) << endl;
            return 0;
        }
        
        // copying files from src to des
        for (int i = 0; i < files.size(); i++)
        {
            cout<<"File is getting copied: "<<files[i]<<endl;
            string src_file_path = src_path + "/" + files[i];
            string des_file_path = des_path + "/" + files[i];

            // copying files from src to des
            cout << "copying " << src_file_path << " to" << des_file_path << endl;
            ifstream src_file(src_file_path.c_str(), ios::binary);
            ofstream des_file(des_file_path.c_str(), ios::binary);
            des_file << src_file.rdbuf(); // .rdbuf() reads the entire file
            src_file.close();
            des_file.close();

            // removing files from src
            remove(src_file_path.c_str());
        }

        cout<<"All files are copied from "<<src_path<<" to "<<des_path<<endl;
        return 0;
    }

    string get_cwd(){
        // returns the current working directory
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            return cwd;
        }
        else
        {
            cerr << "unable to get current working directory " << strerror(errno) << endl;
            exit(1);  
        }
    }

    vector<string> pull_get_files(string path){
        // returns the list of files in the given path
        vector<string> files;
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir(path.c_str())) != NULL)
        {
            while ((ent = readdir(dir)) != NULL)
            {
                string file_name = ent->d_name;
                if (file_name != "." && file_name != "..")
                {
                    files.push_back(file_name);
                }
            }
            closedir(dir);
        }
        else
        {
            cerr << "unable to open directory " << strerror(errno) << endl;
            exit(1);
        }
        return files;
    }

}