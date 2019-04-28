// Huffman TreeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Huffman Tree.h"
#include "Huffman TreeDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <algorithm> 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHuffmanTreeDlg dialog



CHuffmanTreeDlg::CHuffmanTreeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HUFFMANTREE_DIALOG, pParent)
	, m_SourceText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHuffmanTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_SourceText);
	DDX_Control(pDX, IDC_TREE, m_ctrlTree);
}

BEGIN_MESSAGE_MAP(CHuffmanTreeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CHuffmanTreeDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CHuffmanTreeDlg message handlers

BOOL CHuffmanTreeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHuffmanTreeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHuffmanTreeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHuffmanTreeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


///////////////////////////////////////////////////////////


void InsertionSort(CArray<sym, sym>& arr, int size);
void JoinCouples(CArray<sym, sym>& arr, int& treeSize, int);



void CHuffmanTreeDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CArray<sym, sym> Arr;
	sym tmp;

	UpdateData(TRUE);

	char symbol, alph[26];
	bool isUnique = true;
	int k = 0;
	int length = m_SourceText.GetLength();
	int ID = 0;

	for (int i = 0; i < length; i++) 
	{
			int count = 1;
			symbol = m_SourceText.GetAt(i);
			isUnique = true;

			for (int j = 0; j < 26; ++j) 
			{
				if (symbol == alph[j]) 
				{ 
					isUnique = false; 
					break;
				}
			}

			if (isUnique) 
			{
				for (int j = i + 1; j < length; ++j) 
				{
					if (symbol == m_SourceText.GetAt(j))
					{
						count++;
					}
				}
				tmp.symbol = symbol;
				tmp.count = count;
				tmp.weight = count;
				tmp.id = ID;
				Arr.Add(tmp);
				alph[k] = symbol;
				++k;
				++ID;
			}
	}

	alph[k] = '\0';


	InsertionSort(Arr, Arr.GetSize());
	JoinCouples(Arr, k, ID);
	





	HTREEITEM* tree_items = new HTREEITEM[k + 1];
	
	int i = 0;
	for (i = 0; i < Arr.GetSize(); i++)
	{
		if (Arr[i].parent_id == 0)
		{
			CString c = 0;
			if (Arr[i].weight >= 10 && Arr[i].weight < 100)
			{
				char real = (Arr[i].weight / 10) + 48;
				char mod = (Arr[i].weight % 10) + 48;
				c = c + real + mod;
			}
			else
			{
				c = c + char(Arr[i].weight + 48);
			}
			
			HTREEITEM root = m_ctrlTree.InsertItem(c + CString(Arr.GetAt(i).symbol), TVI_ROOT);
			int j = Arr[i].id;
			tree_items[j] = root;
			break;
		}
	}

	MakeTree(Arr,i, tree_items);

	delete[] tree_items;
	UpdateData(FALSE);
}



void InsertionSort(CArray<sym, sym>& arr, int size)
{
	for (int i = 1; i < size; i++) 
	{
		int j = i;
		if ((!(arr[j].isJoined)) && (!(arr[j- 1].isJoined)))
		{
			while (arr[j].count < arr[j - 1].count) 
			{
				std::swap(arr[j], arr[j - 1]);
				j--;
				if (j == 0)
				{
					break;
				}
			}
		}
	}
}



void JoinCouples(CArray<sym, sym>& arr, int& treeSize, int ID) 
{
	int i = 0;
	int number = arr.GetSize() - 1;
	//Find symbols with same weight into couples

	while(i<arr.GetSize()) 
	{
		for (int j = i + 1; j < arr.GetSize(); j++) 
		{
			if ((!arr[i].isJoined) && !arr[j].isJoined && (arr[i].weight == arr[j].weight))
			{
				sym tmp;
				tmp.id = ID++;
				tmp.symbol = '~';
				tmp.weight = arr[i].weight + arr[j].weight;
				tmp.child1_id = arr[i].id;
				tmp.child2_id = arr[j].id;
				/*tmp.child1 = arr[i].symbol;
				tmp.child2 = arr[j].symbol;*/
				tmp.isJoined = false;
				
				arr[i].isJoined = true; // iranc el petq chi mtcnel sortavorman mej
				arr[j].isJoined = true;
				/*arr[i].parent = tmp.symbol;
				arr[j].parent = tmp.symbol;*/
				arr[i].parent_id = tmp.id;
				arr[j].parent_id = tmp.id;
				arr.Add(tmp);
				++treeSize;
				--number;
			}
			else break;
		}
		++i;
	}


	//Count odd symbols' numbers
	int count = 0;
	for (int j = 0; j < arr.GetSize(); j++)
	{
		if (!arr[j].isJoined)
		{
			++count;
		}
	}

	InsertionSort(arr, arr.GetSize());

	number = arr.GetSize() - 1;
	//Join odd symbols
	while (count != 1)
	{
		for (int i = 0; i < arr.GetSize(); i++) 
		{
			for (int j = i + 1; j < arr.GetSize(); j++) 
			{
				if (((!arr[i].isJoined) && !arr[j].isJoined))
				{
					sym tmp;
					tmp.id = ++ID;
					tmp.symbol = '~';
					tmp.weight = arr[i].weight + arr[j].weight;
					tmp.child1_id = arr[i].id;
					tmp.child2_id = arr[j].id;
					/*tmp.child1 = arr[i].symbol;
					tmp.child2 = arr[j].symbol;*/
					tmp.isJoined = false;

					arr[i].isJoined = true; // iranc el petq chi mtcnel sortavorman mej
					arr[j].isJoined = true;
					/*arr[i].parent = tmp.symbol;
					arr[j].parent = tmp.symbol;*/
					arr[i].parent_id = tmp.id;
					arr[j].parent_id = tmp.id;
					arr.Add(tmp);

					--count;
					++treeSize;
				}
			}
			InsertionSort(arr, arr.GetSize());
		}
	}
}


int CHuffmanTreeDlg::MakeTree(CArray<sym, sym>& arr, int index, HTREEITEM* tree_items)
{
	UpdateData(true);

	sym c = arr[index];
	int a = arr[index].child1_id;
	int b = arr[index].child2_id;
	if (a == -1 && b == -1)
	{
		return 0;
	}
	else 
	{
		for (int i = 0; i < arr.GetSize(); ++i)
		{
			if (arr[i].id == a)
			{
				int j = arr[i].parent_id;
				CString c = 0;
				if (arr[i].weight >= 10 && arr[i].weight < 100)
				{
					char real = (arr[i].weight / 10) + 48;
					char mod = (arr[i].weight % 10) + 48;
					c = c + real + mod;
				}
				else
				{
					c = c + char(arr[i].weight + 48);
				}
				HTREEITEM tmp = m_ctrlTree.InsertItem(c + CString(arr.GetAt(i).symbol), tree_items[j]);
				j = arr[i].id;
				tree_items[j] = tmp;
				MakeTree(arr, i, tree_items);
			}

			if (arr[i].id == b)
			{
				int j = arr[i].parent_id;
				CString c = 0;
				if (arr[i].weight >= 10 && arr[i].weight < 100)
				{
					char real = (arr[i].weight / 10) + 48;
					char mod = (arr[i].weight % 10) + 48;
					c = c + real + mod;
				}
				else
				{
					c = c + char(arr[i].weight + 48);
				}
				HTREEITEM tmp = m_ctrlTree.InsertItem(c + CString(arr.GetAt(i).symbol), tree_items[j]);
				int k = arr[i].id;
				tree_items[k] = tmp;
				MakeTree(arr, i, tree_items);
			}
		}
	}
	

	UpdateData(false);
}
