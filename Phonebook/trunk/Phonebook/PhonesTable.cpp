#include "StdAfx.h"
#include "PhonesTable.h"
#include "PhonebookDBException.h"

CPhonesTable::CPhonesTable(CDatabase &cDatabase)
:CPhonebookRecSet(&cDatabase)
{
  CDispnameToAttrname a_tDispToAttrName[] = 
  {
    CDispnameToAttrname(_T("��� �� ��� �������"), _T("code")),
    CDispnameToAttrname(_T("��� �������"),        _T("phone_type")),
    CDispnameToAttrname(_T(""),            _T("")),
  };
  if(LoadDB(CDispnameToAttrname(_T("������ ��������"), _T("phonebook.dbo.phones")), &a_tDispToAttrName[0], 0) != TRUE)
  {
    throw CPhoneBookDBException(_T("Unable to load 'phones' table"));
  }
}

CPhonesTable::~CPhonesTable(void)
{
}
