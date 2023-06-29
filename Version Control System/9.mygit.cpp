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
#include <sstream>
#include <map>

using namespace std;

#include "1.add.cpp"
#include "2.commit.cpp"
#include "3.log.cpp"
#include "4.merge.cpp"
#include "5.pull.cpp"
#include "6.push.cpp"
#include "7.rollback.cpp"
#include "8.status.cpp"


int init();
string retrieve_version_no();
void retrieve_sha(string , string );
void retrieve_filename(string , string );



int main(int argc, char* argv[]){
    
}