#include<fstream>
#include<iostream>
using namespace std;
int main() {
char entry[10000];
std::fstream file;

file.open ("a1bc3.txt", std::ios::out | std::ios::in );

if (file.is_open()){
    std::cin >> entry;
}
else {
    std::cout << "Failed to open.\n" ;
}

file << entry << std::endl;

std::cout << "\n\n" ;
string s;
file >> s;

std::cout << s << "\n\n" ;

file.close();
return 0;
}
