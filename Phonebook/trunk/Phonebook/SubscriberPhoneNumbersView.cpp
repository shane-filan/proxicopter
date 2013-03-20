// SubscriberPhoneNumbersView.cpp : implementation of the CSubscriberPhoneNumbersView class
//

#include "stdafx.h"
#include "PhoneBook.h"

#include "SubscriberPhoneNumbersDoc.h"
#include "SubscriberPhoneNumbersView.h"
#include "SubscriberPhoneNumbersDlg.h"
#include ".\SubscriberPhoneNumbersview.h"
 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSubscriberPhoneNumbersView

IMPLEMENT_DYNCREATE(CSubscriberPhoneNumbersView, CListView)

BEGIN_MESSAGE_MAP(CSubscriberPhoneNumbersView, CListView)
END_MESSAGE_MAP()


// CSubscriberPhoneNumbersView construction/destruction

CSubscriberPhoneNumbersView::CSubscriberPhoneNumbersView()
{
  // TODO: add construction code here

}

CSubscriberPhoneNumbersView::~CSubscriberPhoneNumbersView()
{
}

BOOL CSubscriberPhoneNumbersView::PreCreateWindow(CREATESTRUCT& cs)
{
  // TODO: Modify the Window class or styles here by modifying
  //  the CREATESTRUCT cs

  return CListView::PreCreateWindow(cs);
}

void CSubscriberPhoneNumbersView::OnInitialUpdate()
{
  CListView::OnInitialUpdate();

  // TODO: You may populate your ListView with items by directly accessing
  //  its list control through a call to GetListCtrl().
  long lWndStyle = GetWindowLong(m_hWnd, GWL_STYLE);
  lWndStyle |= LVS_REPORT;
  SetWindowLong(m_hWnd, GWL_STYLE, lWndStyle);  
  CListCtrl& oListCtrl = GetListCtrl();
  oListCtrl.SetExtendedStyle( oListCtrl.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

  oListCtrl.InsertColumn(CSubscriberPhoneNumbersDoc::eColCode,       _T("��� �� ������"), LVCFMT_LEFT);
  oListCtrl.InsertColumn(CSubscriberPhoneNumbersDoc::eColFirstName,  _T("���"), LVCFMT_LEFT);
  oListCtrl.InsertColumn(CSubscriberPhoneNumbersDoc::eColSecondName, _T("�������"), LVCFMT_LEFT);
  oListCtrl.InsertColumn(CSubscriberPhoneNumbersDoc::eColThirdName,  _T("�������"), LVCFMT_LEFT);
  oListCtrl.InsertColumn(CSubscriberPhoneNumbersDoc::eColIDNumb,     _T("���"), LVCFMT_LEFT);
  oListCtrl.InsertColumn(CSubscriberPhoneNumbersDoc::eColCityCode,   _T("��� �� ����"), LVCFMT_LEFT);
  oListCtrl.InsertColumn(CSubscriberPhoneNumbersDoc::eColAddress,    _T("�����"), LVCFMT_LEFT);

  /* ������������ �� �������� ������ ��������� �� ������� �� */
  oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColCode,       LVSCW_AUTOSIZE_USEHEADER);
  oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColFirstName,  LVSCW_AUTOSIZE_USEHEADER);
  oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColSecondName, LVSCW_AUTOSIZE_USEHEADER);
  oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColThirdName,  LVSCW_AUTOSIZE_USEHEADER);
  oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColIDNumb,     LVSCW_AUTOSIZE_USEHEADER);
  oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColCityCode,   LVSCW_AUTOSIZE_USEHEADER);
  oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColAddress,    LVSCW_AUTOSIZE_USEHEADER);

  memset(m_abAscSorting, TRUE, sizeof(m_abAscSorting));

  /* ��������� �������� �� ������ */
  UpdateColumnsContent();
  m_iCurrRowSelected = 0;
}

BOOL CSubscriberPhoneNumbersView::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
  CMenu oCntxMenu;
  CMenu *pSubMenu = 0;
  POINT tCur;
  
  int iMenuChoice;
  if (message == WM_NOTIFY)
  {
    int iNumb = 0;
    switch(((LPNMHDR)lParam)->code)
    {
      case NM_DBLCLK:
        /* ��� ����� ���� �� ������ �� �������� �������� ��������� ��� */
        ExecuteCntxMenuCmd(eCmdUpdate); 
        break;
      case NM_RCLICK:        
        oCntxMenu.LoadMenuW(IDR_CONTEXT_MENU);
        pSubMenu = oCntxMenu.GetSubMenu(0);
        GetCursorPos(&tCur);
        iMenuChoice = pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD, tCur.x, tCur.y, this);
        /* ���������� �� �������, ������� �� ������������� ���� */
        switch(iMenuChoice)
        {
          case ID_OPTIONS_EDIT:   ExecuteCntxMenuCmd(eCmdUpdate); break;
          case ID_OPTIONS_DELETE: ExecuteCntxMenuCmd(eCmdDelete); break;
          case ID_OPTIONS_ADD:    ExecuteCntxMenuCmd(eCmdInsert); break;        
          case ID_OPTIONS_FIND:   ExecuteCntxMenuCmd(eCmdFind);   break; 
          default: break; 
        }
        break;
      case LVN_COLUMNCLICK:
        /* ��������� �� ����� �� ������ */
        iNumb = ((LPNMLISTVIEW)lParam)->iSubItem;
        m_abAscSorting[iNumb] = !m_abAscSorting[iNumb];
        GetDocument()->SortByColumn((CSubscriberPhoneNumbersDoc::eColumn)iNumb, m_abAscSorting[iNumb]);
        UpdateColumnsContent();
        break;
      case LVN_ITEMCHANGED:
        /* ����� �� �������� ��������� ��� */
        m_iCurrRowSelected = ((LPNMLISTVIEW)lParam)->iItem;
        break;
      default:
        break;
    }
  }

  return CListView::OnChildNotify(message, wParam, lParam, pResult);
}

void CSubscriberPhoneNumbersView::UpdateColumnsContent()
{
  m_SubscriberPhoneNumbersArray.RemoveAndFreeAll();
  /* ��������� �� ������ � ������, ������ �������� ���������� ������ */
  if(GetDocument()->SelectAll(m_SubscriberPhoneNumbersArray) == TRUE)
  {
    CListCtrl& oListCtrl = GetListCtrl();   
    oListCtrl.DeleteAllItems();

    for(int i = m_SubscriberPhoneNumbersArray.GetCount(); i != 0 ; )
    {
      i--;
      CString csTempBuff;
      csTempBuff.Format(_T("%d"),  m_SubscriberPhoneNumbersArray[i]->m_iCode);
      int iRowIdx = oListCtrl.InsertItem(CSubscriberPhoneNumbersDoc::eColCode, csTempBuff);
      SetRowData(iRowIdx, *m_SubscriberPhoneNumbersArray[i]);
    }
  }
}

void CSubscriberPhoneNumbersView::ExecuteCntxMenuCmd(eMenuCmd eCmd)
{
  CSubscriberPhoneNumbers oSubscriberPhoneNumbers;
  if(m_SubscriberPhoneNumbersArray.GetCount())
    oSubscriberPhoneNumbers = *m_SubscriberPhoneNumbersArray[m_iCurrRowSelected];

  if(eCmd == eCmdDelete)
  {
    GetDocument()->DeleteWhereId(oSubscriberPhoneNumbers.m_iId);
  }
  else
  {
    CCitiesArray oCitiesArray;
    GetDocument()->SelectAllCityCodes(oCitiesArray);
    CSubscriberPhoneNumbersDlg oEditDlg(oSubscriberPhoneNumbers, eCmd, &oCitiesArray);
    
    if(oEditDlg.DoModal() != IDOK)
      return;

    CSubscriberPhoneNumbers oCity;
    switch(eCmd)
    {
    case eCmdUpdate:
      oCity = oEditDlg.GetCityData();
      if(GetDocument()->UpdateWhereId(oCity.m_iId, oCity) == FALSE)
        MessageBox(_T("������ ��� �����.\n����������� ������ ��� �� ���������"), 0, MB_OK|MB_ICONWARNING);
      
      break;
    case eCmdInsert:
      oCity = oEditDlg.GetCityData();
      if(GetDocument()->Insert(oCity) == FALSE)
        MessageBox(_T("������ ��� �����.\n����������� ������"), 0, MB_OK|MB_ICONWARNING); 
      break;
    case eCmdFind:
      oCity = oEditDlg.GetCityData();
      GetDocument()->SelectByContent(oCity);
      UpdateColumnsContent();
      break;
    default:
      ASSERT(0);
      break;  
    }
  }
}

void CSubscriberPhoneNumbersView::OnUpdate(CView *pSender, LPARAM lHint, CObject *pHint)
{
  if(lHint == 0)
  {
    UpdateColumnsContent();
  }
  else
  {
    UpdateSingleRow(((CSubscriberPhoneNumbers*)lHint)->m_iId);
  }
}

void CSubscriberPhoneNumbersView::UpdateSingleRow(int iRecId)
{
  for(int i = 0; i < m_SubscriberPhoneNumbersArray.GetCount(); i++)
  {
    /* �������� ���� ��� � ������ ID � ������� � ������� �� ������������ */
    if(m_SubscriberPhoneNumbersArray[i]->m_iId == iRecId)
    {      
      CSubscriberPhoneNumbers *poUpdatedSubscriber = new CSubscriberPhoneNumbers;
      if(!GetDocument()->SelectWhereId(iRecId, *poUpdatedSubscriber))
        return;

      delete m_SubscriberPhoneNumbersArray[i];
      m_SubscriberPhoneNumbersArray[i] = poUpdatedSubscriber;
      SetRowData(i, *poUpdatedSubscriber);

      break;
    }
  }
}

void CSubscriberPhoneNumbersView::SetRowData(int iRowIdx, CSubscriberPhoneNumbers &oSubscriber)
{
  CListCtrl& oListCtrl = GetListCtrl();
  CString csTempBuff;
  csTempBuff.Format(_T("%d"),  oSubscriber.m_iCode);
  oListCtrl.SetItemText(iRowIdx, CSubscriberPhoneNumbersDoc::eColCode, csTempBuff);
  oListCtrl.SetItemText(iRowIdx, CSubscriberPhoneNumbersDoc::eColFirstName, oSubscriber.m_szFirstName);
  oListCtrl.SetItemText(iRowIdx, CSubscriberPhoneNumbersDoc::eColSecondName,oSubscriber.m_szSecondName);
  oListCtrl.SetItemText(iRowIdx, CSubscriberPhoneNumbersDoc::eColThirdName, oSubscriber.m_szThirdName);
  oListCtrl.SetItemText(iRowIdx, CSubscriberPhoneNumbersDoc::eColIDNumb,    oSubscriber.m_szIDNumb);
  oListCtrl.SetItemText(iRowIdx, CSubscriberPhoneNumbersDoc::eColCityCode,  oSubscriber.m_szCityCode);
  oListCtrl.SetItemText(iRowIdx, CSubscriberPhoneNumbersDoc::eColAddress,   oSubscriber.m_szAddress);  

  /* ������������ �� �������� ������ ��������� �� ����� � */
  oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColCode, LVSCW_AUTOSIZE_USEHEADER);
  /* ������������ �� �������� ������ ����. ������� �� ���� ����� */
  oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColFirstName,  LVSCW_AUTOSIZE);
  oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColSecondName, LVSCW_AUTOSIZE);
  oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColThirdName,  LVSCW_AUTOSIZE);
  oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColIDNumb,     LVSCW_AUTOSIZE);
  oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColCityCode,   LVSCW_AUTOSIZE);
  oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColAddress,    LVSCW_AUTOSIZE);
}

// CSubscriberPhoneNumbersView diagnostics

#ifdef _DEBUG
void CSubscriberPhoneNumbersView::AssertValid() const
{
  CListView::AssertValid();
}

void CSubscriberPhoneNumbersView::Dump(CDumpContext& dc) const
{
  CListView::Dump(dc);
}

CSubscriberPhoneNumbersDoc* CSubscriberPhoneNumbersView::GetDocument() const // non-debug version is inline
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSubscriberPhoneNumbersDoc)));
  return (CSubscriberPhoneNumbersDoc*)m_pDocument;
}
#endif //_DEBUG


// CSubscriberPhoneNumbersView message handlers
