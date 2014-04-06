//
// file name: hworld.cpp
//
//   purpose: wxWindows "Hello world"
//

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
	#include "wx/notebook.h"
	#include "wx/statbox.h"
	#include <wx/colordlg.h>
	#include <wx/dir.h>
	#include <wx/config.h>
	#include <wx/progdlg.h>
#include <wx/image.h>
#include "folder.xpm"
#include "xpms/default_bg.xpm"
#include "ani_button.h"
#include "config.h"
#include "xpms/ani_xpms.h"
#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include "rskin.h"
#include "skin.h"
#include "skincanvas.h"
/*#include <wx/txtstrm.h>
#include <wx/wfstream.h>

extern wxFFileOutputStream output;
extern  wxTextOutputStream cout;*/


class MyApp: public wxApp
{
    virtual bool OnInit();
};



enum
{
    ID_Quit = 1,
    ID_About,
    ID_NOTEBOOK,
		ID_CanvasPaint,
		ID_TextBgColour,
		ID_TextFgColour,
		ID_VisPeakColour,
		ID_VisTopColour,
		ID_VisMiddleColour,
		ID_VisBottomColour,
		ID_VisBgColour,
		ID_VisBgGridColour,
		ID_OscMinColour,
		ID_OscMaxColour,
		ID_EqGraphTopColour,
		ID_EqGraphMiddleColour,
		ID_EqGraphBottomColour,
		ID_EqSliderTopColour,
		ID_EqSliderMiddleColour,
		ID_EqSliderBottomColour,
		ID_PlNormalColour,
		ID_PlActiveColour,
		ID_PlBgColour,
		ID_PlSelectedColour,
		ID_TemplateSelector,
		ID_OnRefreshSkin,
		ID_SelectSkinDirectory,
		ID_ExportSkin,
		ID_LoadMainBitmap,
		ID_LoadEqBitmap,
		ID_LoadPlBitmap,
		ID_SkinTemplateDirectory,
		ID_prefsMenu,
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Quit,  MyFrame::OnQuit)
    EVT_MENU(ID_About, MyFrame::OnAbout)
	  EVT_MENU(ID_SkinTemplateDirectory, MyFrame::OnSelectSkinTemplateDirectory)
		EVT_BUTTON(ID_TextBgColour, MyFrame::OnTextBgColour)
		EVT_BUTTON(ID_TextFgColour, MyFrame::OnTextFgColour)
		EVT_BUTTON(ID_VisPeakColour, MyFrame::OnVisPeakColour)
		EVT_BUTTON(ID_VisTopColour, MyFrame::OnVisTopColour)
		EVT_BUTTON(ID_VisMiddleColour, MyFrame::OnVisMiddleColour)
		EVT_BUTTON(ID_VisBottomColour, MyFrame::OnVisBottomColour)
		EVT_BUTTON(ID_VisBgColour, MyFrame::OnVisBgColour)
		EVT_BUTTON(ID_VisBgGridColour, MyFrame::OnVisBgGridColour)
		EVT_BUTTON(ID_OscMinColour, MyFrame::OnOscMinColour)
		EVT_BUTTON(ID_OscMaxColour, MyFrame::OnOscMaxColour)
		EVT_BUTTON(ID_EqGraphTopColour, MyFrame::OnEqGraphTopColour)
		EVT_BUTTON(ID_EqGraphMiddleColour, MyFrame::OnEqGraphMiddleColour)
		EVT_BUTTON(ID_EqGraphBottomColour, MyFrame::OnEqGraphBottomColour)
		EVT_BUTTON(ID_EqSliderTopColour, MyFrame::OnEqSliderTopColour)
		EVT_BUTTON(ID_EqSliderMiddleColour, MyFrame::OnEqSliderMiddleColour)
		EVT_BUTTON(ID_EqSliderBottomColour, MyFrame::OnEqSliderBottomColour)
		EVT_BUTTON(ID_PlNormalColour, MyFrame::OnPlNormalColour)
		EVT_BUTTON(ID_PlActiveColour, MyFrame::OnPlActiveColour)
		EVT_BUTTON(ID_PlBgColour, MyFrame::OnPlBgColour)
		EVT_BUTTON(ID_PlSelectedColour, MyFrame::OnPlSelectedColour)
		EVT_BUTTON(ID_OnRefreshSkin, MyFrame::OnRefreshSkin)
		EVT_BUTTON(ID_SelectSkinDirectory, MyFrame::OnSelectSkinDirectory)
		EVT_BUTTON(ID_ExportSkin, MyFrame::OnExportSkin)
		EVT_BUTTON(ID_LoadMainBitmap, MyFrame::OnLoadMainBitmap)
		EVT_BUTTON(ID_LoadEqBitmap, MyFrame::OnLoadEqBitmap)
		EVT_BUTTON(ID_LoadPlBitmap, MyFrame::OnLoadPlBitmap)
		EVT_LISTBOX(ID_TemplateSelector, MyFrame::OnTemplateSelected)
		EVT_NOTEBOOK_PAGE_CHANGED(ID_NOTEBOOK, MyFrame::OnPageChanged)
		EVT_CLOSE(MyFrame::OnClose)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( "RitschiSkin", wxPoint(50,50), wxSize(568,456) );
    frame->Show( TRUE );
    SetTopWindow( frame );
    return TRUE;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
	
    /*wxMenu *menuFile = new wxMenu;

    menuFile->Append( ID_About, "&About..." );
    menuFile->AppendSeparator();
    menuFile->Append( ID_Quit, "E&xit" );

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );

    SetMenuBar( menuBar );
*/
		wxMenu *canvasMenu = new wxMenu;
		wxMenu *prefsMenu = new wxMenu;
		prefsMenu->Append( ID_SkinTemplateDirectory, "&Skin-Vorlagen Verzeichnis..." );
		canvasMenu->Append( ID_prefsMenu, "Einstellungen",prefsMenu );
		canvasMenu->Append( ID_About, "Ü&ber..." );
		canvasMenu->AppendSeparator();
		canvasMenu->Append( ID_Quit, "&Beenden" );
    //--
//    	miniFrameTest = new wxMiniFrame(this, ID_Frame ,"Hello");

	m_SkinCanvas = new MyCanvas( this, ID_CanvasPaint,canvasMenu,m_MainPreview,wxPoint( -1, -1), wxSize(275, 348) );
	wxBoxSizer *SkinCanvasSizer = new wxBoxSizer( wxHORIZONTAL );
	SkinCanvasSizer->Add( m_SkinCanvas,1,wxALL | wxEXPAND,10 );
	
	m_notebook = new wxNotebook(this, ID_NOTEBOOK); 
	wxPanel *SkinPanel = new wxPanel(m_notebook, -1);
	
	wxBoxSizer *button_sizer = new wxBoxSizer( wxVERTICAL );
	wxStaticBox *TemplateNameBox = new wxStaticBox(SkinPanel, -1, "Vorlagen");
	wxStaticBoxSizer *TemplateNameBoxSizer = new wxStaticBoxSizer( TemplateNameBox, wxVERTICAL );
	button_sizer->Add( TemplateNameBoxSizer, 1,wxALL | wxEXPAND, 5 );
	m_TemplateSelectorListBox = new wxListBox(SkinPanel, ID_TemplateSelector);
	TemplateNameBoxSizer->Add( m_TemplateSelectorListBox, 1,wxALL | wxEXPAND, 5 );
	button_sizer->Add( new wxButton(SkinPanel, ID_OnRefreshSkin, "Skin auffrischen"),0,wxALL | wxEXPAND,5);
	//button_sizer->Add( new wxButton(SkinPanel, -1, "Drück mich"),0,wxALL | wxEXPAND,5);




	
	SkinPanel->SetAutoLayout( TRUE );
	SkinPanel->SetSizer( button_sizer );
// 'Farben' Panel
		wxPanel *ColourPanel = new wxPanel(m_notebook, -1);
		
		wxBoxSizer *ColourSizer = new wxBoxSizer( wxVERTICAL );
	//-- Text
		wxStaticBox *TextBox = new wxStaticBox(ColourPanel, -1 ,"Text");
		wxStaticBoxSizer *TextBoxSizer = new wxStaticBoxSizer( TextBox, wxVERTICAL );
		wxGridSizer *TextColorSizer = new wxGridSizer(2, 2);
		
		m_TextFgColourButton = new wxButton(ColourPanel, ID_TextFgColour,"",wxPoint(-1,-1),wxSize(50,13));
		m_TextFgColourButton->SetBackgroundColour(wxColour("GREEN"));
		TextColorSizer->Add(new wxStaticText(ColourPanel,-1,"Vordergrund"),1,wxALIGN_LEFT|wxEXPAND);
		TextColorSizer->Add(m_TextFgColourButton,0,wxALIGN_RIGHT|wxLEFT,5); //wxLEFT|wxRIGHT,10
		wxBoxSizer *TextBackgroundColourSizer = new wxBoxSizer( wxHORIZONTAL );
		m_TextBgColourButton = new wxButton(ColourPanel, ID_TextBgColour,"",wxPoint(-1,-1),wxSize(50,13));
		m_TextBgColourButton->SetBackgroundColour(wxColour("BLACK"));
		TextColorSizer->Add(new wxStaticText(ColourPanel,-1,"Hintergrund"),1,wxALIGN_LEFT|wxEXPAND);
		TextColorSizer->Add(m_TextBgColourButton,0,wxALIGN_RIGHT|wxLEFT,5);
		TextBoxSizer->Add(TextColorSizer,0,wxALIGN_TOP|wxEXPAND|wxLEFT|wxRIGHT,5);
	//-- End Text	

	//-- Vis
		wxStaticBox *VisBox = new wxStaticBox(ColourPanel, -1, "Visualisation");
		wxStaticBoxSizer *VisBoxSizer = new wxStaticBoxSizer( VisBox, wxVERTICAL );
		wxBoxSizer *VisColourSizer = new wxBoxSizer( wxHORIZONTAL );
/*--*/
		wxGridSizer *VisFireSizer = new wxGridSizer(2, 4);

		m_VisPeakColourButton = new wxButton(ColourPanel, ID_VisPeakColour,"",wxPoint(-1,-1),wxSize(50,13));
		m_VisPeakColourButton->SetBackgroundColour(wxColour("GREEN"));
		m_VisTopColourButton = new wxButton(ColourPanel, ID_VisTopColour,"",wxPoint(-1,-1),wxSize(50,13));
		m_VisTopColourButton->SetBackgroundColour(wxColour("BLACK"));
		m_VisMiddleColourButton = new wxButton(ColourPanel, ID_VisMiddleColour,"",wxPoint(-1,-1),wxSize(50,13));
		m_VisMiddleColourButton->SetBackgroundColour(wxColour("RED"));
		m_VisBottomColourButton = new wxButton(ColourPanel, ID_VisBottomColour,"",wxPoint(-1,-1),wxSize(50,13));
		m_VisBottomColourButton->SetBackgroundColour(wxColour("RED"));
		m_OscMinColourButton = new wxButton(ColourPanel, ID_OscMinColour,"",wxPoint(-1,-1),wxSize(50,13));
		m_OscMinColourButton->SetBackgroundColour(wxColour("WHITE"));
		m_OscMaxColourButton = new wxButton(ColourPanel, ID_OscMaxColour,"",wxPoint(-1,-1),wxSize(50,13));
		m_OscMaxColourButton->SetBackgroundColour(wxColour("BLACK"));
		VisFireSizer->Add(new wxStaticText(ColourPanel,-1,"Peaks"),1,wxALIGN_LEFT|wxEXPAND);
		VisFireSizer->Add(m_VisPeakColourButton,0,wxALIGN_RIGHT|wxLEFT,5);
		VisFireSizer->Add(new wxStaticText(ColourPanel,-1,"oben"),1,wxALIGN_LEFT|wxEXPAND);
		VisFireSizer->Add(m_VisTopColourButton,0,wxALIGN_RIGHT|wxLEFT,5);
		VisFireSizer->Add(new wxStaticText(ColourPanel,-1,"mitte"),1,wxALIGN_LEFT|wxEXPAND);
		VisFireSizer->Add(m_VisMiddleColourButton,0,wxALIGN_RIGHT|wxLEFT,5);
		VisFireSizer->Add(new wxStaticText(ColourPanel,-1,"unten"),1,wxALIGN_LEFT|wxEXPAND);
		VisFireSizer->Add(m_VisBottomColourButton,0,wxALIGN_RIGHT|wxLEFT,5);
/*		wxBoxSizer *VisColourSizer1 = new wxBoxSizer( wxVERTICAL );
			wxBoxSizer *VisPeaksSizer= new wxBoxSizer( wxHORIZONTAL );
				VisPeaksSizer->Add(new wxStaticText(ColourPanel,-1,"Peaks"),1,wxALIGN_LEFT|wxEXPAND);
				VisPeaksSizer->Add(m_VisPeakColourButton,0,wxALIGN_RIGHT|wxLEFT,5); //wxLEFT|wxRIGHT,10
			wxBoxSizer *VisTopSizer= new wxBoxSizer( wxHORIZONTAL );
				VisTopSizer->Add(new wxStaticText(ColourPanel,-1,"oben"),1,wxALIGN_LEFT|wxEXPAND);
				VisTopSizer->Add(m_VisTopColourButton,0,wxALIGN_RIGHT|wxLEFT,5); //wxLEFT|wxRIGHT,10
			wxBoxSizer *VisMiddleSizer= new wxBoxSizer( wxHORIZONTAL );
				VisMiddleSizer->Add(new wxStaticText(ColourPanel,-1,"mitte"),1,wxALIGN_LEFT|wxEXPAND);
				VisMiddleSizer->Add(m_VisMiddleColourButton,0,wxALIGN_RIGHT|wxLEFT,5); //wxLEFT|wxRIGHT,10
			wxBoxSizer *VisBottomSizer= new wxBoxSizer( wxHORIZONTAL );
				VisBottomSizer->Add(new wxStaticText(ColourPanel,-1,"unten"),1,wxALIGN_LEFT|wxEXPAND);
				VisBottomSizer->Add(m_VisBottomColourButton,0,wxALIGN_RIGHT|wxLEFT,5); //wxLEFT|wxRIGHT,10

			VisColourSizer1->Add(VisPeaksSizer,0,wxALIGN_TOP|wxEXPAND|wxLEFT|wxRIGHT,5);
			VisColourSizer1->Add(VisTopSizer,0,wxALIGN_TOP|wxEXPAND|wxLEFT|wxRIGHT,5);
			VisColourSizer1->Add(VisMiddleSizer,0,wxALIGN_TOP|wxEXPAND|wxLEFT|wxRIGHT,5);
			VisColourSizer1->Add(VisBottomSizer,0,wxALIGN_TOP|wxEXPAND|wxLEFT|wxRIGHT,5);*/
		VisColourSizer->Add(VisFireSizer,0,wxEXPAND|wxALIGN_TOP|wxLEFT|wxRIGHT,5);		
		wxBoxSizer *VisColourSizer2 = new wxBoxSizer( wxVERTICAL );
	
		wxGridSizer *VisOscSizer = new wxGridSizer(2, 2);
		VisOscSizer->Add(new wxStaticText(ColourPanel,-1,"min"),1,wxALIGN_LEFT|wxEXPAND);
		VisOscSizer->Add(m_OscMinColourButton,0,wxALIGN_RIGHT|wxRIGHT,5);
		VisOscSizer->Add(new wxStaticText(ColourPanel,-1,"max"),1,wxALIGN_LEFT|wxEXPAND);
		VisOscSizer->Add(m_OscMaxColourButton,0,wxALIGN_RIGHT|wxRIGHT,5);
/*			wxBoxSizer *VisMinSizer= new wxBoxSizer( wxHORIZONTAL );
			
				VisMinSizer->Add(new wxStaticText(ColourPanel,-1,"min"),1,wxALIGN_LEFT|wxEXPAND);
				VisMinSizer->Add(m_OscMinColourButton,0,wxALIGN_RIGHT|wxLEFT,5); //wxLEFT|wxRIGHT,10
			wxBoxSizer *VisMaxSizer= new wxBoxSizer( wxHORIZONTAL );
				VisMaxSizer->Add(new wxStaticText(ColourPanel,-1,"max"),1,wxALIGN_LEFT|wxEXPAND);
				VisMaxSizer->Add(m_OscMaxColourButton,0,wxALIGN_RIGHT|wxLEFT,5); //wxLEFT|wxRIGHT,10
*/
			VisColourSizer2->Add(new wxStaticText(ColourPanel,-1,"Oscilloskop"),1,wxALIGN_LEFT|wxEXPAND|wxLEFT,5);
			VisColourSizer2->Add(VisOscSizer,0,wxALIGN_TOP|wxEXPAND|wxLEFT|wxRIGHT,5);
/*			VisColourSizer2->Add(VisMinSizer,0,wxALIGN_TOP|wxEXPAND|wxLEFT|wxRIGHT,5);
			VisColourSizer2->Add(VisMaxSizer,0,wxALIGN_TOP|wxEXPAND|wxLEFT|wxRIGHT,5);
*/
			
		VisColourSizer->Add(VisColourSizer2,0,wxEXPAND);//<---			
		VisBoxSizer->Add(VisColourSizer,0,wxALIGN_TOP|wxEXPAND);
		VisBoxSizer->Add(30, 10);

		wxGridSizer *VisBgSizer = new wxGridSizer(2, 2);
	
		m_VisBgColourButton = new wxButton(ColourPanel, ID_VisBgColour,"",wxPoint(-1,-1),wxSize(50,13));
		m_VisBgColourButton->SetBackgroundColour(wxColour("BLACK"));
		VisBgSizer->Add(new wxStaticText(ColourPanel,-1,"Hintergrund"),1,wxALIGN_LEFT|wxEXPAND);
		VisBgSizer->Add(m_VisBgColourButton,0,wxALIGN_RIGHT|wxLEFT,5);
		m_VisBgGridColourButton = new wxButton(ColourPanel, ID_VisBgGridColour,"",wxPoint(-1,-1),wxSize(50,13));
		m_VisBgGridColourButton->SetBackgroundColour(wxColour("GRAY"));
		VisBgSizer->Add(new wxStaticText(ColourPanel,-1,"Hintergrund Gitter"),1,wxALIGN_LEFT|wxEXPAND);
		VisBgSizer->Add(m_VisBgGridColourButton,0,wxALIGN_RIGHT|wxLEFT,5);

		VisBoxSizer->Add(VisBgSizer,0,wxALIGN_TOP|wxEXPAND|wxLEFT|wxRIGHT,5);
	
		//-- End Vis

		//-- Eq
		wxStaticBox *EqBox = new wxStaticBox(ColourPanel, -1 ,"Equalizer");
		wxStaticBoxSizer *EqBoxSizer = new wxStaticBoxSizer( EqBox, wxHORIZONTAL );
		wxBoxSizer *EqGraphSizer = new wxBoxSizer( wxVERTICAL );
		EqBoxSizer->Add(EqGraphSizer,1,wxALIGN_TOP|wxEXPAND|wxLEFT|wxRIGHT,5);
		EqGraphSizer->Add(new wxStaticText(ColourPanel,-1,"Graph"));
		EqGraphSizer->Add(3, 3);
		wxGridSizer *EqGraphColourSizer = new wxGridSizer(2, 3);
		m_EqGraphTopColourButton = new wxButton(ColourPanel, ID_EqGraphTopColour,"",wxPoint(-1,-1),wxSize(50,13));
		m_EqGraphTopColourButton->SetBackgroundColour(wxColour("RED"));
		m_EqGraphMiddleColourButton = new wxButton(ColourPanel, ID_EqGraphMiddleColour,"",wxPoint(-1,-1),wxSize(50,13));
		m_EqGraphMiddleColourButton->SetBackgroundColour(wxColour("YELLOW"));
		m_EqGraphBottomColourButton = new wxButton(ColourPanel, ID_EqGraphBottomColour,"",wxPoint(-1,-1),wxSize(50,13));
		m_EqGraphBottomColourButton->SetBackgroundColour(wxColour("GREEN"));
		EqGraphColourSizer->Add(new wxStaticText(ColourPanel,-1,"oben"),1,wxEXPAND);
		EqGraphColourSizer->Add(m_EqGraphTopColourButton,0,wxALIGN_RIGHT);
		EqGraphColourSizer->Add(new wxStaticText(ColourPanel,-1,"mitte"),1,wxEXPAND);
		EqGraphColourSizer->Add(m_EqGraphMiddleColourButton,0,wxALIGN_RIGHT);
		EqGraphColourSizer->Add(new wxStaticText(ColourPanel,-1,"unten"),1,wxEXPAND);
		EqGraphColourSizer->Add(m_EqGraphBottomColourButton,0,wxALIGN_RIGHT);
		EqGraphSizer->Add(EqGraphColourSizer,1,wxALIGN_TOP|wxEXPAND|wxLEFT|wxRIGHT);
	
		//EqBoxSizer->Add(10, 10);
	wxBoxSizer *EqSliderSizer = new wxBoxSizer( wxVERTICAL );
	
		EqBoxSizer->Add(EqSliderSizer,1,wxALIGN_TOP|wxEXPAND|wxLEFT|wxRIGHT,5);
		EqSliderSizer->Add(new wxStaticText(ColourPanel,-1,"Schieberegler"));
		EqSliderSizer->Add(3, 3);
		wxGridSizer *EqSliderColourSizer = new wxGridSizer(2, 3);
		m_EqSliderTopColourButton = new wxButton(ColourPanel, ID_EqSliderTopColour,"",wxPoint(-1,-1),wxSize(50,13));
		m_EqSliderTopColourButton->SetBackgroundColour(wxColour("RED"));
		m_EqSliderMiddleColourButton = new wxButton(ColourPanel, ID_EqSliderMiddleColour,"",wxPoint(-1,-1),wxSize(50,13));
		m_EqSliderMiddleColourButton->SetBackgroundColour(wxColour("YELLOW"));
		m_EqSliderBottomColourButton = new wxButton(ColourPanel, ID_EqSliderBottomColour,"",wxPoint(-1,-1),wxSize(50,13));
		m_EqSliderBottomColourButton->SetBackgroundColour(wxColour("GREEN"));
		EqSliderColourSizer->Add(new wxStaticText(ColourPanel,-1,"oben"),1,wxEXPAND);
		EqSliderColourSizer->Add(m_EqSliderTopColourButton,0,wxALIGN_RIGHT);
		EqSliderColourSizer->Add(new wxStaticText(ColourPanel,-1,"mitte"),1,wxEXPAND);
		EqSliderColourSizer->Add(m_EqSliderMiddleColourButton,0,wxALIGN_RIGHT);
		EqSliderColourSizer->Add(new wxStaticText(ColourPanel,-1,"unten"),1,wxEXPAND);
		EqSliderColourSizer->Add(m_EqSliderBottomColourButton,0,wxALIGN_RIGHT);
		EqSliderSizer->Add(EqSliderColourSizer,1,wxALIGN_TOP|wxEXPAND|wxLEFT|wxRIGHT);	
		//-- End Eq
		//-- Pl
		wxStaticBox *PlBox = new wxStaticBox(ColourPanel, -1 ,"Playlist");
		wxStaticBoxSizer *PlBoxSizer = new wxStaticBoxSizer( PlBox, wxHORIZONTAL );
		wxGridSizer *PlColour1Sizer = new wxGridSizer(2, 2);
		m_PlNormalColourButton = new wxButton(ColourPanel, ID_PlNormalColour,"",wxPoint(-1,-1),wxSize(50,13));
		m_PlNormalColourButton->SetBackgroundColour(wxColour("GREEN"));
		m_PlActiveColourButton = new wxButton(ColourPanel, ID_PlActiveColour,"",wxPoint(-1,-1),wxSize(50,13));
		m_PlActiveColourButton->SetBackgroundColour(wxColour("WHITE"));
		PlColour1Sizer->Add(new wxStaticText(ColourPanel,-1,"normal"),1,wxEXPAND);
		PlColour1Sizer->Add(m_PlNormalColourButton,0,wxALIGN_RIGHT);
		PlColour1Sizer->Add(new wxStaticText(ColourPanel,-1,"aktiv"),1,wxEXPAND);
		PlColour1Sizer->Add(m_PlActiveColourButton,0,wxALIGN_RIGHT);
		PlBoxSizer->Add(PlColour1Sizer,1,wxALIGN_TOP|wxEXPAND|wxLEFT|wxRIGHT,5);
		//PlBoxSizer->Add(10, 10);
		
		wxGridSizer *PlColour2Sizer = new wxGridSizer(2, 2);
		m_PlBgColourButton = new wxButton(ColourPanel, ID_PlBgColour,"",wxPoint(-1,-1),wxSize(50,13));
		m_PlBgColourButton->SetBackgroundColour(wxColour("BLACK"));
		m_PlSelectedColourButton = new wxButton(ColourPanel, ID_PlSelectedColour,"",wxPoint(-1,-1),wxSize(50,13));
		m_PlSelectedColourButton->SetBackgroundColour(wxColour("BLUE"));
		PlColour2Sizer->Add(new wxStaticText(ColourPanel,-1,"hinten"),1,wxEXPAND);
		PlColour2Sizer->Add(m_PlBgColourButton,0,wxALIGN_RIGHT);
		PlColour2Sizer->Add(new wxStaticText(ColourPanel,-1,"gewählt"),1,wxEXPAND);
		PlColour2Sizer->Add(m_PlSelectedColourButton,0,wxALIGN_RIGHT);
		PlBoxSizer->Add(PlColour2Sizer,1,wxALIGN_TOP|wxEXPAND|wxLEFT|wxRIGHT,5);
		
		
		//-- End Pl
		

		ColourSizer->Add( TextBoxSizer,0,wxEXPAND|wxALL, 5);
		ColourSizer->Add( VisBoxSizer,0,wxEXPAND|wxALL, 5);
		ColourSizer->Add( EqBoxSizer,0,wxEXPAND|wxALL, 5);
		ColourSizer->Add( PlBoxSizer,0,wxEXPAND|wxALL, 5);
		ColourPanel->SetAutoLayout( TRUE );
		ColourPanel->SetSizer( ColourSizer );

// 'Farben' Panel Ende
	wxPanel *BitmapPanel = new wxPanel(m_notebook, -1);
	wxBoxSizer *BitmapPanelSizer = new wxBoxSizer( wxVERTICAL );

	wxStaticBox *LoadBitmapsBox = new wxStaticBox(BitmapPanel, -1 ,"Hintergrund Bilder");

/*	wxFont BoldFont = LoadBitmapsBox->GetFont();
	BoldFont.SetWeight(wxBOLD);

	LoadBitmapsBox->SetFont(*wxSWISS_FONT);*/

	wxStaticBoxSizer *LoadBitmapsBoxSizer = new wxStaticBoxSizer( LoadBitmapsBox, wxVERTICAL );
	BitmapPanelSizer->Add(LoadBitmapsBoxSizer,0,wxEXPAND|wxALL,5);
	
	wxGridSizer *LoadBitmapsSizer = new wxGridSizer( 2, 3 );
	LoadBitmapsSizer->Add(new wxStaticText(BitmapPanel, -1, "Main:"),1,wxALIGN_LEFT|wxEXPAND);
	LoadBitmapsSizer->Add(new wxButton(BitmapPanel, ID_LoadMainBitmap, "Laden..."),0,wxALIGN_RIGHT);
	LoadBitmapsSizer->Add(new wxStaticText(BitmapPanel, -1, "Equalizer:"),1,wxALIGN_LEFT|wxEXPAND);
	LoadBitmapsSizer->Add(new wxButton(BitmapPanel, ID_LoadEqBitmap, "Laden..."),0,wxALIGN_RIGHT);
	LoadBitmapsSizer->Add(new wxStaticText(BitmapPanel, -1, "Playlist:"),1,wxALIGN_LEFT|wxEXPAND);
	LoadBitmapsSizer->Add(new wxButton(BitmapPanel, ID_LoadPlBitmap, "Laden..."),0,wxALIGN_RIGHT);
	LoadBitmapsBoxSizer->Add(LoadBitmapsSizer,0,wxEXPAND|wxALL,5);

	wxStaticBox *BitmapPrefsBox = new wxStaticBox(BitmapPanel, -1 ,"Optionen");
	wxStaticBoxSizer *BitmapPrefsBoxSizer = new wxStaticBoxSizer( BitmapPrefsBox, wxVERTICAL );
	
	wxGridSizer *BitmapStyleSizer = new wxGridSizer( 3, 2 );
	BitmapPrefsBoxSizer->Add(BitmapStyleSizer,1,wxEXPAND|wxALL,5);
	BitmapPanelSizer->Add(BitmapPrefsBoxSizer,1,wxEXPAND|wxALL,5);
	BitmapPanel->SetSizer( BitmapPanelSizer );
	BitmapPanel->SetAutoLayout( TRUE );
	//wxString AniButtonPath="/home/oracle/wx_swe/rskin/media/all_frames/";

	m_AniButton1 = new AniButton( BitmapPanel, -1 ,this,1, wxBitmap( _1_frame_1),wxBitmap( _1_frame_2) ,wxBitmap( _1_frame_3) ,wxBitmap( _1_frame_4) ,wxBitmap( _1_frame_5 ) );
	m_AniButton2 = new AniButton( BitmapPanel, -1 ,this,2, wxBitmap( _2_frame_1),wxBitmap( _2_frame_2) ,wxBitmap( _2_frame_3) ,wxBitmap( _2_frame_4) ,wxBitmap( _2_frame_5 ) );
	m_AniButton3 = new AniButton( BitmapPanel, -1 ,this,3, wxBitmap( _3_frame_1),wxBitmap( _3_frame_2) ,wxBitmap( _3_frame_3) ,wxBitmap( _3_frame_4) ,wxBitmap( _3_frame_5 ) );
	m_AniButton4 = new AniButton( BitmapPanel, -1 ,this,4, wxBitmap( _4_frame_1),wxBitmap( _4_frame_2) ,wxBitmap( _4_frame_3) ,wxBitmap( _4_frame_4) ,wxBitmap( _4_frame_5  ) );
	m_AniButton5 = new AniButton( BitmapPanel, -1 ,this,5, wxBitmap( _5_frame_1),wxBitmap( _5_frame_2) ,wxBitmap( _5_frame_3) ,wxBitmap( _5_frame_4) ,wxBitmap( _5_frame_5 ) );
	m_AniButton6 = new AniButton( BitmapPanel, -1 ,this,6, wxBitmap( _6_frame_1),wxBitmap( _6_frame_2) ,wxBitmap( _6_frame_3) ,wxBitmap( _6_frame_4) ,wxBitmap( _6_frame_5 ) );
	m_AniButton1->Check();

	BitmapStyleSizer->Add(m_AniButton1);
	BitmapStyleSizer->Add(m_AniButton2);
	BitmapStyleSizer->Add(m_AniButton3);
	BitmapStyleSizer->Add(m_AniButton4);
	BitmapStyleSizer->Add(m_AniButton5);
	BitmapStyleSizer->Add(m_AniButton6);
	wxPanel *ExportPanel = makeExportPanel(m_notebook);
#ifdef __WXMSW_
	m_SkinTemplateDirectory = wxGetCwd() + "/templates";
#endif
#ifdef __WXGTK_
	m_SkinTemplateDirectory = c_SkinTemplateDirectory;
#endif

	LoadPreferences();
	
	//m_SkinTemplateDirectory = "/home/oracle/wx_swe/rskin/templates2";

	/*--read SkinTemplateList--*/
	if (wxDirExists(m_SkinTemplateDirectory))
	{
		wxDir dir(m_SkinTemplateDirectory);
		wxString TemplateName;
		bool cont = dir.GetFirst(&TemplateName, wxEmptyString, wxDIR_DIRS);
		while ( cont )
		{
			m_TemplateSelectorListBox->Append( TemplateName );
			cont = dir.GetNext(&TemplateName);
		}
	}
	else
		wxLogError("Vorlagen-Verzeichnis wurde nicht gefunden.");
	/*-- end read SkinTemplateList--*/

	m_mySkinObject = new Skin();
	m_mySkinObject->SetTemplatePath(m_SkinTemplateDirectory);
	
// -- m_SkinCanvas
	//wxBitmap DefaultBitmap("/home/oracle/wx_swe/rskin/default.bmp",wxBITMAP_TYPE_BMP);
	wxBitmap DefaultBitmap(default_bg_xpm);
	m_SkinCanvas->SetMainBitmap( DefaultBitmap );
	m_SkinCanvas->SetEqBitmap( DefaultBitmap );
	m_SkinCanvas->SetPlBitmap( DefaultBitmap );
	m_MainPreview = wxBitmap(275,348);
 	wxMemoryDC m_MainPreview_dc;
  m_MainPreview_dc.SelectObject(m_MainPreview);
 	wxMemoryDC DefaultBitmap_dc;
  DefaultBitmap_dc.SelectObject(DefaultBitmap);
	m_MainPreview_dc.Blit(0, 0, 275, 116, &DefaultBitmap_dc , 0, 0);
	m_MainPreview_dc.Blit(0, 116, 275, 116, &DefaultBitmap_dc , 0, 0);
	m_MainPreview_dc.Blit(0, 232, 275, 116, &DefaultBitmap_dc , 0, 0);
	m_SkinCanvas->SetBitmap( m_MainPreview );
// -- Ende m_SkinCanvas

	m_mySkinObject->SetTextBgColour(m_TextBgColourButton->GetBackgroundColour());
	m_mySkinObject->SetTextFgColour(m_TextFgColourButton->GetBackgroundColour());
	m_mySkinObject->SetVisPeakColour(m_VisPeakColourButton->GetBackgroundColour());
	m_mySkinObject->SetVisTopColour(m_VisTopColourButton->GetBackgroundColour());
	m_mySkinObject->SetVisMiddleColour(m_VisMiddleColourButton->GetBackgroundColour());
	m_mySkinObject->SetVisBottomColour(m_VisBottomColourButton->GetBackgroundColour());
	m_mySkinObject->SetVisBgColour(m_VisBgColourButton->GetBackgroundColour());
	m_mySkinObject->SetVisBgGridColour(m_VisBgGridColourButton->GetBackgroundColour());
	m_mySkinObject->SetOscMinColour(m_OscMinColourButton->GetBackgroundColour());
	m_mySkinObject->SetOscMaxColour(m_OscMaxColourButton->GetBackgroundColour());
	m_mySkinObject->SetEqGraphTopColour(m_EqGraphTopColourButton->GetBackgroundColour());
	m_mySkinObject->SetEqGraphMiddleColour(m_EqGraphMiddleColourButton->GetBackgroundColour());
	m_mySkinObject->SetEqGraphBottomColour(m_EqGraphBottomColourButton->GetBackgroundColour());
	m_mySkinObject->SetEqSliderTopColour(m_EqSliderTopColourButton->GetBackgroundColour());
	m_mySkinObject->SetEqSliderMiddleColour(m_EqSliderMiddleColourButton->GetBackgroundColour());
	m_mySkinObject->SetEqSliderBottomColour(m_EqSliderBottomColourButton->GetBackgroundColour());
	m_mySkinObject->SetPlNormalColour(m_PlNormalColourButton->GetBackgroundColour());
	m_mySkinObject->SetPlActiveColour(m_PlActiveColourButton->GetBackgroundColour());
	m_mySkinObject->SetPlBgColour(m_PlBgColourButton->GetBackgroundColour());
	m_mySkinObject->SetPlSelectedColour(m_PlSelectedColourButton->GetBackgroundColour());

	m_notebook->AddPage(BitmapPanel, "Bilder", TRUE);
	m_notebook->AddPage(SkinPanel, "Skin", TRUE);
	m_notebook->AddPage(ColourPanel, "Farben", TRUE);
	m_notebook->AddPage(ExportPanel, "SkinExport", TRUE);
    //--
	wxNotebookSizer *topsizer = new wxNotebookSizer(m_notebook);
	SkinCanvasSizer->Add( topsizer ,0,wxEXPAND|wxALL );
	SkinCanvasSizer->SetSizeHints(this);
	SetAutoLayout( TRUE );
	SetSizer( SkinCanvasSizer );
	
	m_notebook->SetSelection(0);
	//	m_SkinCanvas->StartEdit();
	wxInitAllImageHandlers();

}

MyFrame::~MyFrame()
{
	delete m_mySkinObject;
}

void MyFrame::LoadPreferences()
{
	m_config = new wxConfig("RitschiSkin");
	wxConfigBase::Set(m_config);
	wxString str;
	m_config->Read("SkinDirectory", &str);
	m_SkinDirectory->SetValue(str);
	m_config->Read("SkinTemplateDirectory", &m_SkinTemplateDirectory);
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	
	//delete m_config;  // Wird offenbar automatisch gelöscht.
	Close( TRUE );
}

void MyFrame::OnClose( wxCloseEvent& event)
{
	m_config->Write("SkinDirectory", m_SkinDirectory->GetValue());
	m_config->Write("SkinTemplateDirectory", m_SkinTemplateDirectory);

	this->Destroy();


}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox( "RitschiSkin von Richard Spindler\noracle2025@gmx.de",
                  "About RitschiSkin", wxOK | wxICON_INFORMATION );
}

void MyFrame::OnTextBgColour(wxCommandEvent& WXUNUSED(event))
{
	wxColourDialog dialog(this);
  if (dialog.ShowModal() == wxID_OK)
  {
    wxColourData retData = dialog.GetColourData();
    m_mySkinObject->SetTextBgColour(retData.GetColour());
		m_TextBgColourButton->SetBackgroundColour(retData.GetColour());
		RefreshSkinView();
	}


}

void MyFrame::OnTextFgColour(wxCommandEvent& WXUNUSED(event))
{
	wxColourDialog dialog(this);
  if (dialog.ShowModal() == wxID_OK)
  {
    wxColourData retData = dialog.GetColourData();
    m_mySkinObject->SetTextFgColour(retData.GetColour());
		m_TextFgColourButton->SetBackgroundColour(retData.GetColour());
		RefreshSkinView();
	}

}

void MyFrame::OnVisPeakColour(wxCommandEvent& WXUNUSED(event))
{
	wxColourDialog dialog(this);
  if (dialog.ShowModal() == wxID_OK)
  {
    wxColourData retData = dialog.GetColourData();
    m_mySkinObject->SetVisPeakColour(retData.GetColour());
		m_VisPeakColourButton->SetBackgroundColour(retData.GetColour());
		wxMemoryDC bitmap_dc;
		bitmap_dc.SelectObject(m_MainPreview);
		m_mySkinObject->DrawVisPreview( bitmap_dc );
		m_SkinCanvas->SetBitmap( m_MainPreview );
	}

}

void MyFrame::OnVisTopColour(wxCommandEvent& WXUNUSED(event))
{
	wxColourDialog dialog(this);
  if (dialog.ShowModal() == wxID_OK)
  {
    wxColourData retData = dialog.GetColourData();
    m_mySkinObject->SetVisTopColour(retData.GetColour());
		m_VisTopColourButton->SetBackgroundColour(retData.GetColour());
		wxMemoryDC bitmap_dc;
		bitmap_dc.SelectObject(m_MainPreview);
		m_mySkinObject->DrawVisPreview( bitmap_dc );
		m_SkinCanvas->SetBitmap( m_MainPreview );
	}

}

void MyFrame::OnVisMiddleColour(wxCommandEvent& WXUNUSED(event))
{
	wxColourDialog dialog(this);
  if (dialog.ShowModal() == wxID_OK)
  {
    wxColourData retData = dialog.GetColourData();
    m_mySkinObject->SetVisMiddleColour(retData.GetColour());
		m_VisMiddleColourButton->SetBackgroundColour(retData.GetColour());
		wxMemoryDC bitmap_dc;
		bitmap_dc.SelectObject(m_MainPreview);
		m_mySkinObject->DrawVisPreview( bitmap_dc );
		m_SkinCanvas->SetBitmap( m_MainPreview );
	}

}

void MyFrame::OnVisBottomColour(wxCommandEvent& WXUNUSED(event))
{
	wxColourDialog dialog(this);
  if (dialog.ShowModal() == wxID_OK)
  {
    wxColourData retData = dialog.GetColourData();
    m_mySkinObject->SetVisBottomColour(retData.GetColour());
		m_VisBottomColourButton->SetBackgroundColour(retData.GetColour());
		wxMemoryDC bitmap_dc;
		bitmap_dc.SelectObject(m_MainPreview);
		m_mySkinObject->DrawVisPreview( bitmap_dc );
		m_SkinCanvas->SetBitmap( m_MainPreview );
	}

}

void MyFrame::OnVisBgColour(wxCommandEvent& WXUNUSED(event))
{
	wxColourDialog dialog(this);
  if (dialog.ShowModal() == wxID_OK)
  {
    wxColourData retData = dialog.GetColourData();
    m_mySkinObject->SetVisBgColour(retData.GetColour());
		m_VisBgColourButton->SetBackgroundColour(retData.GetColour());
		wxMemoryDC bitmap_dc;
		bitmap_dc.SelectObject(m_MainPreview);
		m_mySkinObject->DrawVisPreview( bitmap_dc );
		m_SkinCanvas->SetBitmap( m_MainPreview );
	}

}

void MyFrame::OnVisBgGridColour(wxCommandEvent& WXUNUSED(event))
{
	wxColourDialog dialog(this);
  if (dialog.ShowModal() == wxID_OK)
  {
    wxColourData retData = dialog.GetColourData();
    m_mySkinObject->SetVisBgGridColour(retData.GetColour());
		m_VisBgGridColourButton->SetBackgroundColour(retData.GetColour());
		wxMemoryDC bitmap_dc;
		bitmap_dc.SelectObject(m_MainPreview);
		m_mySkinObject->DrawVisPreview( bitmap_dc );
		m_SkinCanvas->SetBitmap( m_MainPreview );
	}

}

void MyFrame::OnOscMinColour(wxCommandEvent& WXUNUSED(event))
{
	wxColourDialog dialog(this);
  if (dialog.ShowModal() == wxID_OK)
  {
    wxColourData retData = dialog.GetColourData();
    m_mySkinObject->SetOscMinColour(retData.GetColour());
		m_OscMinColourButton->SetBackgroundColour(retData.GetColour());
	}

}

void MyFrame::OnOscMaxColour(wxCommandEvent& WXUNUSED(event))
{
	wxColourDialog dialog(this);
  if (dialog.ShowModal() == wxID_OK)
  {
    wxColourData retData = dialog.GetColourData();
    m_mySkinObject->SetOscMaxColour(retData.GetColour());
		m_OscMaxColourButton->SetBackgroundColour(retData.GetColour());
	}

}

void MyFrame::OnEqGraphTopColour(wxCommandEvent& WXUNUSED(event))
{
	wxColourDialog dialog(this);
  if (dialog.ShowModal() == wxID_OK)
  {
    wxColourData retData = dialog.GetColourData();
    m_mySkinObject->SetEqGraphTopColour(retData.GetColour());
		m_EqGraphTopColourButton->SetBackgroundColour(retData.GetColour());
		wxMemoryDC bitmap_dc;
		bitmap_dc.SelectObject(m_MainPreview);
		m_mySkinObject->DrawEqPreviewGradients( bitmap_dc, 116 );
		m_SkinCanvas->SetBitmap( m_MainPreview );
	}

}

void MyFrame::OnEqGraphMiddleColour(wxCommandEvent& WXUNUSED(event))
{
	wxColourDialog dialog(this);
  if (dialog.ShowModal() == wxID_OK)
  {
    wxColourData retData = dialog.GetColourData();
    m_mySkinObject->SetEqGraphMiddleColour(retData.GetColour());
		m_EqGraphMiddleColourButton->SetBackgroundColour(retData.GetColour());
		wxMemoryDC bitmap_dc;
		bitmap_dc.SelectObject(m_MainPreview);
		m_mySkinObject->DrawEqPreviewGradients( bitmap_dc, 116 );
		m_SkinCanvas->SetBitmap( m_MainPreview );
	}

}

void MyFrame::OnEqGraphBottomColour(wxCommandEvent& WXUNUSED(event))
{
	wxColourDialog dialog(this);
  if (dialog.ShowModal() == wxID_OK)
  {
    wxColourData retData = dialog.GetColourData();
    m_mySkinObject->SetEqGraphBottomColour(retData.GetColour());
		m_EqGraphBottomColourButton->SetBackgroundColour(retData.GetColour());
		wxMemoryDC bitmap_dc;
		bitmap_dc.SelectObject(m_MainPreview);
		m_mySkinObject->DrawEqPreviewGradients( bitmap_dc, 116 );
		m_SkinCanvas->SetBitmap( m_MainPreview );
	}

}

void MyFrame::OnEqSliderTopColour(wxCommandEvent& WXUNUSED(event))
{
	wxColourDialog dialog(this);
  if (dialog.ShowModal() == wxID_OK)
  {
    wxColourData retData = dialog.GetColourData();
    m_mySkinObject->SetEqSliderTopColour(retData.GetColour());
		m_EqSliderTopColourButton->SetBackgroundColour(retData.GetColour());
		wxMemoryDC bitmap_dc;
		bitmap_dc.SelectObject(m_MainPreview);
		m_mySkinObject->DrawEqPreviewGradients( bitmap_dc, 116 );
		m_SkinCanvas->SetBitmap( m_MainPreview );
	}

}

void MyFrame::OnEqSliderMiddleColour(wxCommandEvent& WXUNUSED(event))
{
	wxColourDialog dialog(this);
  if (dialog.ShowModal() == wxID_OK)
  {
    wxColourData retData = dialog.GetColourData();
    m_mySkinObject->SetEqSliderMiddleColour(retData.GetColour());
		m_EqSliderMiddleColourButton->SetBackgroundColour(retData.GetColour());
		wxMemoryDC bitmap_dc;
		bitmap_dc.SelectObject(m_MainPreview);
		m_mySkinObject->DrawEqPreviewGradients( bitmap_dc, 116 );
		m_SkinCanvas->SetBitmap( m_MainPreview );
	}

}

void MyFrame::OnEqSliderBottomColour(wxCommandEvent& WXUNUSED(event))
{
	wxColourDialog dialog(this);
  if (dialog.ShowModal() == wxID_OK)
  {
    wxColourData retData = dialog.GetColourData();
    m_mySkinObject->SetEqSliderBottomColour(retData.GetColour());
		m_EqSliderBottomColourButton->SetBackgroundColour(retData.GetColour());
		wxMemoryDC bitmap_dc;
		bitmap_dc.SelectObject(m_MainPreview);
		m_mySkinObject->DrawEqPreviewGradients( bitmap_dc, 116 );
		m_SkinCanvas->SetBitmap( m_MainPreview );
	}

}

void MyFrame::OnPlNormalColour(wxCommandEvent& WXUNUSED(event))
{
	wxColourDialog dialog(this);
  if (dialog.ShowModal() == wxID_OK)
  {
    wxColourData retData = dialog.GetColourData();
    m_mySkinObject->SetPlNormalColour(retData.GetColour());
		m_PlNormalColourButton->SetBackgroundColour(retData.GetColour());
		wxMemoryDC bitmap_dc;
		bitmap_dc.SelectObject(m_MainPreview);
		m_mySkinObject->DrawPlTextPreview(bitmap_dc,232);
		m_SkinCanvas->SetBitmap( m_MainPreview );
	}

}

void MyFrame::OnPlActiveColour(wxCommandEvent& WXUNUSED(event))
{
	wxColourDialog dialog(this);
  if (dialog.ShowModal() == wxID_OK)
  {
    wxColourData retData = dialog.GetColourData();
    m_mySkinObject->SetPlActiveColour(retData.GetColour());
		m_PlActiveColourButton->SetBackgroundColour(retData.GetColour());
		wxMemoryDC bitmap_dc;
		bitmap_dc.SelectObject(m_MainPreview);
		m_mySkinObject->DrawPlTextPreview(bitmap_dc,232);
		m_SkinCanvas->SetBitmap( m_MainPreview );	
	}

}

void MyFrame::OnPlBgColour(wxCommandEvent& WXUNUSED(event))
{
	wxColourDialog dialog(this);
  if (dialog.ShowModal() == wxID_OK)
  {
    wxColourData retData = dialog.GetColourData();
    m_mySkinObject->SetPlBgColour(retData.GetColour());
		m_PlBgColourButton->SetBackgroundColour(retData.GetColour());
		wxMemoryDC bitmap_dc;
		bitmap_dc.SelectObject(m_MainPreview);
		m_mySkinObject->DrawPlTextPreview(bitmap_dc,232);
		m_SkinCanvas->SetBitmap( m_MainPreview );	
	}

}

void MyFrame::OnPlSelectedColour(wxCommandEvent& WXUNUSED(event))
{
	wxColourDialog dialog(this);
  if (dialog.ShowModal() == wxID_OK)
  {
    wxColourData retData = dialog.GetColourData();
    m_mySkinObject->SetPlSelectedColour(retData.GetColour());
		m_PlSelectedColourButton->SetBackgroundColour(retData.GetColour());
		wxMemoryDC bitmap_dc;
		bitmap_dc.SelectObject(m_MainPreview);
		m_mySkinObject->DrawPlTextPreview(bitmap_dc,232);
		m_SkinCanvas->SetBitmap( m_MainPreview );	
	}

}

void MyFrame::OnTemplateSelected(wxCommandEvent& WXUNUSED(event))
{
	m_mySkinObject->SetTemplateName(m_TemplateSelectorListBox->GetStringSelection());
}

void MyFrame::OnRefreshSkin(wxCommandEvent& WXUNUSED(event))
{
	RefreshSkinView();
}

void MyFrame::RefreshSkinView()
{
	if (m_TemplateSelectorListBox->Number())
	{
	
		m_mySkinObject->SetMainBg(m_SkinCanvas->GetMainBitmap());
		m_mySkinObject->SetEqBg(m_SkinCanvas->GetEqBitmap());
		m_mySkinObject->SetPlBg(m_SkinCanvas->GetPlBitmap());
		wxProgressDialog Progress("RitschiSkin", "Berechne Vorschau...", 11, this,wxPD_APP_MODAL );
		wxBitmap MainPreview = m_mySkinObject->GetMainPreview(&Progress);
		wxBitmap EqPreview = m_mySkinObject->GetEqPreview(&Progress);
		wxBitmap PlPreview = m_mySkinObject->GetPlPreview(&Progress);

		m_MainPreview = wxBitmap(275,348);
		//m_MainPreview.SetHeight( 232 );
		//m_MainPreview.SetWidth( 275 );
		wxMemoryDC m_MainPreview_dc;
		m_MainPreview_dc.SelectObject(m_MainPreview);
		wxMemoryDC MainPreview_dc;
		MainPreview_dc.SelectObject(MainPreview);
		wxMemoryDC EqPreview_dc;
		EqPreview_dc.SelectObject(EqPreview);
		wxMemoryDC PlPreview_dc;
		PlPreview_dc.SelectObject(PlPreview);

		m_MainPreview_dc.Blit(0, 0, 275, 116, &MainPreview_dc , 0, 0);
		m_MainPreview_dc.Blit(0, 116, 275, 116, &EqPreview_dc , 0, 0);
		m_MainPreview_dc.Blit(0, 232, 275, 116, &PlPreview_dc , 0, 0);

		//m_MainPreview = mySkinObject->GetMainPreview();
		m_SkinCanvas->SetBitmap( m_MainPreview );
	}
	else
	{
		wxLogError("Es konnten keine Vorlagen gefunden werden.");
	}
}

wxPanel* MyFrame::makeExportPanel(wxWindow* parent)
{

	wxPanel* ExportPanel = new wxPanel(parent, -1);
	wxBoxSizer *ExportPanelSizer = new wxBoxSizer( wxVERTICAL );
	//-- Text
	wxStaticBox *SkinDirectoryBox = new wxStaticBox(ExportPanel, -1 ,"WinAmp\\Skins Verzeichnis");
	wxStaticBoxSizer *SkinDirectoryBoxSizer = new wxStaticBoxSizer( SkinDirectoryBox, wxHORIZONTAL );
	ExportPanelSizer->Add(SkinDirectoryBoxSizer,0,wxEXPAND|wxALL,5);
	m_SkinDirectory = new wxTextCtrl(ExportPanel, -1,"",wxDefaultPosition,wxDefaultSize,wxTE_READONLY);
	SkinDirectoryBoxSizer->Add(m_SkinDirectory,1,wxEXPAND|wxALL,5);
	wxBitmapButton* SelectSkinDir = new wxBitmapButton(ExportPanel, ID_SelectSkinDirectory, wxBitmap(folder_xpm));
	SkinDirectoryBoxSizer->Add(SelectSkinDir,0,wxEXPAND|wxTOP|wxRIGHT|wxBOTTOM,5);

	wxStaticBox *SkinNameInputBox = new wxStaticBox(ExportPanel, -1 ,"Name der Skin");
	wxStaticBoxSizer *SkinNameInputBoxSizer = new wxStaticBoxSizer( SkinNameInputBox, wxHORIZONTAL );
	ExportPanelSizer->Add(SkinNameInputBoxSizer,0,wxEXPAND|wxALL,5);
	m_SkinNameInput = new wxTextCtrl(ExportPanel, -1);
	SkinNameInputBoxSizer->Add(m_SkinNameInput,1,wxEXPAND|wxALL,5);
/* //--Info Files
	wxStaticBox *SkinInfoFilesBox = new wxStaticBox(ExportPanel, -1 ,"Info Dateien");
	wxStaticBoxSizer *SkinInfoFilesBoxSizer = new wxStaticBoxSizer( SkinInfoFilesBox, wxVERTICAL );
	ExportPanelSizer->Add(SkinInfoFilesBoxSizer,1,wxEXPAND|wxALL,5);
	
	wxCheckBox *File_id_dizCheckBox = new wxCheckBox( ExportPanel, -1, "File_id.diz");
	SkinInfoFilesBoxSizer->Add(File_id_dizCheckBox,0,wxEXPAND|wxLEFT|wxRIGHT|wxTOP,5);


	wxTextCtrl *File_id_dizText = new wxTextCtrl(ExportPanel, -1,"",wxDefaultPosition,wxDefaultSize, wxTE_MULTILINE);

	SkinInfoFilesBoxSizer->Add(File_id_dizText,1,wxEXPAND|wxALL,5);
	SkinInfoFilesBox->SetAutoLayout( TRUE );


	wxCheckBox *Readme_txtCheckBox = new wxCheckBox( ExportPanel, -1, "Readme.diz");
	SkinInfoFilesBoxSizer->Add(Readme_txtCheckBox,0,wxEXPAND);

	wxTextCtrl *Readme_txtText = new wxTextCtrl(ExportPanel, -1,"",wxDefaultPosition,wxDefaultSize, wxTE_MULTILINE);
	SkinInfoFilesBoxSizer->Add(Readme_txtText,1,wxEXPAND|wxALL,5);
*/
	
	ExportPanelSizer->Add( new wxButton(ExportPanel, ID_ExportSkin, "Exportieren"),0,wxALL | wxEXPAND,5);

	ExportPanel->SetAutoLayout( TRUE );
	ExportPanel->SetSizer( ExportPanelSizer );
	return ExportPanel;
}

void MyFrame::OnSelectSkinDirectory(wxCommandEvent& WXUNUSED(event))
{
	wxDirDialog dialog( this, "WinAmp/Skins Verzeichnis wählen" );

  if (dialog.ShowModal() == wxID_OK)
  {
		m_mySkinObject->SetSkinsDirectory( dialog.GetPath() );
		m_SkinDirectory->SetValue( dialog.GetPath() );
	}

}

void MyFrame::OnExportSkin(wxCommandEvent& event)
{
	/*m_SkinDirectory
		m_SkinNameInput*/
	if ( (m_SkinNameInput->GetValue()) != "" )
	{
		wxString hh = m_SkinDirectory->GetValue() +  "/" +  m_SkinNameInput->GetValue();
		m_mySkinObject->SaveSkin( hh );
	}
}

void MyFrame::OnLoadMainBitmap(wxCommandEvent& event)
{
	wxFileDialog OpenDialog( this, "Bild öffnen", "", "", "Alle Dateien (*.*)|*.*|BMP Bilder (*.bmp)|*.bmp|GIF Bilder (*.gif)|*.gif|JPEG Bilder (*.jpg)|*.jpg",wxOPEN|wxFILE_MUST_EXIST);
	if ( OpenDialog.ShowModal() == wxID_OK)
	{
		//m_SkinCanvas->SetMainBitmap(wxBitmap(OpenDialog.GetDirectory() + "/" + OpenDialog.GetFilename(),wxBITMAP_TYPE_BMP) );
		m_SkinCanvas->SetMainBitmap( wxImage(OpenDialog.GetDirectory() + "/" + OpenDialog.GetFilename()).ConvertToBitmap() );
	}
}
void MyFrame::OnLoadEqBitmap(wxCommandEvent& event)
{
	wxFileDialog OpenDialog( this, "Bild öffnen", "", "", "Alle Dateien (*.*)|*.*|BMP Bilder (*.bmp)|*.bmp|GIF Bilder (*.gif)|*.gif|JPEG Bilder (*.jpg)|*.jpg",wxOPEN|wxFILE_MUST_EXIST);
	if ( OpenDialog.ShowModal() == wxID_OK)
	{
		//m_SkinCanvas->SetEqBitmap(wxBitmap(OpenDialog.GetDirectory() + "/" + OpenDialog.GetFilename(),wxBITMAP_TYPE_BMP) );

		
		m_SkinCanvas->SetEqBitmap( wxImage(OpenDialog.GetDirectory() + "/" + OpenDialog.GetFilename()).ConvertToBitmap() );

		
	}
}
void MyFrame::OnLoadPlBitmap(wxCommandEvent& event)
{
	wxFileDialog OpenDialog( this, "Bild öffnen", "", "", "Alle Dateien (*.*)|*.*|BMP Bilder (*.bmp)|*.bmp|GIF Bilder (*.gif)|*.gif|JPEG Bilder (*.jpg)|*.jpg",wxOPEN|wxFILE_MUST_EXIST);
	if ( OpenDialog.ShowModal() == wxID_OK)
	{
		//m_SkinCanvas->SetPlBitmap(wxBitmap(OpenDialog.GetDirectory() + "/" + OpenDialog.GetFilename(),wxBITMAP_TYPE_BMP) );
		m_SkinCanvas->SetPlBitmap( wxImage(OpenDialog.GetDirectory() + "/" + OpenDialog.GetFilename()).ConvertToBitmap() );
	}
}

void MyFrame::OnPageChanged(wxNotebookEvent& event)
{
	if ( event.GetSelection() == 0 )
	{
		m_SkinCanvas->StartEdit();
	}
	else
	{
		if ( !event.GetOldSelection() )
			RefreshSkinView();

		m_SkinCanvas->StopEdit();
	}
}


void MyFrame::AniButtonCallback( int number )
{
	m_AniButton1->Check( 1 == number );
	m_AniButton2->Check( 2 == number );
	m_AniButton3->Check( 3 == number );
	m_AniButton4->Check( 4 == number );
	m_AniButton5->Check( 5 == number );
	m_AniButton6->Check( 6 == number );
	m_SkinCanvas->SetAlignment( number );
}

void MyFrame::OnSelectSkinTemplateDirectory(wxCommandEvent& event)
{
	wxDirDialog dialog( this, "Skin-Vorlagen Verzeichnis wählen" );
	dialog.SetPath(m_SkinTemplateDirectory);
  if (dialog.ShowModal() == wxID_OK)
  {
		m_SkinTemplateDirectory = dialog.GetPath();
		m_mySkinObject->SetTemplatePath(m_SkinTemplateDirectory);
			
		wxDir dir(m_SkinTemplateDirectory);
		wxString TemplateName;
		m_TemplateSelectorListBox->Clear();
		bool cont = dir.GetFirst(&TemplateName, wxEmptyString, wxDIR_DIRS);
		while ( cont )
		{
			m_TemplateSelectorListBox->Append( TemplateName );
			cont = dir.GetNext(&TemplateName);
		}

		
	}

}
