/*  skin.cpp
 */

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/dcmemory.h>
#include <wx/image.h>
#include <wx/tokenzr.h>
#include <wx/progdlg.h>

#include "skin.h"

/* Skin file includes */
#include "main_preview.h"
#include "main_previewSh.h"
#include "eq_preview.h"
#include "eq_previewSh.h"
#include "pl_preview.h"
#include "pl_previewSh.h"

#include "main_render.h"
#include "main_renderSh.h"
#include "balance_render.h"
#include "eqmain_render.h"
#include "pledit_render.h"
#include "titlebar_render.h"
#include "cbuttons_render.h"
#include "posbar_render.h"
#include "volume_render.h"
#include "eq_ex_render.h"
#include "monoster_render.h"
#include "shufrep_render.h"
#include "balance_renderSh.h"
#include "eqmain_renderSh.h"
#include "pledit_renderSh.h"
#include "titlebar_renderSh.h"
#include "cbuttons_renderSh.h"
#include "posbar_renderSh.h"
#include "volume_renderSh.h"
#include "eq_ex_renderSh.h"
#include "monoster_renderSh.h"
#include "shufrep_renderSh.h"
/* -- */

//#include "init.xpm"
#include "text_template.xpm"
#include "numbers_template.xpm"
//#include "color_table.h"

#include <wx/log.h>
#include <wx/datstrm.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
//#include <wx/msgdlg.h>

/*#include <wx/txtstrm.h>
#include <wx/wfstream.h>

 wxFFileOutputStream output( stderr );
  wxTextOutputStream cout( output );*/




Skin::Skin()
{
        m_TemplatePath = "/home/oracle/wx_swe/rskin/templates2";
        m_TemplateName = "Default";
        m_TextBgColour = *wxBLACK;
        m_TextFgColour = *wxWHITE;
        m_VisPeakColour = *wxRED;
        m_VisTopColour = *wxBLACK;
        m_VisMiddleColour = ColourGradient( *wxBLACK, *wxWHITE , 3, 2 );;
        m_VisBottomColour = *wxWHITE;
        m_VisBgColour = *wxBLACK;
        m_VisBgGridColour = *wxLIGHT_GREY;
        m_OscMinColour = *wxWHITE;
        m_OscMaxColour = *wxBLACK;
        m_EqGraphTopColour = *wxBLACK;
        m_EqGraphMiddleColour = ColourGradient( *wxBLACK, *wxWHITE , 3, 2 );
        m_EqGraphBottomColour = *wxWHITE;
         m_EqSliderTopColour = *wxBLACK;
        m_EqSliderMiddleColour = ColourGradient( *wxBLACK, *wxRED , 3, 2 );
        m_EqSliderBottomColour= *wxRED;
        m_PlNormalColour = *wxLIGHT_GREY;
        m_PlActiveColour = *wxWHITE;
        m_PlBgColour = *wxBLACK;
        m_PlSelectedColour = *wxBLUE;

#ifdef __WXMSW__
        m_black_index = 0;
        m_lightblue_index = 255;
        m_darkblue_index = 132;//128
        m_white_index = 16777215;
        m_lightgray_index = 13026246;
        m_gray_index = 8684164;//8421504
        m_green_index = 33280;//32768
        m_pink_index = 16711935;
#else
        m_black_index = 0;
        m_lightblue_index = 248;
        m_darkblue_index = 128;
        m_white_index = 16317688;
        m_lightgray_index = 12632256;
        m_gray_index = 8421504;
        m_green_index = 32768;
        m_pink_index = 16253176;
#endif

/*        wxImage initImage("init.bmp",wxBITMAP_TYPE_BMP);

        unsigned char* initData = initImage.GetData();

        m_black_index = initData[0]*65536+initData[1]*256+initData[2];
        m_lightblue_index = initData[3]*65536+initData[4]*256+initData[5];
        m_darkblue_index = initData[6]*65536+initData[7]*256+initData[8];
        m_white_index = initData[9]*65536+initData[10]*256+initData[11];
        m_lightgray_index = initData[12]*65536+initData[13]*256+initData[14];
        m_gray_index = initData[15]*65536+initData[16]*256+initData[17];
        m_green_index = initData[18]*65536+initData[19]*256+initData[20];
        m_pink_index = initData[21]*65536+initData[22]*256+initData[23];
*/
/*        wxFFileOutputStream oust("color_table.h");
        wxTextOutputStream output1( oust );
//        output1 << "const int m_black_index = ";
        output1 << "const int m_black_index = " << m_black_index << ";" << endl;
        output1 << "const int m_lightblue_index = " << m_lightblue_index << ";" << endl;
        output1 << "const int m_darkblue_index = " << m_darkblue_index << ";" << endl;
        output1 << "const int m_white_index = " << m_white_index << ";" << endl;
        output1 << "const int m_lightgray_index = " << m_lightgray_index << ";" << endl;
        output1 << "const int m_gray_index = " << m_gray_index << ";" << endl;
        output1 << "const int m_green_index = " << m_green_index << ";" << endl;
        output1 << "const int m_pink_index = " << m_pink_index << ";" << endl;
*/

}

Skin::~Skin()
{
}

int Skin::SetTemplateName( const wxString& TemplateName )
{
        m_TemplateName = TemplateName;
        return 0;
}

int Skin::SetTemplatePath( const wxString& TemplatePath )
{
        m_TemplatePath = TemplatePath;
        wxString tmpString = m_TemplateName;
        m_TemplateName = "Default";
        wxImage initImage(ArrangeShapeElements( main_shArr ));

        unsigned char* initData = initImage.GetData();

        m_black_index = initData[19890]*65536+initData[19890+1]*256+initData[19890+2];
        m_lightblue_index = initData[2535]*65536+initData[2535+1]*256+initData[2535+2];
        m_darkblue_index = initData[16638]*65536+initData[16638+1]*256+initData[16638+2];
        m_white_index = initData[855]*65536+initData[855+1]*256+initData[855+2];
        m_lightgray_index = initData[0]*65536+initData[0+1]*256+initData[0+2];
        m_gray_index = initData[11700]*65536+initData[11700+1]*256+initData[11700+2];
        m_green_index = initData[20775]*65536+initData[20775+1]*256+initData[20775+2];

        initImage = wxImage(ArrangeShapeElements( shufrep_shArr ));
        initData = initImage.GetData();

        m_pink_index = initData[9681]*65536+initData[9681+1]*256+initData[9681+2];
        m_TemplateName = tmpString;
        return 0;
}

void Skin::SetMainBg( const wxBitmap& MainBg )
{
        m_MainBg = MainBg;
}

void Skin::SetEqBg( const wxBitmap& EqBg)
{
        m_EqBg = EqBg;
}

void Skin::SetPlBg( const wxBitmap& PlBg)
{
        m_PlBg = PlBg;
}

int Skin::SaveSkin( wxString& SkinDirectoryName )
{
        if (!wxDirExists(SkinDirectoryName))
        {
                wxMkdir(SkinDirectoryName, 0755);
        }

        CalcMainBitmap().SaveFile(SkinDirectoryName + "/main.bmp" , wxBITMAP_TYPE_BMP );
        CalcCbuttonsBitmap().SaveFile(SkinDirectoryName + "/cbuttons.bmp" , wxBITMAP_TYPE_BMP );
        CalcBalanceBitmap().SaveFile(SkinDirectoryName + "/balance.bmp" , wxBITMAP_TYPE_BMP );
        CalcMonosterBitmap().SaveFile(SkinDirectoryName + "/monoster.bmp" , wxBITMAP_TYPE_BMP );
        CalcPosbarBitmap().SaveFile(SkinDirectoryName + "/posbar.bmp" , wxBITMAP_TYPE_BMP );
        CalcShufrepBitmap().SaveFile(SkinDirectoryName + "/shufrep.bmp" , wxBITMAP_TYPE_BMP );
        CalcTitlebarBitmap().SaveFile(SkinDirectoryName + "/titlebar.bmp" , wxBITMAP_TYPE_BMP );
        CalcVolumeBitmap().SaveFile(SkinDirectoryName + "/volume.bmp" , wxBITMAP_TYPE_BMP );
        CalcEqmainBitmap().SaveFile(SkinDirectoryName + "/eqmain.bmp" , wxBITMAP_TYPE_BMP );
        CalcEq_exBitmap().SaveFile(SkinDirectoryName + "/eq_ex.bmp" , wxBITMAP_TYPE_BMP );
        CalcPleditBitmap().SaveFile(SkinDirectoryName + "/pledit.bmp" , wxBITMAP_TYPE_BMP );
        CalcTextBitmap().SaveFile(SkinDirectoryName + "/text.bmp" , wxBITMAP_TYPE_BMP );
        CalcNums_exBitmap().SaveFile(SkinDirectoryName + "/numbers.bmp" , wxBITMAP_TYPE_BMP );
        SavePleditTxt( SkinDirectoryName + "/pledit.txt" );
        SaveViscolorTxt( SkinDirectoryName + "/viscolor.txt" );

        return 0;
}

wxBitmap Skin::GetMainPreview( wxProgressDialog* Progress )
{
        Progress->Update( 1 );
        wxBitmap MainPreviewBitmap = ArrangeBitmapElements( m_MainBg , main_preview_arr );
        Progress->Update( 2 );

        wxBitmap MainPreviewShape =        ArrangeShapeElements( main_preview_shArr);
        Progress->Update( 3 );
        wxBitmap MainPreview = ApplyShape( MainPreviewBitmap , MainPreviewShape, 275, 116 );

        wxMemoryDC MainPreview_dc;
        MainPreview_dc.SelectObject( MainPreview );
        DrawVisPreview( MainPreview_dc );
        DrawTextPreview( MainPreview_dc );
        return MainPreview;

}

wxBitmap Skin::GetEqPreview( wxProgressDialog* Progress )
{
        Progress->Update( 4 );

        wxBitmap EqPreviewBitmap = ArrangeBitmapElements( m_EqBg , eq_preview_arr );
        Progress->Update( 5 );

        wxBitmap EqPreviewShape =        ArrangeShapeElements( eq_preview_shArr);
        Progress->Update( 6 );

        wxBitmap EqPreview = ApplyShape( EqPreviewBitmap , EqPreviewShape, 275, 116 );
        Progress->Update( 7 );

        wxMemoryDC EqPreview_dc;
        EqPreview_dc.SelectObject( EqPreview );
        DrawEqPreviewGradients( EqPreview_dc , 0);
        return EqPreview;

}

wxBitmap Skin::GetPlPreview( wxProgressDialog* Progress )
{

        wxBitmap PlPreviewBitmap = ArrangeBitmapElements( m_PlBg , pl_preview_arr );
        Progress->Update( 8 );

        wxBitmap PlPreviewShape =        ArrangeShapeElements( pl_preview_shArr);
        Progress->Update( 9 );

        wxBitmap PlPreview = ApplyShape( PlPreviewBitmap , PlPreviewShape, 275, 116 );
        Progress->Update( 10 );

        wxMemoryDC PlPreview_dc;
        PlPreview_dc.SelectObject( PlPreview );
        PlPreview_dc.SetBrush(wxBrush(m_PlBgColour, wxSOLID));
        PlPreview_dc.SetPen( wxPen(  m_PlBgColour, 1,wxSOLID ) );
        PlPreview_dc.DrawRectangle( 12, 20, 243, 58 );
        DrawPlTextPreview( PlPreview_dc, 0 );
        return PlPreview;

}

void Skin::DrawPlTextPreview( wxDC& canvas, int offset )
{
        canvas.SetBrush(wxBrush(m_PlBgColour, wxSOLID));
        canvas.SetPen( wxPen(  m_PlBgColour, 1,wxSOLID ) );
        canvas.DrawRectangle( 12, offset+20, 243, 58 );
        canvas.SetFont(*wxSMALL_FONT);
        canvas.SetTextBackground(m_PlBgColour);
        canvas.SetTextForeground(m_PlActiveColour);
        canvas.SetClippingRegion( 12, offset+20, 243, 58 );
        wxCoord w, h,wi,hi;
        canvas.DrawText("1. Erster Song", 14, offset+22);
        canvas.GetTextExtent("1. Erster Song", &w, &h );
        canvas.SetTextForeground(m_PlNormalColour);
        canvas.DrawText("2. Zweiter Song",14,offset+22+h);
        canvas.GetTextExtent("2. Zweiter Song", &w, &h );
        canvas.SetTextBackground(m_PlSelectedColour);
        canvas.GetTextExtent("3. Dritter Song", &wi, &hi );
        canvas.SetBrush(wxBrush(m_PlSelectedColour, wxSOLID));
        canvas.SetPen( wxPen( m_PlSelectedColour , 1,wxSOLID ) );
        canvas.DrawRectangle(0,offset+22+2*h,275,hi );
        canvas.DrawText("3. Dritter Song",14,offset+22+2*h);
}

wxBitmap Skin::CalcMainBitmap()
{
        wxBitmap Bitmap = ArrangeBitmapElements( m_MainBg , main_arr );
        wxBitmap Shape =        ArrangeShapeElements( main_shArr );
        return ApplyShape( Bitmap ,Shape , Shape.GetWidth(), Shape.GetHeight() );
}

wxBitmap Skin::CalcCbuttonsBitmap()
{
        wxBitmap Bitmap = ArrangeBitmapElements( m_MainBg , cbuttons_arr );
        wxBitmap Shape =        ArrangeShapeElements( cbuttons_shArr );
        return ApplyShape( Bitmap ,Shape , Shape.GetWidth(), Shape.GetHeight() );
}

wxBitmap Skin::CalcBalanceBitmap()
{
        wxBitmap Bitmap = ArrangeBitmapElements( m_MainBg , balance_arr );
        wxBitmap Shape =        ArrangeShapeElements( balance_shArr );
        return ApplyShape( Bitmap ,Shape , Shape.GetWidth(), Shape.GetHeight() );
}

wxBitmap Skin::CalcMonosterBitmap()
{
        wxBitmap Bitmap = ArrangeBitmapElements( m_MainBg , monoster_arr );
        wxBitmap Shape =        ArrangeShapeElements( monoster_shArr );
        return ApplyShape( Bitmap ,Shape , Shape.GetWidth(), Shape.GetHeight() );
}

wxBitmap Skin::CalcPosbarBitmap()
{
        wxBitmap Bitmap = ArrangeBitmapElements( m_MainBg , posbar_arr );
        wxBitmap Shape =        ArrangeShapeElements( posbar_shArr );
        return ApplyShape( Bitmap ,Shape , Shape.GetWidth(), Shape.GetHeight() );
}

wxBitmap Skin::CalcShufrepBitmap()
{
        wxBitmap Bitmap = ArrangeBitmapElements( m_MainBg , shufrep_arr );
        wxBitmap Shape =        ArrangeShapeElements( shufrep_shArr );
        return ApplyShape( Bitmap ,Shape , Shape.GetWidth(), Shape.GetHeight() );
}

wxBitmap Skin::CalcTitlebarBitmap()
{
        wxBitmap Bitmap = ArrangeBitmapElements( m_MainBg , titlebar_arr );
        wxBitmap Shape =        ArrangeShapeElements( titlebar_shArr );
        return ApplyShape( Bitmap ,Shape , Shape.GetWidth(), Shape.GetHeight() );
}

wxBitmap Skin::CalcVolumeBitmap()
{
        wxBitmap Bitmap = ArrangeBitmapElements( m_MainBg , volume_arr );
        wxBitmap Shape =        ArrangeShapeElements( volume_shArr );
        return ApplyShape( Bitmap ,Shape , Shape.GetWidth(), Shape.GetHeight() );
}

wxBitmap Skin::CalcEqmainBitmap()// Attention ColorGradients
{
        wxBitmap Bitmap = ArrangeBitmapElements( m_EqBg , eqmain_arr );
        wxBitmap Shape =        ArrangeShapeElements( eqmain_shArr );
        wxMemoryDC EqmainBitmap_dc;
        EqmainBitmap_dc.SelectObject( Bitmap );
        DrawEqmainGradients(EqmainBitmap_dc);
        return ApplyShape( Bitmap ,Shape , Shape.GetWidth(), Shape.GetHeight() );
}

wxBitmap Skin::CalcEq_exBitmap()
{
        wxBitmap Bitmap = ArrangeBitmapElements( m_EqBg , eq_ex_arr );
        wxBitmap Shape =        ArrangeShapeElements( eq_ex_shArr );
        return ApplyShape( Bitmap ,Shape , Shape.GetWidth(), Shape.GetHeight() );
}

wxBitmap Skin::CalcPleditBitmap()
{
        wxBitmap Bitmap = ArrangeBitmapElements( m_PlBg , pledit_arr );
        wxBitmap Shape =        ArrangeShapeElements( pledit_shArr );
        return ApplyShape( Bitmap ,Shape , Shape.GetWidth(), Shape.GetHeight() );
}

wxBitmap Skin::CalcPlaypausBitmap()
{
        wxBitmap Preview( 200,50 );
        return Preview;
}

wxBitmap Skin::CalcTextBitmap()
{
        wxBitmap TextTemplate(155,18);
        int i, j;
        wxMemoryDC TextTemplate_dc;
        TextTemplate_dc.SelectObject(TextTemplate);
        TextTemplate_dc.SetPen( wxPen( m_TextBgColour , 1,wxSOLID ) );
        TextTemplate_dc.SetBrush( wxBrush( m_TextBgColour , wxSOLID ) );
        TextTemplate_dc.DrawRectangle( 0, 0, 155,18 );
        TextTemplate_dc.SetPen( wxPen( m_TextFgColour , 1,wxSOLID ) );

        for ( i = 0; i < 18; i++ )
                for ( j = 0; j < 155; j++ )
                {
                        if (text_template[i+3][j]=='.')
                        TextTemplate_dc.DrawPoint(j,i);
                }

        return TextTemplate;
}

wxBitmap Skin::CalcNums_exBitmap()
{
        wxBitmap NumberTemplate(99,13);
        int i, j;
        wxMemoryDC NumberTemplate_dc;
        NumberTemplate_dc.SelectObject(NumberTemplate);
        NumberTemplate_dc.SetPen( wxPen( m_TextBgColour , 1,wxSOLID ) );
        NumberTemplate_dc.SetBrush( wxBrush( m_TextBgColour , wxSOLID ) );
        NumberTemplate_dc.DrawRectangle( 0, 0, 99,13 );
        NumberTemplate_dc.SetPen( wxPen( m_TextFgColour , 1,wxSOLID ) );

        for ( i = 0; i < 13; i++ )
                for ( j = 0; j < 99; j++ )
                {
                        if (numbers_template[i+3][j]=='.')
                        NumberTemplate_dc.DrawPoint(j,i);
                }

        return NumberTemplate;
}


wxBitmap Skin::ApplyShape( wxBitmap& srcBitmap , wxBitmap& shapeBitmap, int width, int height )
{
        wxImage srcImage( srcBitmap );
        wxImage shapeImage( shapeBitmap );
        int i;
        unsigned char* srcData = srcImage.GetData();
        unsigned char* shapeData = shapeImage.GetData();
        unsigned char* resultData_char = new unsigned char[width*height*3];
        int* resultData = new int[width*height*3];
        for ( i = 0; i < (width*height*3); i++ )
        {
                resultData[i]=0;
        }

        for ( i = 0; i < (width*height); i++ )
        {
                int compare = shapeData[i*3]*65536+shapeData[i*3+1]*256+shapeData[i*3+2];
                if (compare == m_black_index)/*Schwarz*/
                {
                        resultData[i*3]=srcData[i*3]-64;
                        resultData[i*3+1]=srcData[i*3+1]-64;
                        resultData[i*3+2]=srcData[i*3+2]-64;
                }
    else if (compare == m_lightblue_index)/*Blau*/ /*windows:255 gtk:248*/
                {
                        resultData[i*3]=srcData[i*3];
                        resultData[i*3+1]=srcData[i*3+1];
                        resultData[i*3+2]=srcData[i*3+2];
                }
                else if (compare == m_darkblue_index)/*Blau*/
                {
                        resultData[i*3]=srcData[i*3];
                        resultData[i*3+1]=srcData[i*3+1];
                        resultData[i*3+2]=srcData[i*3+2];
                }
    else if (compare == m_white_index)/*Weiß*/ /*windows:16777215 gtk:16317688*/
                {
                        resultData[i*3]=srcData[i*3]+64;
                        resultData[i*3+1]=srcData[i*3+1]+64;
                        resultData[i*3+2]=srcData[i*3+2]+64;
                }
    else if (compare == m_lightgray_index)/*Hellgrau*/
                {
                        resultData[i*3]=srcData[i*3]+38;
                        resultData[i*3+1]=srcData[i*3+1]+38;
                        resultData[i*3+2]=srcData[i*3+2]+38;
                }
    else if (compare == m_gray_index)/*Dunkelgrau*/
                {
                        resultData[i*3]=srcData[i*3]-38;
                        resultData[i*3+1]=srcData[i*3+1]-38;
                        resultData[i*3+2]=srcData[i*3+2]-38;
                }
    else if (compare == m_green_index)/*Grün->HintergrundFarbe!*/
                {
                        resultData[i*3]=m_TextBgColour.Red();
                        resultData[i*3+1]=m_TextBgColour.Green();
                        resultData[i*3+2]=m_TextBgColour.Blue();
                }
                else if (compare == m_pink_index) /*16711935: Rosa->Vordergrundfarbe*/
                {
                        resultData[i*3]=m_TextFgColour.Red();
                        resultData[i*3+1]=m_TextFgColour.Green();
                        resultData[i*3+2]=m_TextFgColour.Blue();
                }
          else
                {
                        resultData[i*3]=shapeData[i*3];
                        resultData[i*3+1]=shapeData[i*3+1];
                        resultData[i*3+2]=shapeData[i*3+2];
    }
#if 0
                                switch (compare)
    {
      case m_black_index:/*Schwarz*/
                                        resultData[i*3]=srcData[i*3]-64;
                                        resultData[i*3+1]=srcData[i*3+1]-64;
                                        resultData[i*3+2]=srcData[i*3+2]-64;
        break;
      case m_lightblue_index:/*Blau*/ /*windows:255 gtk:248*/
                                        resultData[i*3]=srcData[i*3];
                                        resultData[i*3+1]=srcData[i*3+1];
                                        resultData[i*3+2]=srcData[i*3+2];
        break;
      case m_darkblue_index:/*Blau*/
                                        resultData[i*3]=srcData[i*3];
                                        resultData[i*3+1]=srcData[i*3+1];
                                        resultData[i*3+2]=srcData[i*3+2];
        break;
      case m_white_index:/*Weiß*/ /*windows:16777215 gtk:16317688*/
                                        resultData[i*3]=srcData[i*3]+64;
                                        resultData[i*3+1]=srcData[i*3+1]+64;
                                        resultData[i*3+2]=srcData[i*3+2]+64;
        break;
      case m_lightgray_index:/*Hellgrau*/
                                        resultData[i*3]=srcData[i*3]+38;
                                        resultData[i*3+1]=srcData[i*3+1]+38;
                                        resultData[i*3+2]=srcData[i*3+2]+38;
        break;
      case m_gray_index:/*Dunkelgrau*/
                                        resultData[i*3]=srcData[i*3]-38;
                                        resultData[i*3+1]=srcData[i*3+1]-38;
                                        resultData[i*3+2]=srcData[i*3+2]-38;
        break;
      case m_green_index:/*Grün->HintergrundFarbe!*/
                                resultData[i*3]=m_TextBgColour.Red();
                                resultData[i*3+1]=m_TextBgColour.Green();
                                resultData[i*3+2]=m_TextBgColour.Blue();
        break;
                        case m_pink_index: /*16711935: Rosa->Vordergrundfarbe*/
                                        resultData[i*3]=m_TextFgColour.Red();
                                        resultData[i*3+1]=m_TextFgColour.Green();
                                        resultData[i*3+2]=m_TextFgColour.Blue();
        break;
      default:
                                        resultData[i*3]=shapeData[i*3];
                                        resultData[i*3+1]=shapeData[i*3+1];
                                        resultData[i*3+2]=shapeData[i*3+2];
        break;
    }

#endif
#if 0

                switch (compare)
    {
      case 0:/*Schwarz*/
                                        resultData[i*3]=srcData[i*3]-64;
                                        resultData[i*3+1]=srcData[i*3+1]-64;
                                        resultData[i*3+2]=srcData[i*3+2]-64;
        break;
      case 248:/*Blau*/ /*windows:255 gtk:248*/
                                        resultData[i*3]=srcData[i*3];
                                        resultData[i*3+1]=srcData[i*3+1];
                                        resultData[i*3+2]=srcData[i*3+2];
        break;
      case 128:/*Blau*/
                                        resultData[i*3]=srcData[i*3];
                                        resultData[i*3+1]=srcData[i*3+1];
                                        resultData[i*3+2]=srcData[i*3+2];
        break;
      case 16317688:/*Weiß*/ /*windows:16777215 gtk:16317688*/
                                        resultData[i*3]=srcData[i*3]+64;
                                        resultData[i*3+1]=srcData[i*3+1]+64;
                                        resultData[i*3+2]=srcData[i*3+2]+64;
        break;
      case 12632256:/*Hellgrau*/
                                        resultData[i*3]=srcData[i*3]+38;
                                        resultData[i*3+1]=srcData[i*3+1]+38;
                                        resultData[i*3+2]=srcData[i*3+2]+38;
        break;
      case 8421504:/*Dunkelgrau*/
                                        resultData[i*3]=srcData[i*3]-38;
                                        resultData[i*3+1]=srcData[i*3+1]-38;
                                        resultData[i*3+2]=srcData[i*3+2]-38;
        break;
      case 32768:/*Grün->HintergrundFarbe!*/
                                resultData[i*3]=m_TextBgColour.Red();
                                resultData[i*3+1]=m_TextBgColour.Green();
                                resultData[i*3+2]=m_TextBgColour.Blue();
        break;
                        case 16253176: /*16711935: Rosa->Vordergrundfarbe*/
                                        resultData[i*3]=m_TextFgColour.Red();
                                        resultData[i*3+1]=m_TextFgColour.Green();
                                        resultData[i*3+2]=m_TextFgColour.Blue();
        break;
      default:
                                        resultData[i*3]=shapeData[i*3];
                                        resultData[i*3+1]=shapeData[i*3+1];
                                        resultData[i*3+2]=shapeData[i*3+2];
        break;
    }
#endif
        }

        for ( i = 0; i < (width*height*3); i++ )
        {
                if ( resultData[i] > 255 )
                        resultData[i] = 255;
                else if ( resultData[i] < 0 )
                        resultData[i] = 0;
                resultData_char[i]=resultData[i];
        }
        delete [] resultData;

        wxImage resultImage(width, height, resultData_char);

        return resultImage.ConvertToBitmap();
}

/* Erzeugt eine Bitmap, die die Elemente aus srcBitmap
 * enthält, angeordnet gemäß den Angaben in 'list'.
 * 'char** list' ist folgendermassen aufgebaut:
 *     "breite_resultierendes_Bitmap höhe_resultierendes_Bitmap"
 *     "Anzahl_der_Umordnungen"
 *     "breite höhe x_source y_source x_destination y_destination"
 */
wxBitmap Skin::ArrangeBitmapElements( wxBitmap& srcBitmap , char** list )
{
        wxStringTokenizer tkz(list[0]);
        long int width, height, count, i;
        long int xdest, ydest, cwidth, cheight, xsrc, ysrc;
         tkz.GetNextToken().ToLong( &width );
         tkz.GetNextToken().ToLong( &height );
        tkz.SetString(list[1]);
         tkz.GetNextToken().ToLong( &count );

        wxBitmap destBitmap( (int)width, (int)height );

// prepare device contexts
        wxMemoryDC srcBitmap_dc;
        wxMemoryDC destBitmap_dc;
  srcBitmap_dc.SelectObject(srcBitmap);
  destBitmap_dc.SelectObject(destBitmap);

        destBitmap_dc.SetBrush(wxBrush( *wxBLUE, wxSOLID));
        destBitmap_dc.SetPen( wxPen( *wxBLUE , 1,wxSOLID ) );
        destBitmap_dc.DrawRectangle( 0, 0, width, height );
        for ( i = 2; i < (count+2); i++ )
        {
                tkz.SetString(list[i]);
                 tkz.GetNextToken().ToLong( &cwidth );
                 tkz.GetNextToken().ToLong( &cheight );
                 tkz.GetNextToken().ToLong( &xsrc );
                 tkz.GetNextToken().ToLong( &ysrc );
                 tkz.GetNextToken().ToLong( &xdest );
                 tkz.GetNextToken().ToLong( &ydest );


                destBitmap_dc.Blit( xdest, ydest, cwidth, cheight, &srcBitmap_dc, xsrc, ysrc );
        }

        return destBitmap;
}


/* Erzeugt eine Bitmap, die Elemente aus einer Vorlagendatei
 * enthält, angeordnet gemäß den Angaben in 'list'.
 * 'char** list' ist folgendermassen aufgebaut:
 *     "breite_resultierendes_Bitmap höhe_resultierendes_Bitmap"
 *     "Anzahl_der_Umordnungen"
 *     "Name_der_Vorlagen_datei breite höhe x_source y_source x_destination y_destination"
 * Wird nur für die Erzeugung der Vorschau genutzt, templates
 * der Version2 brauchen für den Export nicht modifiziert werden.
 */
wxBitmap Skin::ArrangeShapeElements(char** list )
{
        wxStringTokenizer tkz(list[0]);
        wxString TemplateFileName;
        wxString tmpString;
        long int width, height, count, i;
        long int xdest, ydest, cwidth, cheight, xsrc, ysrc;
         tkz.GetNextToken().ToLong( &width );
         tkz.GetNextToken().ToLong( &height );
        tkz.SetString(list[1]);
         tkz.GetNextToken().ToLong( &count );

        wxBitmap srcBitmap;
        wxBitmap destBitmap( (int)width, (int)height );
        wxString dde;

        // prepare device contexts

        wxMemoryDC srcBitmap_dc;
        wxMemoryDC destBitmap_dc;
//        wxMemoryDC hardCopyBitmap_dc;
  srcBitmap_dc.SelectObject(srcBitmap);
  destBitmap_dc.SelectObject(destBitmap);
//  hardCopyBitmap_dc.SelectObject(hardCopyBitmap);

        destBitmap_dc.SetBrush(wxBrush( *wxBLUE, wxSOLID));
        destBitmap_dc.SetPen( wxPen( *wxBLUE , 1,wxSOLID ) );
        destBitmap_dc.DrawRectangle( 0, 0, width, height );

        for ( i = 2; i < (count+2); i++ )
        {
                tkz.SetString(list[i]);
                tmpString = tkz.GetNextToken();
                if (tmpString != TemplateFileName)
                {
                        TemplateFileName = tmpString;
                        if ( !srcBitmap.LoadFile( m_TemplatePath + "/" + m_TemplateName + "/" + TemplateFileName + ".bmp", wxBITMAP_TYPE_BMP) )
                        {
                                wxLogError(" Vorlage-Datei \"" + TemplateFileName + "\" konnte nicht geöffnet werden.");
                        }
                        srcBitmap_dc.SelectObject(srcBitmap);
                }
                 tkz.GetNextToken().ToLong( &cwidth );
                 tkz.GetNextToken().ToLong( &cheight );
                 tkz.GetNextToken().ToLong( &xsrc );
                 tkz.GetNextToken().ToLong( &ysrc );
                 tkz.GetNextToken().ToLong( &xdest );
                 tkz.GetNextToken().ToLong( &ydest );

                        destBitmap_dc.Blit( xdest, ydest, cwidth, cheight, &srcBitmap_dc, xsrc, ysrc );
        }
        return destBitmap;
}

wxColour Skin::ColourGradient(const wxColour& firstColour, const wxColour& secondColour, int steps, int index )
{
// wxColor result;
 unsigned char red;
 unsigned char green;
 unsigned char blue;
 red = ((secondColour.Red()-firstColour.Red())/steps)*index+firstColour.Red();
 green = ((secondColour.Green()-firstColour.Green())/steps)*index+firstColour.Green();
 blue = ((secondColour.Blue()-firstColour.Blue())/steps)*index+firstColour.Blue();
        return wxColour( red, green, blue );
}

void Skin::DrawEqPreviewGradients( wxDC& canvas, int offset )
{
        int i;
        canvas.SetPen( wxPen(  m_EqSliderMiddleColour, 1,wxSOLID ) );
        canvas.SetBrush( wxBrush( m_EqSliderMiddleColour, wxSOLID ) );
        wxBitmap tmpBitmap(11,11);
        wxMemoryDC tmpBitmap_dc;
        tmpBitmap_dc.SelectObject(tmpBitmap);
        tmpBitmap_dc.Blit(0,0,11,11,&canvas,22,offset+63);

        canvas.DrawRectangle( 21, offset+38, 14, 63 );
        for ( i = 1; i < 6; i++ )
        {
                canvas.SetPen( wxPen( ColourGradient(m_EqSliderTopColour,m_EqSliderMiddleColour,5,i) , 1,wxSOLID ) );
                canvas.SetBrush( wxBrush( ColourGradient(m_EqSliderTopColour,m_EqSliderMiddleColour,5,i), wxSOLID ) );
                canvas.DrawRectangle( 59+i*18, offset+38, 15, 63 );
        }
        for ( i = 1; i < 6; i++ )
        {
                canvas.SetPen( wxPen( ColourGradient(m_EqSliderMiddleColour,m_EqSliderBottomColour,5,i) , 1,wxSOLID ) );
                canvas.SetBrush( wxBrush( ColourGradient(m_EqSliderMiddleColour,m_EqSliderBottomColour,5,i), wxSOLID ) );
                canvas.DrawRectangle( 150+i*18, offset+38, 15, 63 );
        }

        for ( i = 0; i < 8; i++ )
        {
                canvas.SetPen( wxPen( ColourGradient(m_EqGraphTopColour,m_EqGraphMiddleColour,8,i) , 1,wxSOLID ) );
                canvas.DrawLine(88+(i*55)/8, offset+19+i,95+(i*55)/8, offset+19+i );
        }

        for ( i = 0; i < 8; i++ )
        {
                canvas.SetPen( wxPen( ColourGradient(m_EqGraphMiddleColour,m_EqGraphBottomColour,8,i) , 1,wxSOLID ) );
                canvas.DrawLine(143+(i*55)/8 ,offset+27+i ,150+(i*55)/8,offset+27+i );

        }
        canvas.Blit(22,offset+63,11,11,&tmpBitmap_dc,0,0);
        for ( i = 0; i < 10; i++ )
        {
                canvas.Blit(79+i*18,offset+38+(i*50)/9 ,11,11,&tmpBitmap_dc,0,0);
        }
}

void Skin::DrawEqmainGradients( wxDC& canvas )
{
        int i;
        canvas.SetPen( wxPen( m_EqSliderBottomColour , 1,wxSOLID ) );
        canvas.SetBrush( wxBrush( m_EqSliderBottomColour, wxSOLID ) );
        canvas.DrawRectangle( 13, 164, 14, 63 );
        for ( i = 1; i < 14; i++ )
        {
                canvas.SetPen( wxPen( ColourGradient(m_EqSliderBottomColour,m_EqSliderMiddleColour,13,i) , 1,wxSOLID ) );
                canvas.SetBrush( wxBrush( ColourGradient(m_EqSliderBottomColour,m_EqSliderMiddleColour,13,i), wxSOLID ) );
                canvas.DrawRectangle( 13+i*15, 164, 14, 63 );
        }
for ( i = 1; i < 15; i++ )
        {
                canvas.SetPen( wxPen( ColourGradient(m_EqSliderMiddleColour,m_EqSliderTopColour,14,i) , 1,wxSOLID ) );
                canvas.SetBrush( wxBrush( ColourGradient(m_EqSliderMiddleColour,m_EqSliderTopColour,14,i), wxSOLID ) );
                canvas.DrawRectangle( 13+(i-1)*15, 229, 14, 63 );
        }

for ( i = 0; i < 9; i++ )
{
        canvas.SetPen( wxPen( ColourGradient(m_EqGraphTopColour,m_EqGraphMiddleColour,9,i) , 1,wxSOLID ) );
        canvas.DrawPoint(115, i+294);
}
for ( i = 0; i < 10; i++ )
{
        canvas.SetPen( wxPen( ColourGradient(m_EqGraphMiddleColour,m_EqGraphBottomColour,9,i) , 1,wxSOLID ) );
        canvas.DrawPoint(115, i+303);
}

}

void Skin::SetTextBgColour( const wxColour& TextBgColour )
{
        m_TextBgColour = TextBgColour;
}

void Skin::SetTextFgColour( const wxColour& TextFgColour )
{
        m_TextFgColour = TextFgColour;
}

void Skin::SetVisPeakColour( const wxColour& VisPeakColour )
{
        m_VisPeakColour = VisPeakColour;
}

void Skin::SetVisTopColour( const wxColour& VisTopColour )
{
        m_VisTopColour = VisTopColour;
}

void Skin::SetVisMiddleColour( const wxColour& VisMiddleColour )
{
        m_VisMiddleColour = VisMiddleColour;
}

void Skin::SetVisBottomColour( const wxColour& VisBottomColour )
{
        m_VisBottomColour = VisBottomColour;
}

void Skin::SetOscMinColour( const wxColour& OscMinColour )
{
        m_OscMinColour = OscMinColour;
}

void Skin::SetOscMaxColour( const wxColour& OscMaxColour )
{
        m_OscMaxColour = OscMaxColour;
}

void Skin::SetEqGraphTopColour( const wxColour& EqGraphTopColour )
{
        m_EqGraphTopColour = EqGraphTopColour;
}

void Skin::SetEqGraphMiddleColour( const wxColour& EqGraphMiddleColour )
{
        m_EqGraphMiddleColour = EqGraphMiddleColour;
}

void Skin::SetEqGraphBottomColour( const wxColour& EqGraphBottomColour )
{
        m_EqGraphBottomColour = EqGraphBottomColour;
}

void Skin::SetEqSliderTopColour( const wxColour& EqSliderTopColour )
{
        m_EqSliderTopColour = EqSliderTopColour;
}

void Skin::SetEqSliderMiddleColour( const wxColour& EqSliderMiddleColour )
{
        m_EqSliderMiddleColour = EqSliderMiddleColour;
}

void Skin::SetEqSliderBottomColour( const wxColour& EqSliderBottomColour )
{
        m_EqSliderBottomColour = EqSliderBottomColour;
}

void Skin::SetPlNormalColour( const wxColour& PlNormalColour )
{
        m_PlNormalColour = PlNormalColour;
}

void Skin::SetPlActiveColour( const wxColour& PlActiveColour )
{
        m_PlActiveColour = PlActiveColour;
}

void Skin::SetPlBgColour( const wxColour& PlBgColour )
{
        m_PlBgColour = PlBgColour;
}

void Skin::SetPlSelectedColour( const wxColour& PlSelectedColour )
{
        m_PlSelectedColour = PlSelectedColour;
}

void  Skin::SetVisBgColour( const wxColour& VisBgColour )
{
        m_VisBgColour = VisBgColour;
}

void  Skin::SetVisBgGridColour( const wxColour& VisBgGridColour )
{
        m_VisBgGridColour = VisBgGridColour;
}

int Skin::SetSkinsDirectory( const wxString& SkinsDirectory )
{
        m_SkinsDirectory = SkinsDirectory;
        return 0;
}

void Skin::DrawVisPreview( wxDC& canvas )
{
/*                wxColour m_VisPeakColour;
                wxColour m_VisTopColour;
                wxColour m_VisMiddleColour;
                wxColour m_VisBottomColour;
                wxColour m_VisBgColour;
                wxColour m_VisBgGridColour;*/
        int i, j;
        bool DrawLines1[14] = { true, false, false, false, false, false, false, false, false, false, false, false, false, false };
        bool DrawLines2[14] = { true, false, false, false, false, false, false, false, false, false, false, false, false, false };
        bool DrawLines3[14] = { true, false, false, false, false, false, false, false, false, false, false, false, false, false };

        bool DrawLines4[14] = { true, true, false, false, false, true, false, false, false, false, false, false, false, false };

        bool DrawLines5[14] = { true, true, false, true, false, true, true, true, false, false, false, false, false, false };

        bool DrawLines6[14] = { true, true, false, true, true, true, true, true, true, false, false, false, false, false };

        bool DrawLines7[14] = { true, true, true, true, true, true, true, true, true, false, false, false, false };

        bool DrawLines8[14] = { true, true, true, true, true, true, true, true, true, true, false, false, false, false };

        bool DrawLines9[14] = { true, true, true, true, true, true, true, true, true, true, false, false, false, false };

        bool DrawLines10[14] = { true, true, true, true, true, true, true, true, true, true, false, false, false, false };

        bool DrawLines11[14] = { true, true, true, true, true, true, true, true, true, true, true, false, false, false };

        bool DrawLines12[14] = { true, true, true, true, true, true, true, true, true, true, true, true, true, true };
        int DrawPeaks[14] = {0,0,2,4,4,5,3,4,5,6,9,9,10,11};
        canvas.SetPen( wxPen( m_VisBgColour , 1,wxSOLID ) );
        canvas.SetBrush( wxBrush( m_VisBgColour , wxSOLID ) );
        canvas.DrawRectangle( 24, 43, 76,16 );
        canvas.SetPen( wxPen( m_VisBgGridColour , 1,wxSOLID ) );
        for ( j = 0; j < 8; j++ )
                for ( i = 0; i < 38; i++ )
                {
                        canvas.DrawPoint(24+i*2,44+j*2);
                }
        for ( i = 0; i < 14; i++ )
        {
                canvas.SetPen( wxPen( ColourGradient(m_VisTopColour,m_VisMiddleColour,6,0) , 1,wxSOLID ) );
                canvas.SetBrush( wxBrush( ColourGradient(m_VisTopColour,m_VisMiddleColour,6,0) , wxSOLID ) );
                        if (DrawLines1[i])
                                canvas.DrawRectangle( 24+i*4, 47, 3,1 );
        }
        for ( i = 0; i < 14; i++ )
        {
                canvas.SetPen( wxPen( ColourGradient(m_VisTopColour,m_VisMiddleColour,6,1) , 1,wxSOLID ) );
                canvas.SetBrush( wxBrush( ColourGradient(m_VisTopColour,m_VisMiddleColour,6,1) , wxSOLID ) );
                        if (DrawLines2[i])
                                canvas.DrawRectangle( 24+i*4, 48, 3,1 );
        }
        for ( i = 0; i < 14; i++ )
        {
                canvas.SetPen( wxPen( ColourGradient(m_VisTopColour,m_VisMiddleColour,6,2) , 1,wxSOLID ) );
                canvas.SetBrush( wxBrush( ColourGradient(m_VisTopColour,m_VisMiddleColour,6,2) , wxSOLID ) );
                        if (DrawLines3[i])
                                canvas.DrawRectangle( 24+i*4, 49, 3,1 );
        }
        for ( i = 0; i < 14; i++ )
        {
                canvas.SetPen( wxPen( ColourGradient(m_VisTopColour,m_VisMiddleColour,6,3) , 1,wxSOLID ) );
                canvas.SetBrush( wxBrush( ColourGradient(m_VisTopColour,m_VisMiddleColour,6,3) , wxSOLID ) );
                        if (DrawLines4[i])
                                canvas.DrawRectangle( 24+i*4, 50, 3,1 );
        }
        for ( i = 0; i < 14; i++ )
        {
                canvas.SetPen( wxPen( ColourGradient(m_VisTopColour,m_VisMiddleColour,6,4) , 1,wxSOLID ) );
                canvas.SetBrush( wxBrush( ColourGradient(m_VisTopColour,m_VisMiddleColour,6,4) , wxSOLID ) );
                        if (DrawLines5[i])
                                canvas.DrawRectangle( 24+i*4, 51, 3,1 );
        }
        for ( i = 0; i < 14; i++ )
        {
                canvas.SetPen( wxPen( ColourGradient(m_VisTopColour,m_VisMiddleColour,6,5) , 1,wxSOLID ) );
                canvas.SetBrush( wxBrush( ColourGradient(m_VisTopColour,m_VisMiddleColour,6,5) , wxSOLID ) );
                        if (DrawLines6[i])
                                canvas.DrawRectangle( 24+i*4, 52, 3,1 );
        }


                for ( i = 0; i < 14; i++ )
        {
                canvas.SetPen( wxPen( ColourGradient(m_VisMiddleColour,m_VisBottomColour,6,1) , 1,wxSOLID ) );
                canvas.SetBrush( wxBrush( ColourGradient(m_VisMiddleColour,m_VisBottomColour,6,1) , wxSOLID ) );
                        if (DrawLines7[i])
                                canvas.DrawRectangle( 24+i*4, 53, 3,1 );
        }
        for ( i = 0; i < 14; i++ )
        {
                canvas.SetPen( wxPen( ColourGradient(m_VisMiddleColour,m_VisBottomColour,6,2) , 1,wxSOLID ) );
                canvas.SetBrush( wxBrush( ColourGradient(m_VisMiddleColour,m_VisBottomColour,6,2) , wxSOLID ) );
                        if (DrawLines8[i])
                                canvas.DrawRectangle( 24+i*4, 54, 3,1 );
        }
        for ( i = 0; i < 14; i++ )
        {
                canvas.SetPen( wxPen( ColourGradient(m_VisMiddleColour,m_VisBottomColour,6,3) , 1,wxSOLID ) );
                canvas.SetBrush( wxBrush( ColourGradient(m_VisMiddleColour,m_VisBottomColour,6,3) , wxSOLID ) );
                        if (DrawLines9[i])
                                canvas.DrawRectangle( 24+i*4, 55, 3,1 );
        }
        for ( i = 0; i < 14; i++ )
        {
                canvas.SetPen( wxPen( ColourGradient(m_VisMiddleColour,m_VisBottomColour,6,4) , 1,wxSOLID ) );
                canvas.SetBrush( wxBrush( ColourGradient(m_VisMiddleColour,m_VisBottomColour,6,4) , wxSOLID ) );
                        if (DrawLines10[i])
                                canvas.DrawRectangle( 24+i*4, 56, 3,1 );
        }
        for ( i = 0; i < 14; i++ )
        {
                canvas.SetPen( wxPen( ColourGradient(m_VisMiddleColour,m_VisBottomColour,6,5) , 1,wxSOLID ) );
                canvas.SetBrush( wxBrush( ColourGradient(m_VisMiddleColour,m_VisBottomColour,6,5) , wxSOLID ) );
                        if (DrawLines11[i])
                                canvas.DrawRectangle( 24+i*4, 57, 3,1 );
        }
        for ( i = 0; i < 14; i++ )
        {
                canvas.SetPen( wxPen( ColourGradient(m_VisMiddleColour,m_VisBottomColour,6,6) , 1,wxSOLID ) );
                canvas.SetBrush( wxBrush( ColourGradient(m_VisMiddleColour,m_VisBottomColour,6,6) , wxSOLID ) );
                        if (DrawLines12[i])
                                canvas.DrawRectangle( 24+i*4, 58, 3,1 );
        }

        canvas.SetPen( wxPen( m_VisPeakColour , 1,wxSOLID ) );
        canvas.SetBrush( wxBrush( m_VisPeakColour , wxSOLID ) );
        for ( i = 0; i < 14; i++ )
        {
                canvas.DrawRectangle( 24+i*4, 46+DrawPeaks[i], 3,1 );
        }

}

void Skin::DrawTextPreview( wxDC& canvas )
{
        /*        wxColour m_TextBgColour;
                wxColour m_TextFgColour;*/
        wxBitmap TextTemplate(155,18);
        int i, j;
        wxMemoryDC TextTemplate_dc;
        TextTemplate_dc.SelectObject(TextTemplate);
        TextTemplate_dc.SetPen( wxPen( m_TextBgColour , 1,wxSOLID ) );
        TextTemplate_dc.SetBrush( wxBrush( m_TextBgColour , wxSOLID ) );
        TextTemplate_dc.DrawRectangle( 0, 0, 155,18 );
        TextTemplate_dc.SetPen( wxPen( m_TextFgColour , 1,wxSOLID ) );

        for ( i = 0; i < 18; i++ )
                for ( j = 0; j < 155; j++ )
                {
                        if (text_template[i+3][j]=='.')
                        TextTemplate_dc.DrawPoint(j,i);
                }
        canvas.Blit(111,43,9,6,&TextTemplate_dc,5,6);
        canvas.Blit(121,43,4,6,&TextTemplate_dc,40,6);
        canvas.Blit(161,43,4,6,&TextTemplate_dc,20,6);
        canvas.Blit(156,43,4,6,&TextTemplate_dc,20,6);

        canvas.Blit(113,27,4,6,&TextTemplate_dc,85,0);
        canvas.Blit(118,27,4,6,&TextTemplate_dc,40,0);
        canvas.Blit(123,27,4,6,&TextTemplate_dc,95,0);
        canvas.Blit(128,27,4,6,&TextTemplate_dc,90,0);
        canvas.Blit(133,27,4,6,&TextTemplate_dc,10,0);
        canvas.Blit(138,27,4,6,&TextTemplate_dc,35,0);
        canvas.Blit(143,27,4,6,&TextTemplate_dc,40,0);
        canvas.Blit(148,27,4,6,&TextTemplate_dc,90,0);
        canvas.Blit(153,27,4,6,&TextTemplate_dc,50,0);
        canvas.Blit(158,27,4,6,&TextTemplate_dc,40,0);
        canvas.Blit(163,27,4,6,&TextTemplate_dc,65,0);


        TextTemplate=CalcNums_exBitmap();
        TextTemplate_dc.SelectObject(TextTemplate);
        canvas.Blit(48,26,9,13,&TextTemplate_dc,0,0);
        canvas.Blit(60,26,9,13,&TextTemplate_dc,0,0);
        canvas.Blit(78,26,9,13,&TextTemplate_dc,0,0);
        canvas.Blit(90,26,9,13,&TextTemplate_dc,45,0);
}

void Skin::SavePleditTxt( const wxString& FileName )
{
        /*        wxColour m_PlNormalColour;
                wxColour m_PlActiveColour;
                wxColour m_PlBgColour;
                wxColour m_PlSelectedColour;*/
        wxString tmpString ="sdfghmdfgbnm,";

         wxFFileOutputStream output( FileName );
  wxTextOutputStream PleditTxt( output );


  PleditTxt << "[Text]" << endl;
  PleditTxt << "Normal=#";
        tmpString.Printf("%2x%2x%2x",m_PlNormalColour.Red(),m_PlNormalColour.Green(),m_PlNormalColour.Blue());
        if (m_PlNormalColour.Red()<=15)
                tmpString.SetChar(0, '0');
        if (m_PlNormalColour.Green()<=15)
                tmpString.SetChar(2, '0');
        if (m_PlNormalColour.Blue()<=15)
                tmpString.SetChar(4, '0');
  PleditTxt << tmpString << endl;

  PleditTxt << "Current=#";
        tmpString.Printf("%2x%2x%2x",m_PlActiveColour.Red(),m_PlActiveColour.Green(),m_PlActiveColour.Blue());
        if (m_PlActiveColour.Red()<=15)
                tmpString.SetChar(0, '0');
        if (m_PlActiveColour.Green()<=15)
                tmpString.SetChar(2, '0');
        if (m_PlActiveColour.Blue()<=15)
                tmpString.SetChar(4, '0');
  PleditTxt << tmpString << endl;

  PleditTxt << "NormalBG=#";
        tmpString.Printf("%2x%2x%2x",m_PlBgColour.Red(),m_PlBgColour.Green(),m_PlBgColour.Blue());
        if (m_PlBgColour.Red()<=15)
                tmpString.SetChar(0, '0');
        if (m_PlBgColour.Green()<=15)
                tmpString.SetChar(2, '0');
        if (m_PlBgColour.Blue()<=15)
                tmpString.SetChar(4, '0');
  PleditTxt << tmpString << endl;

  PleditTxt << "SelectedBG=#";
        tmpString.Printf("%2x%2x%2x",m_PlSelectedColour.Red(),m_PlSelectedColour.Green(),m_PlSelectedColour.Blue());
        if (m_PlSelectedColour.Red()<=15)
                tmpString.SetChar(0, '0');
        if (m_PlSelectedColour.Green()<=15)
                tmpString.SetChar(2, '0');
        if (m_PlSelectedColour.Blue()<=15)
                tmpString.SetChar(4, '0');
  PleditTxt << tmpString << endl;
}

void Skin::SaveViscolorTxt( const wxString& FileName )
{
        wxString tmpString;
        wxColor tmpColor;
        int i;
         wxFFileOutputStream output( FileName );
  wxTextOutputStream ViscolorTxt( output );

/*                wxColour m_VisPeakColour;
                wxColour m_VisTopColour;
                wxColour m_VisMiddleColour;
                wxColour m_VisBottomColour;
                wxColour m_VisBgColour;
                wxColour m_VisBgGridColour;
                wxColour m_OscMinColour;
                wxColour m_OscMaxColour; */



        tmpString.Printf("%i,%i,%i",m_VisBgColour.Red(),m_VisBgColour.Green(),m_VisBgColour.Blue());
  ViscolorTxt << tmpString << "\t\t //background" << endl;
        tmpString.Printf("%i,%i,%i",m_VisBgGridColour.Red(),m_VisBgGridColour.Green(),m_VisBgGridColour.Blue());
  ViscolorTxt << tmpString << endl;
        for ( i = 0; i < 8; i++ )
        {
                tmpColor = ColourGradient(m_VisTopColour,m_VisMiddleColour,8,i);
                tmpString.Printf("%i,%i,%i",tmpColor.Red(),tmpColor.Green(),tmpColor.Blue());
                ViscolorTxt << tmpString << endl;
        }
        for ( i = 0; i < 8; i++ )
        {
                tmpColor = ColourGradient(m_VisMiddleColour,m_VisBottomColour,7,i);
                tmpString.Printf("%i,%i,%i",tmpColor.Red(),tmpColor.Green(),tmpColor.Blue());
                ViscolorTxt << tmpString << endl;
        }
        for ( i = 0; i < 5; i++ )
        {
                tmpColor = ColourGradient(m_OscMinColour,m_OscMaxColour,4,i);
                tmpString.Printf("%i,%i,%i",tmpColor.Red(),tmpColor.Green(),tmpColor.Blue());
                ViscolorTxt << tmpString << endl;
        }

        tmpString.Printf("%i,%i,%i",m_VisPeakColour.Red(),m_VisPeakColour.Green(),m_VisPeakColour.Blue());
  ViscolorTxt << tmpString << endl;

}
