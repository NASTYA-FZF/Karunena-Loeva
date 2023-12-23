
// Karunena-LoevaDlg.h: файл заголовка
//

#pragma once
#include "Drawer.h"
#include "Signal.h"

// Диалоговое окно CKarunenaLoevaDlg
class CKarunenaLoevaDlg : public CDialogEx
{
// Создание
public:
	CKarunenaLoevaDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KARUNENALOEVA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	double A1;
	double A2;
	double A3;
	double f1;
	double f2;
	double f3;
	double fi1;
	double fi2;
	double fi3;
	int N;
	double fd;
	int p;
	afx_msg void OnBnClickedDraw();
	Drawer drw;
	afx_msg void OnBnClickedAkm();
	signal s;
	int num_vector;
	afx_msg void OnBnClickedDrawvector();
	Drawer drw_vec;
	Matrix V, U, sigma;
	CEdit res_work;
	Drawer drw_U;
	int num_vector_U;
	afx_msg void OnBnClickedDrawU();
	Drawer drw_singular;
};
