#ifndef __HANGULUTIL__
#define __HANGULUTIL__
#define DEL L'\\'
#include <map>
using namespace std;

class JamoMapper{
private:
	static map<wchar_t, map<wchar_t, wchar_t>> s_pMap;
	static map<wchar_t, wchar_t> s_pMobile;
	static map<wchar_t, map<wchar_t, wchar_t>> s_pMobileFunctionalMap;
public:
	static wchar_t combine(wchar_t x, wchar_t y);
	static wchar_t getFundamentalVowel(wchar_t x);
	static wchar_t combineMobile(wchar_t x, wchar_t y);
	JamoMapper();
};

class JamoCombiner{
private:
	static JamoMapper s_pMapper;
public:
	static wchar_t combine(wchar_t x, wchar_t y);
	static wchar_t combineMobile(wchar_t x, wchar_t y);
	static wchar_t getFundamentalVowel(wchar_t x);
	static wchar_t resolveInit(wchar_t x);
	static wchar_t resolveMiddle(wchar_t x);
	static wchar_t resolveMiddleSingle(wchar_t x);
	static wchar_t resolveFinal(wchar_t x);
	static wchar_t resolveFinalSingle(wchar_t x);
};

wchar_t AndromedaToKorean(wchar_t x);

#endif