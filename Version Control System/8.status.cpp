namespace mygitstatus{

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

    string get_sha(string);
    
    vector<string> get_files(string);
    map<string, string> get_map(string);
    string get_cwd();

    int status()
    {
        string cwd_path = get_cwd();
        string mygit_path = cwd_path + "/.mygit/";

        vector<string> files = get_files(cwd_path); //store all files of cwd into a vector
        int n = files.size();

        string version_file_path = mygit_path;
        version_file_path += "version_no.txt"; //goto version no.txt file

        fstream version_no_file(version_file_path, std::ios_base::in);
        string version_no;
        version_no_file >> version_no; //store the version no from version.txt file
        version_no_file.close();

        string index_path = mygit_path + version_no; //goto current version folder
        index_path = index_path + "/index.txt";      //goto index.txt file

        map<string, string> map_index = get_map(index_path); //store the contents of index file in a map

        vector<string> newfiles;
        vector<string> deletedfiles;
        vector<string> modifiedfiles;

        map<string, string> map_cwd; //create a map for cwd files(storing filename:sha)

        for (int i = 0; i < n; i++)
        {
            string sha = get_sha(files[i]);
            map_cwd[files[i]] = sha;
        }
        for (int i = 0; i < n; i++)
        {
            string sha = get_sha(files[i]);
            if (map_index.find(files[i]) == map_index.end()) //file exist in cwd map but not in index map
            {
                newfiles.push_back(files[i]);
            }
            else if (map_index[files[i]] != sha) //sha of same file name dosent match
            {
                modifiedfiles.push_back(files[i]);
            }
        }

        sort(files.begin(), files.end());
        for (auto f : map_index) //file exist in map but not in vector
        {
            if (find(files.begin(), files.end(), f.first) == files.end())
            {
                deletedfiles.push_back(f.first);
            }
        }

        cout << "no. of modified files " << modifiedfiles.size() << endl;
        cout << "no. of new files " << newfiles.size() << endl;
        cout << "no. of deleted files " << deletedfiles.size() << endl;

        return 1;
    }

    

}