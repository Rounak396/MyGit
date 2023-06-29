namespace mygitadd{
    #include <iostream> 
    #include <fstream> // for file I/O
    #include <sstream> // for string streams
    #include <string>  // for strings
    #include <vector>  // for vectors
    #include <dirent.h> // for directory
    #include <sys/stat.h> // for stat
    #include <unistd.h> // for getcwd. get current working directory
    #include <stdio.h>  // stdio.h is the C header for the C standard library, whereas cstdio is the C++ version of the same thing.
    #include <stdlib.h> // stdlib.h is the C header for the C standard library, whereas cstdlib is the C++ version of the same thing.
    #include <string.h>  // for string
    #include <sys/types.h> // types.h is a header file in the standard library of the C programming language containing definitions of important data types and macros.
    #include <sys/wait.h> // wait.h is a header file in the C standard library for the C programming language which contains constructs that facilitate waiting for and sending signals to child processes.
    #include <fcntl.h> // for file control
    #include <errno.h> // for error number. errno is defined by the ISO C standard to be a modifiable lvalue of type int, and must not be explicitly declared; errno may be a macro.
    #include <time.h> // for time
    #include <algorithm> // for sort
    #include <map>      // for map

    using namespace std;


   char cwd[PATH_MAX]; // current working directory. PATH_MAX is the maximum number of bytes in a pathname, including the terminating null character.
   string mygit_path; // mygit path. mygit is the name of the version control system.
   string version_no_file_path; // version no file path. version no file is the file that stores the version number. version_no_file_path= mygit_path + "/version_no"
   string version_no; // version no. version no is the version number. 
   string index_path; // index path. index is the file that stores the file names and their hashes. index_path= mygit_path + "/index"
   string base_path; // base path. base is the directory that stores the files. base_path= mygit_path + "/base"
   int n;


   vector<string> files; // files. files is the vector that stores the file names.
   vector<string> hashes; // hashes. hashes is the vector that stores the hashes of the files.
   map<string, string> map_index; // fixed map declaration
   vector<string> new_files; 
   vector<string> modified_files;
   vector<string> deleted_files;


   string get_sha(string);  // get sha. get sha is the function that returns the sha of the file. sha means secure hash algorithm.
   vector<string> get_files(string); // get files. get files is the function that returns the vector of file names in the directory.
   void get_index(); // get index. get index is the function that returns the map of file names and their hashes.
   map<string, string> get_map(); // get map. get map is the function that returns the map of file names and their hashes.




  int add_new(vector<string>& newf){
      for (int i=0; i<newf.size(); i++){
          string filename= newf[i];

          // copy the file from current working directory to cureent version.
          string s= cwd; 
          string path_in= s + "/" + filename; // path_in is the path of the file in the current working directory, used for copying the file to the base folder.
          string sha = get_sha(path_in);  
          string path_out= mygit_path + version_no + "/" + filename; 

          string copy_cmd = "cp ";  
          copy_cmd = copy_cmd + path_in + " "; 
          copy_cmd = copy_cmd + s + "/.mygit/base/" + filename;
          system(copy_cmd.c_str()); //files copied from cwd to base folder



          // copying the file from base folder to current version folder
         
          ifstream fin;  // input file stream. By this we can read from a file.
          ofstream fout; // output file stream. By this we can write to a file.

          fin.open(path_in, ios::in); // open the file in read mode
          fout.open(path_out, ios::out); // open the file in write mode
          string line;

          while (fin){
              getline(fin, line);
              fout << line << endl;
            }

          fin.close();
          fout.close();

          map_index[filename] = sha;//add new file in the map
          cout<<"adding new file: "<<filename<<endl;
        
        } 

        string main_index_path = string(cwd) + "/.mygit/main_index.txt";
    
        ofstream main_index_file(main_index_path, ios::app);
        for (int i = 0; i < newf.size(); i++)
        {
            string filename = newf[i];
        
            //in main index file add the new file name and the version no in which it came into existence
            main_index_file << filename << " " << version_no << "\n";

        }

        main_index_file.close();

        //change the index file of current version accordingly
        ofstream fout1;
        fout1.open(index_path, ios::out);
        for (auto it = map_index.begin(); it != map_index.end(); it++)
        {
            string line;
            line += it->first + " " + it->second;
            fout1 << line << endl;
        }
        fout1.close();

        return 1;
    }




    int add_modified(vector<string> modifiedf){
        for (int i = 0; i < modifiedf.size(); i++)
        {
            string filename = modifiedf[i];
            string s = cwd;
            string path_in = s + "/" + filename;
            string path_out = mygit_path + version_no + "/" + filename;
            ifstream fin(path_in);
            ofstream fout(path_out);
            //modify the file line by line
            string line;
            while (fin)
            {
                getline(fin, line);
                fout << line << endl;
            }
            fin.close();
            fout.close();

            string sha = get_sha(filename);
            map_index[filename] = sha;//change sha of the file in map
            cout<<"adding modified file: "<<filename<<endl;
        }

        //change the index file of current version accordingly
        ofstream fout1;
        fout1.open(index_path, ios::out);
        for (auto it = map_index.begin(); it != map_index.end(); it++)
        {
            string line;
            line += it->first + " " + it->second;
            fout1 << line << endl;
        }
        fout1.close();

        return 1;
    }




    int add_deleted(vector<string> deletedf)
    {   
        //path from where the file is to be deleted i.e the current version
        string delete_in = mygit_path + version_no + "/";
    
    
        for (int i = 0; i < deletedf.size(); i++)
        {
            string str = delete_in + deletedf[i];
            map_index.erase(deletedf[i]);//delete the file from map
            remove(str.c_str());//delete file in current version
            cout<<"deleting file: "<<deletedf[i]<<endl;
        }
        
        //change the index file  of current version accordingly
        ofstream fout1;
        fout1.open(index_path, ios::out);
        for (auto it = map_index.begin(); it != map_index.end(); it++)
        {
            string line;
            line += it->first + " " + it->second;
            fout1 << line << endl;
        }
        fout1.close();
        
        return 1;
    }




    int add(){
        mygit_path=" ";
        if(getcwd(cwd, sizeof(cwd)) != NULL) {
            mygit_path= string(cwd);
            mygit_path += "/.mygit/"; //myit path is the path to .mygit folder
        }
        else {
            perror("Unable to get the current working directory!");
            return 0;
        }

        //get files into a vector from the cwd
        files = get_files(cwd);
        n = files.size();

        //goto the current version and read the version no
        version_no_file_path = mygit_path + "version_no.txt";
        fstream vcfile(version_no_file_path, std::ios_base::in);
        vcfile >> version_no;
    
        //go to current version index file and create an map
        index_path = mygit_path + version_no + "/" + "index.txt";
        map_index = get_map();

        // comparing for new , modified and deleted files
        for (int i = 0; i < n; i++)
        {
            string sha = get_sha(files[i]);

            if (map_index.find(files[i]) == map_index.end())//file exist in vector but not in map
            {
                new_files.push_back(files[i]);
            }
            else if (map_index[files[i]] != sha)//sha of same file name dosent match
            {
                modified_files.push_back(files[i]);
            }
        }

        sort(files.begin(), files.end());
        for (auto it = map_index.begin(); it != map_index.end(); it++)
        {
            if (find(files.begin(), files.end(), it->first) == files.end())//file exist in map but not in vector
            {
                deleted_files.push_back(it->first);
            }
        }

        // display all the new files
        if(files.size()==0){
            cout<<"No files to add"<<endl;
        }
        else if(files.size()!=0){
            cout<<"New files: "<<endl;
            for (int i = 0; i < new_files.size(); i++)
            {
                cout << new_files[i] << endl;
            }
        }

        // display all the modified files
        if(modified_files.size()==0){
            cout<<"No files to modify"<<endl;
        }
        else if(modified_files.size()!=0){
            cout<<"Modified files: "<<endl;
            for (int i = 0; i < modified_files.size(); i++)
            {
                cout << modified_files[i] << endl;
            }
        }

        // display all the deleted files
        if(deleted_files.size()==0){
            cout<<"No files to delete"<<endl;
        }
        else if(deleted_files.size()!=0){
            cout<<"Deleted files: "<<endl;
            for (int i = 0; i < deleted_files.size(); i++)
            {
                cout << deleted_files[i] << endl;
            }
        }
        cout<<endl;

        //add the files to the current version
        int new_processed =0;
        int modified_processed =0;
        int deleted_processed =0;

        if (new_files.size()!=0)
        {
            new_processed = add_new(new_files);
            if(new_processed) 
            new_files.clear();
            if(new_files.size()!=0){
                cout<<"New files were not cleared"<<endl;
            }
            else{
                cout<<"New files were cleared"<<endl;
            }
        }

        if (modified_files.size()!=0)
        {
            modified_processed = add_modified(modified_files);
            if(modified_processed) 
            modified_files.clear();
            if(modified_files.size()!=0){
                cout<<"Modified files were not cleared"<<endl;
            }
            else{
                cout<<"Modified files were cleared"<<endl;
            }
        }

        if (deleted_files.size()!=0)
        {
            deleted_processed = add_deleted(deleted_files);
            if(deleted_processed) 
            deleted_files.clear();
            if(deleted_files.size()!=0){
                cout<<"Deleted files were not cleared"<<endl;
            }
            else{
                cout<<"Deleted files were cleared"<<endl;
            }
        }

        if (new_files.size() == 0 && modified_files.size() == 0 &&  deleted_files.size() == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }


        if(new_processed && modified_processed && deleted_processed){
            cout<<"All files were added successfully"<<endl;
        }
        else{
            cout<<"Some files were not added successfully"<<endl;
        }

    }




    string get_sha(string file_name)
    {
        string s = "sha1sum " + file_name + " > temp.txt";

        char arr[255];
        strcpy(arr, s.c_str());//store string s in char array
        system(arr);//sha calculation

        FILE *filepointer = fopen("temp.txt", "r+");//open temp.txt file to read the sha
        char aux[100];
        fread(aux, sizeof(char), 100, filepointer);//reading in sha in aux array
        string input = aux;
        stringstream ss(input);
        string sha;
        ss >> sha;
        fclose(filepointer);

        remove("temp.txt");//delete temp.txt file
    
        return sha;
    }




    vector<string> get_files(string path)
    {
        struct dirent *pointerp;
        DIR *dir = opendir(path.c_str()); //pointer to the directory whose files we wish to copy
        if (dir == NULL)
        {
            cout << "Failed to open the Directory";
            exit(EXIT_FAILURE);
        }
    
        vector<string> v; //vector to store the filenames
        while ((pointerp = readdir(dir)) != NULL) //readdir(dir) will point to the files one by one
        {
            //cout << pointerp->d_name << endl;
            string file_name = pointerp->d_name;
            if (file_name == "." || file_name == ".." || file_name == ".mygit" || file_name == "a.out" || file_name == ".vscode" || file_name=="mygit" || file_name=="1.add.cpp" || file_name=="2.commit.cpp" || file_name=="3.log.cpp" || file_name=="4.merge.cpp" || file_name=="5.pull.cpp" || file_name=="6.push.cpp" || file_name=="7.rollback.cpp" ||  file_name=="8.status.hpp" || file_name=="9.mygit.cpp" || file_name=="mygit" || file_name=="pull" || file_name=="push" )
            {
                v.push_back(file_name); //push the file in vector
            }
            
        }
        closedir(dir); //close the directory 
        return v; //return the vector
    }




    map<string, string> get_map(string path)//make map from index file given the path of index.txt
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
                index_map[filename] = sha;//filename:sha
            }
        }
        else        
        {
            perror("unable to open file in get_map function");
            exit(1);
        }
        return index_map;
    }

};
