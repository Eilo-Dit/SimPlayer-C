
// simPlayerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "simPlayer.h"
#include "simPlayerDlg.h"
#include "afxdialogex.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


std::string Unicode2Utf8(const std::wstring& strIn);

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CsimPlayerDlg 对话框


CsimPlayerDlg::CsimPlayerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SIMPLAYER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsimPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLD_VOL, m_slidVol);
	DDX_Control(pDX, IDC_SLD_RATE, m_slidRate);
}

BEGIN_MESSAGE_MAP(CsimPlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_PLAY, &CsimPlayerDlg::OnBnClickedBtnPlay)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON3, &CsimPlayerDlg::OnBnClickedButtonStop)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CsimPlayerDlg 消息处理程序

BOOL CsimPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//初始媒体对象
	int argc = 1;
	char* argv[2];
	argv[0] = (char*)"--ignore-config";//多字节转 Unicode，再转 utf-8 
	vlc_ins = libvlc_new(argc, argv); 
	//设置定时器
	SetTimer(24, 500, NULL);

	//m_path=Unicode2Utf8(L"file:///1.mp4");
	//media = libvlc_media_new_location(vlc_ins, m_path.c_str());
	//player = libvlc_media_player_new_from_media(media);
	//libvlc_media_player_set_hwnd(player, GetDlgItem(IDC_VIDEO)->m_hWnd);
	//libvlc_media_player_play(player);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CsimPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CsimPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CsimPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//析构函数
CsimPlayerDlg::~CsimPlayerDlg()
{
	//KillTimer(24);

	if(player)libvlc_media_player_release(player);
	if(media)libvlc_media_release(media);
	if(vlc_ins)libvlc_release(vlc_ins);
}

//“播放”按钮
void CsimPlayerDlg::OnBnClickedBtnPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	CString cs,path;
	static std::wstring op;
	GetDlgItemText(IDC_BTN_PLAY, cs);
	GetDlgItemText(IDC_EDIT_PATH,path);
	//配置文件路径
	std::wstring pp = L"file:///"; 
	pp += path.GetBuffer(); 
	//加载”新“视频文件
	if(op!=pp){
		m_path = Unicode2Utf8(pp);
		media = libvlc_media_new_location(vlc_ins, m_path.c_str());
		player = libvlc_media_player_new_from_media(media);
		libvlc_media_player_set_hwnd(player, GetDlgItem(IDC_VIDEO)->m_hWnd);
		op = pp;
	}

	if (cs == L"播放") {
		cs = L"暂停";
		libvlc_media_player_play(player);
	}
	else
	{
		cs = L"播放";
		libvlc_media_player_pause(player);
	}
	SetDlgItemText(IDC_BTN_PLAY, cs);
}

//音量调节
void CsimPlayerDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString cs;
	int vol = 100 - m_slidVol.GetPos();
	cs.Format(L"%d", vol);
	libvlc_audio_set_volume(player, vol);
	SetDlgItemText(IDC_VOL_NUM, cs);

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


//进度调节
void CsimPlayerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString cs,ct;
	int re = m_slidRate.GetPos();

	if (player) {
		libvlc_time_t tm = libvlc_media_player_get_length(player) / 1000;
		float tn = tm/100.0*re;//拖动位置秒数
		TRACE("%02d:%02d:%02d", int(tn / 3600), int(tn / 60), (int)tn % 60);
		libvlc_media_player_set_position(player,tn/tm);//单位:百分比
		ct.Format(L"%02d:%02d:%02d", int(tn / 3600), int(tn / 60), (int)tn % 60);
		cs.Format(L"%02d:%02d:%02d", int(tm / 3600), int(tm / 60), (int)tm % 60);
		cs = ct + L"/" + cs;
		SetDlgItemText(IDC_RATE_TXT, cs);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

//停止
void CsimPlayerDlg::OnBnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码
	if(player){
		libvlc_media_player_stop(player);
		SetDlgItemText(IDC_BTN_PLAY, L"播放");
	}
}
//格式转换
std::string Unicode2Utf8(const std::wstring& strIn)
{
	std::string str;
	int length = ::WideCharToMultiByte(CP_UTF8, 0, strIn.c_str(), strIn.size(), NULL, 0, NULL, NULL);
	str.resize(length + 1);
	::WideCharToMultiByte(CP_UTF8, 0, strIn.c_str(), strIn.size(), (LPSTR)str.c_str(), length, NULL, NULL);
	return str;
}

//定时器
void CsimPlayerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString cs,ct;
	if (nIDEvent == 24) {
		if (player) {
			//播放状态
			libvlc_state_t state = libvlc_media_player_get_state(player);
			if (state == libvlc_Ended)//如果播放完毕，则停止
			{
				libvlc_media_player_stop(player);
				SetDlgItemText(IDC_BTN_PLAY, L"播放");
			}
			//获取视频总秒数，视频当前播放百分比
			libvlc_time_t tm =libvlc_media_player_get_length(player)/1000;
					float tn =libvlc_media_player_get_position(player)*100.0;
			tn = tm / 100.0 * tn;
			TRACE("%d\r\n", int((tn / tm) * 100.0));
			ct.Format(L"%02d:%02d:%02d",int(tn / 3600),int(tn / 60),(int)tn%60);
			//cs.Format(L"%02d:%02d:%02d", int(tm / 3600000), int(tm / 60000) % 60, int(tm / 1000) % 60);
			cs.Format(L"%02d:%02d:%02d", int(tm / 3600),int(tm / 60),(int)tm%60);
			cs = ct + L"/" + cs;
			//设置进度文字
			SetDlgItemText(IDC_RATE_TXT,cs);
			//设置进度条
			m_slidRate.SetPos(int((tn / tm) * 100.0));
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}
