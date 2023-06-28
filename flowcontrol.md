To create a version control system using C++, I have divided my implementation into 9 files. Here's a breakdown of what each file should include and its purpose:

`add.cpp` : This file handles the functionality of adding files to the version control system. It should contain code to identify new files or modifications to existing files and track them for the next commit.

`commit.cpp` : This file handles the process of creating a new commit in the version control system. It should include code to collect the changes made to files since the last commit and store them as a new commit object with relevant metadata like commit message, author, timestamp, etc.

`log.cpp` : This file is responsible for displaying the commit history. It should contain code to retrieve the commit objects and display their details, such as commit message, author, timestamp, and any other relevant information.

`merge.cpp` : This file handles the merging of branches in the version control system. It should include code to identify the changes made in different branches and merge them appropriately, resolving conflicts if necessary.

`pull.cpp` : This file deals with retrieving updates from a remote repository. It should contain code to fetch the latest commits from the remote repository and integrate them into the local repository.

`push.cpp` : This file handles pushing local commits to a remote repository. It should include code to validate the changes being pushed, ensure synchronization with the remote repository, and update the remote branch.

`rollback.cpp` : This file is responsible for reverting to a previous commit. It should contain code to identify the desired commit and revert the changes made after that commit.

`status.cpp` : This file displays the current status of the working directory. It should include code to compare the current state of files with the last commit and show the modifications or new files that have not been committed yet.

`mygit.cpp` : This file serves as the entry point of your version control system. It should include the main function, which coordinates the execution of different functionalities and interacts with the user through a command-line interface or any other user interface you choose to implement.

Remember that this breakdown is a general guideline, and the exact implementation will depend on your specific requirements and design choices. Additionally, you will need to consider data structures, algorithms, and the use of appropriate libraries to fulfill the functionality outlined in each file.