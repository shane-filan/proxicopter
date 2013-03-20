#pragma once
#include "AfxTempl.h"

/* ���� ������� �� ������ ������� */
#define TABLE_HEADER \
  int   m_iId;       \
  int   m_iRevNumb;  \

/* ���������� �� ���� �� ������ ������� ��������, ����� � ������� ����� */
enum eMenuCmd{eCmdUpdate = 0, eCmdInsert, eCmdDelete, eCmdFind};

#define MENU_CMD_DELETE _T("������")
#define MENU_CMD_INSERT _T("������")
#define MENU_CMD_UPDATE _T("����������")
#define MENU_CMD_FIND   _T("�����")

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