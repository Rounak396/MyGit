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

    string get_cwd()
    {
        char cwd_path[PATH_MAX];
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

    string get_sha(string file_name)
    {
        string s = "sha1sum " + file_name + " > temp.txt";

        char arr[255];
        strcpy(arr, s.c_str()); //store string s in char array
        system(arr);            //sha calculation

        FILE *filepointer = fopen("temp.txt", "r+"); //open temporary file to read the sha
        char aux[100];
        fread(aux, sizeof(char), 100, filepointer); //reading in sha in aux array
        string input = aux;
        stringstream ss(input);
        string sha;
        ss >> sha;
        fclose(filepointer);

        remove("temp.txt"); //delete temp.txt file

        return sha;
    }

    vector<string> get_files(string cwd_path)
    {
        vector<string> files;
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir(cwd_path.c_str())) != NULL)
        {
            while ((ent = readdir(dir)) != NULL)
            {
                string file_name = ent->d_name;
                if (file_name == "." || file_name == ".." || file_name == ".mygit" || file_name == "a.out" || file_name == ".vscode" || file_name=="mygit" || file_name=="1.add.cpp" || file_name=="2.commit.cpp" || file_name=="3.log.cpp" || file_name=="4.merge.cpp" || file_name=="5.pull.cpp" || file_name=="6.push.cpp" || file_name=="7.rollback.cpp" ||  file_name=="8.status.hpp" || file_name=="9.mygit.cpp" || file_name=="mygit" || file_name=="pull" || file_name=="push" )
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

    map<string, string> get_map(string path) //make map from index file given the path of index.txt
    {
        map<string, string> index_map;
        fstream f(path, std::ios_base::in);
        if (f.is_open())
        {
            string line;
            while (getline(f, line))
            {
                stringstream ss(line);
                string filename = "";
                string sha = "";
                ss >> filename;
                ss >> sha;
                index_map[filename] = sha; //filename:sha
            }
        }
        else
        {
            perror("unable to open file in get_map function");
            exit(1);
        }
        return index_map;
    }

    
}