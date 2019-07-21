#include<iostream>
#include<map>
#include<string>
#include<sstream>
#include<array>
#include<valarray>
#include"xterm-color_48x48.xpm"
using namespace std;

array<unsigned char, 4> change(const char* p)
{
	unsigned char c[6];
	if(*p == '#') {
		for(int i=0; i<6; i++) {
			if(p[i+1] <= '9') c[i] = p[i+1] - '0';
			else c[i] = p[i+1] - 'A' + 10;
		}
		for(int i=0; i<6; i+=2) c[i] = c[i] * 16 + c[i+1];
		return {c[0], c[2], c[4], 0xff};
	} else return {0,0,0,0};
}

int main()
{
	char const **xpm = xterm_color_48x48_xpm;
	stringstream ss;
	ss << xpm[0];
	size_t w, h, color, ch;
	ss >> w >> h >> color >> ch;

	map<string, array<unsigned char, 4>> color_map;
	for(int i=0; i<color; i++) 
		color_map[string(xpm[i+1], ch)] = change(xpm[i+1] + ch + 3);
	
	valarray<float> v(w*h*4);
	int k=0;
	for(int y=0; y<h; y++) 
		for(int x=0; x<ch*w; x+=ch) 
			for(auto& a : color_map[string(xpm[color+1+y] + x, ch)])
				v[k++] = a / 256.0;
	
	valarray<float> v2 = v[gslice(40+w*4*10, {25,25,4}, {4*w,4,1})];
//	cout << 25 << endl << 25 << endl;
//	for(int i=0; i<v2.size(); i++) cout << v2[i] << endl;
//	v2 /= 2;
	v[gslice(0, {15,15}, {w*4,4})] = 0.5;//v[gslice(30+32*30, {15,15,3}, {96,3,1})];
	cout << w << endl << h << endl;
	for(int i=0; i<v.size(); i++) cout << v[i] << endl;
}




