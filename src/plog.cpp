#include<plog/Log.h>
#include<plog/Appenders/ColorConsoleAppender.h>
using namespace std;

int main()
{
	plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
	plog::init(plog::verbose, &consoleAppender);
	plog::init<1>(plog::verbose, "plog.txt");
	LOGD << "hello this is logging";
	LOGD_(1) << "file";
}


