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
        my_git_path += "/.mygit";

        // retrieving version number
        string version_no="";
        string version_no_file_path = my_git_path + "/version_no.txt";
        fstream version_no_file(version_no_file_path.c_str()); // .c_str() converts string to char*. It can be also done by version_no_file.open(version_no_file_path,ios::in);
        version_no_file >> version_no;
        version_no_file.close();
}