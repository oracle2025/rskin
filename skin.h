/*  skin.h
 */

#ifndef _SKIN_H_
#define _SKIN_H_

class wxProgressDialog;

class Skin
{
	public:
		Skin();
		~Skin();
		int SetTemplateName( const wxString& ); // Name of Template
		int SetTemplatePath( const wxString& ); // Path to Template Directory
		int SetSkinsDirectory( const wxString& );
		void SetMainBg( const wxBitmap& );
		void SetEqBg( const wxBitmap& );
		void SetPlBg( const wxBitmap& );
		int SaveSkin( wxString& );        // Saves the Skin in the given Directory
		wxBitmap GetMainPreview( wxProgressDialog* );        // Calculates the Preview
		wxBitmap GetEqPreview( wxProgressDialog* );          // --"--
		wxBitmap GetPlPreview( wxProgressDialog* );          // --"--

	// Rendering Details
		void SetTextBgColour( const wxColour& );
		void SetTextFgColour( const wxColour& );
		void SetVisPeakColour( const wxColour& );
		void SetVisTopColour( const wxColour& );
		void SetVisMiddleColour( const wxColour& );
		void SetVisBottomColour( const wxColour& );
		void SetVisBgColour( const wxColour& );
		void SetVisBgGridColour( const wxColour& );
		void SetOscMinColour( const wxColour& );
		void SetOscMaxColour( const wxColour& );
		void SetEqGraphTopColour( const wxColour& );
		void SetEqGraphMiddleColour( const wxColour& );
		void SetEqGraphBottomColour( const wxColour& );
		void SetEqSliderTopColour( const wxColour& );
		void SetEqSliderMiddleColour( const wxColour& );
		void SetEqSliderBottomColour( const wxColour& );
		void SetPlNormalColour( const wxColour& );
		void SetPlActiveColour( const wxColour& );
		void SetPlBgColour( const wxColour& );
		void SetPlSelectedColour( const wxColour& );
		void DrawPlTextPreview( wxDC& , int );
		void DrawEqPreviewGradients( wxDC& , int);
		void DrawVisPreview( wxDC& );
		void DrawTextPreview( wxDC& );
		
	private:
		wxBitmap m_MainBg;
		wxBitmap m_EqBg;
		wxBitmap m_PlBg;
		wxString m_TemplateName;
		wxString m_TemplatePath;
		wxString m_SkinsDirectory;
		wxBitmap CalcMainBitmap();
		wxBitmap CalcCbuttonsBitmap();
		wxBitmap CalcBalanceBitmap();
		wxBitmap CalcMonosterBitmap();
		wxBitmap CalcPosbarBitmap();
		wxBitmap CalcShufrepBitmap();
		wxBitmap CalcTitlebarBitmap();
		wxBitmap CalcVolumeBitmap();
		wxBitmap CalcEqmainBitmap();
		wxBitmap CalcEq_exBitmap();
		wxBitmap CalcPleditBitmap();
		wxBitmap CalcPlaypausBitmap();
		wxBitmap CalcTextBitmap();
		wxBitmap CalcNums_exBitmap();
		void SavePleditTxt( const wxString& );
		void SaveViscolorTxt( const wxString& );
	// Colors
		wxColour m_TextBgColour;
		wxColour m_TextFgColour;
		wxColour m_VisPeakColour;
		wxColour m_VisTopColour;
		wxColour m_VisMiddleColour;
		wxColour m_VisBottomColour;
		wxColour m_VisBgColour;
		wxColour m_VisBgGridColour;
		wxColour m_OscMinColour;
		wxColour m_OscMaxColour;
		wxColour m_EqGraphTopColour;
		wxColour m_EqGraphMiddleColour;
		wxColour m_EqGraphBottomColour;
		wxColour m_EqSliderTopColour;
		wxColour m_EqSliderMiddleColour;
		wxColour m_EqSliderBottomColour;
		wxColour m_PlNormalColour;
		wxColour m_PlActiveColour;
		wxColour m_PlBgColour;
		wxColour m_PlSelectedColour;
		int m_black_index, m_lightblue_index, m_darkblue_index, m_white_index, m_lightgray_index, m_gray_index, m_green_index, m_pink_index; 
	
		wxBitmap ApplyShape( wxBitmap&, wxBitmap&, int, int );
		wxBitmap ArrangeBitmapElements( wxBitmap&, char** );
		wxBitmap ArrangeShapeElements( char** );
		wxColour ColourGradient(const wxColour& firstColour, const wxColour& secondColour, int steps, int index );
		void DrawEqmainGradients( wxDC& ); 
};


#endif //_SKIN_H_
