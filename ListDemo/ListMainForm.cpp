#include "StdAfx.h"
#include "ListMainForm.h"
#include "MenuWnd.h"
#include "flash10a.tlh"
#include <afx.h>
#include <string>
#include <iostream>
#include <windows.h>  
#include <commdlg.h> 

#define key 10
#define value 10

using namespace std;

using namespace DuiLib;

#define TIMER_ID_TEST 100
#define TIMER_TIME_TEST 1000

/*
* ��ŵڶ�������
*/
std::vector<std::string> domain;

/*
* ��ŵ���������
*/
std::vector<std::string> desc;

std::vector<std::string> edit;

/**
��ʼ��UI�ؼ�
*/
void ListMainForm::Init()
{
	m_pCloseBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("closebtn")));
	//static_cast ǿ������ת����_T ���������ĵ�16.2С��
	m_pMaxBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("maxbtn")));
	m_pRestoreBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("restorebtn")));
	m_pMinBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("minbtn")));
	m_pSearch = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_search")));

	m_pChangeimg = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_changeimg")));
	m_pQRcode = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_QRcode")));
	m_pLogo = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_logo")));
	m_pSetting = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_setting")));
	m_pReturn = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_return")));

	m_pbkc_default = static_cast<CButtonUI*>(m_pm.FindControl(_T("default")));
	m_pbkc_lightblue = static_cast<CButtonUI*>(m_pm.FindControl(_T("lightblue")));
	m_pbkc_green = static_cast<CButtonUI*>(m_pm.FindControl(_T("green")));
	m_pbkc_red = static_cast<CButtonUI*>(m_pm.FindControl(_T("red")));
	m_pbkc_bkiamge = static_cast<CButtonUI*>(m_pm.FindControl(_T("bkiamge")));

	m_pLogin = static_cast<CHorizontalLayoutUI*>(m_pm.FindControl(_T("btn_QQLogion")));
	m_pSkinlayout = static_cast<CVerticalLayoutUI*>(m_pm.FindControl(_T("skinlayout")));
	m_pLoginpage = static_cast<CVerticalLayoutUI*>(m_pm.FindControl(_T("loginpage")));
	m_pMainbk = static_cast<CVerticalLayoutUI*>(m_pm.FindControl(_T("mainbk")));
	m_pQRcodepage = static_cast<CHorizontalLayoutUI*>(m_pm.FindControl(_T("QRcodepage")));

	m_pEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("edit")));
	m_pUNEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("userNmae_Edit")));
	m_pPwdEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("passWord_Edit")));

	m_pWebBrowser = static_cast<CWebBrowserUI*>(m_pm.FindControl(_T("web")));
}

//�����Ҳ�����ȥ��
void ListMainForm::Format(string& str) {
	if (str.length() && str[0] == 34) {//�жϣ������������޳�����
		str = str.substr(1, str.length() - 2);
	}
}

void ListMainForm::StrSplit(const string& str, string& str_Key, string& str_Value) {
	//char a = ':';
	int len = str.find(':'); //��key value�ֿ�
	str_Key = str.substr(0, len);//key
	str_Value = str.substr(len + 1, str.length());//value
	Format(str_Key);
	Format(str_Value);
}


//��ȡ��ֵ��
map<string, string> ListMainForm::GetUrlInfo(const string& strRsp) {
	map<string, string>UserInfoMap;
	string str="";
	for (int index = 1; index < strRsp.length() - 1; index++) {
		if (strRsp[index] != ',' && index != strRsp.length() - 2 || strRsp[index] == ',' && strRsp[index+1]!=34) {
			str += strRsp[index];
		}
		else {
			if (index == strRsp.length() - 2)
				str += strRsp[index];
			string str_Key="", str_Value="";
			StrSplit(str, str_Key, str_Value);
			UserInfoMap.insert(make_pair(str_Key, str_Value));
			str.clear();
		}
	}
	return UserInfoMap;
}

CString UTF82WCS(const char* szU8)
{
	//Ԥת�����õ�����ռ�Ĵ�С;
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);

	//����ռ�Ҫ��'\0'�����ռ䣬MultiByteToWideChar�����'\0'�ռ�
	wchar_t* wszString = new wchar_t[wcsLen + 1];

	//ת��
	::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);

	//������'\0'
	wszString[wcsLen] = '\0';

	CString unicodeString(wszString);


	delete[] wszString;
	wszString = NULL;

	return unicodeString;
}

//char* UTF8ToUnicode(char* szUTF8)
//{
//	int wcscLen = ::MultiByteToWideChar(CP_UTF8, NULL, szUTF8, strlen(szUTF8), NULL, 0);//�õ�����ռ�Ĵ�С
//	wchar_t* wszcString = new wchar_t[wcscLen + 1];//��'\0'����ռ�
//	::MultiByteToWideChar(CP_UTF8, NULL, szUTF8, strlen(szUTF8), wszcString, wcscLen);   //ת��
//	wszString[wcsLen] = '\0';
//	char *m_char;
//	int len = WideCharToMultiByte(CP_ACP, 0, wszcString, wcslen(wszcString), NULL, 0, NULL, NULL);
//	m_char = new char[len + 1];
//	WideCharToMultiByte(CP_ACP, 0, wszcString, wcslen(wszcString), m_char, len, NULL, NULL);
//	m_char[len] = '\0';
//	return m_char;
//}



/**
*����һ��ȫ�ֲ��Ժ�����������ListMainForm�ࡣ
*һ��������ĺ���Ӧ�ú���������أ�����ɵĺ�����Ҫ��������������Utils��
*
*/
//void TestMemoryFunc()
//{
//	int* array = new int[10]; //ʹ��vs�ṩ���ڴ�鿴���߿��Ե�֪ ������ڴ��������ģ�����ͨ��memset��ͳһ��ʼ���ڴ�
//	memset(array, 0x0F, sizeof(int) * 10);
//
//
//	char chInput[512];
//	sprintf(chInput, "int:%d\n", array[0]);//�ֶ��޸��ڴ棬 �뽫array�еĵ�һ�����ִ�С�޸�Ϊ15��
//	DUITRACE(_T("array---[0]: %s"), chInput);//ע���ô˷������������Ϣ��vs�ĵ��Դ�����
//
//	//OutputDebugString(chInput);
//
//	//TestMem* m;
//	//for (int i = 0; i < 190464; i++) {
//	//	m =new  TestMem;
//	//	m->count = 15;
//	//}
//}

DWORD WINAPI ListMainForm::Search(LPVOID lpParameter)
{
	//TestMemoryFunc();

	try
	{
		struct Prama* prama = (struct Prama *)lpParameter;//ָ������ת������void* ת��ΪĿ��ָ������
		CListUI* pList = prama->pList;
		CButtonUI* pSearch = prama->pSearch;
		CDuiString tDomain = prama->tDomain;
		//-------------------------------------
		/*
		* �������ѭ��
		*/
		for (int i = 0; i < 100; i++)
		{
			std::stringstream ss;//ʹ��stringstream�����ַ���ƴ�� 
			ss << "www." << i << ".com";
			domain.push_back(ss.str());
			ss.clear();
			ss << "it's " << i;
			desc.push_back(ss.str());
			CListTextElementUI* pListElement = new CListTextElementUI;
			pListElement->SetTag(i);
			if (pListElement != NULL)
			{
				::PostMessage(prama->hWnd, WM_ADDLISTITEM, 0L, (LPARAM)pListElement);
			}
			/*
			*	Sleep Ϊ��չʾ��ӵĶ�̬Ч�����ʷ���������ٶȣ�ͬʱ���Կ�����ӹ����н�����Ȼ������Ӧ
			*/
			::Sleep(100);
		}
		
		delete prama;//һ��Ҫɾ��������������������ڴ�й©��new Prama��deleteҪ�ɶԳ���


		pSearch->SetEnabled(true);
		return 0;
	}
	catch (...)
	{
		return 0;
	}
}



void ListMainForm::Login()
{
	::MessageBox(NULL, "��¼�ɹ�", _T("��ʾ"), MB_OK);
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
	//WinExec("D:\\c++Study\\duilib_new\\duilib_teach\\bin\\QQDemo.exe", SW_SHOW);
}


LPTSTR GetImgPath() {
	OPENFILENAME ofn;
	char szFile[1000];
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "All\0*.*\0" "PNG(*.png)\0*.png\0" "BMP(*.bmp)\0*.bmp\0" "JPEG(*.jpg,*.jpeg)\0*.jpg;*.jpeg\0" "GIF(*.gif)\0*.gif\0";

	LPTSTR path_image;
	if (GetOpenFileName(&ofn)) {
		path_image = ofn.lpstrFile;
		return path_image;
	}
	else {
		return 0;
	}
}

//ͨ��SetWindowPosѭ��ʵ�ִ��ڶ���
void ListMainForm::ShakeWnd()
{
	// TODO: Add your control notification handler code here
	//CDuiRect rcWnd;
	//::GetWindowRect(*this, &rcWnd);
	int m_move = 5;
	//PlaySound("shake.wav", NULL, SND_FILENAME | SND_ASYNC);
	//Ϊ��ʹ���ڶ������ܻص�ԭ����λ�ã���������i����Ϊ5�ı�������i<5*n+1;
	SetWindowPos(m_hWnd, NULL, 492,216, 385, 295, SWP_SHOWWINDOW);
	for (int i = 1; i < 11; i++)
	{
		//rcWnd.Offset(0, m_move);//OffsetRect������ָ���ľ����ƶ���ָ����λ��,�����ǽ����������ƶ�5����   ��������Ϊ�����ƺ�������
		SetWindowPos(m_hWnd, NULL, 492 ,(216 - m_move), 385, 295, SWP_SHOWWINDOW);
		//MoveWindow(m_hWnd, rcWnd.left, rcWnd.right, rcWnd.GetWidth(), rcWnd.GetHeight(), SWP_SHOWWINDOW);
		Sleep(40);
		//rcWnd.Offset(m_move, 0);
		//SetWindowPos(m_hWnd, NULL, 385, 205, 200, 200, SWP_SHOWWINDOW);
		SetWindowPos(m_hWnd, NULL, (492 - m_move), 216, 385, 295, SWP_SHOWWINDOW);
		Sleep(40);
		if (5 == m_move)
		{
			m_move = -5;
		}
		else
		{
			m_move = 5;
		}
	}
	SetWindowPos(m_hWnd, NULL, 492, 216, 385, 295, SWP_SHOWWINDOW);
}

void ListMainForm::ChangeImg()
{
	LPTSTR path_image = 0;
	CDuiString path_temp = m_pEdit->GetText();
	if (!access(path_temp, 0))
	{
		m_pChangeimg->SetNormalImage(path_temp);
		m_pEdit->SetText(_T("    ��ϲ�㣡ͷ������ɹ�"));
	}
	else
		path_image = GetImgPath();

	if (path_image != 0)
	{
		m_pChangeimg->SetNormalImage(_T(path_image));
		m_pEdit->SetText(_T("��ַ:") + _bstr_t(path_image));
	}
	else if(path_image == 0 && access(path_temp, 0) == -1)
		m_pEdit->SetText(_T("    ��ѡ����ȷ��ͼƬ·��"));
}


static size_t DownloadCallback(void *buffer, size_t sz, size_t nmemb, void *writer)
{
	string* psResponse = (string*)writer;
	size_t size = sz * nmemb;
	psResponse->append((char*)buffer, size);

	return sz * nmemb;
	
}

bool ListMainForm::CheckUInfo(string str_UN, string str_Pwd) {
	if (str_UN == "" && str_Pwd == "") {
		::MessageBox(NULL, "�û��������벻��Ϊ�գ����鲢��������", _T("��ʾ"), MB_OK);
		return false;
	}
	else if (str_UN == "") {
		::MessageBox(NULL, "�û�������Ϊ�գ����鲢��������", _T("��ʾ"), MB_OK);
		return false;
	}
	else if (str_Pwd == "") {
		::MessageBox(NULL, "���벻��Ϊ�գ����鲢��������", _T("��ʾ"), MB_OK);
		return false;
	}
	else
		return true;
}

string ListMainForm::GetUserInfo(CEditUI* m_pUNEdit, CEditUI* m_pPwdEdit) {
	string str_UN = m_pUNEdit->GetText();
	string str_Pwd = m_pPwdEdit->GetText();
	string str_UInfo = "";
	if(CheckUInfo(str_UN, str_Pwd)){
	str_UInfo = "username=" + str_UN + "&pwd=" + str_Pwd;
	}
	else {
		str_UInfo = "";
	}
	return str_UInfo;
	
	
}

//
string ComboSetopt(CURL *curl,string strUrl,string strTmpStr) {
	//string* p1 = &strTmpStr;
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 2);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DownloadCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strTmpStr);
	CURLcode res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	string strRsp;
	if (res != CURLE_OK)
	{
		strRsp = "error";
	}
	else
	{
		strRsp = strTmpStr;
	}
	return strRsp;
}

static string GetCodeNum(string urlContent) {
	if (urlContent.length() >= 8) {
		basic_string<char>str_CodeNum = urlContent.substr(8, 1);
		return str_CodeNum;
	}
	else if (urlContent == "error")
	{
		return "0";
	}
}

static string GetUrlContent(string str_UInfo)
{
	string strUrl = "http://localhost:8081/login?"+str_UInfo;//username=ljm&pwd=111111
	string strTmpStr="";
	string* p2 = &strTmpStr;
	CURL *curl= NULL;
	string urlContent = ComboSetopt(curl, strUrl, *p2);//�������Ϻ�����װһϵ��curl_easy_setopt
	//CURL *curl = curl_easy_init();
	
	return urlContent;
	
}

bool CheckLogin(string str_CodeNum) {
	if (str_CodeNum == "1") {
		return true;
	}
	else if(str_CodeNum=="0")
	{
		::MessageBox(NULL, "���������ȶ����������ӳ�ʱ", _T("��ʾ"), MB_OK);
		PostQuitMessage(0);
	}
	else {
		return false;
	}
}





/***
*TODO ��д�����ڵ��search��ť֮��ǰ����Χ�����Ͻ���ת����ת�뾶Ϊ50�����Ƕ��̣߳���ʱ��

*/

void ListMainForm::OnSearch()
{

	struct Prama *prama = new Prama;

	CListUI* pList = static_cast<CListUI*>(m_pm.FindControl(_T("domainlist"))); //���ʣ� �˴���������Ż���
	CEditUI* pEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("input")));
	pEdit->SetEnabled(false);
	CDuiString input = pEdit->GetText();
	m_pSearch->SetEnabled(false);//���ʣ��˴�Ϊ��ҪSetEnabled(false);��
	pList->RemoveAll();
	domain.empty();
	domain.resize(0);
	desc.empty();
	desc.resize(0);
	DWORD dwThreadID = 0;
	pList->SetTextCallback(this);//[1]

	prama->hWnd = GetHWND();//���ṹ�帳ֵ���ýṹ�崫�ݲ����ĺô��ǣ���Ҫ���ӻ���ɾ��һ��������ʱ�����ֱ���޸Ľṹ��
	prama->pList = pList;
	prama->pSearch = m_pSearch;
	prama->tDomain = input;

	//�����߳̽����߳�ִ�к�����search,
	HANDLE hThread = CreateThread(NULL, 0, &ListMainForm::Search, (LPVOID)prama, 0, &dwThreadID);
}

/*
* �ؼ��Ļص�������IListCallbackUI �е�һ���麯������Ⱦʱ������,��[1]�������˻ص�����
*/
LPCTSTR  ListMainForm::GetItemText(CControlUI* pControl, int iIndex, int iSubItem)
{
	TCHAR szBuf[MAX_PATH] = { 0 };
	switch (iSubItem)
	{
	case 0:
		_stprintf(szBuf, _T("%d"), iIndex);
		break;
	case 1:
	{
#ifdef _UNICODE		
		int iLen = domain[iIndex].length();
		LPWSTR lpText = new WCHAR[iLen + 1];
		::ZeroMemory(lpText, (iLen + 1) * sizeof(WCHAR));
		::MultiByteToWideChar(CP_ACP, 0, domain[iIndex].c_str(), -1, (LPWSTR)lpText, iLen);
		_stprintf(szBuf, lpText);
		delete[] lpText;
#else
		_stprintf(szBuf, domain[iIndex].c_str());
#endif
	}
	break;
	case 2:
	{
#ifdef _UNICODE
		int iLen = desc[iIndex].length();
		LPWSTR lpText = new WCHAR[iLen + 1];
		::ZeroMemory(lpText, (iLen + 1) * sizeof(WCHAR));
		::MultiByteToWideChar(CP_ACP, 0, desc[iIndex].c_str(), -1, (LPWSTR)lpText, iLen);
		_stprintf(szBuf, lpText);
		delete[] lpText;
#else
		_stprintf(szBuf, desc[iIndex].c_str());
#endif
	}
	break;
	}
	pControl->SetUserData(szBuf);
	return pControl->GetUserData();
}

string WChar2Ansi(LPCWSTR pwszSrc)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if (nLen <= 0) return std::string("");
	char* pszDst = new char[nLen];
	if (NULL == pszDst) return std::string("");
	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen - 1] = 0;
	std::string strTemp(pszDst);
	delete[] pszDst;
	return strTemp;
}

//void ListMainForm::SaveUserInfo(Context context, string number,
//	string password) {
//	//�����ı�
//	ifstream ins("text.txt");
//	ofstream ous("text.txt");
//	map<string, string> UserInfo = GetUrlInfo(strUnicode);
//	map<string, string>::iterator iter = UserInfo.begin();
//	for (; iter != UserInfo.end(); iter++) {
//		ous << iter->first << " " << iter->second << endl;
//	}
//
//}

void ListMainForm::OnQQLogin() {
	string str_UInfo = GetUserInfo(m_pUNEdit, m_pPwdEdit);
	if (str_UInfo != "") {
		string urlContent = GetUrlContent(str_UInfo);
		CStringW cstrUnicode = UTF82WCS(urlContent.c_str());//string ת CStringW
		string strUnicode = WChar2Ansi(cstrUnicode);//CStringW ת string
		string codeNum = GetCodeNum(urlContent);//��ȡ
		bool loginNum = CheckLogin(codeNum);
		if (!loginNum) {
			ShakeWnd();
			::MessageBox(NULL, "�û���������󣬵�¼ʧ��", _T("��ʾ"), MB_OK);
		}
		else if (loginNum)
		{
			::MessageBox(NULL, "��¼�ɹ�", _T("��ʾ"), MB_OK);
			map<string, string> UserInfo = GetUrlInfo(strUnicode);

			//ifstream ins("text.txt");
			ofstream ous("D:\\Project\\c++\\duilib_teach\\text\\UserInfo.txt");
			//ous.open("text.txt", ios::in | ios::out | ios::binary);
			map<string, string>::iterator iter = UserInfo.begin();
			for (; iter != UserInfo.end(); iter++) {
				ous << iter->first << "       " << iter->second << endl;
				
			}
			time_t t = time(0);
			char tmp[64];
			strftime(tmp, sizeof(tmp), "%Y/%m/%d %X %A", localtime(&t));//���ƻ�ȡ��¼ʱ��
			ous <<"��¼ʱ�䣺"<< tmp << endl;
			ous << flush; //����
			ous.close();//�ر�
			//CString strUnicode = UTF82WCS(UserInfo);
		}
	}
}

/**
* DUI����ڲ��������Ϣ�ص���������Ϣ��TNotifyUI����һ����Ϣ����Ȼ��һЩ��������Ϣ�����ͣ�
��Ϣ�ķ����ߣ���Ϣ������ʱ�䣬��Ϣ����ʱ������λ�õȵȣ� �����ڴ˴����϶ϵ㣬�鿴dui��Ϣ��ת˳��
*/
void  ListMainForm::Notify(TNotifyUI& msg)
{
	if (msg.sType == _T("windowinit"))
		OnPrepare(msg);
	else if (msg.sType == _T("click"))
	{
		if (msg.pSender == m_pCloseBtn)
		{
			PostQuitMessage(0);
			return;
		}
		else if (msg.pSender == m_pMinBtn)
		{
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
			return;
		}
		else if (msg.pSender == m_pMaxBtn)
		{
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); return;
		}
		else if (msg.pSender == m_pRestoreBtn)
		{
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0); return;
		}
		else if (msg.pSender == m_pSearch)
		{
			OnSearch();
		}
		else if (msg.pSender == m_pChangeimg)
		{
			ChangeImg();
		}
		else if (msg.pSender == m_pLogo)
		{
			ShellExecute(NULL, _T("open"), _T("http://www.datedu.cn/"), NULL, NULL, SW_SHOW);
		}
		else if (msg.pSender == m_pLogin)
		{
			OnQQLogin();
			/*if (!GetUrlReturn())
			{
				::MessageBox(NULL, "��¼ʧ��", _T("��ʾ"), MB_OK);
			}*/
			/*if (m_pQRcodepage) m_pQRcodepage->SetVisible(true);
			if (m_pLoginpage) m_pLoginpage->SetVisible(false);

			if (m_pSkinlayout) m_pSkinlayout->SetVisible(false);*/
		}
		else if (msg.pSender == m_pQRcode)
		{
			if (m_pQRcodepage) m_pQRcodepage->SetVisible(false);
			if (m_pLoginpage) m_pLoginpage->SetVisible(true);

			if (m_pSkinlayout) m_pSkinlayout->SetVisible(false);
		}
		else if (msg.pSender == m_pSetting)
		{
			if (m_pLoginpage) m_pLoginpage->SetVisible(false);
			if (m_pSkinlayout) m_pSkinlayout->SetVisible(true);
			if (m_pReturn) m_pReturn->SetVisible(true);
			if (m_pSetting) m_pSetting->SetVisible(false);

			if (m_pQRcodepage) m_pQRcodepage->SetVisible(false);
		}
		else if (msg.pSender == m_pReturn)
		{
			if (m_pLoginpage) m_pLoginpage->SetVisible(true);
			if (m_pSkinlayout) m_pSkinlayout->SetVisible(false);
			if (m_pReturn) m_pReturn->SetVisible(false);
			if (m_pSetting) m_pSetting->SetVisible(true);

			if (m_pQRcodepage) m_pQRcodepage->SetVisible(false);
		}
		else if (msg.pSender == m_pbkc_default)
		{
			Changebk(m_pbkc_default->GetBkColor());
			//m_pMainbk->SetBkColor(m_pbkc_default->GetBkColor());
			/*m_pMainbk->SetBkImage(_T("͸��.png"));*/
		}
		else if (msg.pSender == m_pbkc_lightblue)
		{
			Changebk(m_pbkc_lightblue->GetBkColor());
		}
		else if (msg.pSender == m_pbkc_green)
		{
			Changebk(m_pbkc_green->GetBkColor());
		}
		else if (msg.pSender == m_pbkc_red)
		{
			Changebk(m_pbkc_red->GetBkColor());
		}
		else if (msg.pSender == m_pbkc_bkiamge)
		{
			LPTSTR path_image;
			path_image = GetImgPath();
			if(path_image)
			m_pMainbk->SetBkImage(_T(path_image));
		}
	}
	else if (msg.sType == _T("setfocus"))
	{
	}
	else if (msg.sType == _T("itemclick"))
	{
	}
	else if (msg.sType == _T("itemactivate"))
	{
		int iIndex = msg.pSender->GetTag();
		CDuiString sMessage = _T("Click: ");;
#ifdef _UNICODE		  //˼���˴��궨���Ŀ����ʲô��
		int iLen = domain[iIndex].length();
		LPWSTR lpText = new WCHAR[iLen + 1];
		::ZeroMemory(lpText, (iLen + 1) * sizeof(WCHAR));
		::MultiByteToWideChar(CP_ACP, 0, domain[iIndex].c_str(), -1, (LPWSTR)lpText, iLen);
		sMessage += lpText;
		delete[] lpText;
#else
		sMessage += domain[iIndex].c_str();//�˴�����c++��������أ�����	CDuiString CDuiString::operator+(LPCTSTR lpStr) const

#endif
		::MessageBox(NULL, sMessage.GetData(), _T("��ʾ(by tojen)"), MB_OK);
	}

	else if (msg.sType == _T("showactivex")) {
		if (msg.pSender->GetName() != _T("flash")) return;
		IShockwaveFlash* pFlash = NULL;
		CActiveXUI* pActiveX = static_cast<CActiveXUI*>(msg.pSender);
		pActiveX->GetControl(IID_IUnknown, (void**)&pFlash);
		if (pFlash != NULL) {
			pFlash->put_WMode(_bstr_t(_T("Transparent")));
			pFlash->put_Movie(_bstr_t(CPaintManagerUI::GetInstancePath() + _T("\\skin\\WeChatRes\\��ά��.swf")));
			pFlash->DisableLocalSecurity();
			pFlash->put_AllowScriptAccess(L"always");
			BSTR response;
			pFlash->CallFunction(L"<invoke name=\"setButtonText\" returntype=\"xml\"><arguments><string>Click me!</string></arguments></invoke>", &response);
			pFlash->Release();
		}
	}

	else if (msg.sType == _T("menu"))
	{
		if (msg.pSender->GetName() != _T("domainlist")) return;
		CMenuWnd* pMenu = new CMenuWnd();
		if (pMenu == NULL) { return; }
		POINT pt = { msg.ptMouse.x, msg.ptMouse.y };
		::ClientToScreen(*this, &pt);//��ǰ��������ת��Ϊϵͳ���꣬�൱�ھֲ�����ϵת��Ϊ��������ϵ��
		pMenu->Init(msg.pSender, pt);
	}
	else if (msg.sType == _T("menu_Delete")) {
		CListUI* pList = static_cast<CListUI*>(msg.pSender);
		int nSel = pList->GetCurSel();//dui�ṩ�Ŀ�ݷ�����
		if (nSel < 0) return;
		pList->RemoveAt(nSel);
		domain.erase(domain.begin() + nSel);//��˼���˴�Ϊ��Ҫɾ��domain������
		desc.erase(desc.begin() + nSel);
	}
}

LRESULT  ListMainForm::OnAddListItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CListTextElementUI* pListElement = (CListTextElementUI*)lParam;
	CListUI* pList = static_cast<CListUI*>(m_pm.FindControl(_T("domainlist")));
	if (pList) pList->Add(pListElement);
	return 0;
}

/***
*���²��ִ�������WindowImplBase::OnCreate�� �����˽���ԭʼ�Ĵ��ڽ�������
*/
LRESULT  ListMainForm::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	

	CDialogBuilder builder;
	CDuiString strResourcePath = m_pm.GetResourcePath();
	if (strResourcePath.IsEmpty())
	{
		strResourcePath = m_pm.GetInstancePath();
		strResourcePath += GetSkinFolder().GetData();
	}
	m_pm.SetResourcePath(strResourcePath.GetData());

	m_pm.Init(m_hWnd);
	CControlUI* pRoot = builder.Create(GetSkinFile().GetData(), (UINT)0, NULL, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");
	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);

	Init();
	SetTimer(this->m_hWnd, TIMER_ID_TEST, TIMER_TIME_TEST, 0);


	return 0;
}



/***
����ʹ���ڴ���Ϲ��ߣ����ԣ����ڣ���ʾ��Ϲ��ߣ������Ŀ����ڴ�ֻ������������
*/
void ListMainForm::onTimerTest() 
{
	void * ptr = malloc(1024*1024);

	Sleep(10);//ע����������
	if (ptr)
		free(ptr);
}


void ListMainForm::OnTimer(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case TIMER_ID_TEST:
	{
		onTimerTest();
		break;
	}
	default:
		break;
	}
}


LRESULT  ListMainForm::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	/*if (!::IsZoomed(*this)) {
		RECT rcSizeBox = m_pm.GetSizeBox();
		if (pt.y-3 < rcClient.top + rcSizeBox.top) {
			if (pt.x-3 < rcClient.left + rcSizeBox.left) return HTTOPLEFT;
			if (pt.x+3 > rcClient.right - rcSizeBox.right) return HTTOPRIGHT;
			return HTTOP;
		}
		else if (pt.y > rcClient.bottom - rcSizeBox.bottom) {
			if (pt.x < rcClient.left + rcSizeBox.left) return HTBOTTOMLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTBOTTOMRIGHT;
			return HTBOTTOM;
		}
		if (pt.x < rcClient.left + rcSizeBox.left) return HTLEFT;
		if (pt.x > rcClient.right - rcSizeBox.right) return HTRIGHT;
	}*/

	RECT rcCaption = m_pm.GetCaptionRect();
	if (pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom) {
		CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
		if (pControl && _tcscmp(pControl->GetClass(), DUI_CTR_BUTTON) != 0 &&
			_tcscmp(pControl->GetClass(), DUI_CTR_OPTION) != 0 &&
			_tcscmp(pControl->GetClass(), DUI_CTR_TEXT) != 0)
			return HTCAPTION;
	}

	return HTCLIENT;
}

/**
*��С�ı�Ļص����������Գ���ע�ͣ��޸Ĵ��� ��Ч��
*/
LRESULT  ListMainForm::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SIZE szRoundCorner = m_pm.GetRoundCorner();
	if (!::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0)) {
		CDuiRect rcWnd;
		::GetWindowRect(*this, &rcWnd);
		rcWnd.Offset(-rcWnd.left, -rcWnd.top);
		rcWnd.right++; rcWnd.bottom++;
		RECT rc = { rcWnd.left, rcWnd.top + szRoundCorner.cx, rcWnd.right, rcWnd.bottom };
		HRGN hRgn1 = ::CreateRectRgnIndirect(&rc);
		HRGN hRgn2 = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom - szRoundCorner.cx, szRoundCorner.cx, szRoundCorner.cy);
		::CombineRgn(hRgn1, hRgn1, hRgn2, RGN_OR);
		::SetWindowRgn(*this, hRgn1, TRUE);
		::DeleteObject(hRgn1);
		::DeleteObject(hRgn2);
	}

	bHandled = FALSE;
	return 0;
}

LRESULT  ListMainForm::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
	CDuiRect rcWork = oMonitor.rcWork;
	rcWork.Offset(-oMonitor.rcMonitor.left, -oMonitor.rcMonitor.top);

	LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
	lpMMI->ptMaxPosition.x = rcWork.left;
	lpMMI->ptMaxPosition.y = rcWork.top;
	lpMMI->ptMaxSize.x = rcWork.right;
	lpMMI->ptMaxSize.y = rcWork.bottom;

	bHandled = FALSE;
	return 0;
}

LRESULT  ListMainForm::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// ��ʱ�����յ�WM_NCDESTROY���յ�wParamΪSC_CLOSE��WM_SYSCOMMAND
	if (wParam == SC_CLOSE) {
		::PostQuitMessage(0L);
		bHandled = TRUE;
		return 0;
	}
	BOOL bZoomed = ::IsZoomed(*this);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if (::IsZoomed(*this) != bZoomed) {
		if (!bZoomed) {
			if (m_pMaxBtn) m_pMaxBtn->SetVisible(false);
			if (m_pRestoreBtn) m_pRestoreBtn->SetVisible(true);
		}
		else {
			if (m_pMaxBtn) m_pMaxBtn->SetVisible(true);
			if (m_pRestoreBtn) m_pRestoreBtn->SetVisible(false);
		}
	}
	return lRes;
}

/***
* ��������windowsϵͳ�ĸ�����Ϣ��WM= windows  message
*/
LRESULT  ListMainForm::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch (uMsg) {
	case WM_ADDLISTITEM:   lRes = OnAddListItem(uMsg, wParam, lParam, bHandled); break;
	case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_CLOSE:         lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
	case WM_DESTROY:       lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
	case WM_NCACTIVATE:    lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
	case WM_NCCALCSIZE:    lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
	case WM_NCPAINT:       lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
	case WM_NCHITTEST:     lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
	case WM_SIZE:          lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
	case WM_GETMINMAXINFO: lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); break;
	case WM_SYSCOMMAND:    lRes = OnSysCommand(uMsg, wParam, lParam, bHandled); break;
	case WM_TIMER:
	{
		OnTimer(wParam, lParam);
		break;
	}
	default:
		bHandled = FALSE;
	}
	if (bHandled) return lRes;
	if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

/****
���ʣ�
1.��ͳ����ִ��searchǰ��listdemo.exe���ڴ������������28
2.���Լ����һ���ڴ�й©�Ĵ��룬��ִ��serarch֮���ڴ�ռ�ó���1M��


*/