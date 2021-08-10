#ifndef MyList_HPP
#define MyList_HPP

#include <wx/icon.h>
#include <wx/combobox.h>
#include <wx/listctrl.h>
#include <wx/imaglist.h>

#include <images/file.xpm>
#include <images/folder.xpm>

#include <tuple>
#include <vector>
#include <filesystem>

enum class EType : uint8_t
{
  ENone,
  EFile,
  EFolder,
  ESymlinkFile,
  ESymlinkFolder
};

struct TListElement
{
  std::string e_name;
  std::string e_size;
  std::string e_ts;
  EType e_type;
};

using TListElementVector = std::vector<TListElement>;

class MyList : public wxListCtrl
{
  public:

  TListElementVector m_list;

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
    SetImageList(m_imageList, wxIMAGE_LIST_SMALL);
  }

  virtual ~MyList()
  {
    if (m_imageList) delete m_imageList;
  }

  void Initialize(const std::vector<std::string>& columns)
  {
    for (auto& col : columns)
    {
      AppendColumn(col);
    }
  }

  std::string GetItemTextFromEvent(wxListEvent& event, int col = 0)
  {
    wxListItem info;

    info.m_col = col;
    info.m_mask = wxLIST_MASK_TEXT;
    info.m_itemId = event.m_itemIndex;
    GetItem(info);

    return info.m_text.ToStdString();
  }

  TListElementVector GetSelectedItems(void)
  {
    long item = -1;
    TListElementVector selected;

    for (;;)
    {
      item = GetNextItem(
               item,
               wxLIST_NEXT_ALL,
               wxLIST_STATE_SELECTED);

      if (item == -1) break;

      selected.push_back(m_list[item]);
    }

    return selected;
  }

  virtual void ReInitialize(void)
  {
    SetItemCount(0);
    DeleteAllItems();
    m_list.clear();
    m_list.push_back({
      "..", "", "", EType::EFolder
    });
  }

  private:

  wxImageList *m_imageList;

  virtual wxString OnGetItemText(long item, long column) const wxOVERRIDE
  {
    std::string text;

    if (column == 0)
      text = m_list[item].e_name;
    else if (column == 1)
      text = m_list[item].e_size;
    else if (column == 2)
      text = m_list[item].e_ts;

    return text;
  }

  virtual int OnGetItemColumnImage(long item, long column) const wxOVERRIDE
  {
    int idx = -1;

    if (column == 0)
    {
      auto type = m_list[item].e_type;

      if (type == EType::EFile)
        idx = 0;
      else if (type == EType::EFolder)
        idx = 1;
    }

    return idx;
  }
};

#endif