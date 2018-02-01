#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProcChild(HWND, UINT, WPARAM, LPARAM);


HWND f, c;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("HelloWin");
	static char szAppNameChild[] = TEXT("HelloWinChild");
	HWND hwnd;
	HWND hwndChild;
	MSG msg;
	WNDCLASS wndclass;
	WNDCLASS wndclassChild;

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


	//�����Ӵ���
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

	//�����Ӹ�������

	//������WS_CHILD ���Ի��ô���֮����ֻ�����������������
	//�Ӵ��ڵĻ��������ܳ��������ڣ����Գ����߽�

	//ȡ������WS_CHILD �����л�����������ƣ�ֻ����ͬ��������ʾ�Ļ��ƣ�ͬʱ�Ӵ��ڻ��ڸ����ڵ�ǰ��

	//ע��**ֻ���ϸ���Ӹ����Ĺ�ϵ����ʵ�ָ��������ٵ�ʱ���Ӵ���һ�����٣����ֻ������parentWnd,û��WS_CHILD������Ϊ�����ϸ���Ӹ�����ϵ��

	//���ϸ���Ӹ������ڹ�ϵ֮�£���С���Ӵ��ڻ����Ӵ�����С�������ڵ����½ǣ����ϸ�����С��ϵͳ��������½ǡ�

	//SetParent(c, f); �˺�����ʵ������WS_CHILDһ����Ч�������ǲ���Ӱ�촰�ڵ����Ա�λ�������Ҫ����һ����ô����Ҫ�Լ�����
	hwndChild = CreateWindow(szAppNameChild,
		TEXT("The hellow program Child"),
		WS_OVERLAPPEDWINDOW|WS_CHILD,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		300,
		200,
		hwnd,
		NULL,
		hInstance,
		NULL);

	//����Ϊ�����ϸ��Ӹ�����ϵ
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
	//�Ӵ��ڴ�������

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//��������Ϣת��Ϊ�ַ���Ϣ������WM_CHAR�п��Ի������ļ����ַ�
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
		
		SetParent(c, f);//������parentWnd,

		MessageBox(NULL, TEXT("���Ǹ����ڣ��������!,���ø��Ӵ��ڹ�ϵ"),
			"������", MB_OKCANCEL);
		return 0;

	case WM_RBUTTONDOWN:
		MessageBox(NULL, TEXT("���Ǹ����ڣ��Ҽ�����!"),
			"������", MB_OKCANCEL);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rect);

		DrawText(hdc, TEXT("Hello, ���Ǹ�����!"), -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		EndPaint(hwnd, &ps);
		return 0;

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
		MessageBox(NULL, TEXT("�����Ӵ��ڣ��������!"),
			"�Ӵ���", MB_OKCANCEL);
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rect);

		DrawText(hdc, TEXT("Hello, �����Ӵ���!"), -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		EndPaint(hwnd, &ps);
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}