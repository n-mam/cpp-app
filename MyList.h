#ifndef MyList_HPP
#define MyList_HPP

#include <wx/icon.h>
#include <wx/combobox.h>
#include <wx/listctrl.h>
#include <wx/imaglist.h>

#include <images/file.xpm>
#include <images/folder.xpm>
#include <images/host.xpm>

#include <tuple>
#include <vector>
#include <filesystem>

using TOnGetItemImageCbk = std::function<int (long, long)>;
using TOnGetItemTextCbk = std::function<wxString (long, long)>;

class MyList : public wxListCtrl
{
  public:

  MyList(
    wxWindow *parent,
    const wxWindowID id,
    const wxPoint& pos,
    const wxSize& size,
    long style)
  : wxListCtrl(parent, id, pos, size, style)
  {
    m_imageList = new wxImageList(24, 24, true, 1);
    m_imageList->Add(wxIcon(file_xpm));
    m_imageList->Add(wxIcon(folder_xpm));
    m_imageList->Add(wxIcon(host_xpm));
    SetImageList(m_imageList, wxIMAGE_LIST_SMALL);
  }

  virtual ~MyList()
  {
    if (m_imageList) delete m_imageList;
  }

  void Initialize(const std::vector<std::string>& columns, TOnGetItemTextCbk tCbk, TOnGetItemImageCbk iCbk)
  {
    for (auto& col : columns)
    {
      AppendColumn(col);
    }

    iOnGetItemTextCbk = tCbk;
    iOnGetItemImageCbk = iCbk;
  }

  std::string GetColumnTextFromEvent(wxListEvent& event, int col = 0)
  {
    wxListItem info;

    info.m_col = col;
    info.m_mask = wxLIST_MASK_TEXT;
    info.m_itemId = event.m_itemIndex;
    GetItem(info);

    return info.m_text.ToStdString();
  }

  std::vector<long> GetSelectedItemIndexes(void)
  {
    long idx = -1;
    std::vector<long> selected;

    for (;;)
    {
      idx = GetNextItem(
          idx,
          wxLIST_NEXT_ALL,
          wxLIST_STATE_SELECTED);

      if (idx == -1) break;

      selected.push_back(idx);
    }

    return selected;
  }

  virtual void ReInitialize(void)
  {
    SetItemCount(0);
    DeleteAllItems();
  }

  private:

  wxImageList *m_imageList;

  TOnGetItemTextCbk iOnGetItemTextCbk;

  TOnGetItemImageCbk iOnGetItemImageCbk;

  virtual wxString OnGetItemText(long item, long column) const wxOVERRIDE
  {
    return iOnGetItemTextCbk(item, column);
  }

  virtual int OnGetItemColumnImage(long item, long column) const wxOVERRIDE
  {
    return iOnGetItemImageCbk(item, column);
  }
};

#endif