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

#ifndef __ACCOUNTDIAG_HPP_
#define __ACCOUNTDIAG_HPP_

#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/listctrl.h>
#include <wx/panel.h>
#include <wx/sizer.h>

class AccountDiag : public wxDialog {
public:
	AccountDiag(wxWindow *parent, wxWindowID id = wxID_ANY);
	virtual ~AccountDiag();

	wxButton *AcCloseBtn;
	wxButton *AcEditBtn;
	wxButton *AcNewBtn;
	wxButton *AcRemoveBtn;
	wxListCtrl *AcListCtrl;
	wxPanel *Panel1;

protected:
	static const long ID_LISTCTRL2;
	static const long AC_BTN_NEW;
	static const long AC_BTN_REMOVE;
	static const long AC_BTN_EDIT;
	static const long ID_PANEL1;
	static const long AC_BTN_CLOSE;

private:
	void OnInit(wxInitDialogEvent &event);

	void OpenNew(wxCommandEvent &event);
	void RemoveAcc(wxCommandEvent &event);
	void OpenEdit(wxCommandEvent &event);

	void CloseDiag(wxCommandEvent &event);

	DECLARE_EVENT_TABLE()
};

#endif // __ACCOUNTDIAG_HPP_