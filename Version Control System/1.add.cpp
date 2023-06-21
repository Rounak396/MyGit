namespace mygitadd{
    #include <iostream> 
    #include <fstream> // for file I/O
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



}
