#include "State.hpp"
#include "Hangul.hpp"
#include "func.hpp"
#include <string>
#include <vector>
using namespace std;


bool isBufferOnlyConsonant(wchar_t v) {
	if (v == L'3' || v == L'6' || v == L'9' || v == L'0') {
		return false;
	}
	return true;
}
bool isBufferOnlyVowel(wchar_t v) {
	if (v == L'3' || v == L'6' || v == L'9' || v == L'0') {
		return true;
	}
	return false;
}
#ifdef __CHOSUNG__
void PushToStack(wstring* str, wchar_t x) {	
	int N = str->length();
	if (N == 0)
	{
		str->push_back(JamoCombiner::getFundamentalVowel(x));
	}
	else
	{
		if (0x3131 <= (*str)[N - 1] && (*str)[N - 1] <= 0x314E) {
			if (JamoCombiner::combineMobile((*str)[N - 1], x) != 0) {
				(*str)[N - 1] = JamoCombiner::combineMobile((*str)[N - 1], x);
			}
			else {
				(*str)[N - 2] = JamoCombiner::combine((*str)[N - 2], (*str)[N - 1]);
				(*str)[N - 1] = JamoCombiner::getFundamentalVowel(x);
			}
		}
		else {
			str->push_back(JamoCombiner::getFundamentalVowel(x));
		}
	}
}
void FlushBuffer(wstring* str, wchar_t x) {
	int N = str->length();
	if (x == 'p') {
		if (0x3131<=(*str)[N-1] && (*str)[N-1]<=0x314E) {
			wchar_t FF = (*str)[N - 1];
			FF = JamoCombiner::combineMobile(FF, L'p');
			(*str)[N - 1] = FF;
		}
		else if (JamoCombiner::resolveFinal((*str)[N - 1])==0) {
			wchar_t J = JamoCombiner::resolveInit((*str)[N - 1]);
			wchar_t M = JamoCombiner::resolveMiddle((*str)[N - 1]);
			wchar_t Mfixed = JamoCombiner::combineMobile(M, L'p');
			(*str)[N - 1] = JamoCombiner::combine(J, Mfixed);
		}
	}
	else if (x == 'q') {
		(*str)[N - 1] = JamoCombiner::combineMobile((*str)[N - 1], L'q');
	}
	else if (isBufferOnlyConsonant(x)) {
		if (0x3131 <= (*str)[N - 1] && (*str)[N - 1] <= 0x314E) {
			if (JamoCombiner::combineMobile((*str)[N - 1], x) != 0) {
				(*str)[N - 1] = JamoCombiner::combineMobile((*str)[N - 1], x);
			}
			else {
				(*str)[N - 2] = JamoCombiner::combine((*str)[N - 2], (*str)[N - 1]);
				(*str)[N - 1] = JamoCombiner::getFundamentalVowel(x);
			}
		}
		else {
			str->push_back(JamoCombiner::getFundamentalVowel(x));
		}
	}
	else if (isBufferOnlyVowel(x)) {
		wchar_t JM = (*str)[N - 1];
		wchar_t Mx = JamoCombiner::resolveMiddleSingle((*str)[N - 1]);
		if (0x3131 <= JM && JM <= 0x314E) {
			wchar_t M = JamoCombiner::getFundamentalVowel(x);
			JM = JamoCombiner::combine(JM, M);
			(*str)[N - 1] = JM;
		}
		else {
			Mx = JamoCombiner::combineMobile(Mx, x);
			JM = JamoCombiner::combine(JM, DEL);
			(*str)[N - 1] = JamoCombiner::combine(JM, Mx);
		}
	}
}
#endif
#ifdef __BATCHIM__
void PushToStack(wstring* str, wchar_t x) {	
	int N = str->length();
	if (N == 0)
	{
		str->push_back(JamoCombiner::getFundamentalVowel(x));
	}
	else
	{
		if (0x3131 <= (*str)[N - 1] && (*str)[N - 1] <= 0x314E) {
			(*str)[N - 1] = JamoCombiner::combineMobile((*str)[N - 1], x);
		}
		else {
			str->push_back(JamoCombiner::getFundamentalVowel(x));
		}
	}
}
void FlushBuffer(wstring* str, wchar_t x) {
	int N = str->length();
	if (x == 'p') {
		if (0x3131<=(*str)[N-1] && (*str)[N-1]<=0x314E) {
			wchar_t FF = (*str)[N - 1];
			str->pop_back();
			FF = JamoCombiner::combineMobile(FF, L'p');
			N--;
			(*str)[N - 1] = JamoCombiner::combine((*str)[N - 1], FF);
		}
		else if (JamoCombiner::resolveFinal((*str)[N - 1])==0) {
			wchar_t J = JamoCombiner::resolveInit((*str)[N - 1]);
			wchar_t M = JamoCombiner::resolveMiddle((*str)[N - 1]);
			wchar_t Mfixed = JamoCombiner::combineMobile(M, L'p');
			(*str)[N - 1] = JamoCombiner::combine(J, Mfixed);
		}
		else {
			wchar_t JM = JamoCombiner::combine((*str)[N - 1], DEL);
			wchar_t F = JamoCombiner::resolveFinalSingle((*str)[N - 1]);
			wchar_t Ffixed = JamoCombiner::combineMobile(F, L'p');
			(*str)[N - 1] = JamoCombiner::combine(JM, Ffixed);
		}
	}
	else if (x == 'q') {
		wchar_t JM = JamoCombiner::combine((*str)[N - 1], DEL);
		wchar_t F = JamoCombiner::resolveFinalSingle((*str)[N - 1]);
		wchar_t Ffixed = JamoCombiner::combineMobile(F, L'q');
		(*str)[N - 1] = JamoCombiner::combine(JM, Ffixed);
	}
	else if (isBufferOnlyConsonant(x)) {
		wchar_t JM = (*str)[N - 1];
		wchar_t F = JamoCombiner::resolveFinal(JM);
		wchar_t Fx = JamoCombiner::resolveFinalSingle(JM);
		if (F == 0) {
			JM = JamoCombiner::combine(JM, JamoCombiner::getFundamentalVowel(x));
			(*str)[N - 1] = JM;
		}
		else if (JamoCombiner::combineMobile(Fx, x) != 0) {
			JM = JamoCombiner::combine(JM, DEL);
			Fx = JamoCombiner::combineMobile(Fx, x);
			(*str)[N - 1] = JamoCombiner::combine(JM, Fx);
		}
		else {
			Fx = JamoCombiner::getFundamentalVowel(x);
			(*str)[N - 1] = JamoCombiner::combine(JM, Fx);
		}
	}
	else if (isBufferOnlyVowel(x)) {
		wchar_t JM = (*str)[N - 1];
		wchar_t Fx = JamoCombiner::resolveFinalSingle(JM);
		if (0x3131 <= JM && JM <= 0x314E) {
			wchar_t M = JamoCombiner::getFundamentalVowel(x);
			JM = JamoCombiner::combine(JM, M);
			(*str)[N - 1] = JM;
		}
		else if (Fx == 0) {
			wchar_t M = JamoCombiner::resolveMiddleSingle(JM);
			JM = JamoCombiner::combine(JM, DEL);
			M = JamoCombiner::combineMobile(M, x);
			(*str)[N - 1] = JamoCombiner::combine(JM, M);
		}
		else {
			JM = JamoCombiner::combine(JM, DEL);
			(*str)[N - 1] = JM;
			wchar_t JMx = JamoCombiner::combine(Fx, JamoCombiner::getFundamentalVowel(x));
			str->push_back(JMx);
		}
	}
}
#endif
void onDeleteKey(wstring* str, wchar_t x) {
	int N = str->length();
	if (N != 0) {
		str->pop_back();
	}
}