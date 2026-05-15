#include<iostream>
#include<unistd.h>
#include<vector>
#include<string>
#include<sstream>

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

void handleType(string command){
  if(command=="echo"||command=="echo"||command=="exit"||command=="type"){
    cout<<command<<" is a shell builtin";
  }else{
    cout<<command<<": not found";
  }
}

bool handleCommand(vector<string>& tokens){
  if(tokens[0]=="type"){
    handleType(tokens[1]);
    return true;
  }
  if(tokens[0]=="echo"){
    handleEcho(tokens);
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