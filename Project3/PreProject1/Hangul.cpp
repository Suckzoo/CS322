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

	s_pMap[L'で'][L'た'] = L'と';
	s_pMap[L'で'][L'だ'] = L'ど';
	s_pMap[L'で'][L'び'] = L'な';
	s_pMap[L'ぬ'][L'っ'] = L'ね';
	s_pMap[L'ぬ'][L'つ'] = L'の';
	s_pMap[L'ぬ'][L'び'] = L'は';
	s_pMap[L'ぱ'][L'び'] = L'ひ';
	s_pMap[L'と'][DEL] = L'で';
	s_pMap[L'ど'][DEL] = L'で';
	s_pMap[L'な'][DEL] = L'で';
	s_pMap[L'ね'][DEL] = L'ぬ';
	s_pMap[L'の'][DEL] = L'ぬ';
	s_pMap[L'は'][DEL] = L'ぬ';
	s_pMap[L'ひ'][DEL] = L'ぱ';

	wchar_t indx = 0xAC00;
	for (auto firstLetter : J)
	{
		for (auto secondLetter : M)
		{
			s_pMap[firstLetter][secondLetter] = indx;
			if (wstring(L"とどなねのはひ").find(JamoCombiner::resolveMiddle(indx))
				== wstring::npos)
			{
				s_pMap[indx][DEL] = firstLetter;
			}

			if (secondLetter == L'で')
			{
				s_pMap[indx][L'た'] = indx + (0x1C);
				s_pMap[indx][L'だ'] = indx + (0x1C * 2);
				s_pMap[indx][L'び'] = indx + (0x1C * 3);
				s_pMap[indx + (0x1C)][DEL] = indx;
				s_pMap[indx + (0x1C * 2)][DEL] = indx;
				s_pMap[indx + (0x1C * 3)][DEL] = indx;
			}
			if (secondLetter == L'ぬ')
			{
				s_pMap[indx][L'っ'] = indx + (0x1C);
				s_pMap[indx][L'つ'] = indx + (0x1C * 2);
				s_pMap[indx][L'び'] = indx + (0x1C * 3);
				s_pMap[indx + (0x1C)][DEL] = indx;
				s_pMap[indx + (0x1C * 2)][DEL] = indx;
				s_pMap[indx + (0x1C * 3)][DEL] = indx;
			}
			if (secondLetter == L'ぱ')
			{
				s_pMap[indx][L'び'] = indx + (0x1C);
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
	s_pMobile[L'1'] = L'ぁ';
	s_pMobileFunctionalMap[L'ぁ'][L'q'] = L'あ';
	s_pMobileFunctionalMap[L'ぁ'][L'p'] = L'せ';
	s_pMobile[L'2'] = L'い';
	s_pMobileFunctionalMap[L'い'][L'p'] = L'ぇ';
	s_pMobileFunctionalMap[L'ぇ'][L'q'] = L'え';
	s_pMobileFunctionalMap[L'ぇ'][L'p'] = L'ぜ';
	s_pMobile[L'4'] = L'ぉ';
	s_pMobile[L'5'] = L'け';
	s_pMobileFunctionalMap[L'け'][L'p'] = L'げ';
	s_pMobileFunctionalMap[L'げ'][L'q'] = L'こ';
	s_pMobileFunctionalMap[L'げ'][L'p'] = L'そ';
	s_pMobile[L'7'] = L'さ';
	s_pMobileFunctionalMap[L'さ'][L'q'] = L'ざ';
	s_pMobileFunctionalMap[L'さ'][L'p'] = L'じ';
	s_pMobileFunctionalMap[L'じ'][L'q'] = L'す';
	s_pMobileFunctionalMap[L'じ'][L'p'] = L'ず';
	s_pMobile[L'8'] = L'し';
	s_pMobileFunctionalMap[L'し'][L'p'] = L'ぞ';

	//Mobile M section
	s_pMobile[L'3'] = L'た';
	s_pMobileFunctionalMap[L'た'][L'p'] = L'ち';
	s_pMobileFunctionalMap[L'ち'][L'9'] = L'ぢ';
	s_pMobileFunctionalMap[L'た'][L'9'] = L'だ';
	s_pMobileFunctionalMap[L'た'][L'3'] = L'っ';
	s_pMobileFunctionalMap[L'っ'][L'9'] = L'つ';
	s_pMobileFunctionalMap[L'っ'][L'p'] = L'づ';
	s_pMobileFunctionalMap[L'づ'][L'9'] = L'て';

	s_pMobile[L'6'] = L'で';
	s_pMobileFunctionalMap[L'で'][L'9'] = L'な';
	s_pMobileFunctionalMap[L'で'][L'3'] = L'と';
	s_pMobileFunctionalMap[L'と'][L'9'] = L'ど';
	s_pMobileFunctionalMap[L'で'][L'p'] = L'に';
	s_pMobileFunctionalMap[L'で'][L'6'] = L'ぬ';
	s_pMobileFunctionalMap[L'ぬ'][L'9'] = L'は';
	s_pMobileFunctionalMap[L'ぬ'][L'3'] = L'ね';
	s_pMobileFunctionalMap[L'ね'][L'9'] = L'の';
	s_pMobileFunctionalMap[L'ぬ'][L'p'] = L'ば';
	
	s_pMobile[L'9'] = L'び';
	s_pMobileFunctionalMap[L'ぱ'][L'0'] = L'ひ';

	s_pMobile[L'0'] = L'ぱ';
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
	return  (wstring(L"ぁあいぇえぉけげこさざしじすずせぜそぞ").at((x - 0xAC00) / 0x24B));
}
wchar_t JamoCombiner::resolveMiddle(wchar_t x)
{
	return L'た' + (((x-0xAC00) % 0x24B) / 0x1C);
}
wchar_t JamoCombiner::resolveMiddleSingle(wchar_t x)
{
	wchar_t M = L'た' + (((x-0xAC00) % 0x24B) / 0x1C);
	if (M == L'と') return L'た';
	if (M == L'ど') return L'だ';
	if (M == L'な') return L'び';
	if (M == L'ね') return L'っ';
	if (M == L'の') return L'つ';
	if (M == L'は') return L'び';
	if (M == L'ひ') return L'び';
	return M;
}
wchar_t JamoCombiner::resolveFinal(wchar_t x)
{
	static const wchar_t End[28] = {0, L'ぁ', L'あ', L'ぃ', L'い', L'ぅ', L'う', L'ぇ',
									L'ぉ', L'お', L'か', L'が', L'き', L'ぎ', L'く',
									L'ぐ', L'げ', L'ご', L'さ', L'ざ', L'し', L'じ',
									L'ず', L'せ', L'ぜ', L'そ', L'ぞ' };
	return End[((x-0xAC00) %  0x1C)];
}
wchar_t JamoCombiner::resolveFinalSingle(wchar_t x)
{
	wchar_t px = x;
	px -= 0xAC00;
	px = px % 0x1C;
	if (px == 0x1 || px==0x9) return L'ぁ';
	else if (px == 0x2)	return L'あ';
	else if (px == 0x3 || px == 0xC || px == 0x12 || px == 0x13) return L'さ';
	else if (px == 0x4)	return L'い';
	else if (px == 0x5 || px == 0x16) return L'じ';
	else if (px == 0x6 || px == 0xF || px == 0x1B) return L'ぞ';
	else if (px == 0x7) return L'ぇ';
	else if (px == 0x8)	return L'ぉ';
	else if (px == 0xA || px == 0x10) return L'け';
	else if (px == 0xB || px == 0x11) return L'げ';
	else if (px == 0xD || px == 0x19) return L'ぜ';
	else if (px == 0xE || px == 0x1A) return L'そ';
	else if (px == 0x14) return L'ざ';
	else if (px == 0x15) return L'し';
	else if (px == 0x17) return L'ず';
	else if (px == 0x18) return L'せ';
	return 0;
}

void init(set<wchar_t>& J, set<wchar_t>& M)
{
	J.insert(L'ぁ');
	J.insert(L'あ');
	J.insert(L'い');
	J.insert(L'ぇ');
	J.insert(L'え');
	J.insert(L'ぉ');
	J.insert(L'け');
	J.insert(L'げ');
	J.insert(L'こ');
	J.insert(L'さ');
	J.insert(L'ざ');
	J.insert(L'し');
	J.insert(L'じ');
	J.insert(L'す');
	J.insert(L'ず');
	J.insert(L'せ');
	J.insert(L'ぜ');
	J.insert(L'そ');
	J.insert(L'ぞ');
	M.insert(L'た');
	M.insert(L'だ');
	M.insert(L'ち');
	M.insert(L'ぢ');
	M.insert(L'っ');
	M.insert(L'つ');
	M.insert(L'づ');
	M.insert(L'て');
	M.insert(L'で');
	M.insert(L'と');
	M.insert(L'ど');
	M.insert(L'な');
	M.insert(L'に');
	M.insert(L'ぬ');
	M.insert(L'ね');
	M.insert(L'の');
	M.insert(L'は');
	M.insert(L'ば');
	M.insert(L'ぱ');
	M.insert(L'ひ');
	M.insert(L'び');
}

void HandleThirdLetter(wchar_t firstLetter, wchar_t secondLetter,
	wchar_t thirdLetter, wchar_t indx,
	map<wchar_t, map<wchar_t, wchar_t>>& s_pMap)
{
	if (thirdLetter == L'ぁ')
	{
		s_pMap[indx][L'ぁ'] = indx + 1; // ぁ
		s_pMap[indx + 1][L'さ'] = indx + 3; //ぃ
		s_pMap[indx + 1][DEL] = indx;
		s_pMap[indx + 3][DEL] = indx + 1;
	}
	if (thirdLetter == L'あ')
	{
		s_pMap[indx][L'あ'] = indx + 2; // あ
		s_pMap[indx + 2][DEL] = indx;
	}
	if (thirdLetter == L'い')
	{
		s_pMap[indx][L'い'] = indx + 4; // い
		s_pMap[indx + 4][L'じ'] = indx + 5; // ぅ
		s_pMap[indx + 4][L'ぞ'] = indx + 6; // う
		s_pMap[indx + 4][DEL] = indx;
		s_pMap[indx + 5][DEL] = indx + 4;
		s_pMap[indx + 6][DEL] = indx + 4;
	}
	if (thirdLetter == L'ぇ')
	{
		s_pMap[indx][L'ぇ'] = indx + 7; // ぇ
		s_pMap[indx + 7][DEL] = indx;
	}
	if (thirdLetter == L'え')
	{
	}
	if (thirdLetter == L'ぉ')
	{
		s_pMap[indx][L'ぉ'] = indx + 8; // ぉ
		s_pMap[indx + 8][L'ぁ'] = indx + 9; // お
		s_pMap[indx + 8][L'け'] = indx + 10; // か
		s_pMap[indx + 8][L'げ'] = indx + 11; // が
		s_pMap[indx + 8][L'さ'] = indx + 12; // き
		s_pMap[indx + 8][L'ぜ'] = indx + 13; // ぎ
		s_pMap[indx + 8][L'そ'] = indx + 14; // く
		s_pMap[indx + 8][L'ぞ'] = indx + 15; // ぐ
		s_pMap[indx + 8][DEL] = indx;
		s_pMap[indx + 9][DEL] = indx + 8;
		s_pMap[indx + 10][DEL] = indx + 8;
		s_pMap[indx + 11][DEL] = indx + 8;
		s_pMap[indx + 12][DEL] = indx + 8;
		s_pMap[indx + 13][DEL] = indx + 8;
		s_pMap[indx + 14][DEL] = indx + 8;
		s_pMap[indx + 15][DEL] = indx + 8;
	}
	if (thirdLetter == L'け')
	{
		s_pMap[indx][L'け'] = indx + 16; // け
		s_pMap[indx + 16][DEL] = indx;
	}
	if (thirdLetter == L'げ')
	{
		s_pMap[indx][L'げ'] = indx + 17; // げ
		s_pMap[indx + 17][L'さ'] = indx + 18; // ご
		s_pMap[indx + 17][DEL] = indx;
		s_pMap[indx + 18][DEL] = indx + 17;
	}
	if (thirdLetter == L'こ')
	{
	}
	if (thirdLetter == L'さ')
	{
		s_pMap[indx][L'さ'] = indx + 19; // さ
		s_pMap[indx + 19][DEL] = indx;
	}
	if (thirdLetter == L'ざ')
	{
		s_pMap[indx][L'ざ'] = indx + 20; // ざ
		s_pMap[indx + 20][DEL] = indx;
	}
	if (thirdLetter == L'し')
	{
		s_pMap[indx][L'し'] = indx + 21; // し
		s_pMap[indx + 21][DEL] = indx;
	}
	if (thirdLetter == L'じ')
	{
		s_pMap[indx][L'じ'] = indx + 22; // じ
		s_pMap[indx + 22][DEL] = indx;
	}
	if (thirdLetter == L'す')
	{
	}
	if (thirdLetter == L'ず')
	{
		s_pMap[indx][L'ず'] = indx + 23; // ず
		s_pMap[indx + 23][DEL] = indx;
	}
	if (thirdLetter == L'せ')
	{
		s_pMap[indx][L'せ'] = indx + 24; // せ
		s_pMap[indx + 24][DEL] = indx;
	}
	if (thirdLetter == L'ぜ')
	{
		s_pMap[indx][L'ぜ'] = indx + 25; // ぜ
		s_pMap[indx + 25][DEL] = indx;
	}
	if (thirdLetter == L'そ')
	{
		s_pMap[indx][L'そ'] = indx + 26; // そ
		s_pMap[indx + 26][DEL] = indx;
	}
	if (thirdLetter == L'ぞ')
	{
		s_pMap[indx][L'ぞ'] = indx + 27; // ぞ
		s_pMap[indx + 27][DEL] = indx;
	}
}