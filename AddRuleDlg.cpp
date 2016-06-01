// AddRuleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "fire.h"
#include "AddRuleDlg.h"
//********************************************************
#include <winsock2.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddRuleDlg dialog


CAddRuleDlg::CAddRuleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddRuleDlg::IDD, pParent)
{
	m_sdadd = _T("");
	m_sdport = _T("");
	m_ssadd = _T("");
	m_ssport = _T("");
	ipFltDrv.LoadDriver("DrvFltIp", NULL, NULL, TRUE);	
}


void CAddRuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddRuleDlg)
	DDX_Control(pDX, IDC_COMBO2, m_protocol);
	DDX_Control(pDX, IDC_COMBO1, m_action);
	DDX_Text(pDX, IDC_DADD, m_sdadd);
	DDV_MaxChars(pDX, m_sdadd, 15);
	DDX_Text(pDX, IDC_DPORT, m_sdport);
	DDX_Text(pDX, IDC_SADD, m_ssadd);
	DDV_MaxChars(pDX, m_ssadd, 15);
	DDX_Text(pDX, IDC_SPORT, m_ssport);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddRuleDlg, CDialog)
	//{{AFX_MSG_MAP(CAddRuleDlg)
	//ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_EN_KILLFOCUS(IDC_SADD, OnKillfocusSadd)
	ON_EN_KILLFOCUS(IDC_DADD, OnKillfocusDadd)
	ON_BN_CLICKED(IDC_ADDSAVE, OnAddsave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

//**************************************************************************
//添加至IPFilter，发送指令至驱动
DWORD CAddRuleDlg::AddFilter(IPFilter pf)
{

	DWORD result = ipFltDrv.WriteIo(ADD_FILTER, &pf, sizeof(pf));
	if (result != DRV_SUCCESS) 
	{
		AfxMessageBox("Unable to add rule to the driver");
		return FALSE;
	}

	else
		return TRUE;
}

//*************************************************************************
//检测输入的IP地址是否非法

BOOL CAddRuleDlg::Verify(CString str)
{
	int index=0;
	for(int i = 0;i<3;i++){
		
    index = str.Find(_T('.'));
	//get the position of the first '.'
	if(index==-1)
	return FALSE;
	else
	{

	CString temp =str.Left(str.Find(_T('.')));
	//get the left side of the '.'
	int flag=1;
	//judge it is all number
	for(int j =0;j<temp.GetLength();j++){
		if(str[j]>='0'&&str[j]<='9'){
		}
		else
			return FALSE;
	}
	str.Delete(0,index+1);
	//delete the string left
	}
	}
	for(int j =0;j<str.GetLength();j++){
		if(str[j]>='0'&&str[j]<='9'){
		}
		else
			return FALSE;
	}
     //MessageBox("可以");
	// Your code
	return TRUE;
}

//*****************************************************************

void CAddRuleDlg::OnKillfocusSadd() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	BOOL bresult = Verify(m_ssadd);
	if(bresult == FALSE)
		MessageBox("Invalid IP Address");	
}

void CAddRuleDlg::OnKillfocusDadd() 
{
	// TODO: Add your control notification handler code here
	// This will check wether the IP address you had given
	// corresponds to a valid IP address or not. If not it
	// will prompt you for a valid IP address.

	UpdateData();
    BOOL bresult = Verify(m_sdadd);
	if(bresult == FALSE)
		MessageBox("Invalid IP Address");
	
}

//将新增的规则写入文件
void CAddRuleDlg::OnAddsave() 
{
	// Your code
	UpdateData();
	BOOL addAct;
	int addType;
	int action = m_action.GetCurSel();
	char ch[30];
    //action:allow or deny
	//type: tcp ip icmp
	if(action == 0 )
	addAct = FALSE;
	else
	addAct = TRUE;
	int type = m_protocol.GetCurSel();
	if(type == 0)
	addType=1;
    if(type ==1)
	addType=17;
	if(type==2)
	addType=6;
	wsprintf(ch,"Action: %d, Protocol %d",action,type);
	MessageBox(ch);
	IPFilter ip;
	ip.destinationIp = inet_addr((LPCTSTR)m_sdadd);
	ip.sourceIp=inet_addr((LPCTSTR)m_ssadd);
	ip.destinationMask = inet_addr("255.255.255.255");
	ip.destinationPort = htons(atoi((LPCTSTR)m_sdport));
	ip.sourceMask = inet_addr("255.255.255.255");
	ip.sourcePort = htons(atoi((LPCTSTR)m_ssport));
    ip.protocol = addType;
    ip.drop = addAct;
	
    CString _str;
	char   ch1[100];
	wsprintf(ch1,"%s,%s,%s,%s,%s,%s,%d,%d\n",
			 m_sdadd,
			 "255.255.255.255",
			 m_sdport,
			 m_ssadd,
			 "255.255.255.255",
			 m_ssport,
			 addType,
			 addAct);
    if( NewFile()== FALSE)
	MessageBox("unable to create file");				//create a new file
	
	GotoEnd();
	 
	
	//MessageBox(_str);
	SaveFile(ch1);
	//	MessageBox("Unalbe tol write to file");
	if(CloseFile() == FALSE)
		MessageBox("Unalbe to close the file");
    DWORD result = AddFilter(ip);


}
BOOL CAddRuleDlg::NewFile(void)
{
/* This will open an existing file or open a new file if the file
   doesnot exists
*/
	_hFile = CreateFile("saved.rul",
						GENERIC_WRITE | GENERIC_READ,
						FILE_SHARE_READ | FILE_SHARE_WRITE,
						NULL,
						OPEN_ALWAYS,
						NULL,
						NULL);

	/* If unable to obtain the handle values*/
	if(_hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	
	return TRUE;		// File has been opened succesfully
}
//******************************************************
// This will move the file pointer to the end of the file so that 
// it can be easily added to the file

DWORD CAddRuleDlg::GotoEnd(void)
{
	DWORD val;

	DWORD size = GetFileSize(_hFile,NULL);
	if(size == 0)
		return size;
	val = SetFilePointer(_hFile,0,NULL,FILE_END);

	/* If unable to set the file pointer to the end of the file */
 	if(val == 0)
	{
		MessageBox("Unable to set file pointer");
		return GetLastError();
	}
	return val;
}

/* This code will save the data into the file which is given by the parameter*/

DWORD CAddRuleDlg::SaveFile(char*  str)
{
	DWORD   bytesWritten;
	/* Try to write the string passed as parameter to the file and if any 
		error occurs return the appropriate values
	*/
	DWORD	_len =  strlen(str);
	if(WriteFile(_hFile, str, _len, &bytesWritten, NULL) == 0)
	{
		MessageBox("Unalbe to write to the file\n");
		return FALSE;
	}
	return TRUE;
}

/* This function will close the existing file */
BOOL CAddRuleDlg::CloseFile()
{
	if(!_hFile)
	{
	//	MessageBox("File handle does not exist");
		return FALSE;
	}

// if there is an appropriate handle then close it and return app values
    else{
		if(CloseHandle(_hFile) != 0)
		{
			return TRUE;
		}
		else 
			return FALSE;
	}
}