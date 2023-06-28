namespace mygitrollback{
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
    
    using namespace std;
    
    string base_path = "";
    char cwd_path[PATH_MAX];
    string mygit_path;
    string verion_no_file_path;
    string version_no;
    string indexpath;
    map<string,string> map_index;


    string get_cwd();
    map<string, string> get_map(string path);
    vector<string> get_files(string path);
    string get_sha(string);


    int rollback(){

        // gettting current working directory
        string cwd_path = get_cwd();
        string mygit_path = cwd_path + "/.mygit";

        // retrieving version number
        string version_no_file_path = mygit_path + "/version_no.txt";
        fstream version_no_file(version_no_file_path.c_str()); // .c_str() converts string to char*. It can be also done by version_no_file.open(version_no_file_path,ios::in);
        version_no_file >> version_no;
        int current_version = atoi(version_no.c_str()); // also can be done by stoi(version_no)
        
        // getting the version number to which we want to rollback
        int to_version_no = current_version - 1;
        string last_version_no = to_string(to_version_no);
    
        string current_version_path = mygit_path+version_no;
    
        indexpath = mygit_path + version_no + "/" + "index.txt";
    
        //removing the files in current version
        DIR* folder = opendir(current_version_path.c_str());
        struct dirent *next;
        string filepath;
        while ( (next = readdir(folder)) != NULL )
        {   
            filepath=current_version_path;
            filepath+= next->d_name;
            remove(filepath.c_str());
        }    
        closedir(folder);

        
    }
}