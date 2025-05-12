#include "pch.h"
//#include <Windows.h> 
//#include <iostream>
//#include "vlc.h" 
//#include <conio.h> 
//std::string Unicode2Utf8(const std::wstring& strIn)
//{
//	std::string str;
//	int length = ::WideCharToMultiByte(CP_UTF8, 0, strIn.c_str(), strIn.size(), NULL, 0, NULL, NULL);
//	str.resize(length + 1);
//			     ::WideCharToMultiByte(CP_UTF8, 0, strIn.c_str(), strIn.size(), (LPSTR)str.c_str(), length, NULL, NULL);
//	return str;
//}
//int main() {
//	int argc = 1;
//	char* argv[2];
//	argv[0] = (char*)"--ignore-config";//多字节转 Unicode，再转 utf-8 
//	libvlc_instance_t* vlc_ins = libvlc_new(argc, argv); //std::string path = Unicode2Utf8(L"股市讨论.mp4"); 
//														 //libvlc_media_t* media = libvlc_media_new_path(vlc_ins, path.c_str()); 
//	std::string path = Unicode2Utf8(L"file:///1.mp4");
//	libvlc_media_t* media = libvlc_media_new_location(vlc_ins, path.c_str());
//	libvlc_media_player_t* player = libvlc_media_player_new_from_media(media);
//	
//	//libvlc_media_player_set_hwnd(Player, GetDlgItem(IDC_STATIC_VIDEO)->m_hWnd;);
//	//libvlc_media_player_set_hwnd(player, /*::GetDesktopWindow()*/ AfxGetApp()->m_pMainWnd->m_hWnd);
//	do {
//		int ret = libvlc_media_player_play(player);
//		if (ret == -1)
//		{
//			printf("error found!\r\n"); break;
//		}
//		int vol = -1; //只有 media 解析加载完成，才会有下面的参数 
//		while (vol == -1) {
//			Sleep(10);
//			vol = libvlc_audio_get_volume(player);
//		}
//		printf("volume is %d\r\n", vol);
//		libvlc_audio_set_volume(player, 100);
//		libvlc_time_t tm = libvlc_media_player_get_length(player);
//		printf("%02d:%02d:%02d.%03d\r\n", int(tm / 3600000), int(tm / 60000) % 60, int(tm / 1000) % 60, int(tm) % 1000);
//		int width = libvlc_video_get_width(player);
//		int height = libvlc_video_get_height(player);
		//printf("width=%d height=%d\r\n", width, height);
//		while (!_kbhit())
//		{
//			printf("%f%%\r", 100.0 * libvlc_media_player_get_position(player));
//			Sleep(500);
//		}
//		getchar();
//		libvlc_media_player_pause(player);
//		getchar();
//		libvlc_media_player_play(player);
//		getchar();
//		libvlc_media_player_stop(player);
//	} while (0);
//	libvlc_media_player_release(player);
//	libvlc_media_release(media);
//	libvlc_release(vlc_ins);
//	return 0;
//}