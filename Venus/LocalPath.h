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
	// ��ջ����¼
	void CleanIndex();

private:
	// ��ȡ�����ļ�����Ϣ�ຯ��
	string GetExePath(void);
	void CheckFolderExist(string lnkpath);
	int endsWith(char s1[],char s2[]);
	void getFiles(string path, vector<ShortCut>& files);
	wchar_t* CharToWchar(const char* c);
	bool ReadShortcut(LPWSTR lpwLnkFile, LPSTR lpDescFile);

private:
	map<CString, CString> index;
	string strLocalPath;
};

