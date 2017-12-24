#include "stdafx.h"
#include "fun.h"
#include <time.h>



string Hex2bin(CStringA strHex)
{
	string strRet;
	DWORD dwCur = 0;

	strHex.Remove(' ');
	strHex.MakeLower();

	strRet.resize(strHex.GetLength() / 2);

	while (strHex.GetLength() >= 2)
	{		
		CStringA strTemp = strHex.Left(2);
		strHex = strHex.Mid(2);

		DWORD dwHex = 0;

		unsigned char c = strTemp[0];
		if (c >= '0' && c <= '9')
		{
			dwHex += (c - '0') * 16;
		}
		else if (c >= 'a' && c <= 'f')
		{
			dwHex += (c - 'a' + 10) * 16;
		}
		else
		{
			continue;
		}

		c = strTemp[1];
		if (c >= '0' && c <= '9')
		{
			dwHex += (c - '0');
		}
		else if (c >= 'a' && c <= 'f')
		{
			dwHex += (c - 'a' + 10);
		}
		else
		{
			continue;
		}

		strRet[dwCur++] = dwHex;
	}

	return strRet;
}

std::string Bin2Hex(string &strBin)
{
	string str;
	char szTemp[10] = { 0 };

	for (int i=0;i<strBin.size();i++)
	{
		sprintf(szTemp,"%02x ",(unsigned char)strBin[i]);
		str = str + szTemp;
	}

	return str;
}

CStringA CStringA2Utf8(CStringA strGbk)
{
	CString strUnicode = CA2W(strGbk);
	
	CStringA strUtf8;

	int nLen = WideCharToMultiByte(CP_UTF8, 0, strUnicode, -1, NULL, 0, NULL, NULL);

	WideCharToMultiByte(CP_UTF8, 0, strUnicode, -1, strUtf8.GetBuffer(nLen + 1), nLen, NULL, NULL);
	strUtf8.ReleaseBuffer();

	return strUtf8;
}

CStringA Utf82CStringA(CStringA strUtf8)
{
	CString strUnicode;

	int nLen = MultiByteToWideChar(CP_UTF8, 0, strUtf8, -1, NULL, 0);

	MultiByteToWideChar(CP_UTF8, 0, strUtf8, -1, strUnicode.GetBuffer(nLen + 1), nLen);
	strUnicode.ReleaseBuffer();
	
	return CW2A(strUnicode);
}

string Dword2String(DWORD dw)
{
	DWORD dwData = dw;
	DWORD dwData2 = 0x80 * 0x80 * 0x80 * 0x80;
	int nLen = 4;
	byte hex[5] = { 0 };
	DWORD dwOutLen = 0;

	while (nLen > 0)
	{
		if (dwData > dwData2)
		{
			hex[nLen] = dwData / dwData2;
			dwData = dwData % dwData2;
			dwOutLen++;
		}

		dwData2 /= 0x80;
		nLen--;
	}

	hex[0] = dwData;
	dwOutLen++;

	for (int i = 0; i < (int)(dwOutLen - 1); i++)
	{
		hex[i] += 0x80;
	}

	return string((const char *)hex, dwOutLen);
}

DWORD String2Dword(string str, DWORD &dwOutLen)
{
	DWORD dwLen = str.size();

	if (!dwLen)	return 0;


	DWORD dwRet = 0;
	DWORD dwTemp = 1;
	int nLen = 0;
	while (nLen < 5 && nLen<dwLen)
	{
		unsigned char c = (unsigned char)str[nLen];

		if (!(c >> 7))
		{
			dwRet += c * dwTemp;
			nLen++;
			break;
		}
		else
		{
			dwRet += (c & 0x7f) * dwTemp;
			dwTemp *= 0x80;
			nLen++;
		}
	}

	dwOutLen = nLen;

	return dwRet;
}

CStringA Utc2BeijingTime(DWORD dwUtc)
{
	CStringA strTime;

	time_t utc = dwUtc;
	struct tm *tmdate = localtime(&utc);

	strTime.Format("%d-%02d-%02d %02d:%02d:%02d", 
		tmdate->tm_year + 1900, tmdate->tm_mon + 1 , tmdate->tm_mday, tmdate->tm_hour, tmdate->tm_min,tmdate->tm_sec);

	return strTime;
}

