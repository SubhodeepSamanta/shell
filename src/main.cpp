#include <iostream>
#include <string>
using namespace std;

int main() {
  // Flush after every std::cout / std:cerr
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
      if(commandType=="echo" || commandType=="exit") cout<<commandType<<" is a shell builtin\n";
      else cout<<commandType<<": not found\n";
    }
    else cout<<command<<": command not found\n";
  }
}
