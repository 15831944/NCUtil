
#ifndef _TEXTUTILS_H_
#define _TEXTUTILS_H_

#include <string>
using namespace std;

class TextUtils
{
public:
	TextUtils(void);
	~TextUtils(void);

	//去掉字符串两端的空格
	static string trim(string& str);
protected:

private:

};

#endif