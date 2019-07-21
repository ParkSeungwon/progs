#include<fstream>
#include<vector>
#include<iostream>
using namespace std;

typedef struct WAV_HEADER {
    char                RIFF[4];        // RIFF Header      Magic header
    unsigned long       ChunkSize;      // RIFF Chunk Size  
    char                WAVE[4];        // WAVE Header      
    char                fmt[4];         // FMT header       
    unsigned long       Subchunk1Size;  // Size of the fmt chunk
    unsigned short      AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM 
    unsigned short      NumOfChan;      // Number of channels 1=Mono 2=Sterio 
    unsigned long       SamplesPerSec;  // Sampling Frequency in Hz
    unsigned long       bytesPerSec;    // bytes per second 
    unsigned short      blockAlign;     // 2=16-bit mono, 4=16-bit stereo 
    unsigned short      bitsPerSample;  // Number of bits per sample      
    char                Subchunk2ID[4]; // "data"  string   
    unsigned long       Subchunk2Size;  // Sampled data length
} wav_hdr;

int main(int ac, char** av)
{ 
	if(ac < 2) {
		cout << av[0] << " [file]" << endl;
		return 0;
	}
	wav_hdr *header; 
	ifstream f(av[1], ios::binary|ios::ate);
	int sz = f.tellg();
	char buf[sz];
	f.seekg(0, ios::beg);
	f.read(buf, sz);
//	header = reinterpret_cast<wav_hdr*>(buf);
//	cout << "sampling rate : " << header->SamplesPerSec << endl;
//	cout << "audio format : " << header->AudioFormat << endl;
//	cout << "channel : " << header->NumOfChan << endl;
//	cout << "data size : " << header->Subchunk2Size << endl;
//	cout << "bits per sample : " << header->bitsPerSample << endl;
//	//char* data = header->Subchunk2Size + sizeof(unsigned long);
//
//	cout << "File is                    :" << sz << " bytes." << endl;
//	cout << "RIFF header                :" << header->RIFF[0] << header->RIFF[1] << header->RIFF[2] << header->RIFF[3] << endl;
//	cout << "WAVE header                :" << header->WAVE[0] << header->WAVE[1] << header->WAVE[2] << header->WAVE[3] << endl;
//	cout << "FMT                        :" << header->fmt[0] << header->fmt[1] << header->fmt[2] << header->fmt[3] << endl;
//	cout << "Data size                  :" << header->ChunkSize << endl;
//
//	// Display the sampling Rate from the header
//	cout << "Sampling Rate              :" << header->SamplesPerSec << endl;
//	cout << "Number of bits used        :" << header->bitsPerSample << endl;
//	cout << "Number of channels         :" << header->NumOfChan << endl;
//	cout << "Number of bytes per second :" << header->bytesPerSec << endl;
//	cout << "Data length                :" << header->Subchunk2Size << endl;
//	cout << "Audio Format               :" << header->AudioFormat << endl;
//	// Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
//
//	cout << "Block align                :" << header->blockAlign << endl;
//	cout << "Data string                :" << header->Subchunk2ID[0] << header->Subchunk2ID[1] << header->Subchunk2ID[2] << header->Subchunk2ID[3] << endl;
//

	union {
		short n;
		char c[2];
	} u;
	vector<short> v;
	for(int i=44; i<sz; i+=2) {
		u.c[0] = buf[i];
		u.c[1] = buf[i+1];
		v.push_back(u.n);
	}
	for(auto& a : v) cout << a << ' ';
}
