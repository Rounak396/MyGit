# MyGit
MyGit is a version control system developed using C++..
## Installation
Use the following command to install MyGit:
```bash
make install
```
## Usage
Use the following command to initialize MyGit:
```bash
mygit init
```
Use the following command to add files to the staging area:
```bash
mygit add <filename>
```
Use the following command to commit files to the repository:
```bash
mygit commit -m "commit message"
```
Use the following command to view the commit history:
```bash
mygit log
```
Use the following command to view the status of the repository:
```bash
mygit status
```
Use the following command to view the difference between the working directory and the staging area:
```bash
mygit diff
```
Use the following command to view the difference between the staging area and the repository:
```bash
mygit diff --staged
```
Use the following command to view the difference between two commits:
```bash
mygit diff <commit-id-1> <commit-id-2>
```
Use the following command to view the difference between two branches:
```bash
mygit diff <branch-name-1> <branch-name-2>
```
Use the following command to create a new branch:
```bash
mygit branch <branch-name>
```
Use the following command to switch to a branch:
```bash
mygit checkout <branch-name>
```
Use the following command to merge two branches:
```bash
mygit merge <branch-name>
```
Use the following command to delete a branch:
```bash
mygit branch -d <branch-name>
```
Use the following command to push the repository to a remote repository:
```bash
mygit push <remote-name> <branch-name>
```
Use the following command to pull the repository from a remote repository:
```bash
mygit pull <remote-name> <branch-name>
```
Use the following command to clone a repository from a remote repository:
```bash
mygit clone <remote-name> <branch-name>
```
Use the following commands to configure the username and email:
```bash
mygit config --global user.name <username>
mygit config --global user.email <email>
```
Use the following command to merge two commits:
```bash
mygit rebase <commit-id-1> <commit-id-2>
```
Use the following command to view the remote repositories:
```bash
mygit remote -v
```
Use the following command to add a remote repository:
```bash
mygit remote add <remote-name> <remote-url>
```
Use the following command to remove a remote repository:
```bash
mygit remote remove <remote-name>
```..
