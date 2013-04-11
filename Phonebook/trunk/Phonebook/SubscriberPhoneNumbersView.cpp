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
	//	the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

void CSubscriberPhoneNumbersView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: You may populate your ListView with items by directly accessing
	//	its list control through a call to GetListCtrl().
	long lWndStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	lWndStyle |= LVS_REPORT;
	SetWindowLong(m_hWnd, GWL_STYLE, lWndStyle);
	CListCtrl& oListCtrl = GetListCtrl();
	oListCtrl.SetExtendedStyle( oListCtrl.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

	oListCtrl.InsertColumn(CSubscriberPhoneNumbersDoc::eColSubscrCode, _T("��� �� ������"), LVCFMT_LEFT);
	oListCtrl.InsertColumn(CSubscriberPhoneNumbersDoc::eColPhoneCode, _T("��� �� ��� �������"), LVCFMT_LEFT);
	oListCtrl.InsertColumn(CSubscriberPhoneNumbersDoc::eColPhoneNumber, _T("�������"), LVCFMT_LEFT);

	// ������������ �� �������� ������ ��������� �� ������� �� 
	oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColSubscrCode, LVSCW_AUTOSIZE_USEHEADER);
	oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColPhoneCode, LVSCW_AUTOSIZE_USEHEADER);
	oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColPhoneNumber, LVSCW_AUTOSIZE_USEHEADER);

	memset(m_abAscSorting, TRUE, sizeof(m_abAscSorting));

	// ��������� �������� �� ������ 
	UpdateColumnsContent();
	m_nCurrRowSelected = 0;
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
				// ��� ����� ���� �� ������ �� �������� �������� ��������� ��� 
				ExecuteCntxMenuCmd(eCmdUpdate); 
				break;
			case NM_RCLICK:	
				oCntxMenu.LoadMenuW(IDR_CONTEXT_MENU);
				pSubMenu = oCntxMenu.GetSubMenu(0);
				GetCursorPos(&tCur);
				iMenuChoice = pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD, tCur.x, tCur.y, this);
				// ���������� �� �������, ������� �� ������������� ���� 
				switch(iMenuChoice)
				{
					case ID_OPTIONS_EDIT:	ExecuteCntxMenuCmd(eCmdUpdate); break;
					case ID_OPTIONS_DELETE: ExecuteCntxMenuCmd(eCmdDelete); break;
					case ID_OPTIONS_ADD:	ExecuteCntxMenuCmd(eCmdInsert); break;
					case ID_OPTIONS_FIND:	ExecuteCntxMenuCmd(eCmdFind);	break; 
					default: break; 
				}
				break;
			case LVN_COLUMNCLICK:
				// ��������� �� ����� �� ������ 
				iNumb = ((LPNMLISTVIEW)lParam)->iSubItem;
				m_abAscSorting[iNumb] = !m_abAscSorting[iNumb];
				GetDocument()->SortByColumn((CSubscriberPhoneNumbersDoc::eColumn)iNumb, m_abAscSorting[iNumb]);
				UpdateColumnsContent();
				break;
			case LVN_ITEMCHANGED:
				// ����� �� �������� ��������� ��� 
				m_nCurrRowSelected = ((LPNMLISTVIEW)lParam)->iItem;
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
	// ��������� �� ������ � ������, ������ �������� ���������� ������ 
	if(GetDocument()->SelectAll(m_SubscriberPhoneNumbersArray) == TRUE)
	{
		CListCtrl& oListCtrl = GetListCtrl();	 
		oListCtrl.DeleteAllItems();

		for(int i = m_SubscriberPhoneNumbersArray.GetCount(); i != 0 ; )
		{
			i--;
			CString csTempBuff;
			csTempBuff.Format(_T("%d"),	m_SubscriberPhoneNumbersArray[i]->m_nSubscrId);
			int iRowIdx = oListCtrl.InsertItem(CSubscriberPhoneNumbersDoc::eColSubscrCode, csTempBuff);
			SetRowData(iRowIdx, *m_SubscriberPhoneNumbersArray[i]);
		}
	}
}

void CSubscriberPhoneNumbersView::ExecuteCntxMenuCmd(eMenuCmd eCmd)
{
	CSubscriberPhoneNumbers oSubscriberPhoneNumber;
	if(m_SubscriberPhoneNumbersArray.GetCount())
		oSubscriberPhoneNumber = *m_SubscriberPhoneNumbersArray[m_nCurrRowSelected];

	if(eCmd == eCmdDelete)
	{
		GetDocument()->DeleteWhereId(oSubscriberPhoneNumber.m_nId);
	}
	else
	{
		CSubscribersArray oSubscrArray;
		GetDocument()->SelectAllSubscribersCodes(oSubscrArray);
		CPhoneTypesArray oPhoneTypesArray;
		GetDocument()->SelectAllPhoneTypesCodes(oPhoneTypesArray);

		CSubscriberPhoneNumbersDlg oEditDlg(oSubscriberPhoneNumber, eCmd, &oSubscrArray, &oPhoneTypesArray);
		
		if(oEditDlg.DoModal() != IDOK)
			return;

		CSubscriberPhoneNumbers oCity;
		switch(eCmd)
		{
		case eCmdUpdate:
			oCity = oEditDlg.GetCityData();
			if(GetDocument()->UpdateWhereId(oCity.m_nId, oCity) == FALSE)
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
		UpdateSingleRow(((CSubscriberPhoneNumbers*)lHint)->m_nId);
	}
}

void CSubscriberPhoneNumbersView::UpdateSingleRow(int iRecId)
{
	for(int i = 0; i < m_SubscriberPhoneNumbersArray.GetCount(); i++)
	{
		// �������� ���� ��� � ������ ID � ������� � ������� �� ������������ 
		if(m_SubscriberPhoneNumbersArray[i]->m_nId == iRecId)
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

void CSubscriberPhoneNumbersView::SetRowData(int iRowIdx, CSubscriberPhoneNumbers &oSubscriberPhoneNumb)
{
	CListCtrl& oListCtrl = GetListCtrl();
	CSubscribers oSubscriber;
	if(!GetDocument()->SelectSubscriberWhereId(oSubscriberPhoneNumb.m_nSubscrId, oSubscriber))
		return;

	CString csTempBuff;
	csTempBuff.Format(_T("%d"),	oSubscriber.m_nCode);
	oListCtrl.SetItemText(iRowIdx, CSubscriberPhoneNumbersDoc::eColSubscrCode,	csTempBuff);

	CPhoneTypes oPhoneType;
	if(!GetDocument()->SelectPhoneTypeWhereId(oSubscriberPhoneNumb.m_nPhoneId, oPhoneType))
		return;

	csTempBuff.Format(_T("%d"),	oPhoneType.m_nCode);
	oListCtrl.SetItemText(iRowIdx, CSubscriberPhoneNumbersDoc::eColPhoneCode, csTempBuff); 

	oListCtrl.SetItemText(iRowIdx, CSubscriberPhoneNumbersDoc::eColPhoneNumber, oSubscriberPhoneNumb.m_szPhoneNumber);
	// ������������ �� �������� ������ ��������� �� ����� � 
	oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColSubscrCode, LVSCW_AUTOSIZE_USEHEADER);
	// ������������ �� �������� ������ ����. ������� �� ���� ����� 
	oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColPhoneCode,	 LVSCW_AUTOSIZE_USEHEADER);
	oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColPhoneNumber, LVSCW_AUTOSIZE);
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
