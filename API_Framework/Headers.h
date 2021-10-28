#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <stdlib.h>



using namespace std;

#include "Struct.h"
#include "Enum.h"
#include "Constant.h"
#include "Define.h"
#include "Bitmap.h"

#pragma comment(lib, "msimg32.lib")


extern HWND g_hWnd;



template <typename T>
inline void Safe_Delete(T& _pObj)
{
	if (_pObj)
	{
		delete _pObj;
		_pObj = nullptr;
	}
}