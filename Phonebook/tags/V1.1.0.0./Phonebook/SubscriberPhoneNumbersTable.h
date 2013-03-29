// SubscriberPhoneNumbersTable.h: interface of the CSubscriberPhoneNumbersTable class
//


#pragma once


// code generated on 05 ���� 2013 �., 19:08 �.
#include "SubscriberPhoneNumbers.h"
#include "SubscribersTable.h"
#include "PhoneTypesTable.h"

class CSubscriberPhoneNumbersTable : private CRecordset
{
public:
	CSubscriberPhoneNumbersTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSubscriberPhoneNumbersTable)

	//Enumerators
public:
	/* ���������� ������� �� �������� � ������� ������ */
	enum eColumn{cColIdx = 0, eColRevNumb, eColSubscrCode, eColPhoneCode, eColPhoneNumber, eCOL_NUMB};


// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.	If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long m_ID;
	long m_REV_NUMB;
	long m_SUBSCRIBER_ID;
	long m_PHONE_ID;
	CStringW m_PHONE_NUMB ;

	/* ���� ���������� ��������� �� DSN:SQLEXPRESS */
	BOOL m_bSQLEn;
		
	CSubscribersTable m_oSubscribersTable;
	CPhoneTypesTable  m_oPhoneTypesTable;

// Overrides
	// Wizard generated virtual function overrides
public:
	virtual CString GetDefaultConnect(); // Default connection string
	virtual CString GetDefaultSQL();     // default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX); // RFX support

	BOOL SelectAll(CSubscriberPhoneNumbersArray &oSubscriberPhoneNumbersArray);
	BOOL SelectWhereId(const int iId, CSubscriberPhoneNumbers &oSubscriber);
	BOOL UpdateWhereId(const int iId, const CSubscriberPhoneNumbers &oSubscriber);
	BOOL Insert(const CSubscriberPhoneNumbers &oSubscriber);
	BOOL DeleteWhereId(const int iId);
	BOOL SortByColumn(const eColumn eCol, const BOOL bAsc);
	BOOL SelectByContent(const CSubscriberPhoneNumbers &oSubscriber);
	BOOL SelectAllSubscribersCodes(CSubscribersArray &oSubscribersArray);
	BOOL SelectAllPhoneTypesCodes(CPhoneTypesArray &oPhoneTypesArray);

	/* ������� �� ������ �� ������� "������� */
	int	GetSubscrCodeBySubscrId(const int iId);
	int	GetSubscrIdBySubscrCode(const int iSubscrCode);
	int	GetPhoneCodeByPhoneId(const int iId);
	int	GetPhoneIdByPhoneCode(const int iPhoneCode);

private:
	void DoExchangeFromDatabaseData(CSubscriberPhoneNumbers &oSubscriber);
	void DoExchange��DatabaseData(const CSubscriberPhoneNumbers &oSubscriber);
// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

