namespace mygitmerge{
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

    vector<string> merge_get_files(string);
    string get_cwd();
    string get_sha(string);

    int merge(){
        // removes files from current working directory and move  files from push folder to current working directory
        // (if there is a conflict, then it will not remove the file from current working directory) (also
        // removes file from push after copying)

        // get the current working directory
        string cwd = get_cwd();

        // removing files from cwd
        vector<string> file_in_cwd = merge_get_files(cwd);
        for(int i=0;i<file_in_cwd.size();i++){
            string file_path = cwd + "/" + file_in_cwd[i];
            remove(file_path.c_str());
        }


        // moving files from push folder to cwd
        string push_path = cwd + "/.mygit/push";
        vector<string> file_in_push = merge_get_files(push_path);
        for(int i=0;i<file_in_push.size();i++){
            string file_path = push_path + "/" + file_in_push[i];
            string new_file_path = cwd + "/" + file_in_push[i];
            rename(file_path.c_str(),new_file_path.c_str());
            cout<< "Moving file" << file_in_push[i] << " from push folder to current working directory" << endl;

            ifstream ifile(file_path.c_str());

            string s;
            ofstream ofile(new_file_path.c_str());

            ifile.open(file_path,ios::in);
            ofile.open(new_file_path,ios::out);

            while(ifile){
                getline(ifile , s);
                ofile << s << endl;
            }

            remove(file_path.c_str());

            ifile.close();
            ofile.close();
        }
        return 0;
    }

    string get_cwd(){
        char cwd_path[PATH_MAX];
        string current_path;
        if(getcwd(cwd_path,PATH_MAX) != NULL){
            current_path = cwd_path;
        }
        else{
            perror("Unable to get current working directory");
            exit (1);
        }
        return current_path;
    }

    vector<string> merge_get_files(string path){
        vector<string> files;
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir (path.c_str())) != NULL) {
            /* print all the files and directories within directory */
            while ((ent = readdir (dir)) != NULL) {
                string file_name = ent->d_name;
                if(file_name != "." && file_name != ".."){
                    files.push_back(file_name);
                }
            }
            closedir (dir);
        } else {
            /* could not open directory */
            perror ("Unable to open directory");
            exit (1);
        }
        return files;
    

}