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

        cout << "copying all files from " << src_path << endl;
        vector<string> files = push_get_files(src_path);

        // creating push folder
        if (mkdir(des_path.c_str(), 0777) == -1 && errno != EEXIST)
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
}
