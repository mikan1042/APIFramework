#pragma once


const DWORD KEY_UP		= 0x00000001;
const DWORD KEY_DOWN	= 0x00000002;
const DWORD KEY_LEFT	= 0x00000004;
const DWORD KEY_RIGHT	= 0x00000008;
const DWORD KEY_ESCAPE	= 0x00000010;
const DWORD KEY_SHIFT   = 0x00000020;
const DWORD KEY_UP_SHIFT = 0x00000040;

// ** 마우스 좌측 키 입력 확인.


const int WindowsWidth = 1280;
const int WindowsHeight = 720;


// 사운드 
#define SOUND_VOLUME 0.05f
#define SOUND_VOLUME_MAX 1.0f
#define SOUND_VOLUME_MIN 0.0f