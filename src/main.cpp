#include<iostream>
#include<unistd.h>
#include<vector>
#include<string>
#include<sstream>
#include<sys/types.h>
#include<sys/wait.h>

using namespace std;

string readInput(){
    cout<<"$ ";
    string line;
    getline(cin,line);
    return line;
}

vector<string> tokenizer(string& line){
  stringstream ss(line);
  string word;
  vector<string> tokens;
  while(ss>>word){
    tokens.push_back(word);
  }
  return tokens;
}

void handleEcho(vector<string>& tokens){
  for(int i=1;i<tokens.size();i++){
    cout<<tokens[i];
    if(i!=tokens.size()) cout<<" ";
  }
  return;
}

string externalCommandCheck(string& command){
  string dir;
  const char* pathENV=getenv("PATH");
  string path(pathENV);
  stringstream ss(path);
  while(getline(ss,dir,':')){
    string fullCommand= dir+'/'+command;
    if(access(fullCommand.c_str(),X_OK)==0) return fullCommand;
  }
  return "";
}

void handleType(string command){
  if(command=="echo"||command=="echo"||command=="exit"||command=="type"){
    cout<<command<<" is a shell builtin";
  }else if(externalCommandCheck(command)!=""){
    cout<<command<<" is "<<externalCommandCheck(command);
  }else{
    cout<<command<<": not found";
  }
}

void externalCommandRun(vector<string>& tokens){
   pid_t pid=fork();
   vector<char*>args;
   for(int i=0;i<tokens.size();i++){
    args.push_back(tokens[i].data());
   }
   args.push_back(NULL);
   if(pid==0){
    execvp(args[0],args.data());
   }else{
    waitpid(pid,NULL,0);
   }
}


bool handleCommand(vector<string>& tokens){
  if(tokens[0]=="type"){
    handleType(tokens[1]);
    return true;
  }
  else if(tokens[0]=="echo"){
    handleEcho(tokens);
    return true;
  }
  else if(externalCommandCheck(tokens[0])!=""){
    externalCommandRun(tokens);
    return true;
  }
  return false;
}

int main(){
  cout<<unitbuf;
  cerr<<unitbuf;
  while(true){
    string line=readInput();
    vector<string> tokens=tokenizer(line);
    bool commandWorked= handleCommand(tokens);
    if(tokens[0]=="exit") break;
    if(!commandWorked) cout<<tokens[0]<<": command not found";
    cout<<endl;
  }
  return 0;
}