// SubscribersPhoneNumbers.h : Declaration of the CSubscribersPhoneNumbers

#pragma once

// code generated on 20 �������� 2013 �., 23:56 �.
#include "DbTableInterface.h"

class CSubscribersPhoneNumbers : virtual private CRecordset, public CDbTableInterface
{
public:
	CSubscribersPhoneNumbers(CDatabase* pDatabase, const TCHAR *pszDBPath = 0);
	DECLARE_DYNAMIC(CSubscribersPhoneNumbers)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_id;
	long	m_rev_nmb;
	long	m_subscriber_id;
	long	m_phone_id;
	CStringW	m_phone_number;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string
  enum    eTableColumns{eColSubscriberId=0, eColPhoneId, eColPhoneNumb};

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
  virtual BOOL     WriteRow(CArray<CString> &a_csRowData, HANDLE hRow);
  virtual BOOL     AddRow(CArray<CString> &a_csRowData);
  virtual HANDLE   ReadRow(CArray<CString> &a_csRowData,  int iRowNmbr);

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

