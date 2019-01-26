#pragma once

/*
* Code By Tojen (qq:342269237)
* 界面设计图片资源80%原创，布局完全原创,学习作品，不好请拍砖
*/
#include <objbase.h>
#include <zmouse.h>
#include <exdisp.h>
#include <comdef.h>
#include <vector>
#include <sstream>
#include <io.h>
#include <shellapi.h>

#include "MenuWnd.h"
#include "..\DuiLib\UIlib.h"

#include <fstream>
#include <winioctl.h>
#include <map>
#include<iostream>
#include <string>
#include "../libcURL/include/curl.h"

#ifdef _DEBUG
#pragma comment(lib, "../libcURL/lib/libcurld.lib")
#else
#pragma comment(lib, "../libcURL/lib/libcurl.lib")
#endif

#include "kutfconv.h"

using namespace DuiLib;


#define WM_ADDLISTITEM WM_USER + 50
static map<string, string>myMap;

/*
*  线程函数中传入的结构体变量，使用线程为了使界面线程立即返回，防止卡住，你们懂得。
*/
struct Prama
{
	HWND hWnd;
	CListUI* pList;
	CButtonUI* pSearch;
	CDuiString tDomain;
};

struct TestMem {
	int count;
};


class ListMainForm : public CWindowWnd, public INotifyUI, public IListCallbackUI
{
public:
    ListMainForm() {
    };
	//void Text();

	void OnQQLogin();

	/*void SaveUserInfo(Context context, string number,
		string password);*/

	bool CheckUInfo(string str_UN, string str_Pwd);

	string GetUserInfo(CEditUI* m_pUNEdit, CEditUI* m_pPwdEdit);

	map<string, string> GetUrlInfo(const string& resString);

	void Format(string& str);

	void StrSplit(const string& str, string& s1, string& s2);

	CDuiString GetSkinFolder()
	{

		return _T("skin\\ListRes\\");
	}

	CDuiString GetSkinFile()
	{
		return _T("qq.xml");
	}

    LPCTSTR GetWindowClassName() const 
    { 
        return _T("ScanMainForm"); 
    };

    UINT GetClassStyle() const
    { 
        return CS_DBLCLKS; 
    };

    void OnFinalMessage(HWND /*hWnd*/) 
    { 
        delete this;
    };

	void Init();

    void OnPrepare(TNotifyUI& msg) 
    {

    }

	static DWORD WINAPI Search(LPVOID lpParameter);

	void Login();
	
	void ChangeImg();

	void ShakeWnd();

	//void SetImagePath();

	void OnSearch();

	void Changebk(DWORD control)
	{
		m_pMainbk->SetBkColor(control);
		m_pMainbk->SetBkImage(_T("透明.png"));
	}
 
	LPCTSTR GetItemText(CControlUI* pControl, int iIndex, int iSubItem);

	void Notify(TNotifyUI& msg);

	LRESULT OnAddListItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        bHandled = FALSE;
        return 0;
    }
	void					onTimerTest();
	void				  OnTimer(WPARAM wParam, LPARAM lParam); //定时器

    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        ::PostQuitMessage(0L);
        bHandled = FALSE;
        return 0;
    }

    LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        if( ::IsIconic(*this) ) bHandled = FALSE;
        return (wParam == 0) ? TRUE : FALSE;
    }

    LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        return 0;
    }

    LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        return 0;
    }

	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	*大小改变的回调函数，可以尝试注释，修改代码 看效果
	*/
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/***
	* 处理来着windows系统的各种消息，WM= windows  message
	*/
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
    CPaintManagerUI m_pm;

private:
    CButtonUI* m_pCloseBtn;  //此处成员变量用m_ 开头，请务必准守，不对外暴露的成员一律用private修饰
    CButtonUI* m_pMaxBtn;
    CButtonUI* m_pRestoreBtn;
    CButtonUI* m_pMinBtn;
    CButtonUI* m_pSearch;
    CButtonUI* m_pChangeimg;
    CButtonUI* m_pQRcode;
    CButtonUI* m_pLogo;
    CButtonUI* m_pSetting;
    CButtonUI* m_pReturn;
    CButtonUI* m_pbkc_default;
	CButtonUI* m_pbkc_lightblue;
	CButtonUI* m_pbkc_green;
	CButtonUI* m_pbkc_red;
	CButtonUI* m_pbkc_bkiamge;
    CEditUI* m_pEdit;
	CEditUI* m_pUNEdit;
	CEditUI* m_pPwdEdit;
    CHorizontalLayoutUI* m_pLogin;
    CHorizontalLayoutUI* m_pQRcodepage;
    CVerticalLayoutUI* m_pSkinlayout;
    CVerticalLayoutUI* m_pLoginpage;
    CVerticalLayoutUI* m_pMainbk;

	CWebBrowserUI* m_pWebBrowser;

};
