// GitHubCrawlerMFCDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GitHubCrawlerMFC.h"
#include "GitHubCrawlerMFCDlg.h"
#include "afxdialogex.h"
#include <afxdlgs.h>
#include <afxwin.h>
#include <shlobj.h>
#include <process.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGitHubCrawlerMFCDlg 대화 상자



CGitHubCrawlerMFCDlg::CGitHubCrawlerMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GITHUBCRAWLERMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGitHubCrawlerMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_LANGUAGE, m_comboLanguage);
	DDX_Control(pDX, IDC_EDIT_TOKEN, m_editToken);
	DDX_Control(pDX, IDC_EDIT_SAVE_PATH, m_editSavePath);
	DDX_Control(pDX, IDC_EDIT_FOLDER_NAME, m_editFolderName);
	// 진행 상황 관련 컨트롤 제거
	// DDX_Control(pDX, IDC_EDIT_PROGRESS, m_editProgress);
	// DDX_Control(pDX, IDC_EDIT_COUNT, m_editCount);
}

BEGIN_MESSAGE_MAP(CGitHubCrawlerMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	// 확인/취소 버튼 메시지 매핑 제거
	// ON_BN_CLICKED(IDOK, &CGitHubCrawlerMFCDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CGitHubCrawlerMFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_PATH, &CGitHubCrawlerMFCDlg::OnBnClickedBrowsePath)
	// 중지 버튼 제거 (Python 창을 직접 띄우므로 불필요)
	// ON_BN_CLICKED(IDC_BUTTON_STOP, &CGitHubCrawlerMFCDlg::OnBnClickedStop)
	// 크롤러 완료 메시지 제거
	// ON_MESSAGE(WM_USER + 100, &CGitHubCrawlerMFCDlg::OnCrawlerFinished)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CGitHubCrawlerMFCDlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// CGitHubCrawlerMFCDlg 메시지 처리기

BOOL CGitHubCrawlerMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// 언어 선택 콤보박스 초기화
	m_comboLanguage.AddString(_T("c"));
	m_comboLanguage.AddString(_T("c++"));
	m_comboLanguage.AddString(_T("python"));
	m_comboLanguage.AddString(_T("java"));	
	m_comboLanguage.AddString(_T("c#"));
	m_comboLanguage.AddString(_T("go"));
	m_comboLanguage.AddString(_T("rust"));
	m_comboLanguage.AddString(_T("cobol"));
	m_comboLanguage.AddString(_T("ruby"));
	m_comboLanguage.AddString(_T("swift"));
	m_comboLanguage.SetCurSel(0);  // 기본값으로 C++ 선택

	// 기본 저장 경로 설정
	m_editSavePath.SetWindowText(_T("C:\\Users\\Administrator\\Desktop"));

	// 기본 폴더명 설정
	m_editFolderName.SetWindowText(_T("github_codes"));
		

	// 확인/취소 버튼 숨기기
	GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGitHubCrawlerMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGitHubCrawlerMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGitHubCrawlerMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGitHubCrawlerMFCDlg::OnBnClickedBrowsePath()
{
	// 폴더 선택 대화상자
	BROWSEINFO bi = { 0 };
	bi.hwndOwner = GetSafeHwnd();
	bi.lpszTitle = _T("저장할 폴더를 선택하세요");
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	if (pidl != NULL)
	{
		TCHAR path[MAX_PATH];
		if (SHGetPathFromIDList(pidl, path))
		{
			m_editSavePath.SetWindowText(path);
		}
		CoTaskMemFree(pidl);
	}
}

void CGitHubCrawlerMFCDlg::OnBnClickedButton1()
{
	// 입력값 가져오기
	CString token, language, savePath, folderName;

	m_editToken.GetWindowText(token);
	m_comboLanguage.GetLBText(m_comboLanguage.GetCurSel(), language);
	m_editSavePath.GetWindowText(savePath);
	m_editFolderName.GetWindowText(folderName);

	// 입력값 검증
	if (token.IsEmpty())
	{
		MessageBox(_T("GitHub Token을 입력해주세요."), _T("오류"), MB_OK | MB_ICONERROR);
		return;
	}

	if (savePath.IsEmpty())
	{
		MessageBox(_T("저장 경로를 입력해주세요."), _T("오류"), MB_OK | MB_ICONERROR);
		return;
	}

	if (folderName.IsEmpty())
	{
		MessageBox(_T("폴더명을 입력해주세요."), _T("오류"), MB_OK | MB_ICONERROR);
		return;
	}

	// 언어명을 소문자로 변환 (GitHub API 형식에 맞춤)
	language.MakeLower();

	// 특별한 경우 처리
	if (language == _T("c++")) {
		language = _T("c++");
	}
	else if (language == _T("c#")) {
		language = _T("csharp");
	}
	else if (language == _T("javascript")) {
		language = _T("javascript");
	}

	// 실행 파일 위치 기준으로 경로 설정
	TCHAR exePath[MAX_PATH];
	GetModuleFileName(NULL, exePath, MAX_PATH);
	CString exePathStr(exePath);
	int lastSlash = exePathStr.ReverseFind('\\');
	CString exeDir = exePathStr.Left(lastSlash);

	// .env 파일 저장
	CString envContent;
	envContent.Format(_T("GITHUB_TOKEN=%s\nSAVE_PATH=%s\nFOLDER_NAME=%s"), token, savePath, folderName);

	// .env 파일 저장
	CString envPath = exeDir + _T("\\.env");
	FILE* file = nullptr;
	errno_t err = _wfopen_s(&file, envPath, _T("w"));
	if (err == 0 && file)
	{
		fwrite(CT2A(envContent), 1, strlen(CT2A(envContent)), file);
		fclose(file);
	}

	// crawler.py 파일 존재 확인
	CString crawlerPath = exeDir + _T("\\crawler.py");

	FILE* testFile = nullptr;
	err = _wfopen_s(&testFile, crawlerPath, _T("r"));
	if (err != 0 || !testFile)
	{
		CString errorMsg;
		errorMsg.Format(_T("crawler.py 파일을 찾을 수 없습니다.\n\n경로: %s\n\n파일이 올바른 위치에 있는지 확인해주세요."), crawlerPath);
		MessageBox(errorMsg, _T("파일 오류"), MB_OK | MB_ICONERROR);
		return;
	}
	fclose(testFile);

	// Python 스크립트를 새 콘솔 창에서 실행
	CString command;
	command.Format(_T("cmd /c \"python \"%s\" %s %s %s %s & pause\""),
		crawlerPath, language, token, savePath, folderName);

	// 프로세스 시작 정보
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi = { 0 };

	// 새 콘솔 창에서 실행 (CREATE_NEW_CONSOLE 플래그 사용)
	if (CreateProcess(NULL, command.GetBuffer(), NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		// 프로세스 핸들 정리
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		/*MessageBox(_T("GitHub 크롤링이 시작되었습니다.\n새로 열린 콘솔 창에서 진행 상황을 확인하세요."),
			_T("시작됨"), MB_OK | MB_ICONINFORMATION);*/
	}
	else
	{
		CString errorMsg;
		errorMsg.Format(_T("Python 스크립트 실행에 실패했습니다.\n\n명령어: %s"), command);
		MessageBox(errorMsg, _T("실행 오류"), MB_OK | MB_ICONERROR);
	}
}

// 제거된 함수들:
// - OnBnClickedOk() - 확인 버튼 제거
// - OnBnClickedStop() - 중지 버튼 제거  
// - OnCancel() - 취소 버튼 제거
// - OnCrawlerFinished() - 크롤러 완료 처리 제거
void CGitHubCrawlerMFCDlg::OnBnClickedButtonStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
