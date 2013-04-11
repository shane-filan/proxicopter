// CitiesView.h : interface of the CCitiesView class
//


#pragma once
#include "CitiesDoc.h"

class CCitiesView : public CListView
{
protected: // create from serialization only
	CCitiesView();
	DECLARE_DYNCREATE(CCitiesView)

// Attributes
public:
	CCitiesDoc* GetDocument() const;

private:
  // �������� ������ ��� �� ������� 
  int   m_nCurrRowSelected;
 // ����� ������� ������ �� ��������� �� ����� ���� �� �������� 
  BOOL  m_abAscSorting[CCitiesDoc::eCOL_NUMB];
  // ����� �� ��������� ��� ����� �� ����� ��� �� ������. ��������� �, ��� ���� ID � rev_numb �� ����� 
  // ���, �� �� ������������. �.�. �� ������ �� �� ����������, � ��� ���������� � ������ �� �������� 
  CCitiesArray m_CitiesArray;
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
	virtual ~CCitiesView();
  void UpdateColumnsContent();
  void UpdateSingleRow(int iRecId);
  void SetRowData(int iRowIdx, CCities &oCity);
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

#ifndef _DEBUG  // debug version in CitiesView.cpp
inline CCitiesDoc* CCitiesView::GetDocument() const
   { return reinterpret_cast<CCitiesDoc*>(m_pDocument); }
#endif

