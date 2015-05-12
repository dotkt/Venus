#pragma once

#include <map>
#include <vector>
#include <string>
#include <io.h>
#include <direct.h>
#include <ShlObj.h>

using namespace std;

typedef struct tagShortCut
{
	string fileName;
	string filePath;
}ShortCut;

// ������Դ��
class LocalPath
{
public:
	LocalPath(void);
	~LocalPath(void);

	// ��ʼ������������
	void InitIndex();
	// ��ƥ���ֵ
	bool FindIndex(CString key, vector<CString> &matchs);
	// ��ȷ��ȡֵ
	CString GetLocalPath(CString key);

private:
	map<CString, CString> index;
};

