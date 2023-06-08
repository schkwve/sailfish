/**
 * Sailfish
 * Copyright (C) 2023 Jozef Nagy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "AccountDiag.hpp"

#include <wx/intl.h>
#include <wx/string.h>

const long AccountDiag::ID_LISTCTRL2 = wxNewId();
const long AccountDiag::AC_BTN_NEW = wxNewId();
const long AccountDiag::AC_BTN_REMOVE = wxNewId();
const long AccountDiag::AC_BTN_EDIT = wxNewId();
const long AccountDiag::ID_PANEL1 = wxNewId();
const long AccountDiag::AC_BTN_CLOSE = wxNewId();

BEGIN_EVENT_TABLE(AccountDiag, wxDialog)
END_EVENT_TABLE()

AccountDiag::AccountDiag(wxWindow *parent, wxWindowID id)
{
	wxBoxSizer *BoxSizer1;
	wxBoxSizer *BoxSizer2;
	wxBoxSizer *BoxSizer3;
	wxBoxSizer *BoxSizer4;

	Create(parent, id, "Accounts", wxDefaultPosition, wxDefaultSize,
		   wxDEFAULT_DIALOG_STYLE, _T("id"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize,
						 wxBORDER_STATIC, _T("ID_PANEL1"));
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	AcListCtrl =
		new wxListCtrl(Panel1, ID_LISTCTRL2, wxDefaultPosition, wxDefaultSize,
					   wxLC_REPORT, wxDefaultValidator, _T("ID_LISTCTRL2"));
	BoxSizer3->Add(AcListCtrl, 1,
				   wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
				   5);
	BoxSizer4 = new wxBoxSizer(wxVERTICAL);
	AcNewBtn =
		new wxButton(Panel1, AC_BTN_NEW, _("New"), wxDefaultPosition,
					 wxDefaultSize, 0, wxDefaultValidator, _T("AC_BTN_NEW"));
	BoxSizer4->Add(AcNewBtn, 1,
				   wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
				   5);
	AcRemoveBtn =
		new wxButton(Panel1, AC_BTN_REMOVE, _("Remove"), wxDefaultPosition,
					 wxDefaultSize, 0, wxDefaultValidator, _T("AC_BTN_REMOVE"));
	BoxSizer4->Add(AcRemoveBtn, 1,
				   wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
				   5);
	AcEditBtn =
		new wxButton(Panel1, AC_BTN_EDIT, _("Edit..."), wxDefaultPosition,
					 wxDefaultSize, 0, wxDefaultValidator, _T("AC_BTN_EDIT"));
	BoxSizer4->Add(AcEditBtn, 1,
				   wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
				   5);
	BoxSizer3->Add(BoxSizer4, 0,
				   wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
				   5);
	Panel1->SetSizer(BoxSizer3);
	BoxSizer3->Fit(Panel1);
	BoxSizer3->SetSizeHints(Panel1);
	BoxSizer1->Add(Panel1, 1,
				   wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
				   5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	AcCloseBtn =
		new wxButton(this, AC_BTN_CLOSE, _("Close"), wxDefaultPosition,
					 wxDefaultSize, 0, wxDefaultValidator, _T("AC_BTN_CLOSE"));
	BoxSizer2->Add(AcCloseBtn, 1,
				   wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
				   5);
	BoxSizer1->Add(BoxSizer2, 0, wxALL | wxALIGN_RIGHT, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(wxID_ANY, wxEVT_INIT_DIALOG,
			(wxObjectEventFunction)&AccountDiag::OnInit);
}

AccountDiag::~AccountDiag() {}

void AccountDiag::OnInit(wxInitDialogEvent &event) {}
