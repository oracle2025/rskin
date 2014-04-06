/*  ani_button.cpp
 */

#include "ani_button.h"
#include "rskin.h"
#include <wx/timer.h>
#include <wx/dcclient.h>
enum
{
    ID_FrameTimer = 1,
};

BEGIN_EVENT_TABLE(AniButton, wxPanel)
		EVT_ENTER_WINDOW(AniButton::OnEnter)
		EVT_LEAVE_WINDOW(AniButton::OnLeave)
		EVT_TIMER(ID_FrameTimer, AniButton::OnFrameTimer)
		EVT_PAINT(AniButton::OnPaint)
		EVT_LEFT_UP(AniButton::OnClick)
END_EVENT_TABLE()


#include <wx/txtstrm.h>
#include <wx/wfstream.h>
/*extern wxFFileOutputStream output;
extern  wxTextOutputStream cout;*/

AniButton::AniButton( wxWindow* parent, wxWindowID id, MyFrame* callback_window, int index , const wxBitmap& frame1, const wxBitmap& frame2, const wxBitmap& frame3, const wxBitmap& frame4, const wxBitmap& frame5 )
 :	wxPanel( parent, id )
{
	m_frame1 = frame1;
	m_frame2 = frame2;
	m_frame3 = frame3;
	m_frame4 = frame4;
	m_frame5 = frame5;
	m_callback_window = callback_window;
	m_index = index;
	this->SetSize(m_frame1.GetWidth()+4, m_frame1.GetHeight()+4);
	m_FrameTimer = new wxTimer( this, ID_FrameTimer );
	m_checked = false;
	m_counter = 0;
}

AniButton::~AniButton()
{
	delete m_FrameTimer;
}

void AniButton::OnEnter( wxMouseEvent& event )
{
	m_FrameTimer->Stop();
	m_FrameTimer->Start(150);
}

void AniButton::OnLeave( wxMouseEvent& event )
{
	m_FrameTimer->Stop();
}

void AniButton::OnFrameTimer( wxTimerEvent& event )
{
	wxClientDC canvas(this);
	switch ( m_counter )
	{
		case 0:
			canvas.DrawBitmap(m_frame1,2,2,false);
			break;
		case 1:
			canvas.DrawBitmap(m_frame2,2,2,false);
			break;
		case 2:
			canvas.DrawBitmap(m_frame3,2,2,false);
			break;
		case 3:
			canvas.DrawBitmap(m_frame4,2,2,false);
			break;
		case 4:
			canvas.DrawBitmap(m_frame5,2,2,false);
			break;
		case 5:
			canvas.DrawBitmap(m_frame4,2,2,false);
			break;
		case 6:
			canvas.DrawBitmap(m_frame3,2,2,false);
			break;
		case 7:
			canvas.DrawBitmap(m_frame2,2,2,false);
			m_counter = -1;
			break;
		default:
			m_counter = 0;
			break;
	}

	m_counter++;
}

void AniButton::OnPaint( wxPaintEvent& event )
{
	wxPaintDC canvas(this);
switch ( m_counter )
	{
		case 0:
			canvas.DrawBitmap(m_frame2,2,2,false);
			break;
		case 1:
			canvas.DrawBitmap(m_frame1,2,2,false);
			break;
		case 2:
			canvas.DrawBitmap(m_frame2,2,2,false);
			break;
		case 3:
			canvas.DrawBitmap(m_frame3,2,2,false);
			break;
		case 4:
			canvas.DrawBitmap(m_frame4,2,2,false);
			break;
		case 5:
			canvas.DrawBitmap(m_frame5,2,2,false);
			break;
		case 6:
			canvas.DrawBitmap(m_frame4,2,2,false);
			break;
		case 7:
			canvas.DrawBitmap(m_frame3,2,2,false);
			break;
		default:
			break;
	}
	if ( m_checked )
	{
		canvas.SetPen(*wxBLACK_PEN);
		canvas.SetBrush(wxBrush("white", wxTRANSPARENT));
		canvas.DrawRectangle(1, 1,m_frame1.GetWidth()+2, m_frame1.GetHeight()+2);
	}
/*	else
	{
		canvas.SetPen(*wxWHITE_PEN);
		canvas.SetBrush(wxBrush("white", wxTRANSPARENT));
		canvas.DrawRectangle(1, 1,m_frame1.GetWidth()+2, m_frame1.GetHeight()+2);
	}*/
}

void AniButton::Check( bool checked )
{
	m_checked=checked;
	this->Refresh();
}

void AniButton::UnCheck()
{
	m_checked=false;
	this->Refresh();
}

bool AniButton::Checked()
{
	return m_checked;
}

void AniButton::OnClick( wxMouseEvent& event )
{
/*	if ( m_checked )
		UnCheck();
	else
		Check();*/
	m_callback_window->AniButtonCallback(m_index);
}
