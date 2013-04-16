#pragma once
#include "AfxTempl.h"

// ���� ������� �� ������ ������� 
#define TABLE_HEADER	\
	int	 m_nId;			\
	int	 m_nRevNumb;	\

// ���������� �� ���� �� ������ ������� ��������, ����� � ������� ����� 
enum eMenuCmd{eCmdUpdate = 0, eCmdInsert, eCmdDelete, eCmdFind, eCmdInsertSubscr, eCmdInsertNumb, eCmdDelSubscr, eCmdDelNumb};

#define MENU_CMD_DELETE				_T("������")
#define MENU_CMD_INSERT				_T("������")
#define MENU_CMD_UPDATE				_T("����������")
#define MENU_CMD_FIND				_T("�����")
#define MENU_CMD_INSERT_SUBSCRIBER	_T("������ ��� ������")
#define MENU_CMD_INSERT_NUMBER		_T("������ ��� �����")
#define MENU_CMD_DELETE_SUBSCRIBER	_T("������ ��� ������")
#define MENU_CMD_DELETE_NUMBER		_T("������ ��� �����")


// Don't care �������� 
#define DNC (-1)
#define EMPTY_STRING	_T("")
// ������� �� ������������ ��������� ����� �� ���������, ��������� � ������������� ��
//	��������� ������� ����� ������ ��� ���, ��� ����������� �� ������ 
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

class CPhoneBookErr
{
public:
	enum eErrorType{eGenError = 0, eDBWriteFailed, eDBWReadFailed};
	static void IndicateUser(eErrorType eErr)
	{
		switch(eErr)
		{
		case eGenError:
			MessageBox(0, _T("������ � ������ �����"), 0, MB_OK|MB_ICONWARNING);
			break;
		case eDBWReadFailed:
			MessageBox(0, _T("������ ��� ������"), 0, MB_OK|MB_ICONWARNING);
			break;
		case eDBWriteFailed:
			MessageBox(0, _T("������ ��� �����.\n����������� ������ ��� �� ���������"), 0, MB_OK|MB_ICONWARNING);
			break;
		}
	};
};