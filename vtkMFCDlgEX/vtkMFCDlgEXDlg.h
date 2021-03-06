
// vtkMFCDlgEXDlg.h: 헤더 파일
//

#pragma once


// CvtkMFCDlgEXDlg 대화 상자
class CvtkMFCDlgEXDlg : public CDialogEx
{
// 생성입니다.
public:
	CvtkMFCDlgEXDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VTKMFCDLGEX_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	vtkSmartPointer<vtkRenderWindow> m_vtkWindow;
	void InitVtkWindow(void* hWnd);
	void ResizeVtkWidnow();

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonCone();
	afx_msg void OnBnClickedButtonExVtkpolydata();
	afx_msg void OnBnClickedButtonExVtkarrow();
	afx_msg void OnBnClickedButtonExVtkstlreader();
	afx_msg void OnBnClickedButtonExVtkproperty();
	afx_msg void OnBnClickedButtonExVtkcleanpolydata();
	afx_msg void OnBnClickedButtonExVtkpolydatanormal();
	afx_msg void OnBnClickedButtonExVtkexdecimation();
	afx_msg void OnBnClickedButtonExVtksmoothing();
	afx_msg void OnBnClickedButtonExVtkconnectivityCheck();
	afx_msg void OnBnClickedButtonExVtkclipping();
	afx_msg void OnBnClickedButtonExVtktransform();
};
