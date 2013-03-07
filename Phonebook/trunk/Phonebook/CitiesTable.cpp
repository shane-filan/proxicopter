// CitiesTable.cpp : implementation of the CCitiesTable class
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "CitiesTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCitiesTable implementation

// code generated on 05 ���� 2013 �., 19:08 �.

IMPLEMENT_DYNAMIC(CCitiesTable, CRecordset)

CCitiesTable::CCitiesTable(CDatabase* pdb)
	: CRecordset(pdb)
{
  m_ID = 0;
  m_REV_NUMB = 0;
  m_CODE = L"";
  m_NAME = L"";
  m_AREA = L"";
  m_nFields = 5;
  m_nDefaultType = dynaset;

  m_bSQLEn = TRUE;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CCitiesTable::GetDefaultConnect()
{
  if(m_bSQLEn)
  	return _T("DSN=SQLExpress;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=PROXIMUS-PC;DATABASE=phonebook");
  else
    return _T("");
}

CString CCitiesTable::GetDefaultSQL()
{
  if(m_bSQLEn)
  	return _T("[dbo].[CITIES]");
  else
    return _T("[Cities$]");
}

void CCitiesTable::DoFieldExchange(CFieldExchange* pFX)
{
  pFX->SetFieldType(CFieldExchange::outputColumn);
  // Macros such as RFX_Text() and RFX_Int() are dependent on the
  // type of the member variable, not the type of the field in the database.
  // ODBC will try to automatically convert the column value to the requested type
  RFX_Long(pFX, _T("[ID]"), m_ID);
  RFX_Long(pFX, _T("[REV_NUMB]"), m_REV_NUMB);
  RFX_Text(pFX, _T("[CODE]"), m_CODE);
  RFX_Text(pFX, _T("[NAME]"), m_NAME);
  RFX_Text(pFX, _T("[AREA]"), m_AREA);

}

BOOL CCitiesTable::SelectAll(CCitiesArray &oCitiesArray)
{
  if(IsOpen())
    Close();
  
  try
  {
   Open(CRecordset::dynaset);
  }
  catch(CDBException *)
  {
    /* � ������ �� ������� ��� �������� �� �������� �� ������������ �� ����� ��� ����, 
       ���� ��� ��� ��������� �� ������������. ������ �� �� �� �� ����� XLS ���� */
    m_bSQLEn = FALSE;
    Open(CRecordset::dynaset);
  }
    
  if(!IsBOF())
  {
    /* ���������� �� ������ � ��������� ��� ����� �� ������ �� ��������� */
    while(!IsEOF())
    {
      CCities *poCity = new CCities(int(m_ID), int(m_REV_NUMB), m_CODE.GetBuffer(), m_NAME.GetBuffer(), m_AREA.GetBuffer());
      oCitiesArray.Add(poCity);     
      MoveNext();
    }
  }

  return TRUE;
}

BOOL CCitiesTable::SelectWhereId(const int iId, CCities &oCity)
{
  if(IsOpen())
    Close(); 

  m_strFilter.Format(_T("ID = %d"), iId);
  Open(CRecordset::dynaset);

  if(IsBOF())
    return FALSE; 

  MoveFirst();
  oCity.m_iId = m_ID;
  oCity.m_iRevNumb = m_REV_NUMB;
  _tcscpy(oCity.m_szCode, m_CODE);
  _tcscpy(oCity.m_szName, m_NAME);
  _tcscpy(oCity.m_szArea, m_AREA); 

  return TRUE;  
}

BOOL CCitiesTable::UpdateWhereId(const int iId, const CCities &oCity)
{
  /* �������� ���� ��� ���� ����� ��� ������ ��� �� ���� */
  if(SelectByContent(CCities(oCity.m_iId, oCity.m_iRevNumb, oCity.m_szCode)) == TRUE)
    return FALSE;

  /* �������� ���� ��� ���� ����� ��� ������ ��� �� ���� */
  if(SelectByContent(CCities(oCity.m_iId, oCity.m_iRevNumb, 0, oCity.m_szName)) == TRUE)
    return FALSE;

  CCities oCurrCity;
  if(SelectWhereId(iId, oCurrCity) == FALSE)
    return FALSE;
  
  if(oCurrCity.m_iRevNumb != oCity.m_iRevNumb)
    return FALSE;

  MoveFirst();  
  Edit();
  m_ID = oCity.m_iId;
  m_REV_NUMB = oCurrCity.m_iRevNumb + 1;
  m_CODE = oCity.m_szCode;
  m_NAME = oCity.m_szName;
  m_AREA = oCity.m_szArea; 

  Update();

  m_strFilter = _T("");
  m_strSort = _T("");

  return TRUE;
}

BOOL CCitiesTable::Insert(const CCities &oCity)
{
  if(!CanAppend())
    return FALSE;

  /* �������� ���� ��� ����� ��� ������ ��� �� ���� */
  if(SelectByContent(CCities(-1, 0, oCity.m_szCode)) == TRUE)
    return FALSE;

  /* �������� ���� ��� ����� ��� ����� ��� �� ���� */
  if(SelectByContent(CCities(-1, 0, 0, oCity.m_szName)) == TRUE)
    return FALSE;

  Close();
  m_strFilter = _T("");
  m_strSort = _T("");
  Open(CRecordset::dynaset);

  MoveLast();  
  /* ���������� ID �� ���������� ��� �� ��������� */ 
  int iLastRowId = m_ID;
  AddNew();

  m_ID = iLastRowId + 1;
  m_REV_NUMB = 0;
  m_CODE = oCity.m_szCode;
  m_NAME = oCity.m_szName;
  m_AREA = oCity.m_szArea; 

  Update();

  return TRUE;
}

BOOL CCitiesTable::DeleteWhereId(const int iId)
{
  CCities oCities;
  if(SelectWhereId(iId, oCities) == FALSE)
  {
    m_strFilter = _T("");
    return FALSE;
  }
  
  if(!CanUpdate())
    return FALSE;

  Delete();
  m_strFilter = _T("");

  return TRUE;
}

BOOL CCitiesTable::SortByColumn(const eColumn eCol, const BOOL bAsc)
{
  if(IsOpen())
    Close(); 

  m_strFilter = _T("");
  switch(eCol)
  {
  case eColCode:    
    bAsc ? m_strSort.Format(_T("%s ASC"), _T("CODE")): m_strSort.Format(_T("%s DESC"), _T("CODE"));
    break;
  case eColName:
    bAsc ? m_strSort.Format(_T("%s ASC"), _T("NAME")): m_strSort.Format(_T("%s DESC"), _T("NAME"));
    break;
  case eColArea:
    bAsc ? m_strSort.Format(_T("%s ASC"), _T("AREA")): m_strSort.Format(_T("%s DESC"), _T("AREA"));
    break;
  default:
    return FALSE;
  }

  Open(CRecordset::dynaset);

  return TRUE;
}

BOOL CCitiesTable::SelectByContent(const CCities &oCity)
{
  if(IsOpen())
    Close(); 

  m_strSort = _T("");
  m_strFilter = _T("");
  CString szColFilter;
  if(oCity.m_iId != -1)
  {
    /* ���������� �� �������� ����� �� ��-����������� ���������� */
    szColFilter.Format(_T("ID != %d"), oCity.m_iId);
    m_strFilter += szColFilter;
  }
  /* ��������� �� ��� �� ����������, �� ���� ��������� � ����������� �������� ������ */
  if(_tcslen(oCity.m_szCode))
  {
    if(m_strFilter.GetLength())
      m_strFilter += _T(" AND ");

    szColFilter.Format(_T("CODE = '%s'"), oCity.m_szCode);
    m_strFilter += szColFilter;
  }
  if(_tcslen(oCity.m_szName))
  {
    if(m_strFilter.GetLength())
      m_strFilter += _T(" AND ");

    szColFilter.Format(_T("NAME = '%s'"), oCity.m_szName);
    m_strFilter += szColFilter;
  }
  if(_tcslen(oCity.m_szArea))
  {
    if(m_strFilter.GetLength())
      m_strFilter += _T(" AND ");

    szColFilter.Format(_T("AREA = '%s'"), oCity.m_szArea);
    m_strFilter += szColFilter;
  }

  Open(CRecordset::dynaset);

  if(IsBOF())
    return FALSE; 

  return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable diagnostics

#ifdef _DEBUG
void CCitiesTable::AssertValid() const
{
  CRecordset::AssertValid();
}

void CCitiesTable::Dump(CDumpContext& dc) const
{
  CRecordset::Dump(dc);
}
#endif //_DEBUG

