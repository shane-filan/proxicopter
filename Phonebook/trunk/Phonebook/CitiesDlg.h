#pragma once
#include "Cities.h"
#include "CitiesView.h"
#include "afxwin.h"

// CCitiesDlg dialog
class CCitiesDlg : public CDialog
{
	DECLARE_DYNAMIC(CCitiesDlg)

public:
	CCitiesDlg(const CCities &oCities, CCitiesView::eMenuCmd eCmd, CWnd* pParent = NULL);   // standard constructor
	virtual ~CCitiesDlg();

// Dialog Data
	enum { IDD = IDD_CITIES_EDIT };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
  CCitiesView::eMenuCmd m_eMenuCmd;
  CCities m_oCity;
  CEdit m_Name;
  CEdit m_Area;
  CEdit m_Code;
public:
  afx_msg void OnBnClickedCityEditUpdate();
  virtual BOOL OnInitDialog();
  CCities   GetCityData(){return m_oCity;};
  afx_msg void OnBnClickedOk();
};