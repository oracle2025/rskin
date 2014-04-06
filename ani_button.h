/*  ani_button.h
 */

#ifndef _ANI_BUTTON_H_
#define _ANI_BUTTON_H_
class wxBitmap;
class wxTimer;
class wxTimerEvent;
class MyFrame;
#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/panel.h>

class AniButton: public wxPanel
{
	public:
		AniButton( wxWindow* parent, wxWindowID id, MyFrame* callback_window, int Number , const wxBitmap& frame1, const wxBitmap& frame2, const wxBitmap& frame3, const wxBitmap& frame4, const wxBitmap& frame5 );
		~AniButton();
		void OnEnter( wxMouseEvent& );
		void OnLeave( wxMouseEvent& );
		void OnFrameTimer( wxTimerEvent& event );
		void OnPaint(wxPaintEvent& event);
		void Check( bool = true );
		void UnCheck();
		bool Checked();
		void OnClick( wxMouseEvent& );
  private:
		wxBitmap m_frame1;
		wxBitmap m_frame2;
		wxBitmap m_frame3;
		wxBitmap m_frame4;
		wxBitmap m_frame5;
		wxTimer *m_FrameTimer;
		bool m_checked;
		int m_counter;
		int m_index;
		MyFrame* m_callback_window;
		DECLARE_EVENT_TABLE()	
};

#endif
