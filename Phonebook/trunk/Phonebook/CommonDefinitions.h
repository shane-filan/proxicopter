#pragma once
#include "AfxTempl.h"

/* ���� ������� �� ������ ������� */
#define TABLE_HEADER \
  int   m_iId;       \
  int   m_iRevNumb;  \

/* ���������� �� ���� �� ������ ������� ��������, ����� � ������� ����� */
enum eMenuCmd{eCmdUpdate = 0, eCmdInsert, eCmdDelete, eCmdFind, eCmdInsertSubscr, eCmdInsertNumb, eCmdDelSubscr, eCmdDelNumb};

#define MENU_CMD_DELETE _T("������")
#define MENU_CMD_INSERT _T("������")
#define MENU_CMD_UPDATE _T("����������")
#define MENU_CMD_FIND   _T("�����")
#define MENU_CMD_INSERT_NEW_SUBSCRIBER _T("������ ��� ������")
#define MENU_CMD_INSERT_NEW_NUMBER		 _T("������ ��� �����")
#define MENU_CMD_DELETE_NEW_SUBSCRIBER _T("������ ��� ������")
#define MENU_CMD_DELETE_NEW_NUMBER		 _T("������ ��� �����")


/* Don't care �������� */
#define DNC (-1)

/* ������� �� ������������ ��������� ����� �� ���������, ��������� � ������������� ��
   ��������� ������� ����� ������ ��� ���, ��� ����������� �� ������ */
template <class ROW_TYPE> class CRowsPtrArray: public CTypedPtrArray<CPtrArray, ROW_TYPE*>
{
public:
  ~CRowsPtrArray(void)
  {
    RemoveAndFreeAll();
  };
  void RemoveAndFreeAll()
  {
    for(int i = 0; i < GetCount(); i++)
    {
      delete GetAt(i);
    }
    RemoveAll();
  };
};