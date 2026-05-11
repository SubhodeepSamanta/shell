#include <iostream>
#include <string>
#include <unistd.h>
#include <sstream>
#include<sys/types.h>
#include<sys/wait.h>
#include<vector>
using namespace std;

string executable(string command){
  char* pathEnv=getenv("PATH");
  string path(pathEnv);
  stringstream ss(path);
  string dir;
  while(getline(ss,dir,':')){
    string fullPath=dir+'/'+command;
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
    cout<<"$ ";
    string line;
    getline(cin,line);
    stringstream ss(line);
    vector<string> tokens;
    string word;

    while(ss >> word){
      tokens.push_back(word);
    }
    if(tokens[0]=="exit") break;
    else if(tokens[0]=="echo"){
      for(int i=1;i<tokens.size();i++){
        cout<<tokens[i]<<" ";
      }
      cout<<endl;
    }
    else if(tokens[0]=="type"){
      if(tokens[1]=="echo" || tokens[1]=="type" || tokens[1]=="exit"){
        cout<<tokens[1]<<"is a shell builtin\n";
      }else if(executable(tokens[1])!=""){
        cout<<tokens[1]<<" is "<<executable(tokens[1])<<"\n";
      }else{
        cout<<tokens[1]<<": not found\n";
      }
    }
    else if(executable(tokens[0])!=""){
      pid_t pid=fork();
      if(pid==0){
        vector<char*> args;
        for(auto& token:tokens){
          args.push_back(token.data());
        }
        args.push_back(NULL);
        execvp(args[0],args.data());
      }else{
        waitpid(pid,NULL,0);
      }
      
    }
    else{
      cout<<tokens[0]<<": command no found\n";
    }
  }
  
}
