// PhoneTypesView.h : interface of the CPhoneTypesView class
//


#pragma once
#include "PhoneTypesDoc.h"

class CPhoneTypesView : public CListView
{
protected: // create from serialization only
	CPhoneTypesView();
	DECLARE_DYNCREATE(CPhoneTypesView)

// Attributes
public:
	CPhoneTypesDoc* GetDocument() const;
  /* ���������� ���������� �������, ����� ������������ ���� ������� */
  enum eMenuCmd{eCmdUpdate = 0, eCmdInsert, eCmdDelete, eCmdFind};

private:
  /* �������� ������ ��� �� ������� */
  int   m_iCurrRowSelected;
 /* ����� ������� ������ �� ��������� �� ����� ���� �� �������� */
  BOOL  m_abAscSorting[CPhoneTypesDoc::eCOL_NUMB];
  /* ����� �� ��������� ��� ����� �� ����� ��� �� ������. ��������� �, ��� ���� ID � rev_numb �� ����� 
     ���, �� �� ������������. �.�. �� ������ �� �� ����������, � ��� ���������� � ������ �� �������� */
  CPhoneTypesArray m_PhoneTypesArray;
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
	virtual ~CPhoneTypesView();
  void UpdateColumnsContent();
  void UpdateSingleRow(int iRecId);
  void SetRowData(int iRowIdx, CPhoneTypes &oPhoneType);
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

#ifndef _DEBUG  // debug version in PhoneTypesView.cpp
inline CPhoneTypesDoc* CPhoneTypesView::GetDocument() const
   { return reinterpret_cast<CPhoneTypesDoc*>(m_pDocument); }
#endif

