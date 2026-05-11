#include <iostream>
#include <string>
#include <unistd.h>
#include <sstream>
using namespace std;


string executable(string command){

  char* pathEnv= getenv("PATH");
  string path(pathEnv);
  
  stringstream ss(path);
  string dir;
  while(getline(ss,dir,':')){
    string fullPath=dir.data()+'/'+command;
    if(access(fullPath.data(),F_OK)==0){
      if(access(fullPath.data(),X_OK)==0){
        return fullPath;
      }
    }
  }
  return "";
}

int main() {
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while(true){
    std::cout << "$ ";
    string command;
    getline(cin,command);
    if(command=="exit") break;
    else if(command.substr(0,5)=="echo ") cout<<command.substr(5)<<"\n";

    else if(command.substr(0,5)=="type "){
      string commandType;
      commandType=command.substr(5);
      if(commandType=="echo" || commandType=="exit" || commandType=="type"){
        cout<<commandType<<" is a shell builtin\n";
      }
      else if(executable(commandType)!=""){
        cout<<commandType<<"is: "<<executable(commandType);
      }
      else cout<<commandType<<": not found\n";
    }

    else cout<<command<<": command not found\n";
  }
}
