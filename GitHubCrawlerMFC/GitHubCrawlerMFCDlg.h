// GitHubCrawlerMFCDlg.h: 헤더 파일
//

#pragma once

// CGitHubCrawlerMFCDlg 대화 상자
class CGitHubCrawlerMFCDlg : public CDialogEx
{
	// 생성입니다.
public:
	CGitHubCrawlerMFCDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GITHUBCRAWLERMFC_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	HICON m_hIcon;
	CComboBox m_comboLanguage;  // 언어 선택 콤보박스
	CEdit m_editToken;          // GitHub Token 입력
	CEdit m_editSavePath;       // 저장 경로 입력
	CEdit m_editFolderName;     // 폴더명 입력
	// 진행 상황 관련 컨트롤 제거
	// CEdit m_editProgress;       // 진행 상황 표시
	// CEdit m_editCount;          // 통계 표시

	// 크롤링 관련 변수 제거 (Python 창을 직접 띄우므로 불필요)
	// bool m_bCrawling;           // 크롤링 중인지 여부
	// HANDLE m_hCrawlerProcess;   // 크롤러 프로세스 핸들

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	// 메시지 핸들러
	// afx_msg void OnBnClickedOk();      // 확인 버튼 제거
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBrowsePath();
	// afx_msg void OnBnClickedStop();    // 중지 버튼 제거
	// afx_msg LRESULT OnCrawlerFinished(WPARAM wParam, LPARAM lParam); // 크롤러 완료 처리 제거
	// virtual void OnCancel();           // 취소 버튼 제거
	afx_msg void OnBnClickedButtonStop();
};