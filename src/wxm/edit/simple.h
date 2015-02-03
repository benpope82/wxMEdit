///////////////////////////////////////////////////////////////////////////////
// vim:         ts=4 sw=4
// Name:        wxm/edit/simple.h
// Description: Simple wxMEdit Implementations
// Copyright:   2015  JiaYanwei   <wxmedit@gmail.com>
// License:     GPLv3
///////////////////////////////////////////////////////////////////////////////

#ifndef _WXMEDIT_SIMPLE_H_
#define _WXMEDIT_SIMPLE_H_

#include "../../wxmedit/wxmedit.h"

namespace wxm
{

struct DummyConfigWriter: public ConfigWriter
{
	virtual void Record(const wxString& key, long val) {}
	virtual void Record(const wxString& key, double val) {}
	virtual void Record(const wxString& key, const wxString& val) {}

	virtual void SetConfig(wxConfigBase* cfg) {}
};

struct SimpleWXMEdit: public MadEdit
{
	SimpleWXMEdit(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSIMPLE_BORDER | wxWANTS_CHARS)
		: MadEdit(new DummyConfigWriter(),  parent, id, pos, size, style)
	{
	}
private:
	virtual int CalcLineNumberAreaWidth(MadLineIterator lit, int lineid, int rowid, int toprow, int rowcount) { return 0; }
	virtual int GetLineNumberAreaWidth(int number) { return 0; }
	virtual void OnPaintInPrinting(wxPaintDC& dc, wxMemoryDC& memdc) {}
	virtual LineNumberList SaveBookmarkLineNumberList() { return LineNumberList(); }
	virtual void RestoreBookmarkByLineNumberList(const LineNumberList& linenums) {}
	virtual int CachedLineNumberAreaWidth() { return 0; }
	virtual void CacheLineNumberAreaWidth(int width) {}
	virtual void PaintLineNumberArea(const wxColor & bgcolor, wxDC * dc, const wxRect& rect, bool is_trailing_subrow, MadLineIterator lineiter, int lineid, int text_top) {}
};

struct InFrameWXMEdit;
struct HexPrintingWXMEdit : public SimpleWXMEdit
{
	friend struct InFrameWXMEdit;
	HexPrintingWXMEdit(wxWindow* parent, const wxFont* font);
private:
	virtual void SetWordWrapMode(MadWordWrapMode mode) {}
	virtual MadWordWrapMode GetWordWrapMode() { return wwmWrapByColumn; }
};

struct SimpleTextWXMEdit: public SimpleWXMEdit
{
	SimpleTextWXMEdit(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSIMPLE_BORDER | wxWANTS_CHARS)
		: SimpleWXMEdit(parent, id, pos, size, style)
	{
		InitTextFont();
		SetFixedWidthMode(false);
	}
private:
	virtual void SetWordWrapMode(MadWordWrapMode mode) {}
	virtual MadWordWrapMode GetWordWrapMode() { return wwmNoWrap; }
};

struct SearchingWXMEdit : public SimpleTextWXMEdit
{
	SearchingWXMEdit(wxWindow* parent, bool bSearchWholeWord)
		: SimpleTextWXMEdit(parent, wxID_ANY, wxPoint(-1024, -1024))
	{
		StopRepaint();
		SetSearchOptions(true, bSearchWholeWord);
	}
};

} //namespace wxm

#endif //_WXMEDIT_SIMPLE_H_