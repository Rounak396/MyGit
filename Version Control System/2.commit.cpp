namespace mygitCommit{
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


        using namespace std;

        #include <sys/stat.h> // added header file
        #include <algorithm>

        vector<string> get_files(string);
        string get_cwd();
        string get_sha(string);

        int commit(){
             string cwd = get_cwd();
        
        string version_no_path = cwd + "/.mygit/version_no.txt";

        //read current version no
        ifstream ifile(version_no_path.c_str());
        int version;
        ifile >> version;

        //new version
        version = version + 1;
        ifile.close();
        //write new version no 

        ofstream ofile(version_no_path, ios::trunc);
        ofile << version;

        //in mygit create a new version folder
        string newDir = cwd + "/.mygit/";
        newDir = newDir + to_string(version);
        int check = mkdir(newDir.c_str(), 0777);
        if (!check)
            printf("New version created\n");
        else
        {
            printf("Unable to create new version\n");
            exit(1);
        }
        
        //copy all files to new version from older version
        string cmd = "cp -r"; //  creates a string cmd which contains the copy command
        cmd = cmd + " " + cwd + "/.mygit/"; // adds the absolute path to the .mygit directory
        int x = version - 1; // x is the previous version
        cmd = cmd + to_string(x); // adds the previous version to the command
        cmd = cmd + "/. "; 
        cmd = cmd + cwd + "/.mygit/"; // adds the absolute path to the .mygit directory
        cmd = cmd + to_string(version); 
        cout << cmd << endl; 
        system(cmd.c_str());

        string base_path = cwd + "/.mygit/base/";
        vector<string> files = get_files(cwd); 
        for (int i = 0; i < files.size(); i++)
        {   //diff base_path/file file >> cwd/.mygit/lastversion/file.patch
            //diff btw base file and version file and create patch
            string diff_cmd = "diff " + base_path + files[i];
            diff_cmd = diff_cmd + " " + files[i];
            diff_cmd = diff_cmd + " >> " + cwd + "/.mygit/" + to_string(version - 1) + "/" + files[i] + ".patch";
            system(diff_cmd.c_str());
            
        }

        //remove files after creating patch for it
        for (int i = 0; i < files.size(); i++)
        {
            if(files[i] != "index.txt"){
            string rm_cmd = "rm ";
            rm_cmd = rm_cmd + cwd + "/.mygit/" + to_string(version - 1) + "/" + files[i];
            system(rm_cmd.c_str());
            
            }
        }
      
        cout<<"successfully committed previous version and moved to new version"<<endl;
        return 0;
        }

        string get_cwd()
        {
            char cwd[PATH_MAX];
            if (getcwd(cwd, sizeof(cwd)) != NULL)
            {
                return string(cwd);
            }
            else
            {
                perror("unable to get current working directory");
                return string("");
            }
        }

        vector<string> get_files(string cwd)
        {
            vector<string> files;
            DIR *dir;
            struct dirent *ent;
            if ((dir = opendir(cwd.c_str())) != NULL)
            {
                while ((ent = readdir(dir)) != NULL)
                {
                    string file_name = string(ent->d_name);
                    if (file_name == "." || file_name == ".." || file_name == ".mygit" || file_name == "a.out" || file_name == ".vscode" || file_name=="mygit" || file_name=="1.add.cpp" || file_name=="2.commit.cpp" || file_name=="3.log.cpp" || file_name=="4.merge.cpp" || file_name=="5.pull.cpp" || file_name=="6.push.cpp" || file_name=="7.rollback.cpp" ||  file_name=="8.status.hpp" || file_name=="9.mygit.cpp" || file_name=="mygit" || file_name=="pull" || file_name=="push" )
                    {
                        files.push_back(file_name);
                    }
                }
                closedir(dir);
            }
            else
            {
                perror("opendir() error");
            }
            return files;
        }

        string get_sha(string file_name)
        {
            string cmd = "sha1sum " + file_name + " > temp.txt";
            system(cmd.c_str());
            ifstream ifile("temp.txt");
            string sha;
            ifile >> sha;
            ifile.close();
            cmd = "rm temp.txt";
            system(cmd.c_str());
            return sha;
        }

}
