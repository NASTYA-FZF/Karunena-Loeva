
// Karunena-LoevaDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Karunena-Loeva.h"
#include "Karunena-LoevaDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CKarunenaLoevaDlg



CKarunenaLoevaDlg::CKarunenaLoevaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KARUNENALOEVA_DIALOG, pParent)
	, A1(10)
	, A2(9)
	, A3(5)
	, f1(2)
	, f2(3)
	, f3(4)
	, fi1(0)
	, fi2(1)
	, fi3(2)
	, N(1024)
	, fd(100)
	, p(100)
	, num_vector(1)
	, num_vector_U(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKarunenaLoevaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, A1);
	DDX_Text(pDX, IDC_EDIT3, A2);
	DDX_Text(pDX, IDC_EDIT4, A3);
	DDX_Text(pDX, IDC_EDIT8, f1);
	DDX_Text(pDX, IDC_EDIT5, f2);
	DDX_Text(pDX, IDC_EDIT7, f3);
	DDX_Text(pDX, IDC_EDIT9, fi1);
	DDX_Text(pDX, IDC_EDIT10, fi2);
	DDX_Text(pDX, IDC_EDIT6, fi3);
	DDX_Text(pDX, IDC_EDIT11, N);
	DDX_Text(pDX, IDC_EDIT2, fd);
	DDX_Text(pDX, IDC_EDIT12, p);
	DDX_Text(pDX, IDC_EDIT13, num_vector);
	DDX_Control(pDX, IDC_EDIT14, res_work);
	DDX_Text(pDX, IDC_EDIT15, num_vector_U);
}

BEGIN_MESSAGE_MAP(CKarunenaLoevaDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DRAW, &CKarunenaLoevaDlg::OnBnClickedDraw)
	ON_BN_CLICKED(IDC_AKM, &CKarunenaLoevaDlg::OnBnClickedAkm)
	ON_BN_CLICKED(IDC_DRAWVECTOR, &CKarunenaLoevaDlg::OnBnClickedDrawvector)
	ON_BN_CLICKED(IDC_DRAW_U, &CKarunenaLoevaDlg::OnBnClickedDrawU)
END_MESSAGE_MAP()


// Обработчики сообщений CKarunenaLoevaDlg

BOOL CKarunenaLoevaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	drw.Create(GetDlgItem(IDC_SIGNAL)->GetSafeHwnd());
	drw_vec.Create(GetDlgItem(IDC_VECTOR)->GetSafeHwnd());
	drw_U.Create(GetDlgItem(IDC_PIC2)->GetSafeHwnd());
	drw_singular.Create(GetDlgItem(IDC_SING)->GetSafeHwnd());
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CKarunenaLoevaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CKarunenaLoevaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKarunenaLoevaDlg::OnBnClickedDraw()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(TRUE);
	double A[] = { A1, A2, A3 };
	double f[] = { f1, f2, f3 };
	double fi[] = { fi1, fi2, fi3 };
	s = signal(A, f, fi, N, fd);
	drw.DrawPoints(s.Get_sig(), L"t", L"A", 0., N / fd, 1 / fd, false);
}


void CKarunenaLoevaDlg::OnBnClickedAkm()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(TRUE);
	s.CreateMatrixAKP(p);
	Matrix AKM = s.GetMatrixAKM();
	int strok = AKM.Get_strok(), stolb = AKM.Get_stolb();
	sigma = Matrix(strok, stolb, false);
	V = Matrix(strok, stolb, false);
	U = Matrix(strok, stolb, false);
	AKM.SVD(U, V, sigma);
	U.print_matrix_in_file("Rxx.txt", "U", true);
	V.print_matrix_in_file("Rxx.txt", "V", true);
	sigma.print_matrix_in_file("Rxx.txt", "sigma", true);
	drw_singular.DrawPoints(sigma.GetDiagAl(), L"n", L"Singular", 0., (double)p, 1., true);
	res_work.SetWindowTextW(L"end");
}


void CKarunenaLoevaDlg::OnBnClickedDrawvector()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(TRUE);
	if (num_vector - 1 >= p || num_vector - 1 < 0)
	{
		MessageBox(L"Введит номер базисного вектора из диапазона", L"Ошибка", NULL);
		return;
	}
	drw_vec.DrawPoints(Transpon(V)[num_vector - 1], L"n", L"Vi", 0, s.GetMatrixAKM().Get_stolb(), 1, false);
	res_work.SetWindowTextW(L"");
}


void CKarunenaLoevaDlg::OnBnClickedDrawU()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(TRUE);
	if (num_vector_U - 1 >= p || num_vector - 1 < 0)
	{
		MessageBox(L"Введит номер базисного вектора из диапазона", L"Ошибка", NULL);
		return;
	}
	drw_U.DrawPoints(Transpon(U)[num_vector_U - 1], L"n", L"Ui", 0, s.GetMatrixAKM().Get_stolb(), 1, false);
	res_work.SetWindowTextW(L"");
}
