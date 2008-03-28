#include "wx/settings.h"
#include "drawingutils.h"
#include "wx/dc.h"

//-------------------------------------------------------------------------------------------------
// helper functions
//-------------------------------------------------------------------------------------------------

wxColor DrawingUtils::LightColour(const wxColour& color, int percent)
{
	int rd, gd, bd, high = 0;
	wxColor end_color = wxT("WHITE");
	rd = end_color.Red() - color.Red();
	gd = end_color.Green() - color.Green();
	bd = end_color.Blue() - color.Blue();
	high = 100;

	// We take the percent way of the color from color --> white
	int i = percent;
	int r = color.Red() +  ((i*rd*100)/high)/100;
	int g = color.Green() + ((i*gd*100)/high)/100;
	int b = color.Blue() + ((i*bd*100)/high)/100;
	return wxColor(r, g, b);
}

void DrawingUtils::TruncateText(wxDC& dc, const wxString& text, const int &maxWidth, wxString& fixedText)
{
	int textH, textW;
	int rectSize = maxWidth;
	int textLen = (int)text.Length();
	wxString tempText = text;

	fixedText = wxT("");
	dc.GetTextExtent(text, &textW, &textH);
	if (rectSize >= textW) {
		fixedText = text;
		return;
	}

	// The text does not fit in the designated area,
	// so we need to truncate it a bit
	wxString suffix = wxT("..");
	int w, h;
	dc.GetTextExtent(suffix, &w, &h);
	rectSize -= w;

	for (int i=textLen; i>=0; i--) {
		dc.GetTextExtent(tempText, &textW, &textH);
		if (rectSize > textW) {
			fixedText = tempText;
			fixedText += wxT("..");
			return;
		}
		tempText = tempText.RemoveLast();
	}
}

void DrawingUtils::PaintStraightGradientBox(wxDC& dc,
        const wxRect& rect,
        const wxColour& startColor,
        const wxColour& endColor,
        bool  vertical)
{
	int rd, gd, bd, high = 0;
	rd = endColor.Red() - startColor.Red();
	gd = endColor.Green() - startColor.Green();
	bd = endColor.Blue() - startColor.Blue();

	/// Save the current pen and brush
	wxPen savedPen = dc.GetPen();
	wxBrush savedBrush = dc.GetBrush();

	if ( vertical )
		high = rect.GetHeight()-1;
	else
		high = rect.GetWidth()-1;

	if ( high < 1 )
		return;

	for (int i = 0; i <= high; ++i) {
		int r = startColor.Red() +  ((i*rd*100)/high)/100;
		int g = startColor.Green() + ((i*gd*100)/high)/100;
		int b = startColor.Blue() + ((i*bd*100)/high)/100;

		wxPen p(wxColor(r, g, b));
		dc.SetPen(p);

		if ( vertical )
			dc.DrawLine(rect.x, rect.y+i, rect.x+rect.width, rect.y+i);
		else
			dc.DrawLine(rect.x+i, rect.y, rect.x+i, rect.y+rect.height);
	}

	/// Restore the pen and brush
	dc.SetPen( savedPen );
	dc.SetBrush( savedBrush );
}

void DrawingUtils::DrawButton(wxDC& dc,
                              const wxRect& rect,
                              const bool &focus,
                              const bool &upperTabs,
                              bool vertical   )
{
	wxColour lightGray = LightColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DSHADOW), 30);

	// Define the rounded rectangle base on the given rect
	// we need an array of 9 points for it
	wxColour topStartColor(wxT("WHITE"));
	wxColour topEndColor(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));
	wxColour bottomStartColor(topEndColor);
	wxColour bottomEndColor(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));

	// Define the middle points
	if ( focus ) {
		PaintStraightGradientBox(dc, rect, topStartColor, topEndColor, vertical);
	} else {

		// Incase we use bottom tabs, switch the colors
		topStartColor = wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE);
		topEndColor = lightGray;

		if (upperTabs) {
			PaintStraightGradientBox(dc, rect, topStartColor, topEndColor, vertical);
		} else {
			PaintStraightGradientBox(dc, rect, topEndColor, topStartColor, vertical);
		}
	}

	dc.SetBrush( *wxTRANSPARENT_BRUSH );
}
