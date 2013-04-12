// SubscribersView.h : interface of the CSubscribersView class
//


#pragma once
#include "SubscribersDoc.h"

class CSubscribersView : public CListView
{
protected: // create from serialization only
	CSubscribersView();
	DECLARE_DYNCREATE(CSubscribersView)

// Attributes
public:
	CSubscribersDoc* GetDocument() const;

private:
	// �������� ������ ��� �� ������� 
	int	 m_nCurrRowSelected;
 // ����� ������� ������ �� ��������� �� ����� ���� �� �������� 
	BOOL	m_abAscSorting[CSubscribersDoc::eCOL_NUMB];
	// ����� �� ��������� ��� ����� �� ����� ��� �� ������. ��������� �, ��� ���� ID � rev_numb �� ����� 
	// ���, �� �� ������������. �.�. �� ������ �� �� ����������, � ��� ���������� � ������ �� �������� 
	CSubscribersArray m_SubscribersArray;
// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView *pSender, LPARAM lHint, CObject *pHint);
// Implementation
public:
	virtual ~CSubscribersView();
	void RecreateColumnsContent();
	void UpdateSingleRow(int iRecId);
	void SetRowData(int iRowIdx, CSubscribers &oSubscriber);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

public:
	void ExecuteCntxMenuCmd(eMenuCmd eCmd);
};

#ifndef _DEBUG	// debug version in SubscribersView.cpp
inline CSubscribersDoc* CSubscribersView::GetDocument() const
	 { return reinterpret_cast<CSubscribersDoc*>(m_pDocument); }
#endif

