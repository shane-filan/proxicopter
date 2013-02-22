// PhonebookView.h : interface of the CPhonebookView class
//

#pragma once
#include "afxwin.h"
#include "DBTablesContainer.h"
#include "Sortbutton.h"
class CPhonebookView : public CFormView
{
protected: // create from serialization only
	CPhonebookView();
	DECLARE_DYNCREATE(CPhonebookView)
public:
	enum{ IDD = IDD_PHONEBOOK_FORM };

// Attributes
public:
	CPhonebookDoc* GetDocument() const;
// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CPhonebookView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  CDBTablesContainer *m_pTablesContainer;
  CArray<CDbTableInterface*> m_apTables;
  CArray<HANDLE> m_ahRows;
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedLoaddb();
  CComboBox m_RegSelector;
  int m_iLastRowClicked;
  afx_msg void OnCbnSelchangeRegisterSelector();
  afx_msg void OnBnClickedSortbycol1();
#define COLUMN_NUMBER (7)
#define ROW_NUMBER    (4)
  CSortButton m_SortByCol[7];
  CEdit   m_TableFields[ROW_NUMBER][COLUMN_NUMBER];
  CEdit m_TablePath;
  CEdit m_DSN;
  afx_msg void OnBnClickedSortbycol3();
  afx_msg void OnBnClickedSortbycol2();
  afx_msg void OnBnClickedSortbycol4();
  afx_msg void OnBnClickedSortbycol5();
  afx_msg void OnBnClickedSortbycol6();
  afx_msg void OnBnClickedSortbycol7();
  void ClearSortButtonsLabels();
  void RecreateSortButtonsLabels();
  void ClearRowContent(int iRow);
  void ClearAllRowsContent();
  void RecreateRowsContent();
  void RecreateTableSelectorContent();
  void CleanUpTablesData();
  void CleanUpRowData();
  void SortByCol(int iColNmb);
  afx_msg void OnBnClickedWriteRow();
  afx_msg void OnEnChangeEdit1();
  afx_msg void OnEnChangeEdit8();
  afx_msg void OnEnChangeEdit15();
  afx_msg void OnEnChangeEdit22();
};

#ifndef _DEBUG  // debug version in PhonebookView.cpp
inline CPhonebookDoc* CPhonebookView::GetDocument() const
   { return reinterpret_cast<CPhonebookDoc*>(m_pDocument); }
#endif

