#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProcChild(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProcChild2(HWND, UINT, WPARAM, LPARAM);


HWND f, c;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("HelloWin");
	static char szAppNameChild[] = TEXT("HelloWinChild");
	HWND hwnd;
	HWND hwndChild;
	HWND hwndChild2;
	MSG msg;
	WNDCLASS wndclass;
	WNDCLASS wndclassChild;
	WNDCLASS wndclassChild2;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName,
		TEXT("The hellow program father"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	f = hwnd;
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//创建子窗口
	wndclassChild.style = CS_HREDRAW | CS_VREDRAW;
	wndclassChild.lpfnWndProc = WndProcChild;
	wndclassChild.cbClsExtra = 0;
	wndclassChild.cbWndExtra = 0;
	wndclassChild.hInstance = hInstance;
	wndclassChild.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclassChild.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclassChild.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclassChild.lpszMenuName = NULL;
	wndclassChild.lpszClassName = szAppNameChild;

	if (!RegisterClass(&wndclassChild))
	{
		MessageBox(NULL, TEXT("This program requires windows NT!"),
			szAppNameChild, MB_ICONERROR);
		return 0;
	}

	wndclassChild2.style = CS_HREDRAW | CS_VREDRAW;
	wndclassChild2.lpfnWndProc = WndProcChild2;
	wndclassChild2.cbClsExtra = 0;
	wndclassChild2.cbWndExtra = 0;
	wndclassChild2.hInstance = hInstance;
	wndclassChild2.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclassChild2.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclassChild2.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclassChild2.lpszMenuName = NULL;
	wndclassChild2.lpszClassName = TEXT("child2");
	if (!RegisterClass(&wndclassChild2))
	{
		MessageBox(NULL, TEXT("This program requires windows NT!"),
			TEXT("child2"), MB_ICONERROR);
		return 0;
	}




	//关联子父级窗口

	//设置了WS_CHILD 属性会让窗口之间出现绘制区域关联的情况，
	//子窗口的绘制区域不能超过父窗口，可以超过边界

	//取消设置WS_CHILD 不会有绘制区域的限制，只会有同步隐藏显示的机制，同时子窗口会在父窗口的前面

	//注意**只有严格的子父级的关系才能实现父窗口销毁的时候子窗口一并销毁，如果只设置了parentWnd,没有WS_CHILD我们认为不是严格的子父级关系。

	//在严格的子父级窗口关系之下，最小化子窗口会让子窗口缩小到父窗口的右下角，非严格则缩小到系统桌面的右下角。

	//非严格状态下两个子窗口的移动不会产生影响，严格状态下会产生影响，因为移动没有触发WM_PAINT消息

	//SetParent(c, f); 此函数会实现设置WS_CHILD一样的效果，但是不会影响窗口的属性标位，如果需要保持一致那么就需要自己设置
	
	//严格和非严格子父级情况下最小化父窗口不会触发子窗口的最小化消息
	hwndChild = CreateWindow(szAppNameChild,
		TEXT("The hellow program Child"),
		WS_OVERLAPPEDWINDOW | WS_CHILD,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		300,
		200,
		hwnd,
		NULL,
		hInstance,
		NULL);

	//以下为：非严格子父级关系
	//hwndChild = CreateWindow(szAppNameChild,
	//	TEXT("The hellow program Child"),
	//	WS_OVERLAPPEDWINDOW ,
	//	CW_USEDEFAULT,
	//	CW_USEDEFAULT,
	//	300,
	//	200,
	//	hwnd,
	//	NULL,
	//	hInstance,
	//	NULL);


	c = hwndChild;
	ShowWindow(hwndChild, iCmdShow);
	UpdateWindow(hwndChild);
	//子窗口创建结束

	//**WS_CLIPSIBLINGS 属性设置之后就会减小Z序，其他同属窗口在其上方

	//用于创建两个子窗口，观察是否有影响
	hwndChild2 = CreateWindow(TEXT("child2"),
		TEXT("child2"),
		WS_OVERLAPPEDWINDOW ,
		300,
		300,
		300,
		200,
		hwnd,
		NULL,
		hInstance,
		NULL);
	ShowWindow(hwndChild2, iCmdShow);
	UpdateWindow(hwndChild2);




	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//将按键消息转换为字符消息，这样WM_CHAR中可以获得输入的键盘字符
		DispatchMessage(&msg);
	}
	return msg.wParam;

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	CHAR chCharCode;

	switch (message)
	{
	case WM_CREATE:
		return 0;

	case WM_LBUTTONDOWN:
		SetParent(c, f);//后设置parentWnd,
		MessageBox(NULL, TEXT("这是父窗口，左键按下!,设置父子窗口关系"),
			"父窗口", MB_OKCANCEL);
		return 0;

	case WM_RBUTTONDOWN:
		MessageBox(NULL, TEXT("这是父窗口，右键按下!"),
			"父窗口", MB_OKCANCEL);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, TEXT("Hello, 这是父窗口!"), -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		EndPaint(hwnd, &ps);
		return 0;
	case WM_SYSCOMMAND:
		switch (wParam)
		{
		case SC_MINIMIZE:
			MessageBox(NULL, TEXT("最小化父窗口!"),
				"最小化父窗口", MB_OKCANCEL);
			break;

		default:
			break;
		}
		break;
	case WM_CHAR:
		chCharCode = (TCHAR)wParam;
		return 0;
	case WM_DESTROY:
		//PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProcChild(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;

	switch (message)
	{
	case WM_CREATE:
		return 0;

	case WM_LBUTTONDOWN:
		MessageBox(NULL, TEXT("这是子窗口，左键按下!"),
			"子窗口", MB_OKCANCEL);
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rect);

		DrawText(hdc, TEXT("Hello, 这是子窗口!"), -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		EndPaint(hwnd, &ps);
		return 0;

	case WM_SYSCOMMAND:
		switch (wParam)
		{
		case SC_MINIMIZE:
			MessageBox(NULL, TEXT("最小化子1!"),
				"最小化子1窗口", MB_OKCANCEL);
			break;

		default:
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProcChild2(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;

	switch (message)
	{
	case WM_CREATE:
		return 0;

	case WM_LBUTTONDOWN:
		MessageBox(NULL, TEXT("这是子窗口2，左键按下!"),
			"子窗口2", MB_OKCANCEL);
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rect);

		DrawText(hdc, TEXT("Hello, 22这是子窗口2!"), -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		EndPaint(hwnd, &ps);
		return 0;


	case WM_SYSCOMMAND:
		switch (wParam)
		{
		case SC_MINIMIZE:
			MessageBox(NULL, TEXT("最小化子2!"),
				"最小化子2窗口", MB_OKCANCEL);
			break;

		default:
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
