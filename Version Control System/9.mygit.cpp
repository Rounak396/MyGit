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


#include "1.add.cpp"
#include "2.commit.cpp"
#include "3.log.cpp"
#include "4.merge.cpp"
#include "5.pull.cpp"
#include "6.push.cpp"
#include "7.rollback.cpp"
#include "8.status.cpp"


using namespace std;
using namespace mygitadd;
using namespace mygitCommit;
using namespace mygitlog;
using namespace mygitmerge;
using namespace mygitpull;
using namespace mygitpush;
using namespace mygitrollback;
using namespace mygitstatus;


int init();
string retrieve_version_no();
void retrieve_sha(string , string );
void retrieve_filename(string , string );



int main(int argc, char* argv[]){
    
    string str;
    char * p=argv[1];
    str=p;

    if (str == "init"){    
        if (init() == 0)
        {
            string s = "Mygit successfully initialised!!";
            mygitlog::log_write(s);
            cout << s << endl;
            exit(EXIT_SUCCESS);
        }
        else
        {
            string s = "Error in initialisation!!";
            mygitlog::log_write(s);
            cout << s << endl;
            exit(EXIT_SUCCESS);
        }
    }

    else if (str == "add")
        {
            if (argc == 3)
            {
                string s = "File added successfully!!";
                mygitlog::log_write(s);
                cout << s << endl;
                add(argv[2]);
                exit(EXIT_SUCCESS);
            }
            else
            {
                string s = "Error in adding file!!";
                mygitlog::log_write(s);
                cout << s << endl;
                exit(EXIT_SUCCESS);
            }
        }

    else if (str == "commit")
        {
            if (argc == 3)
            {
                string s = "Commit successful!!";
                mygitlog::log_write(s);
                cout << s << endl;
                commit(argv[2]);
                exit(EXIT_SUCCESS);
            }
            else
            {
                string s = "Error in commit!!";
                mygitlog::log_write(s);
                cout << s << endl;
                exit(EXIT_SUCCESS);
            }
        }

    else if (str == "log")
        {
            if (argc == 2)
            {
                string s = "Log successful!!";
                mygitlog::log_write(s);
                cout << s << endl;
                log();
                exit(EXIT_SUCCESS);
            }
            else
            {
                string s = "Error in log!!";
                mygitlog::log_write(s);
                cout << s << endl;
                exit(EXIT_SUCCESS);
            }
        }

    else if (str == "merge")
        {
            if (argc == 3)
            {
                string s = "Merge successful!!";
                mygitlog::log_write(s);
                cout << s << endl;
                merge(argv[2]);
                exit(EXIT_SUCCESS);
            }
            else
            {
                string s = "Error in merge!!";
                mygitlog::log_write(s);
                cout << s << endl;
                exit(EXIT_SUCCESS);
            }
        }

    else if (str == "pull")
        {
            if (argc == 3)
            {
                string s = "Pull successful!!";
                mygitlog::log_write(s);
                cout << s << endl;
                pull(argv[2]);
                exit(EXIT_SUCCESS);
            }
            else
            {
                string s = "Error in pull!!";
                mygitlog::log_write(s);
                cout << s << endl;
                exit(EXIT_SUCCESS);
            }
        }

    else if (str == "push")
        {
            if (argc == 3)
            {
                string s = "Push successful!!";
                mygitlog::log_write(s);
                cout << s << endl;
                push(argv[2]);
                exit(EXIT_SUCCESS);
            }
            else
            {
                string s = "Error in push!!";
                mygitlog::log_write(s);
                cout << s << endl;
                exit(EXIT_SUCCESS);
            }
        }

    else if (str == "rollback")
        {
            if (argc == 3)
            {
                string s = "Rollback successful!!";
                mygitlog::log_write(s);
                cout << s << endl;
                rollback(argv[2]);
                exit(EXIT_SUCCESS);
            }
            else
            {
                string s = "Error in rollback!!";
                mygitlog::log_write(s);
                cout << s << endl;
                exit(EXIT_SUCCESS);
            }
        }

    else if (str == "status")
        {
            if (argc == 2)
            {
                string s = "Status successful!!";
                mygitlog::log_write(s);
                cout << s << endl;
                status();
                exit(EXIT_SUCCESS);
            }
            else
            {
                string s = "Error in status!!";
                mygitlog::log_write(s);
                cout << s << endl;
                exit(EXIT_SUCCESS);
            }
        }

     else if (str== "retrieve_version_no")
        {
            if (argc == 2)
            {
                string s = "Version number retrieved successfully!!";
                mygitlog::log_write(s);
                cout << s << endl;
                retrieve_version_no();
                exit(EXIT_SUCCESS);
            }
            else
            {
                string s = "Error in retrieving version number!!";
                mygitlog::log_write(s);
                cout << s << endl;
                exit(EXIT_SUCCESS);
            }
        }
        
}