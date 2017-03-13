
#include <iostream>
#include <string>
//#include <cstdio>
#include <sstream>
using namespace std;
int main() {
    string  i, j;
    while(getline(cin, j)) {
        stringstream ss(j), temp;
        while(true) {
            //cout << temp;
            if(ss >> i)
                cout << ' ' << i;
            else {
                cout << " !ss>>i: " << (ss >> i);
                break;
            }
        }
        cout << endl;
    }
    return 0;

}