#include "StdAfx.h"
#include "TextUtils.h"


TextUtils::TextUtils(void)
{
}


TextUtils::~TextUtils(void)
{
}

string TextUtils::trim(string& str){
	int begin = str.find_first_not_of(" ");
	int end = str.find_last_not_of(" ");
	return str.substr(begin,end-begin+1);
}