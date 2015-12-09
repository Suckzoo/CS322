#include "Hangul.hpp"
#include <set>
#include <vector>
using namespace std;

void init(set<wchar_t>& J, set<wchar_t>& M);
void HandleThirdLetter(wchar_t firstLetter, wchar_t secondLetter,
	wchar_t thirdLetter, wchar_t indx,
	map<wchar_t, map<wchar_t, wchar_t>>& s_pMap);

map<wchar_t, map<wchar_t, wchar_t>> JamoMapper::s_pMap;
map<wchar_t, wchar_t> JamoMapper::s_pMobile;
map<wchar_t, map<wchar_t, wchar_t>> JamoMapper::s_pMobileFunctionalMap;
JamoMapper JamoCombiner::s_pMapper = JamoMapper();
JamoMapper::JamoMapper()
{
	set<wchar_t> J;
	set<wchar_t> M;
	init(J, M);

	s_pMap[L'��'][L'��'] = L'��';
	s_pMap[L'��'][L'��'] = L'��';
	s_pMap[L'��'][L'��'] = L'��';
	s_pMap[L'��'][L'��'] = L'��';
	s_pMap[L'��'][L'��'] = L'��';
	s_pMap[L'��'][L'��'] = L'��';
	s_pMap[L'��'][L'��'] = L'��';
	s_pMap[L'��'][DEL] = L'��';
	s_pMap[L'��'][DEL] = L'��';
	s_pMap[L'��'][DEL] = L'��';
	s_pMap[L'��'][DEL] = L'��';
	s_pMap[L'��'][DEL] = L'��';
	s_pMap[L'��'][DEL] = L'��';
	s_pMap[L'��'][DEL] = L'��';

	wchar_t indx = 0xAC00;
	for (auto firstLetter : J)
	{
		for (auto secondLetter : M)
		{
			s_pMap[firstLetter][secondLetter] = indx;
			if (wstring(L"�ȤɤʤͤΤϤ�").find(JamoCombiner::resolveMiddle(indx))
				== wstring::npos)
			{
				s_pMap[indx][DEL] = firstLetter;
			}

			if (secondLetter == L'��')
			{
				s_pMap[indx][L'��'] = indx + (0x1C);
				s_pMap[indx][L'��'] = indx + (0x1C * 2);
				s_pMap[indx][L'��'] = indx + (0x1C * 3);
				s_pMap[indx + (0x1C)][DEL] = indx;
				s_pMap[indx + (0x1C * 2)][DEL] = indx;
				s_pMap[indx + (0x1C * 3)][DEL] = indx;
			}
			if (secondLetter == L'��')
			{
				s_pMap[indx][L'��'] = indx + (0x1C);
				s_pMap[indx][L'��'] = indx + (0x1C * 2);
				s_pMap[indx][L'��'] = indx + (0x1C * 3);
				s_pMap[indx + (0x1C)][DEL] = indx;
				s_pMap[indx + (0x1C * 2)][DEL] = indx;
				s_pMap[indx + (0x1C * 3)][DEL] = indx;
			}
			if (secondLetter == L'��')
			{
				s_pMap[indx][L'��'] = indx + (0x1C);
				s_pMap[indx + (0x1C)][DEL] = indx;
			}
			wchar_t thirdLetterCounter = 0;
			for (auto thirdLetter : J)
			{
				HandleThirdLetter(firstLetter, secondLetter, thirdLetter,
								indx, s_pMap);
			}
			indx += 0x1C;
		}
	}
	//Mobile J section
	s_pMobile[L'1'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'q'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'p'] = L'��';
	s_pMobile[L'2'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'p'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'q'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'p'] = L'��';
	s_pMobile[L'4'] = L'��';
	s_pMobile[L'5'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'p'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'q'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'p'] = L'��';
	s_pMobile[L'7'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'q'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'p'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'q'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'p'] = L'��';
	s_pMobile[L'8'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'p'] = L'��';

	//Mobile M section
	s_pMobile[L'3'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'p'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'9'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'9'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'3'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'9'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'p'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'9'] = L'��';

	s_pMobile[L'6'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'9'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'3'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'9'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'p'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'6'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'9'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'3'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'9'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'p'] = L'��';
	
	s_pMobile[L'9'] = L'��';
	s_pMobileFunctionalMap[L'��'][L'0'] = L'��';

	s_pMobile[L'0'] = L'��';
}
wchar_t JamoMapper::combine(wchar_t x, wchar_t y)
{
	return s_pMap[x][y];
}
wchar_t JamoMapper::getFundamentalVowel(wchar_t x)
{
	return s_pMobile[x];
}
wchar_t JamoMapper::combineMobile(wchar_t x, wchar_t y)
{
	return s_pMobileFunctionalMap[x][y];
}
wchar_t JamoCombiner::combine(wchar_t x, wchar_t y)
{
	return JamoMapper::combine(x, y);
}
wchar_t JamoCombiner::combineMobile(wchar_t x, wchar_t y)
{
	return JamoMapper::combineMobile(x, y);
}
wchar_t JamoCombiner::getFundamentalVowel(wchar_t x)
{
	return JamoMapper::getFundamentalVowel(x);
}
wchar_t JamoCombiner::resolveInit(wchar_t x)
{
	return  (wstring(L"��������������������������������������").at((x - 0xAC00) / 0x24B));
}
wchar_t JamoCombiner::resolveMiddle(wchar_t x)
{
	return L'��' + (((x-0xAC00) % 0x24B) / 0x1C);
}
wchar_t JamoCombiner::resolveMiddleSingle(wchar_t x)
{
	wchar_t M = L'��' + (((x-0xAC00) % 0x24B) / 0x1C);
	if (M == L'��') return L'��';
	if (M == L'��') return L'��';
	if (M == L'��') return L'��';
	if (M == L'��') return L'��';
	if (M == L'��') return L'��';
	if (M == L'��') return L'��';
	if (M == L'��') return L'��';
	return M;
}
wchar_t JamoCombiner::resolveFinal(wchar_t x)
{
	static const wchar_t End[28] = {0, L'��', L'��', L'��', L'��', L'��', L'��', L'��',
									L'��', L'��', L'��', L'��', L'��', L'��', L'��',
									L'��', L'��', L'��', L'��', L'��', L'��', L'��',
									L'��', L'��', L'��', L'��', L'��' };
	return End[((x-0xAC00) %  0x1C)];
}
wchar_t JamoCombiner::resolveFinalSingle(wchar_t x)
{
	wchar_t px = x;
	px -= 0xAC00;
	px = px % 0x1C;
	if (px == 0x1 || px==0x9) return L'��';
	else if (px == 0x2)	return L'��';
	else if (px == 0x3 || px == 0xC || px == 0x12 || px == 0x13) return L'��';
	else if (px == 0x4)	return L'��';
	else if (px == 0x5 || px == 0x16) return L'��';
	else if (px == 0x6 || px == 0xF || px == 0x1B) return L'��';
	else if (px == 0x7) return L'��';
	else if (px == 0x8)	return L'��';
	else if (px == 0xA || px == 0x10) return L'��';
	else if (px == 0xB || px == 0x11) return L'��';
	else if (px == 0xD || px == 0x19) return L'��';
	else if (px == 0xE || px == 0x1A) return L'��';
	else if (px == 0x14) return L'��';
	else if (px == 0x15) return L'��';
	else if (px == 0x17) return L'��';
	else if (px == 0x18) return L'��';
	return 0;
}

void init(set<wchar_t>& J, set<wchar_t>& M)
{
	J.insert(L'��');
	J.insert(L'��');
	J.insert(L'��');
	J.insert(L'��');
	J.insert(L'��');
	J.insert(L'��');
	J.insert(L'��');
	J.insert(L'��');
	J.insert(L'��');
	J.insert(L'��');
	J.insert(L'��');
	J.insert(L'��');
	J.insert(L'��');
	J.insert(L'��');
	J.insert(L'��');
	J.insert(L'��');
	J.insert(L'��');
	J.insert(L'��');
	J.insert(L'��');
	M.insert(L'��');
	M.insert(L'��');
	M.insert(L'��');
	M.insert(L'��');
	M.insert(L'��');
	M.insert(L'��');
	M.insert(L'��');
	M.insert(L'��');
	M.insert(L'��');
	M.insert(L'��');
	M.insert(L'��');
	M.insert(L'��');
	M.insert(L'��');
	M.insert(L'��');
	M.insert(L'��');
	M.insert(L'��');
	M.insert(L'��');
	M.insert(L'��');
	M.insert(L'��');
	M.insert(L'��');
	M.insert(L'��');
}

void HandleThirdLetter(wchar_t firstLetter, wchar_t secondLetter,
	wchar_t thirdLetter, wchar_t indx,
	map<wchar_t, map<wchar_t, wchar_t>>& s_pMap)
{
	if (thirdLetter == L'��')
	{
		s_pMap[indx][L'��'] = indx + 1; // ��
		s_pMap[indx + 1][L'��'] = indx + 3; //��
		s_pMap[indx + 1][DEL] = indx;
		s_pMap[indx + 3][DEL] = indx + 1;
	}
	if (thirdLetter == L'��')
	{
		s_pMap[indx][L'��'] = indx + 2; // ��
		s_pMap[indx + 2][DEL] = indx;
	}
	if (thirdLetter == L'��')
	{
		s_pMap[indx][L'��'] = indx + 4; // ��
		s_pMap[indx + 4][L'��'] = indx + 5; // ��
		s_pMap[indx + 4][L'��'] = indx + 6; // ��
		s_pMap[indx + 4][DEL] = indx;
		s_pMap[indx + 5][DEL] = indx + 4;
		s_pMap[indx + 6][DEL] = indx + 4;
	}
	if (thirdLetter == L'��')
	{
		s_pMap[indx][L'��'] = indx + 7; // ��
		s_pMap[indx + 7][DEL] = indx;
	}
	if (thirdLetter == L'��')
	{
	}
	if (thirdLetter == L'��')
	{
		s_pMap[indx][L'��'] = indx + 8; // ��
		s_pMap[indx + 8][L'��'] = indx + 9; // ��
		s_pMap[indx + 8][L'��'] = indx + 10; // ��
		s_pMap[indx + 8][L'��'] = indx + 11; // ��
		s_pMap[indx + 8][L'��'] = indx + 12; // ��
		s_pMap[indx + 8][L'��'] = indx + 13; // ��
		s_pMap[indx + 8][L'��'] = indx + 14; // ��
		s_pMap[indx + 8][L'��'] = indx + 15; // ��
		s_pMap[indx + 8][DEL] = indx;
		s_pMap[indx + 9][DEL] = indx + 8;
		s_pMap[indx + 10][DEL] = indx + 8;
		s_pMap[indx + 11][DEL] = indx + 8;
		s_pMap[indx + 12][DEL] = indx + 8;
		s_pMap[indx + 13][DEL] = indx + 8;
		s_pMap[indx + 14][DEL] = indx + 8;
		s_pMap[indx + 15][DEL] = indx + 8;
	}
	if (thirdLetter == L'��')
	{
		s_pMap[indx][L'��'] = indx + 16; // ��
		s_pMap[indx + 16][DEL] = indx;
	}
	if (thirdLetter == L'��')
	{
		s_pMap[indx][L'��'] = indx + 17; // ��
		s_pMap[indx + 17][L'��'] = indx + 18; // ��
		s_pMap[indx + 17][DEL] = indx;
		s_pMap[indx + 18][DEL] = indx + 17;
	}
	if (thirdLetter == L'��')
	{
	}
	if (thirdLetter == L'��')
	{
		s_pMap[indx][L'��'] = indx + 19; // ��
		s_pMap[indx + 19][DEL] = indx;
	}
	if (thirdLetter == L'��')
	{
		s_pMap[indx][L'��'] = indx + 20; // ��
		s_pMap[indx + 20][DEL] = indx;
	}
	if (thirdLetter == L'��')
	{
		s_pMap[indx][L'��'] = indx + 21; // ��
		s_pMap[indx + 21][DEL] = indx;
	}
	if (thirdLetter == L'��')
	{
		s_pMap[indx][L'��'] = indx + 22; // ��
		s_pMap[indx + 22][DEL] = indx;
	}
	if (thirdLetter == L'��')
	{
	}
	if (thirdLetter == L'��')
	{
		s_pMap[indx][L'��'] = indx + 23; // ��
		s_pMap[indx + 23][DEL] = indx;
	}
	if (thirdLetter == L'��')
	{
		s_pMap[indx][L'��'] = indx + 24; // ��
		s_pMap[indx + 24][DEL] = indx;
	}
	if (thirdLetter == L'��')
	{
		s_pMap[indx][L'��'] = indx + 25; // ��
		s_pMap[indx + 25][DEL] = indx;
	}
	if (thirdLetter == L'��')
	{
		s_pMap[indx][L'��'] = indx + 26; // ��
		s_pMap[indx + 26][DEL] = indx;
	}
	if (thirdLetter == L'��')
	{
		s_pMap[indx][L'��'] = indx + 27; // ��
		s_pMap[indx + 27][DEL] = indx;
	}
}