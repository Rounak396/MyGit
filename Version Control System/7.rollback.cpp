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
    string cwd_path[PATH_MAX];
    string get_cwd();
    vector<string> get_files(string);
    string get_sha(string);
}