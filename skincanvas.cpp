#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/dcclient.h>
#include <wx/dcmemory.h>

#include "skincanvas.h"

MyCanvas::MyCanvas(wxWindow* parent, wxWindowID id, wxMenu* canvasMenu, wxBitmap& tmpBitmap, const wxPoint& pos , const wxSize& size )
	: wxPanel(parent, id, pos, size )
{
	m_tmpBitmap = tmpBitmap;
	m_MainPosition.x = 0;
	m_MainPosition.y = 0;
	m_PlPosition.x = 0;
	m_PlPosition.y = 0;
	m_EqPosition.x = 0;
	m_EqPosition.y = 0;
	m_LastMousePosition.x = 0;
	m_LastMousePosition.y = 0;
	m_Alignment = 1;
	m_editing = false;
	m_canvasMenu = canvasMenu;
}
void MyCanvas::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	dc.DrawBitmap(m_tmpBitmap,0,0,false);
	DrawArrows(dc);
}
void MyCanvas::OnMouseDown(wxMouseEvent& event)
{
	if (m_editing)
	{
		this->CaptureMouse();
		m_dragging = true;
		m_LastMousePosition.x = event.m_x;
		m_LastMousePosition.y = event.m_y;
		if ( event.m_y > 116 )
			if ( event.m_y > 232 )
				m_MainEqPlDragging = 3;
			else
				m_MainEqPlDragging = 2;
		else
			m_MainEqPlDragging = 1;
	}
}

void MyCanvas::OnMouseUp(wxMouseEvent& event)
{
	if (m_editing)
	{
		DoTmpBitmap();
	}
	m_dragging = false;
	this->ReleaseMouse();
}

void MyCanvas::DoTmpBitmap()
{
	wxMemoryDC tmpBitmap_dc;
	tmpBitmap_dc.SelectObject(m_tmpBitmap);

/*	tmpBitmap_dc.SetPen(*wxLIGHT_GREY_PEN);
	tmpBitmap_dc.SetBrush(*wxLIGHT_GREY_BRUSH);
	tmpBitmap_dc.DrawRectangle( 0, 0, 275, 348 );*/
	DrawBitmaps(tmpBitmap_dc);
}

void MyCanvas::OnMouseMove(wxMouseEvent& event)
{
	if ( event.m_leftDown && m_dragging && m_editing)
	{
		switch(m_Alignment)
		{
			case 1:
				m_MainPosition.x-= (event.m_x-m_LastMousePosition.x);
				m_MainPosition.y-= (event.m_y-m_LastMousePosition.y);
				break;
			case 2:
				switch(m_MainEqPlDragging)
				{
					case 1:
						m_MainPosition.x-= (event.m_x-m_LastMousePosition.x);
						m_MainPosition.y-= (event.m_y-m_LastMousePosition.y);
						break;
					case 2:
						m_EqPosition.x-= (event.m_x-m_LastMousePosition.x);
						m_EqPosition.y-= (event.m_y-m_LastMousePosition.y);
						break;
					case 3:
						m_PlPosition.x-= (event.m_x-m_LastMousePosition.x);
						m_PlPosition.y-= (event.m_y-m_LastMousePosition.y);
						break;
				}
				break;
			case 3:
				if (m_MainEqPlDragging==3)
				{
						m_PlPosition.x-= (event.m_x-m_LastMousePosition.x);
						m_PlPosition.y-= (event.m_y-m_LastMousePosition.y);
				}
				else
				{
						m_MainPosition.x-= (event.m_x-m_LastMousePosition.x);
						m_MainPosition.y-= (event.m_y-m_LastMousePosition.y);
				}
				break;
			case 4:
				m_MainPosition.x-= (event.m_x-m_LastMousePosition.x);
				m_MainPosition.y-= (event.m_y-m_LastMousePosition.y);
				break;
			case 5:
				switch(m_MainEqPlDragging)
				{
					case 1:
						m_MainPosition.x-= (event.m_x-m_LastMousePosition.x);
						m_MainPosition.y-= (event.m_y-m_LastMousePosition.y);
						break;
					case 2:
						m_EqPosition.x-= (event.m_x-m_LastMousePosition.x);
						m_EqPosition.y-= (event.m_y-m_LastMousePosition.y);
						break;
					case 3:
						m_PlPosition.x-= (event.m_x-m_LastMousePosition.x);
						m_PlPosition.y-= (event.m_y-m_LastMousePosition.y);
						break;
				}
				break;
			case 6:
				if (m_MainEqPlDragging==3)
				{
						m_PlPosition.x-= (event.m_x-m_LastMousePosition.x);
						m_PlPosition.y-= (event.m_y-m_LastMousePosition.y);
				}
				else
				{
						m_MainPosition.x-= (event.m_x-m_LastMousePosition.x);
						m_MainPosition.y-= (event.m_y-m_LastMousePosition.y);
				}
				break;
		}

		switch(m_MainEqPlDragging)
		{
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
		}
	
		m_LastMousePosition.x = event.m_x;
		m_LastMousePosition.y = event.m_y;




		wxClientDC client(this);
		DrawBitmaps(client);
		DrawArrows(client);
	}
	else
	{
		m_dragging = false;
		if ( m_editing )
			DoTmpBitmap();
		this->ReleaseMouse();
	}
}
		
void MyCanvas::SetBitmap( wxBitmap& tmpBitmap )
{

	m_tmpBitmap = tmpBitmap;
	Refresh();
}
void MyCanvas::SetMainBitmap( const wxBitmap& MainBitmap )
{
	m_MainBitmap = MainBitmap;
	m_MainPosition.x = 0;
	m_MainPosition.y = 0;
	wxClientDC client(this);
	DrawBitmaps(client);
	DoTmpBitmap();
}

void MyCanvas::SetEqBitmap( const wxBitmap& EqBitmap )
{
	m_EqBitmap = EqBitmap;

	m_EqPosition.x = 0;
	m_EqPosition.y = 0;
	wxClientDC client(this);
	DrawBitmaps(client);
	DoTmpBitmap();
}

void MyCanvas::SetPlBitmap( const wxBitmap& PlBitmap )
{
	m_PlBitmap = PlBitmap;

	m_PlPosition.x = 0;
	m_PlPosition.y = 0;
	wxClientDC client(this);
	DrawBitmaps(client);
	DoTmpBitmap();
}

void MyCanvas::SetAlignment( int Alignment)
{
	m_Alignment = Alignment;
	DoTmpBitmap();
	wxClientDC client(this);
	DrawBitmaps(client);
}

int MyCanvas::GetAlignment()
{
	return m_Alignment;
}

void MyCanvas::StartEdit()
{
	wxClientDC client(this);
	DrawBitmaps(client);
	DoTmpBitmap();
	m_editing = true;
	this->SetCursor(*wxCROSS_CURSOR);
}

void MyCanvas::StopEdit()
{
	if (m_editing)
	{
		wxClientDC SkinCanvasDC(this);
		SkinCanvasDC.DrawBitmap(m_tmpBitmap,0,0,false);
		m_editing = false;
		this->SetCursor(wxNullCursor);
	}
}

void MyCanvas::DrawBitmaps( wxDC& SkinCanDC )
{
	//wxClientDC SkinCanvasDC(this);
	wxMemoryDC Bitmap_dc;
	Bitmap_dc.SelectObject(m_MainBitmap);
	wxBitmap tmpBitmap(275,348);
	
	wxMemoryDC SkinCanvasDC;
	SkinCanvasDC.SelectObject(tmpBitmap);
	
	SkinCanvasDC.SetPen(*wxLIGHT_GREY_PEN);
	SkinCanvasDC.SetBrush(*wxLIGHT_GREY_BRUSH);
	SkinCanvasDC.DrawRectangle( 0, 0, 275, 348 );
	
/*
	wxMemoryDC Bitmap_dc;
	Bitmap_dc.SelectObject(m_MainBitmap);*/
	
	SkinCanvasDC.Blit(0,0,275,116,&Bitmap_dc,m_MainPosition.x,m_MainPosition.y);


	switch(m_Alignment)
	{
		case 1:
			SkinCanvasDC.Blit(0,116,275,116,&Bitmap_dc,m_MainPosition.x,m_MainPosition.y);
			SkinCanvasDC.Blit(0,232,275,116,&Bitmap_dc,m_MainPosition.x,m_MainPosition.y);
			break;
		case 2:
				SkinCanvasDC.Blit(0,116,275,116,&Bitmap_dc,m_EqPosition.x,m_EqPosition.y);
			SkinCanvasDC.Blit(0,232,275,116,&Bitmap_dc,m_PlPosition.x,m_PlPosition.y);

			break;
		case 3:
			SkinCanvasDC.Blit(0,116,275,116,&Bitmap_dc,m_MainPosition.x,m_MainPosition.y+116);
			SkinCanvasDC.Blit(0,232,275,116,&Bitmap_dc,m_PlPosition.x,m_PlPosition.y);
			break;
		case 4:
			SkinCanvasDC.Blit(0,116,275,116,&Bitmap_dc,m_MainPosition.x,m_MainPosition.y+116);
			SkinCanvasDC.Blit(0,232,275,116,&Bitmap_dc,m_MainPosition.x,m_MainPosition.y+232);
			break;
		case 5:
		Bitmap_dc.SelectObject(m_EqBitmap);
		SkinCanvasDC.Blit(0,116,275,116,&Bitmap_dc,m_EqPosition.x,m_EqPosition.y);
		Bitmap_dc.SelectObject(m_PlBitmap);
		SkinCanvasDC.Blit(0,232,275,116,&Bitmap_dc,m_PlPosition.x,m_PlPosition.y);
			break;
		case 6:
			SkinCanvasDC.Blit(0,116,275,116,&Bitmap_dc,m_MainPosition.x,m_MainPosition.y+116);
			Bitmap_dc.SelectObject(m_PlBitmap);
			SkinCanvasDC.Blit(0,232,275,116,&Bitmap_dc,m_PlPosition.x,m_PlPosition.y);
			break;
	}
	SkinCanDC.Blit(0,0,275,348,&SkinCanvasDC,0,0);

}

void MyCanvas::DrawArrows( wxDC& canvas )
{
	switch(m_Alignment)
	{
		case 1:
			if ( (m_MainBitmap.GetHeight()-m_MainPosition.y) <= 0)
			{
				DrawUpArrow( canvas, 0 );
				DrawUpArrow( canvas, 116 );
				DrawUpArrow( canvas, 232 );
			}
			if ( (-m_MainPosition.y) >= 116)
			{
				DrawDownArrow( canvas, 0 );
				DrawDownArrow( canvas, 116 );
				DrawDownArrow( canvas, 232 );
			}
			if ( (m_MainBitmap.GetWidth()-m_MainPosition.x) <= 0)
			{
				DrawLeftArrow( canvas, 0 );
				DrawLeftArrow( canvas, 116 );
				DrawLeftArrow( canvas, 232 );
			}
			if ( -m_MainPosition.x >= 275)
			{
				DrawRightArrow( canvas, 0 );
				DrawRightArrow( canvas, 116 );
				DrawRightArrow( canvas, 232 );
			}
			break;
		case 2:
			if ( (m_MainBitmap.GetHeight()-m_MainPosition.y) <= 0)
			{
				DrawUpArrow( canvas, 0 );
			}
			if ( (-m_MainPosition.y) >= 116)
			{
				DrawDownArrow( canvas, 0 );
			}
			if ( (m_MainBitmap.GetWidth()-m_MainPosition.x) <= 0)
			{
				DrawLeftArrow( canvas, 0 );
			}
			if ( -m_MainPosition.x >= 275)
			{
				DrawRightArrow( canvas, 0 );
			}
			
			if ( (m_MainBitmap.GetHeight()-m_EqPosition.y) <= 0)
			{
				DrawUpArrow( canvas, 116 );
			}
			if ( (-m_EqPosition.y) >= 116)
			{
				DrawDownArrow( canvas, 116 );
			}
			if ( (m_MainBitmap.GetWidth()-m_EqPosition.x) <= 0)
			{
				DrawLeftArrow( canvas, 116 );
			}
			if ( -m_EqPosition.x >= 275)
			{
				DrawRightArrow( canvas, 116 );
			}
			
			if ( (m_MainBitmap.GetHeight()-m_PlPosition.y) <= 0)
			{
				DrawUpArrow( canvas, 232 );
			}
			if ( (-m_PlPosition.y) >= 116)
			{
				DrawDownArrow( canvas, 232 );
			}
			if ( (m_MainBitmap.GetWidth()-m_PlPosition.x) <= 0)
			{
				DrawLeftArrow( canvas, 232 );
			}
			if ( -m_PlPosition.x >= 275)
			{
				DrawRightArrow( canvas, 232 );
			}
			break;
		case 3:
			if ( (m_MainBitmap.GetHeight()-m_MainPosition.y) <= 0)
			{
				DrawUpArrow( canvas, 0 );
			}
			if ( (-m_MainPosition.y) >= 232)
			{
				DrawDownArrow( canvas, 116 );
			}
			if ( (m_MainBitmap.GetWidth()-m_MainPosition.x) <= 0)
			{
				DrawLeftArrow( canvas, 58 );
			}
			if ( -m_MainPosition.x >= 275)
			{
				DrawRightArrow( canvas, 58 );
			}

			if ( (m_MainBitmap.GetHeight()-m_PlPosition.y) <= 0)
			{
				DrawUpArrow( canvas, 232 );
			}
			if ( (-m_PlPosition.y) >= 116)
			{
				DrawDownArrow( canvas, 232 );
			}
			if ( (m_MainBitmap.GetWidth()-m_PlPosition.x) <= 0)
			{
				DrawLeftArrow( canvas, 232 );
			}
			if ( -m_PlPosition.x >= 275)
			{
				DrawRightArrow( canvas, 232 );
			}

			break;
		case 4:
			if ( (m_MainBitmap.GetHeight()-m_MainPosition.y) <= 0)
			{
				DrawUpArrow( canvas, 0 );
			}
			if ( (-m_MainPosition.y) >= 348)
			{
				DrawDownArrow( canvas, 232 );
			}
			if ( (m_MainBitmap.GetWidth()-m_MainPosition.x) <= 0)
			{
				DrawLeftArrow( canvas, 116 );
			}
			if ( -m_MainPosition.x >= 275)
			{
				DrawRightArrow( canvas, 116 );
			}
			break;
		case 5:
			if ( (m_MainBitmap.GetHeight()-m_MainPosition.y) <= 0)
			{
				DrawUpArrow( canvas, 0 );
			}
			if ( (-m_MainPosition.y) >= 116)
			{
				DrawDownArrow( canvas, 0 );
			}
			if ( (m_MainBitmap.GetWidth()-m_MainPosition.x) <= 0)
			{
				DrawLeftArrow( canvas, 0 );
			}
			if ( -m_MainPosition.x >= 275)
			{
				DrawRightArrow( canvas, 0 );
			}
			
			if ( (m_EqBitmap.GetHeight()-m_EqPosition.y) <= 0)
			{
				DrawUpArrow( canvas, 116 );
			}
			if ( (-m_EqPosition.y) >= 116)
			{
				DrawDownArrow( canvas, 116 );
			}
			if ( (m_EqBitmap.GetWidth()-m_EqPosition.x) <= 0)
			{
				DrawLeftArrow( canvas, 116 );
			}
			if ( -m_EqPosition.x >= 275)
			{
				DrawRightArrow( canvas, 116 );
			}
			
			if ( (m_PlBitmap.GetHeight()-m_PlPosition.y) <= 0)
			{
				DrawUpArrow( canvas, 232 );
			}
			if ( (-m_PlPosition.y) >= 116)
			{
				DrawDownArrow( canvas, 232 );
			}
			if ( (m_PlBitmap.GetWidth()-m_PlPosition.x) <= 0)
			{
				DrawLeftArrow( canvas, 232 );
			}
			if ( -m_PlPosition.x >= 275)
			{
				DrawRightArrow( canvas, 232 );
			}

			break;
		case 6:
			if ( (m_MainBitmap.GetHeight()-m_MainPosition.y) <= 0)
			{
				DrawUpArrow( canvas, 0 );
			}
			if ( (-m_MainPosition.y) >= 232)
			{
				DrawDownArrow( canvas, 116 );
			}
			if ( (m_MainBitmap.GetWidth()-m_MainPosition.x) <= 0)
			{
				DrawLeftArrow( canvas, 58 );
			}
			if ( -m_MainPosition.x >= 275)
			{
				DrawRightArrow( canvas, 58 );
			}

			if ( (m_PlBitmap.GetHeight()-m_PlPosition.y) <= 0)
			{
				DrawUpArrow( canvas, 232 );
			}
			if ( (-m_PlPosition.y) >= 116)
			{
				DrawDownArrow( canvas, 232 );
			}
			if ( (m_PlBitmap.GetWidth()-m_PlPosition.x) <= 0)
			{
				DrawLeftArrow( canvas, 232 );
			}
			if ( -m_PlPosition.x >= 275)
			{
				DrawRightArrow( canvas, 232 );
			}

			
			break;
	}

	
}

void MyCanvas::DrawUpArrow( wxDC& canvas, int offset )
{
	canvas.SetPen(*wxBLACK_PEN);
	canvas.DrawLine( 137, offset+0, 130, offset+7);
	canvas.DrawLine( 130, offset+7, 144, offset+7);
	canvas.DrawLine( 144, offset+7, 137, offset+0);
}

void MyCanvas::DrawDownArrow( wxDC& canvas, int offset )
{
	canvas.SetPen(*wxBLACK_PEN);
	canvas.DrawLine( 137, offset+116, 130, offset+109);
	canvas.DrawLine( 130, offset+109, 144, offset+109);
	canvas.DrawLine( 144, offset+109, 137, offset+116);
}

void MyCanvas::DrawLeftArrow( wxDC& canvas, int offset )
{
	canvas.SetPen(*wxBLACK_PEN);
	canvas.DrawLine( 0, offset+58, 7, offset+65);
	canvas.DrawLine( 7, offset+65, 7, offset+51);
	canvas.DrawLine( 7, offset+51 , 0, offset+58);
}

void MyCanvas::DrawRightArrow( wxDC& canvas, int offset )
{
	canvas.SetPen(*wxBLACK_PEN);
	canvas.DrawLine( 274, offset+58, 267, offset+65);
	canvas.DrawLine( 267, offset+65, 267, offset+51);
	canvas.DrawLine( 267, offset+51 , 274, offset+58);
}

wxBitmap MyCanvas::GetMainBitmap()
{

	wxBitmap tmpBitmap( 275, 348 );

	wxMemoryDC tmpBitmap_dc;
	tmpBitmap_dc.SelectObject(tmpBitmap);
	tmpBitmap_dc.SetPen(*wxLIGHT_GREY_PEN);
	tmpBitmap_dc.SetBrush(*wxLIGHT_GREY_BRUSH);
	tmpBitmap_dc.DrawRectangle( 0, 0, 275, 348 );
	DrawBitmaps( tmpBitmap_dc );
	
	wxBitmap result( 275, 116 );
	wxMemoryDC result_dc;
	result_dc.SelectObject(result);
	result_dc.Blit(0,0,275,116,&tmpBitmap_dc,0,0);
	
/*	wxBitmap result( 275, 116 );
	wxMemoryDC result_dc;
	result_dc.SelectObject(result);
	wxMemoryDC Bitmap_dc;
	Bitmap_dc.SelectObject(m_MainBitmap);
	result_dc.SetPen(*wxLIGHT_GREY_PEN);
	result_dc.SetBrush(*wxLIGHT_GREY_BRUSH);
	result_dc.DrawRectangle( 0, 0, 275, 116 );
	result_dc.Blit(0,0,275,116,&Bitmap_dc,m_MainPosition.x,m_MainPosition.y);*/
	
	return result;
}
	
wxBitmap MyCanvas::GetEqBitmap()
{
	wxBitmap tmpBitmap( 275, 348 );

	wxMemoryDC tmpBitmap_dc;
	tmpBitmap_dc.SelectObject(tmpBitmap);
	tmpBitmap_dc.SetPen(*wxLIGHT_GREY_PEN);
	tmpBitmap_dc.SetBrush(*wxLIGHT_GREY_BRUSH);
	tmpBitmap_dc.DrawRectangle( 0, 0, 275, 348 );
	DrawBitmaps( tmpBitmap_dc );
	
	wxBitmap result( 275, 116 );
	wxMemoryDC result_dc;
	result_dc.SelectObject(result);
	result_dc.Blit(0,0,275,116,&tmpBitmap_dc,0,116);
	/*	wxBitmap result(275, 116);
	wxMemoryDC result_dc;
	result_dc.SelectObject(result);
	wxMemoryDC Bitmap_dc;
	Bitmap_dc.SelectObject(m_EqBitmap);
	result_dc.SetPen(*wxLIGHT_GREY_PEN);
	result_dc.SetBrush(*wxLIGHT_GREY_BRUSH);
	result_dc.DrawRectangle( 0, 0, 275, 116 );
	result_dc.Blit(0,0,275,116,&Bitmap_dc,m_EqPosition.x,m_EqPosition.y);*/
	return result;
}
		
wxBitmap MyCanvas::GetPlBitmap()
{
	wxBitmap tmpBitmap( 275, 348 );

	wxMemoryDC tmpBitmap_dc;
	tmpBitmap_dc.SelectObject(tmpBitmap);
	tmpBitmap_dc.SetPen(*wxLIGHT_GREY_PEN);
	tmpBitmap_dc.SetBrush(*wxLIGHT_GREY_BRUSH);
	tmpBitmap_dc.DrawRectangle( 0, 0, 275, 348 );
	DrawBitmaps( tmpBitmap_dc );
	
	wxBitmap result( 275, 116 );
	wxMemoryDC result_dc;
	result_dc.SelectObject(result);
	result_dc.Blit(0,0,275,116,&tmpBitmap_dc,0,232);
/*	wxBitmap result(275, 116);
	wxMemoryDC result_dc;
	result_dc.SelectObject(result);
	wxMemoryDC Bitmap_dc;
	Bitmap_dc.SelectObject(m_PlBitmap);
	result_dc.SetPen(*wxLIGHT_GREY_PEN);
	result_dc.SetBrush(*wxLIGHT_GREY_BRUSH);
	result_dc.DrawRectangle( 0, 0, 275, 116 );
	result_dc.Blit(0,0,275,116,&Bitmap_dc,m_PlPosition.x,m_PlPosition.y);*/
	return result;
}

void MyCanvas::OnPopupMenu(wxMouseEvent& event)
{
	PopupMenu(m_canvasMenu,event.m_x ,event.m_y );

}
		
BEGIN_EVENT_TABLE(MyCanvas, wxPanel)
    EVT_PAINT( MyCanvas::OnPaint)
		EVT_LEFT_DOWN( MyCanvas::OnMouseDown)
		EVT_RIGHT_DOWN( MyCanvas::OnPopupMenu)
		EVT_LEFT_UP(MyCanvas::OnMouseUp)
		EVT_MOTION(MyCanvas::OnMouseMove)
END_EVENT_TABLE()


