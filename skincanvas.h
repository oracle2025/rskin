#ifndef _SKINCANVAS_H_
#define _SKINCANVAS_H_


class MyCanvas: public wxPanel
{
	public:
		MyCanvas(wxWindow* parent, wxWindowID id, wxMenu* canvasMenu,wxBitmap& tmpBitmap, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize );
		void OnPaint(wxPaintEvent& event);
		void SetBitmap( wxBitmap& tmpBitmap );
		void StartEdit();
		void StopEdit();
		void SetMainBitmap( const wxBitmap& );
		void SetEqBitmap( const wxBitmap& );
		void SetPlBitmap( const wxBitmap& );
		wxBitmap GetMainBitmap();
		wxBitmap GetEqBitmap();
		wxBitmap GetPlBitmap();
		void SetAlignment( int ); /* 1_jedes_element_gleichen_bildauschschnit
		                           * 2_alle_gleiches_bild_anders_ausgerichtet
															 * 3_Main_eq_fortgesetztes_Bild_PL_auch
															 * _anderes_ausgerichte
															 * 4_ein_bild_fuer_alle
															 * 5_jedes_anderes_bild
															 * 6_ein_bild_fuer_main_eq
															 */
		int GetAlignment();
		void OnMouseDown(wxMouseEvent& event);
		void OnMouseUp(wxMouseEvent& event);
		void OnMouseMove(wxMouseEvent& event);
		void OnPopupMenu(wxMouseEvent& event);
	private:
		wxBitmap m_tmpBitmap;
		wxBitmap m_MainBitmap;
		wxBitmap m_EqBitmap;
		wxBitmap m_PlBitmap;
		wxPoint m_MainPosition;
		wxPoint m_EqPosition;
		wxPoint m_PlPosition;
		wxPoint m_LastMousePosition;
		int m_Alignment;
		bool m_editing;
		bool m_dragging;
		int m_MainEqPlDragging;
		void DrawBitmaps( wxDC& );
		void DoTmpBitmap();
		void DrawUpArrow( wxDC&, int  );
		void DrawDownArrow( wxDC&, int );
		void DrawLeftArrow( wxDC&, int );
		void DrawRightArrow( wxDC&, int );
		void DrawArrows( wxDC& );
		wxMenu* m_canvasMenu;
		DECLARE_EVENT_TABLE()
};

#endif

