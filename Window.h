#pragma once
#include "wx/wx.h"

class Window : public wxFrame
{

public:
	Window();
	~Window();

public:
	/*wxButton* button1 = nullptr;
	wxButton* button2 = nullptr;
	wxTextCtrl* textBox = nullptr;*/

	int nFieldWidth = 10;
	int nFieldHeight = 10;
	wxButton** btn;

	int* nField = nullptr;
	bool bFirstClick = true;

	void OnButtonClicked(wxCommandEvent& evt);

};

