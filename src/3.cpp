#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

void GetUnicodeChar(unsigned int code, char chars[5]) {
    if (code <= 0x7F) {
        chars[0] = (code & 0x7F); chars[1] = '\0';
    } else if (code <= 0x7FF) {
        // one continuation byte
        chars[1] = 0x80 | (code & 0x3F); code = (code >> 6);
        chars[0] = 0xC0 | (code & 0x1F); chars[2] = '\0';
    } else if (code <= 0xFFFF) {
        // two continuation bytes
        chars[2] = 0x80 | (code & 0x3F); code = (code >> 6);
        chars[1] = 0x80 | (code & 0x3F); code = (code >> 6);
        chars[0] = 0xE0 | (code & 0xF); chars[3] = '\0';
    } else if (code <= 0x10FFFF) {
        // three continuation bytes
        chars[3] = 0x80 | (code & 0x3F); code = (code >> 6);
        chars[2] = 0x80 | (code & 0x3F); code = (code >> 6);
        chars[1] = 0x80 | (code & 0x3F); code = (code >> 6);
        chars[0] = 0xF0 | (code & 0x7); chars[4] = '\0';
    } else {
        // unicode replacement character
        chars[2] = 0xEF; chars[1] = 0xBF; chars[0] = 0xBD;
        chars[3] = '\0';
    }
}
int main()
{
	cout << "unicode" << ',';
	for(int i=0; i<0xf; i++) cout << hex << setiosflags(ios::uppercase) << i << ',';
	cout << endl;

	char ch[5];
	for(int i=0; i<0xffff; i++) {
		if(i % 16 == 0) 
			cout << endl << hex << setiosflags(ios::uppercase) << setfill('0') << setw(4) << i << ',';
		GetUnicodeChar(i, ch);
		cout << ch << ',';
	}
}
