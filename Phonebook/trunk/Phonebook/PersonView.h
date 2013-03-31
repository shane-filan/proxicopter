// PersonView.h : interface of the CPersonView class
//


#pragma once
#include "PersonDoc.h"

class CPersonView : public CListView
{
protected: // create from serialization only
	CPersonView();
	DECLARE_DYNCREATE(CPersonView)

// Attributes
public:

private:

// Operations
public:

// Overrides
public:

protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CPersonView();
	void UpdateColumnsContent();
	void SetRowData(int iRowIdx, CPerson &oPerson, CSubscriberPhoneNumbers &oPhoneNumber);
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
	CPersonDoc* GetDocument() const;
  /* �������� ������ ��� �� ������� */
  int   m_iCurrRowSelected;
 /* ����� ������� ������ �� ��������� �� ����� ���� �� �������� */
  BOOL  m_abAscSorting[CPersonDoc::eCOL_NUMB];
  /* ����� �� ��������� ��� ����� �� ����� ��� �� ������. ��������� �, ��� ���� ID � rev_numb �� ����� 
     ���, �� �� ������������. �.�. �� ������ �� �� ����������, � ��� ���������� � ������ �� �������� */
  CPersonArray m_PersonsArray;
};

#ifndef _DEBUG  // debug version in PersonView.cpp

#endif

#pragma once
