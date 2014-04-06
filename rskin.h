#ifndef _RSKIN_H_
#define _RSKIN_H_

class wxNotebookEvent;
class AniButton;
class wxCommandEvent;
class wxBitmap;
class MyCanvas;
class wxString;
class wxListBox;
class wxTextCtrl;
class wxPanel;
class Skin;
class wxConfig;

class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
		~MyFrame();
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
		void OnSelectSkinTemplateDirectory(wxCommandEvent& event);
		void OnTextBgColour(wxCommandEvent& event);
		void OnTextFgColour(wxCommandEvent& event);
		void OnVisPeakColour(wxCommandEvent& event);
		void OnVisTopColour(wxCommandEvent& event);
		void OnVisMiddleColour(wxCommandEvent& event);
		void OnVisBottomColour(wxCommandEvent& event);
		void OnVisBgColour(wxCommandEvent& event);
		void OnVisBgGridColour(wxCommandEvent& event);
		void OnOscMinColour(wxCommandEvent& event);
		void OnOscMaxColour(wxCommandEvent& event);
		void OnEqGraphTopColour(wxCommandEvent& event);
		void OnEqGraphMiddleColour(wxCommandEvent& event);
		void OnEqGraphBottomColour(wxCommandEvent& event);
		void OnEqSliderTopColour(wxCommandEvent& event);
		void OnEqSliderMiddleColour(wxCommandEvent& event);
		void OnEqSliderBottomColour(wxCommandEvent& event);
		void OnPlNormalColour(wxCommandEvent& event);
		void OnPlActiveColour(wxCommandEvent& event);
		void OnPlBgColour(wxCommandEvent& event);
		void OnPlSelectedColour(wxCommandEvent& event);
		void OnTemplateSelected(wxCommandEvent& event);
		void OnRefreshSkin(wxCommandEvent& event);
		void OnSelectSkinDirectory(wxCommandEvent& event);
		void OnExportSkin(wxCommandEvent& event);
		void OnLoadMainBitmap(wxCommandEvent& event);
		void OnLoadEqBitmap(wxCommandEvent& event);
		void OnLoadPlBitmap(wxCommandEvent& event);
		void OnPageChanged(wxNotebookEvent& event);
		void AniButtonCallback( int );
		void OnClose( wxCloseEvent& );
private:
    wxNotebook* m_notebook;
		MyCanvas* m_SkinCanvas;
		wxBitmap m_MainPreview;
		Skin *m_mySkinObject;
		AniButton* m_AniButton1;
		AniButton* m_AniButton2;
		AniButton* m_AniButton3;
		AniButton* m_AniButton4;
		AniButton* m_AniButton5;
		AniButton* m_AniButton6;
		wxString m_SkinTemplateDirectory;
		wxListBox* m_TemplateSelectorListBox;
		wxButton *m_TextBgColourButton;
		wxButton *m_TextFgColourButton;
		wxButton *m_VisPeakColourButton;
		wxButton *m_VisTopColourButton;
		wxButton *m_VisMiddleColourButton;
		wxButton *m_VisBottomColourButton;
		wxButton *m_VisBgColourButton;
		wxButton *m_VisBgGridColourButton;
		wxButton *m_OscMinColourButton;
		wxButton *m_OscMaxColourButton;
		wxButton *m_EqGraphTopColourButton;
		wxButton *m_EqGraphMiddleColourButton;
		wxButton *m_EqGraphBottomColourButton;
		wxButton *m_EqSliderTopColourButton;
		wxButton *m_EqSliderMiddleColourButton;
		wxButton *m_EqSliderBottomColourButton;
		wxButton *m_PlNormalColourButton;
		wxButton *m_PlActiveColourButton;
		wxButton *m_PlBgColourButton;
		wxButton *m_PlSelectedColourButton;
		wxTextCtrl *m_SkinDirectory;
		wxTextCtrl *m_SkinNameInput;
		wxConfig *m_config;
		void RefreshSkinView();
		wxPanel* makeExportPanel(wxWindow* parent);
		void LoadPreferences();
    DECLARE_EVENT_TABLE()
	
};
#endif
