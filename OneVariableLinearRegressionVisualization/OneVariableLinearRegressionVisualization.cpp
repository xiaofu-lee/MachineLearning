
#include "framework.h"
#include "OneVariableLinearRegressionVisualization.h"
#include "LinearRegressionAlgorithm.h"
#include<stdio.h>
#include <vector>
#include <time.h>

#define DATA_SIZE 250

#define MAX_LOADSTRING 100

using namespace std;

typedef LRESULT(CALLBACK* MsgProc)(HWND hWnd, WPARAM wParam, LPARAM lParam);
typedef struct _WMSG {
	UINT message;
	MsgProc msgProc;
}WMSG;

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
vector<WMSG> wMsgVector;					    // 消息
Data* mData = nullptr;
LinearRegressionAlgorithm* lra = nullptr;

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
VOID				InitMsgPro();
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    OnWinCreate(HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK    OnWinCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK    OnWinPaint(HWND hWnd, WPARAM wParam, LPARAM lParam);
VOID				Paint(HDC hdc, PAINTSTRUCT ps);

//VOID CALLBACK TimerProcedure(HWND hWnd, UINT message, UINT_PTR uTimerID, DWORD lParam);
DWORD WINAPI WinCreate(LPVOID lpThreadParameter);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此处放置代码。
	srand((unsigned int)time(0));
	mData = new Data(DATA_SIZE);
	lra = new LinearRegressionAlgorithm(0.0000000001);
	InitMsgPro();

	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_ONEVARIABLELINEARREGRESSIONVISUALIZATION, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ONEVARIABLELINEARREGRESSIONVISUALIZATION));

	MSG msg;

	// 主消息循环:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ONEVARIABLELINEARREGRESSIONVISUALIZATION));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL/*MAKEINTRESOURCEW(IDC_ONEVARIABLELINEARREGRESSIONVISUALIZATION)*/;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//SetTimer(hWnd, 1, 500, TimerProcedure);

	return TRUE;
}

VOID InitMsgPro()
{
	WMSG wCreateWMSG;
	wCreateWMSG.message = WM_CREATE;
	wCreateWMSG.msgProc = OnWinCreate;
	wMsgVector.push_back(wCreateWMSG);

	WMSG wComWMSG;
	wComWMSG.message = WM_COMMAND;
	wComWMSG.msgProc = OnWinCommand;
	wMsgVector.push_back(wComWMSG);

	WMSG wPaintWMSG;
	wPaintWMSG.message = WM_PAINT;
	wPaintWMSG.msgProc = OnWinPaint;
	wMsgVector.push_back(wPaintWMSG);
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	vector<WMSG>::iterator it;
	for (it = wMsgVector.begin(); it != wMsgVector.end(); it++)
	{
		if (message == it->message) {
			return it->msgProc(hWnd, wParam, lParam);
		}
	}

	switch (message)
	{
	case WM_KEYDOWN: {CreateThread(
		NULL,
		0,
		WinCreate,
		hWnd,
		0,
		(DWORD*)0);
		break; }
	case WM_ERASEBKGND: {break; }
	case WM_DESTROY: {/*KillTimer(hWnd, 1);*/ PostQuitMessage(0); break; }
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

DWORD WINAPI WinCreate(LPVOID lpThreadParameter)
{
	HWND hWnd = (HWND)lpThreadParameter;
	// 训练
	while (true)
	{
		Sleep(8);
		lra->GradientDescentAlgorithm(*mData);
		//UpdateWindow(hWnd);
		InvalidateRect(hWnd, NULL, true);
	}
	return 0;
}

//VOID CALLBACK TimerProcedure(HWND hWnd, UINT message, UINT_PTR uTimerID, DWORD lParam)
//{
//	 //训练
//	while (true)
//	{
//		lra->GradientDescentAlgorithm(*mData);
//		InvalidateRect(hWnd, NULL, true);
//		UpdateWindow(hWnd);
//	}
//}

// WM_CREATE
LRESULT CALLBACK OnWinCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//AnimateWindow(hWnd, 1000, AW_CENTER);
	//InvalidateRect(hWnd, NULL, true);
	return 0;
}

// WM_COMMAND
LRESULT CALLBACK OnWinCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

// WM_PAINT
LRESULT CALLBACK OnWinPaint(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	// PAINTSTRUCT 绘图结构体，存储目标窗口可以绘图的客户端区域(client area)
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps); // DC(可画图的内存对象) 的句柄
	// TODO: 在此处添加使用 hdc 的任何绘图代码...
	Paint(hdc, ps);
	EndPaint(hWnd, &ps);
	return 0;
}

// 绘制散点图
void PaintFunction(HDC hdc, PAINTSTRUCT ps)
{
	HPEN hpen; // 画笔
	hpen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
	hpen = (HPEN)SelectObject(hdc, hpen);

	for (size_t i = 0; i < mData->trainDataVectorSize; i++)
	{
		double x = mData->trainDataVector[i];
		double y = mData->realValueVector[i];
		SetPixel(hdc, x + ps.rcPaint.right / 2, ps.rcPaint.bottom - 10 - y, RGB(255, 0, 0));
	}

	hpen = (HPEN)SelectObject(hdc, hpen);
	DeleteObject(hpen);
}

VOID Paint(HDC hdc, PAINTSTRUCT ps)
{
	HDC mdc = CreateCompatibleDC(0);
	SetBkMode(mdc, TRANSPARENT);
	//SetBkColor(mdc, RGB(0, 0, 0));
	HBITMAP bmp = CreateCompatibleBitmap(hdc, ps.rcPaint.right, ps.rcPaint.bottom);
	bmp = (HBITMAP)SelectObject(mdc, bmp);

	HBRUSH hbrush = CreateSolidBrush(RGB(255, 255, 255));// 画刷
	FillRect(mdc, &(ps.rcPaint), hbrush);

	int x = 10;
	int y = ps.rcPaint.bottom - 160;

#define MAX 80
#define _UNICODE
	wchar_t  BUFF[MAX];

	ZeroMemory(BUFF, MAX);
	swprintf(BUFF, MAX, L"一元线性回归梯度下降可视化");
	TextOutW(mdc, x, y, BUFF, lstrlenW(BUFF));

	ZeroMemory(BUFF, MAX);
	swprintf(BUFF, MAX, L"假设模型 y = %.2f + %.2f * x", mData->thetaParamVector[0], mData->thetaParamVector[1]);
	TextOutW(mdc, x, y + 20, BUFF, lstrlenW(BUFF));

	ZeroMemory(BUFF, MAX);
	swprintf(BUFF, MAX, L"初始化参数 theta[0] = %f, mtheta[1] = %f", lra->thetaParamVector[0], lra->thetaParamVector[1]);
	TextOutW(mdc, x, y + 40, BUFF, lstrlenW(BUFF));

	double xMin = mData->getMin();
	double yMin = lra->predict(xMin);
	ZeroMemory(BUFF, MAX);
	swprintf(BUFF, MAX, L"训练数据集最小数据 xMin = %f, yMin = %f", xMin, yMin);
	TextOutW(mdc, x, y + 60, BUFF, lstrlenW(BUFF));

	double xMax = mData->getMax();
	double yMax = lra->predict(xMax);
	ZeroMemory(BUFF, MAX);
	swprintf(BUFF, MAX, L"训练数据集最大数据 xMax = %f, yMax = %f", xMax, yMax);
	TextOutW(mdc, x, y + 80, BUFF, lstrlenW(BUFF));

	ZeroMemory(BUFF, MAX);
	swprintf(BUFF, MAX, L"X坐标偏移 %d", ps.rcPaint.right / 2);
	TextOutW(mdc, x, y + 100, BUFF, lstrlenW(BUFF));

	ZeroMemory(BUFF, MAX);
	swprintf(BUFF, MAX, L"请按任意键开始训练");
	TextOutW(mdc, x, y + 120, BUFF, lstrlenW(BUFF));

	MoveToEx(mdc, xMin + ps.rcPaint.right / 2, ps.rcPaint.bottom - 10 - yMin, NULL);
	LineTo(mdc, xMax + ps.rcPaint.right / 2, ps.rcPaint.bottom -10 - yMax);

	PaintFunction(mdc, ps);

	BitBlt(hdc, 0, 0, ps.rcPaint.right, ps.rcPaint.bottom, mdc, 0, 0, SRCCOPY);
	bmp = (HBITMAP)SelectObject(mdc, bmp);
	DeleteObject(bmp);
	DeleteDC(mdc);
}
