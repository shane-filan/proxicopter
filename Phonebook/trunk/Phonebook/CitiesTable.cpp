#include "stdafx.h"
#include "CitiesTable.h"
#include "PhonebookDBException.h"

CCitiesTable::CCitiesTable(CDatabase &cDatabase):
CPhonebookRecSet(&cDatabase)
{
  CDispnameToAttrname a_tDispToAttrName[] = 
  {
    CDispnameToAttrname(_T("��� �� ����"), _T("code")),
    CDispnameToAttrname(_T("����"),        _T("name")),
    CDispnameToAttrname(_T("������"),      _T("area")),
    CDispnameToAttrname(_T(""),            _T("")),
  };
  if(LoadDB(CDispnameToAttrname(_T("�������"), _T("phonebook.dbo.cities")), &a_tDispToAttrName[0], 0) != TRUE)
  {
    throw CPhoneBookDBException(_T("Unable to load 'city' table"));
  }
}

CCitiesTable::~CCitiesTable(void)
{
}





