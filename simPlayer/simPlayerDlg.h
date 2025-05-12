
// simPlayerDlg.h: 头文件
//

#pragma once
#include "vlc.h"
#include <string>

// CsimPlayerDlg 对话框
class CsimPlayerDlg : public CDialogEx
{
// 构造
public:
	CsimPlayerDlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CsimPlayerDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIMPLAYER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_slidVol;
	CSliderCtrl m_slidRate;
	afx_msg void OnBnClickedBtnPlay();//播放or暂停
	afx_msg void OnBnClickedButtonStop();//停止
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);//音量条
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);//进度条
	
	libvlc_instance_t* vlc_ins; //媒体句柄
	std::string m_path;//路径
	libvlc_media_t* media ;//播放器
	libvlc_media_player_t* player ;//播放对象
	afx_msg void OnTimer(UINT_PTR nIDEvent);

};
