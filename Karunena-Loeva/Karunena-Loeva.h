
// Karunena-Loeva.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CKarunenaLoevaApp:
// Сведения о реализации этого класса: Karunena-Loeva.cpp
//

class CKarunenaLoevaApp : public CWinApp
{
public:
	CKarunenaLoevaApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CKarunenaLoevaApp theApp;
