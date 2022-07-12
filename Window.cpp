#include "Window.h"


Window::Window() : wxFrame(nullptr, wxID_ANY, "Minesweeper (kinda)", wxPoint(200, 200), wxSize(500, 500)) {

	/*button1 = new wxButton(this, wxID_ANY, "Hello", wxPoint(10, 10), wxSize(200, 100));
	button2 = new wxButton(this, wxID_ANY, "Yello", wxPoint(10, 120), wxSize(200, 100));
	textBox = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 230), wxSize(300, 100));*/

	btn = new wxButton * [nFieldWidth * nFieldHeight];
	wxGridSizer* grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0);

	nField = new int[nFieldWidth * nFieldHeight];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int x = 0; x < nFieldWidth; x++) {
		for (int y = 0; y < nFieldHeight; y++) {
			btn[y * nFieldWidth + x] = new wxButton(this, 10000 + (y * nFieldWidth + x));
			btn[y * nFieldWidth + x]->SetFont(font);
			grid->Add(btn[y * nFieldWidth + x], 1, wxEXPAND | wxALL);

			btn[y * nFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Window::OnButtonClicked, this);
			
			nField[y * nFieldWidth + x] = 0;

		}
	}

	this->SetSizer(grid);
	grid->Layout();

}

Window::~Window() {
	delete[]btn;
}

void Window::OnButtonClicked(wxCommandEvent& evt) {

	//Get Coordinate of Button in Field Array
	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldWidth;

	if (bFirstClick) {
		int mines = 30;
		
		while (mines) {
			int rx = rand() % nFieldWidth;
			int ry = rand() % nFieldHeight;

			if (nField[ry * nFieldWidth + rx] == 0 && rx != x && ry != y) {
				nField[ry * nFieldWidth + rx] = -1;
				mines--;
			}
		}
		bFirstClick = false;
	}

	//Disable Button, preventing it from being pressed again
	btn[y * nFieldWidth + x]->Enable(false);

	//Check if player hit mine
	if (nField[y * nFieldWidth + x] == -1) {
		wxMessageBox("You hit a mine! Game Over!");

		//Reset Game
		bFirstClick = true;
		for (int x = 0; x < nFieldWidth; x++) {
			for (int y = 0; y < nFieldHeight; y++) {
				nField[y * nFieldWidth + x] = 0;
				btn[y * nFieldWidth + x]->SetLabel("");
				btn[y * nFieldWidth + x]->Enable(true);
			}
		}

	}
	else {
		//Count Neighboring mines
		int mine_count = 0;
		for (int i = -1; i < 2; i++) 
			for (int j = -1; j < 2; j++) {
				if (x + i >= 0 && x + i < nFieldWidth && y + j >= 0 && y + j < nFieldHeight) {
					if (nField[(y + j) * nFieldWidth + (x + i)] == -1)
						mine_count++;
				}
			}
		
		// Update buttons label to show mine count if > 0
		if (mine_count > 0) {
			btn[y * nFieldWidth + x]->SetLabel(std::to_string(mine_count));
		}

	}

	evt.Skip();
}