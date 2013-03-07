// CitiesView.cpp : implementation of the CCitiesView class
//

#include "stdafx.h"
#include "PhoneBook.h"

#include "CitiesDoc.h"
#include "CitiesView.h"
#include "CitiesDlg.h"
#include ".\citiesview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCitiesView

IMPLEMENT_DYNCREATE(CCitiesView, CListView)

BEGIN_MESSAGE_MAP(CCitiesView, CListView)
  ON_COMMAND(ID_ROW_FIND, OnRowFind)
END_MESSAGE_MAP()


// CCitiesView construction/destruction

CCitiesView::CCitiesView()
{
	// TODO: add construction code here

}

CCitiesView::~CCitiesView()
{
}

BOOL CCitiesView::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
  if (message == WM_NOTIFY)
  {
    int iNumb = 0;
    switch(((LPNMHDR)lParam)->code)
    {
      case NM_DBLCLK:  
        OnRowDbClicked();
        break;
      case LVN_COLUMNCLICK:
        iNumb = ((LPNMLISTVIEW)lParam)->iSubItem;
        m_abAscSorting[iNumb] = !m_abAscSorting[iNumb];
        GetDocument()->SortByColumn((CCitiesDoc::eColumn)iNumb, m_abAscSorting[iNumb]);
        UpdateColumnsContent();
        break;
      case LVN_ITEMCHANGED:
        m_iCurrRowSelected = ((LPNMLISTVIEW)lParam)->iItem;
        break;
      default:
        break;
    }
  }

  return CListView::OnChildNotify(message, wParam, lParam, pResult);
}

BOOL CCitiesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

void CCitiesView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
  long lWndStyle = GetWindowLong(m_hWnd, GWL_STYLE);
  lWndStyle |= LVS_REPORT;
  SetWindowLong(m_hWnd, GWL_STYLE, lWndStyle);  
  CListCtrl& oListCtrl = GetListCtrl();
  oListCtrl.SetExtendedStyle( oListCtrl.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

  oListCtrl.InsertColumn(CCitiesDoc::eColCode, _T("���"), LVCFMT_LEFT);
  oListCtrl.InsertColumn(CCitiesDoc::eColName, _T("���"), LVCFMT_LEFT);
  oListCtrl.InsertColumn(CCitiesDoc::eColArea, _T("������"), LVCFMT_LEFT);
  oListCtrl.SetColumnWidth(CCitiesDoc::eColCode, LVSCW_AUTOSIZE_USEHEADER);
  oListCtrl.SetColumnWidth(CCitiesDoc::eColName, LVSCW_AUTOSIZE_USEHEADER);
  oListCtrl.SetColumnWidth(CCitiesDoc::eColArea, LVSCW_AUTOSIZE_USEHEADER);

  UpdateColumnsContent();
  m_iCurrRowSelected = 0;
  memset(m_abAscSorting, TRUE, sizeof(m_abAscSorting));
}

void CCitiesView::UpdateColumnsContent()
{
  m_CitiesArray.RemoveAndFreeAll();
  if(GetDocument()->SelectAll(m_CitiesArray) == TRUE)
  {
    CListCtrl& oListCtrl = GetListCtrl();   
    oListCtrl.DeleteAllItems();
    for(int i = m_CitiesArray.GetCount(); i != 0 ; )
    {
      i--;
      int iRowIdx = oListCtrl.InsertItem(CCitiesDoc::eColCode, m_CitiesArray[i]->m_szCode);
      oListCtrl.SetItemText(iRowIdx, CCitiesDoc::eColName, m_CitiesArray[i]->m_szName);
      oListCtrl.SetItemText(iRowIdx, CCitiesDoc::eColArea, m_CitiesArray[i]->m_szArea);
    }
    oListCtrl.SetColumnWidth(CCitiesDoc::eColCode, LVSCW_AUTOSIZE_USEHEADER);
    oListCtrl.SetColumnWidth(CCitiesDoc::eColName, LVSCW_AUTOSIZE);
    oListCtrl.SetColumnWidth(CCitiesDoc::eColArea, LVSCW_AUTOSIZE);
  }
}

void CCitiesView::OnRowDbClicked()
{
  CCitiesDlg oEditDlg(*m_CitiesArray[m_iCurrRowSelected]);
  if(oEditDlg.DoModal() == IDOK)
  {
    CCities oCity;
    switch(oEditDlg.GetCityCmd())
    {
    case CCitiesDlg::eCityUpdate:
      oCity = oEditDlg.GetCityData();
      if(GetDocument()->UpdateWhereId(oCity.m_iId, oCity) == FALSE)
        MessageBox(_T("������ ��� �����.\n����������� ������ ��� �� ���������"), 0, MB_OK|MB_ICONWARNING);
      else
        UpdateColumnsContent();
      break;
    case CCitiesDlg::eCityInsert:
      oCity = oEditDlg.GetCityData();
      if(GetDocument()->Insert(oCity) == FALSE)
        MessageBox(_T("������ ��� �����.\n����������� ������"), 0, MB_OK|MB_ICONWARNING);
      else
        UpdateColumnsContent();      
      break;
    case CCitiesDlg::eCityDelete:
      oCity = oEditDlg.GetCityData();
      GetDocument()->DeleteWhereId(oCity.m_iId);
      UpdateColumnsContent();
      break;
    case CCitiesDlg::eCityFind:
      oCity = oEditDlg.GetCityData();
      GetDocument()->SelectByContent(oCity);
      UpdateColumnsContent();
      break;
    }
  }
}


// CCitiesView diagnostics

#ifdef _DEBUG
void CCitiesView::AssertValid() const
{
	CListView::AssertValid();
}

void CCitiesView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CCitiesDoc* CCitiesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCitiesDoc)));
	return (CCitiesDoc*)m_pDocument;
}
#endif //_DEBUG


// CCitiesView message handlers

void CCitiesView::OnRowFind()
{
  // TODO: Add your command handler code here
}