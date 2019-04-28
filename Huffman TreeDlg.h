
// Huffman TreeDlg.h : header file
//

#pragma once

#include <algorithm> 

///////////////////////////////////////////////////


struct sym
{
	char symbol;
	int count;
	int weight;
	int parent_id = 0;
	int child1_id = -1;
	int child2_id = -1;
	int id;
	/*char parent;
	char child1;
	char child2;*/
	bool isJoined = false;
};



// CHuffmanTreeDlg dialog
class CHuffmanTreeDlg : public CDialogEx
{
// Construction
public:
	CHuffmanTreeDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HUFFMANTREE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_SourceText;
	int m_Result;
	afx_msg void OnBnClickedButton1();
	CTreeCtrl m_ctrlTree;
	int MakeTree(CArray<sym, sym>& arr, int index, HTREEITEM* tree_items);
};
