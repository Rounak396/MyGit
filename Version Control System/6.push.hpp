namespace mygitpush{
    
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
    vector<string> push_get_files(string);
    string get_sha(string);

    int push(){
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

        // copy files from current working directory to push folder
        string src_path = cwd_path;
        string des_path = my_git_path + "/push";

        cout << "copying all files from " << src_path <<"to "<< des_path<< endl;
        vector<string> files = push_get_files(src_path);

        // creating push folder
        if (mkdir(des_path.c_str(), 0777) == -1 && errno != EEXIST) // des_path.c_str() converts the destination path from string to char*
                                                                    // 0777 is the permission for the folder
                                                                    // 1. mkdir(des_path.c_str(), 0777) == -1 means that the directory is not created
                                                                    // 2. errno != EEXIST means that the directory doesn't exist
                                                                    // 3. The code is executed when the directory doesn't exist and the directory is not created */
        {
            cerr << "unable to make push directory " << strerror(errno) << endl;
            return 0;
        }
        
        // copying files from src to des
        for (int i = 0; i < files.size(); i++)
        {
            cout<<"File is getting copied: "<<files[i]<<endl;
            string src_file_path = src_path + "/" + files[i];
            string des_file_path = des_path + "/" + files[i];
            ifstream src_file(src_file_path.c_str());
            ofstream des_file(des_file_path.c_str());
            des_file << src_file.rdbuf();
            src_file.close();
            des_file.close();
        }

        // removing files from current working directory
        for (int i = 0; i < files.size(); i++)
        {
            string file_path = src_path + "/" + files[i];
            if (remove(file_path.c_str()) != 0)
            {
                cerr << "unable to remove file " << strerror(errno) << endl;
                return 0;
            }
        }

        // removing files from push folder
        for (int i = 0; i < files.size(); i++)
        {
            string file_path = des_path + "/" + files[i];
            if (remove(file_path.c_str()) != 0)
            {
                cerr << "unable to remove file " << strerror(errno) << endl;
                return 0;
            }
        }
    }

    string get_cwd(){
        char cwd_path [PATH_MAX] ; 
        string current_path;
        if (getcwd(cwd_path, sizeof(cwd_path)) != NULL)
        {
            current_path = cwd_path;
        }
        else
        {
            perror("unable to get current working directory");
            exit(1);
        }
    return current_path;
}

    vector<string> push_get_files(string path){
        // returns the list of files in the given path
        vector<string> files;
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir(path.c_str())) != NULL)
        {
            while ((ent = readdir(dir)) != NULL)
            {
                string file_name = ent->d_name;
                if (file_name == "." || file_name == ".." || file_name == ".mygit" || file_name == "a.out" || file_name == ".vscode" || file_name=="mygit" || file_name=="1.add.cpp" || file_name=="2.commit.cpp" || file_name=="3.log.cpp" || file_name=="4.merge.cpp" || file_name=="5.pull.cpp" || file_name=="6.push.cpp" || file_name=="7.rollback.cpp" ||  file_name=="8.status.hpp" || file_name=="9.mygit.cpp" || file_name=="mygit" || file_name=="pull" || file_name=="push" )
                {
                    continue;
                }
                else
                {
                    files.push_back(file_name);
                }
            }
            closedir(dir);
        }
        else
        {
            perror("unable to open directory");
            exit(1);
        }
        return files;
    }

    string get_sha(string file_path){
        // returns the sha of the given file
        string sha;
        string command = "sha1sum " + file_path + " > temp.txt";
        system(command.c_str());
        ifstream temp_file("temp.txt");
        temp_file >> sha;
        temp_file.close();
        remove("temp.txt");
        return sha;
    }


}
