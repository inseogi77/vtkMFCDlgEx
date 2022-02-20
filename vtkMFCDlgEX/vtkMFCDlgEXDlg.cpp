
// vtkMFCDlgEXDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "vtkMFCDlgEX.h"
#include "vtkMFCDlgEXDlg.h"
#include "afxdialogex.h"

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


// CvtkMFCDlgEXDlg 대화 상자



CvtkMFCDlgEXDlg::CvtkMFCDlgEXDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VTKMFCDLGEX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CvtkMFCDlgEXDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CvtkMFCDlgEXDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_CONE, &CvtkMFCDlgEXDlg::OnBnClickedButtonCone)
	ON_BN_CLICKED(IDC_BUTTON_EX_VTKPOLYDATA, &CvtkMFCDlgEXDlg::OnBnClickedButtonExVtkpolydata)
	ON_BN_CLICKED(IDC_BUTTON_EX_VTKARROW, &CvtkMFCDlgEXDlg::OnBnClickedButtonExVtkarrow)
	ON_BN_CLICKED(IDC_BUTTON_EX_VTKSTLREADER, &CvtkMFCDlgEXDlg::OnBnClickedButtonExVtkstlreader)
	ON_BN_CLICKED(IDC_BUTTON_EX_VTKPROPERTY, &CvtkMFCDlgEXDlg::OnBnClickedButtonExVtkproperty)
	ON_BN_CLICKED(IDC_BUTTON_EX_VTKCLEANPOLYDATA, &CvtkMFCDlgEXDlg::OnBnClickedButtonExVtkcleanpolydata)
	ON_BN_CLICKED(IDC_BUTTON_EX_VTKPOLYDATANORMAL, &CvtkMFCDlgEXDlg::OnBnClickedButtonExVtkpolydatanormal)
END_MESSAGE_MAP()


// CvtkMFCDlgEXDlg 메시지 처리기

BOOL CvtkMFCDlgEXDlg::OnInitDialog()
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

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	if (this->GetDlgItem(IDC_STATIC_FRAME))
	{
		this->InitVtkWindow(this->GetDlgItem(IDC_STATIC_FRAME)->GetSafeHwnd());	// Initialize VTK window
		this->ResizeVtkWidnow();
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CvtkMFCDlgEXDlg::InitVtkWindow(void* hWnd)
{
	// vtk Render Window 생성
	if (m_vtkWindow == NULL)
	{
		// Interactor 생성
		vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
		// Trackball Camera 인터랙션 스타일 적용
		interactor->SetInteractorStyle(
			vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New());

		// Renderer 생성
		vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
		renderer->SetBackground(0.0, 0.0, 0.0);		// 검은색 배경

		// RenderWindow 생성 후 Dialog 핸들, Renderer 설정
		m_vtkWindow = vtkSmartPointer<vtkRenderWindow>::New();
		m_vtkWindow->SetParentId(hWnd);
		m_vtkWindow->SetInteractor(interactor);
		m_vtkWindow->AddRenderer(renderer);
		m_vtkWindow->Render();
	}
}

void CvtkMFCDlgEXDlg::ResizeVtkWidnow()
{
	CRect rc;
	GetDlgItem(IDC_STATIC_FRAME)->GetClientRect(rc);
	m_vtkWindow->SetSize(rc.Width(), rc.Height());
}

void CvtkMFCDlgEXDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CvtkMFCDlgEXDlg::OnPaint()
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
HCURSOR CvtkMFCDlgEXDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CvtkMFCDlgEXDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CvtkMFCDlgEXDlg::OnBnClickedButtonCone()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//////////////////////////////////////////////////////////////////////////
	// Create a cone source
	vtkSmartPointer<vtkConeSource> coneSource = vtkSmartPointer<vtkConeSource>::New();

	// Create a mapper and actor
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(coneSource->GetOutputPort());
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	// Visualize
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(.1, .2, .3); // Background color dark blue
	renderer->ResetCamera();

	//카메라 설정
	vtkSmartPointer<vtkCamera> cam = renderer->GetActiveCamera(); //renderer에서 카메라 받아오기
	cam->SetClippingRange(0.1, 10);                               //그려질 depth 영역 설정
	cam->SetFocalPoint(0, 0, 0);								  //카메라가 바라보는 시점
	cam->SetViewUp(0, 1, 0);									  //카메라의 upvector 설정
	cam->SetPosition(0, 0, 5);									  //카메라의 위치 설정
	//cam->ParallelProjectionOn();								  // on: orthogonnval view off: perspective view

	//조명 설정
	vtkSmartPointer<vtkLight> newLight = vtkSmartPointer<vtkLight>::New();
	newLight->SetColor(1, 1, 0);								  //조명색 설정(노랑이)
	newLight->SetFocalPoint(cam->GetFocalPoint());                //비추는 지점
	newLight->SetPosition(cam->GetPosition());					  //조명 위치 설정
	renderer->AddLight(newLight);

	//rending
	m_vtkWindow->AddRenderer(renderer);
	m_vtkWindow->Render();
}

void CvtkMFCDlgEXDlg::OnBnClickedButtonExVtkpolydata()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	vtkSmartPointer<vtkPoints> pPoints = vtkSmartPointer<vtkPoints>::New();
	pPoints->InsertPoint(0, 0.0, 0.0, 0.0);
	pPoints->InsertPoint(1, 0.0, 1.0, 0.0);
	pPoints->InsertPoint(2, 1.0, 0.0, 0.0);
	pPoints->InsertPoint(3, 1.0, 1.0, 0.0);

	vtkSmartPointer<vtkCellArray> pPolys = vtkSmartPointer<vtkCellArray>::New();
	pPolys->InsertNextCell(3);
	pPolys->InsertCellPoint(0);
	pPolys->InsertCellPoint(1);
	pPolys->InsertCellPoint(2);
	pPolys->InsertNextCell(3);
	pPolys->InsertCellPoint(1);
	pPolys->InsertCellPoint(3);
	pPolys->InsertCellPoint(2);

	vtkSmartPointer<vtkPolyData> pPolyData = vtkSmartPointer<vtkPolyData>::New();
	pPolyData->SetPoints(pPoints);   //위치 정보
	pPolyData->SetPolys(pPolys);     //형태 정보

	//Create a mapper and actor
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(pPolyData);
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	/////////////////////////////////////////////////////////////////////////////
	// Visualize
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(.1, .2, .3); // Background color dark blue
	renderer->ResetCamera();
	//rending
	m_vtkWindow->AddRenderer(renderer);
	m_vtkWindow->Render();

}

void CvtkMFCDlgEXDlg::OnBnClickedButtonExVtkarrow()
{
	vtkSmartPointer<vtkArrowSource> pArrow = vtkSmartPointer<vtkArrowSource>::New();
	pArrow->SetShaftRadius(0.03);		//파라미터 설정(Option)
	pArrow->SetShaftResolution(100);
	pArrow->SetTipRadius(0.1);
	pArrow->SetTipLength(0.35);
	pArrow->SetTipResolution(100);
	pArrow->Update();

	vtkSmartPointer<vtkPolyData> pPolyData = pArrow->GetOutput();  //vtkPolyData 받아오기

	//Create a mapper and actor
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(pPolyData);
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	/////////////////////////////////////////////////////////////////////////////
	// Visualize
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(.1, .2, .3); // Background color dark blue
	renderer->ResetCamera();
	//rending
	m_vtkWindow->AddRenderer(renderer);
	m_vtkWindow->Render();
}


void CvtkMFCDlgEXDlg::OnBnClickedButtonExVtkstlreader()
{
	vtkSmartPointer<vtkSTLReader> pSTL_Reader = vtkSmartPointer<vtkSTLReader>::New();
	pSTL_Reader->SetFileName("./data/example.stl");		//읽을 파일 지정
	pSTL_Reader->Update();

	vtkSmartPointer<vtkPolyData> pPolyData = pSTL_Reader->GetOutput();	//vtkPolyData 형식으로 받아오기
	
	vtkSmartPointer<vtkSTLWriter> pSTLWriter = vtkSmartPointer<vtkSTLWriter>::New();
	pSTLWriter->SetInputData(pPolyData);			//저장할 vtkPolyData
	pSTLWriter->SetFileName("./data/example1.stl");
	pSTLWriter->Write();							//저장하기

	//Create a mapper and actor
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(pPolyData);
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	/////////////////////////////////////////////////////////////////////////////
	// Visualize
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(.1, .2, .3); // Background color dark blue
	renderer->ResetCamera();
	//rending
	m_vtkWindow->AddRenderer(renderer);
	m_vtkWindow->Render();
}

void CvtkMFCDlgEXDlg::OnBnClickedButtonExVtkproperty()
{
	vtkSmartPointer<vtkArrowSource> arrow = vtkSmartPointer<vtkArrowSource>::New();

	//Create a mapper and actor
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(arrow->GetOutputPort());
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	actor->GetProperty()->SetColor(0, 1, 0);	//색상설정
	actor->GetProperty()->SetOpacity(0.5);      //불투명도 설정 0.0:투명 ~ 1.0:불투명
	actor->GetProperty()->SetPointSize(1.0);    //Vertex 사이즈 설정
	actor->GetProperty()->SetLineWidth(1.0);	//Line 두께 설정

	//VTK_POINTS, VTK_WIREFRAME, VTK_SURFACE
	actor->GetProperty()->SetRepresentation(VTK_SURFACE);  //그리기 방법설정
	//actor->GetProperty()->SetTexture(pTexture); //vtkTexture(Texture Mapping)
	actor->GetProperty()->BackfaceCullingOn();  //Culling ON/OFF
	actor->GetProperty()->LightingOn();			//Lighting ON/OFF
	actor->GetProperty()->ShadingOn();			//Shading ON/OFF

	/////////////////////////////////////////////////////////////////////////////
	// Visualize
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(.1, .2, .3); // Background color dark blue
	renderer->ResetCamera();
	//rending
	m_vtkWindow->AddRenderer(renderer);
	m_vtkWindow->Render();
}


void CvtkMFCDlgEXDlg::OnBnClickedButtonExVtkcleanpolydata()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	vtkSmartPointer<vtkPoints> pPoints = vtkSmartPointer<vtkPoints>::New();
	pPoints->InsertPoint(0, 0.0, 0.0, 0.0);
	pPoints->InsertPoint(1, 0.0, 1.0, 0.0);
	pPoints->InsertPoint(2, 1.0, 0.0, 0.0);
	pPoints->InsertPoint(3, 1.0, 1.0, 0.0);
	pPoints->InsertPoint(4, 0.0, 1.0, 0.0);		//1번점과 중복
	pPoints->InsertPoint(5, 1.0, 0.0, 0.0);     //2번점과 중복

	vtkSmartPointer<vtkCellArray> pPolys = vtkSmartPointer<vtkCellArray>::New();
	pPolys->InsertNextCell(3);
	pPolys->InsertCellPoint(0);
	pPolys->InsertCellPoint(1);
	pPolys->InsertCellPoint(2);
	pPolys->InsertNextCell(3);	
	pPolys->InsertCellPoint(4);
	pPolys->InsertCellPoint(3);
	pPolys->InsertCellPoint(5);

	vtkSmartPointer<vtkPolyData> pPolyData = vtkSmartPointer<vtkPolyData>::New();
	pPolyData->SetPoints(pPoints);   //위치 정보
	pPolyData->SetPolys(pPolys);     //형태 정보

	int nPt = pPolyData->GetNumberOfPoints();   //nPt = 6;
	int nPoly = pPolyData->GetNumberOfPolys();  //nPoly = 2;

	vtkSmartPointer<vtkCleanPolyData> pClean = vtkSmartPointer<vtkCleanPolyData>::New();
	pClean->SetInputData(pPolyData);
	pClean->Update();

	pPolyData->DeepCopy(pClean->GetOutput());  //vtkPolyData 복사하기
	nPt = pPolyData->GetNumberOfPoints();      //nPt = 4;
	nPoly = pPolyData->GetNumberOfPolys();     //nPoly = 2;

	//Create a mapper and actor
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(pPolyData);
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	/////////////////////////////////////////////////////////////////////////////
	// Visualize
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(.1, .2, .3); // Background color dark blue
	renderer->ResetCamera();
	//rending
	m_vtkWindow->AddRenderer(renderer);
	m_vtkWindow->Render();
}


void CvtkMFCDlgEXDlg::OnBnClickedButtonExVtkpolydatanormal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	vtkSmartPointer<vtkSTLReader> pSTL_Reader = vtkSmartPointer<vtkSTLReader>::New();
	pSTL_Reader->SetFileName("./data/example.stl");		//읽을 파일 지정
	pSTL_Reader->Update();

	vtkSmartPointer<vtkPolyData> pPolyData = pSTL_Reader->GetOutput();	//vtkPolyData 형식으로 받아오기

	vtkSmartPointer<vtkPolyDataNormals> normals = vtkSmartPointer<vtkPolyDataNormals>::New();
	normals->SetInputData(pSTL_Reader->GetOutput());			//저장할 vtkPolyData
	normals->ComputePointNormalsOn();						    //Point normal 계산 			
	normals->ComputeCellNormalsOn();                            //Cell normal 계산
	normals->Update();	

	//Create a mapper and actor
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(normals->GetOutputPort());
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	/////////////////////////////////////////////////////////////////////////////
	// Visualize
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(.1, .2, .3); // Background color dark blue
	renderer->ResetCamera();
	//rending
	m_vtkWindow->AddRenderer(renderer);
	m_vtkWindow->Render();
}
