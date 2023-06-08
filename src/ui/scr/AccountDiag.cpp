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

#include <iostream>
#include <sqlite3.h>

#include <wx/intl.h>
#include <wx/string.h>

#include "../../db/db.h"

const long AccountDiag::AC_LISTVIEW = wxNewId();
const long AccountDiag::AC_BTN_NEW = wxNewId();
const long AccountDiag::AC_BTN_REMOVE = wxNewId();
const long AccountDiag::AC_BTN_EDIT = wxNewId();
const long AccountDiag::ID_PANEL1 = wxNewId();
const long AccountDiag::AC_BTN_CLOSE = wxNewId();

BEGIN_EVENT_TABLE(AccountDiag, wxDialog)

EVT_BUTTON(AC_BTN_NEW, AccountDiag::OpenNew)
EVT_BUTTON(AC_BTN_REMOVE, AccountDiag::RemoveAcc)
EVT_BUTTON(AC_BTN_EDIT, AccountDiag::OpenEdit)

EVT_BUTTON(AC_BTN_CLOSE, AccountDiag::CloseDiag)

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
	AcListView =
		new wxListView(Panel1, AC_LISTVIEW, wxDefaultPosition, wxDefaultSize,
					   wxLC_REPORT, wxDefaultValidator, _T("AC_LISTVIEW"));

	wxListItem acNameItem;
	wxListItem acTypeItem;
	wxListItem acServItem;

	acNameItem.SetId(0);
	acNameItem.SetText(_("Name"));
	acNameItem.SetWidth(200);
	AcListView->InsertColumn(0, acNameItem);

	acTypeItem.SetId(1);
	acTypeItem.SetText(_("Type"));
	acTypeItem.SetWidth(50);
	AcListView->InsertColumn(1, acTypeItem);

	acServItem.SetId(2);
	acServItem.SetText(_("Server"));
	acServItem.SetWidth(150);
	AcListView->InsertColumn(2, acServItem);

	BoxSizer3->Add(AcListView, 1,
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

void AccountDiag::OpenNew(wxCommandEvent &event)
{
	// AccountNewDiag *accNewDiag = new AccountNewDiag(nullptr, wxID_ANY);
	// accNewDiag->Show();
}

void AccountDiag::RemoveAcc(wxCommandEvent &event)
{
	long selectedItem = -1;

	for (int i = 0; i < AcListView->GetItemCount(); i++) {
		selectedItem = AcListView->GetFirstSelected();
		if (selectedItem == -1)
			break;

		// This single line is the reason I stared at my screen for 6 hours
		// straight.
		// Fuck you wxWidgets.
		AcListView->Select(selectedItem, false);

		remove_user(selectedItem);
		AcListView->DeleteItem(selectedItem);
	}
}

void AccountDiag::OpenEdit(wxCommandEvent &event) {}

void AccountDiag::CloseDiag(wxCommandEvent &event)
{
	// this is annoying because you have to manually kill the app.
	// to be changed once I get this dialog working and I start working on the
	// main window.
	this->Close();
}