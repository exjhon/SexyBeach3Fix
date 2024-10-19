
// SexyBeach3FixDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "SexyBeach3Fix.h"
#include "SexyBeach3FixDlg.h"
#include "afxdialogex.h"
#include <windows.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <Shellapi.h>
#include <sstream>
#include <iomanip>
#include <vector>
#include <winbase.h>
#include <tchar.h>
#include <shlwapi.h>
#include <tlhelp32.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSexyBeach3FixDlg 对话框
CSexyBeach3FixDlg::CSexyBeach3FixDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEXYBEACH3FIX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSexyBeach3FixDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditResult); // Add DDX for the edit control
}

BEGIN_MESSAGE_MAP(CSexyBeach3FixDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CSexyBeach3FixDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CSexyBeach3FixDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CSexyBeach3FixDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CSexyBeach3FixDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CSexyBeach3FixDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON1, &CSexyBeach3FixDlg::OnBnClickedExecuteAll)
	ON_BN_CLICKED(IDCANCEL, &CSexyBeach3FixDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSexyBeach3FixDlg 消息处理程序
BOOL CSexyBeach3FixDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

    // 请求管理员权限
    if (!IsUserAnAdmin())
    {
        RequestAdminPrivileges();
        ExitProcess(0);
    }
	// 默认选择DXVK的选项
	((CButton*)GetDlgItem(IDC_RADIO6))->SetCheck(TRUE); 


    // 获取当前应用程序的路径
    TCHAR szPath[MAX_PATH];
    GetModuleFileName(NULL, szPath, MAX_PATH);
    CString strAppPath(szPath);
    int nPos = strAppPath.ReverseFind('\\');
    CString strFolderPath = strAppPath.Left(nPos + 1);

    // 检查是否存在主程序文件
    CString strAExePath = strFolderPath + _T("SexyBeach3PlusCN.exe");
    BOOL bAExeExists = PathFileExists(strAExePath);
    CString strBExePath = strFolderPath + _T("Sexyビーチ3Plus.exe");
    BOOL bBExeExists = PathFileExists(strBExePath);
    CString strCExePath = strFolderPath + _T("Sexyビーチ3.exe");
    BOOL bCExeExists = PathFileExists(strCExePath);
    CString strDExePath = strFolderPath + _T("Sexy Beach 3.exe");
    BOOL bDExeExists = PathFileExists(strDExePath);
    // 如果不存在，则显示错误消息
    if (!bAExeExists && !bBExeExists && !bCExeExists && !bDExeExists)
    {
        MessageBox(_T("未找到性感沙滩3主程序，请勿在压缩包里直接运行该程序，\n解压后把本程序放到性感沙滩3游戏目录里运行！\n如果是用于其他游戏，请无视该提醒。\n因为未找到性感沙滩3，专用于性感沙滩3的相关功能已禁用。"), _T("警告"), MB_ICONWARNING);
        GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO8)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO9)->EnableWindow(FALSE);
        return FALSE;
    }
    else {
        //默认修改兼容性
        ((CButton*)GetDlgItem(IDC_RADIO8))->SetCheck(TRUE);
    }
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSexyBeach3FixDlg::OnPaint()
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
HCURSOR CSexyBeach3FixDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
BOOL InstallVCDX(const CString& programPath, const CString& arguments) {
    // 构建命令行
    CString commandLine = _T("\"") + programPath + _T("\" ") + arguments;

    // 创建进程
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;
    if (!CreateProcess(NULL, commandLine.GetBuffer(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        return FALSE;
    }

    // 等待进程退出
    WaitForSingleObject(pi.hProcess, INFINITE);

    // 获取进程退出代码
    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);

    // 关闭进程句柄
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // 返回安装结果
    return (exitCode == 0);
}

//杀死性感沙滩3主程序
bool TerminateSB3Process() {
    const wchar_t* processName = L"SexyBeach3PlusCN.exe"; // 这里的 L 前缀表示宽字符字符串
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32W pEntry;
    pEntry.dwSize = sizeof(pEntry);
    BOOL hRes = Process32FirstW(hSnapShot, &pEntry); // 这里的函数名 Process32FirstW
    while (hRes) {
        if (wcscmp(pEntry.szExeFile, processName) == 0) { // 这里的函数名 wcscmp
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0, (DWORD)pEntry.th32ProcessID);
            if (hProcess != NULL) {
                TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
                CloseHandle(hSnapShot);
                return true;
            }
        }
        hRes = Process32NextW(hSnapShot, &pEntry); // 这里的函数名 Process32NextW
    }
    CloseHandle(hSnapShot);
    return false;
}

bool DeleteFolderFiles(const CString& folderPath) {
    // 构建搜索文件夹的路径
    CString searchPath = folderPath + _T("\\*.*");

    // 初始化查找
    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile(searchPath, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        return false;
    }
    // 遍历文件夹中的文件并删除
    do {
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            // 删除文件
            CString filePath = folderPath + _T("\\") + findData.cFileName;
            DeleteFile(filePath);

        }
    } while (FindNextFile(hFind, &findData));

    // 关闭查找句柄
    FindClose(hFind);

    // 删除文件夹
    if (!RemoveDirectory(folderPath)) return false;
    return true;
}
bool ExtractZip(const CString& zipFilePath, const CString& destFolderPath) {
    // 构建解压命令行
    CString commandLine = _T("powershell -Command \"Expand-Archive -Path '") + zipFilePath + _T("' -DestinationPath '") + destFolderPath + _T("'\"");

    // 创建进程
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;
    if (!CreateProcess(NULL, commandLine.GetBuffer(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "无法启动解压程序" << std::endl;
        return false;
    }

    // 等待进程退出
    WaitForSingleObject(pi.hProcess, INFINITE);

    // 获取进程退出代码
    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);

    // 关闭进程句柄
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // 返回解压结果
    return (exitCode == 0);
}
void FreeRes_ShowError(char* pszText)
{
    LPTSTR szBuffer = new TCHAR[8192];
    ::wsprintf(szBuffer, L"%hs Error[%d]\n", (pszText), ::GetLastError());//宽字符
#ifdef _DEBUG
    ::MessageBox(NULL, szBuffer, _T("ERROR"), MB_OK | MB_ICONERROR);
#endif
}
BOOL FreeMyResource(UINT uiResouceName, char* lpszResourceType, char* lpszSaveFileName)
{
    // 获取程序所在的路径
    TCHAR szModulePath[MAX_PATH];
    GetModuleFileName(NULL, szModulePath, MAX_PATH);
    PathRemoveFileSpec(szModulePath); // 移除文件名，保留目录路径

    // 组合保存文件的完整路径
    CString strSaveFilePath;
    strSaveFilePath.Format(_T("%s\\%s"), szModulePath, CStringW(lpszSaveFileName));

    HRSRC hRsrc = ::FindResource(GetModuleHandle(NULL), MAKEINTRESOURCE(uiResouceName), CStringW(lpszResourceType));
    if (hRsrc == NULL)
    {
        FreeRes_ShowError("FindResource");
        return FALSE;
    }
    DWORD dwSize = ::SizeofResource(NULL, hRsrc);
    if (0 >= dwSize)
    {
        FreeRes_ShowError("SizeofResource");
        return FALSE;
    }
    HGLOBAL hGlobal = ::LoadResource(NULL, hRsrc);
    if (NULL == hGlobal)
    {
        FreeRes_ShowError("LoadResource");
        return FALSE;
    }
    LPVOID lpVoid = ::LockResource(hGlobal);
    if (NULL == lpVoid)
    {
        FreeRes_ShowError("LockResource");
        return FALSE;
    }
    FILE* fp = NULL;
    fopen_s(&fp, CStringA(strSaveFilePath), "wb+"); // CStringA 将 Unicode 字符串转换为 ANSI 字符串
    if (NULL == fp)
    {
        FreeRes_ShowError("fopen");
        return FALSE;
    }
    fwrite(lpVoid, sizeof(char), dwSize, fp);
    fclose(fp);

    return TRUE;
}


void CSexyBeach3FixDlg::OnBnClickedButton1()
{
    Reg1();
    Reg2();
}


void CSexyBeach3FixDlg::OnBnClickedButton2()
{
    // 构建注册表键值
    CString strRegPath = _T("\VirtualStore\\MACHINE\\SOFTWARE\\WOW6432Node\\Illusion\\SexyBeach3Plus\\");

    // 删除注册表项
    LONG lResult = RegDeleteKey(HKEY_CLASSES_ROOT, strRegPath);

    if (lResult == ERROR_SUCCESS)
    {
        AppendToEditCtrl(_T("成功删除错误注册表项。\r\n"));
    }
    else if (lResult == ERROR_FILE_NOT_FOUND)
    {
        AppendToEditCtrl(_T("未找到注册表项 SexyBeach3Plus。\r\n"));
    }
    else
    {
        MessageBox(_T("删除错误注册表项失败。"), _T("错误"), MB_ICONWARNING);
    }
}

void CSexyBeach3FixDlg::OnBnClickedButton3()
{
    CString strExePath;
    GetModuleFileName(NULL, strExePath.GetBuffer(MAX_PATH), MAX_PATH);
    strExePath.ReleaseBuffer();
    strExePath = strExePath.Left(strExePath.ReverseFind('\\')); // 去掉文件名，只保留目录路径

    // 构建源文件路径
    CString strSrcFilePath = strExePath + _T("\\data\\gsd.cfg");
    std::ifstream file(strSrcFilePath, std::ios::binary);

    if (!file) {
        MessageBox(_T("无法打开配置文件。"), _T("错误"), MB_ICONWARNING);
        return; // 遇到错误，立即停止执行
    }
    std::vector<unsigned char> bytes(std::istreambuf_iterator<char>(file), {});

    file.close(); // 关闭文件

    // 修改第21个字节为 0x02
    if (bytes.size() >= 21) {
        bytes[20] = 0x02;
    }
    else {
        MessageBox(_T("查找配置项失败"), _T("错误"), MB_ICONWARNING);
        return; // 遇到错误，立即停止执行
    }

    // 回写并保存文件
    std::ofstream outFile(strSrcFilePath, std::ios::binary);
    if (!outFile) {
        MessageBox(_T("关闭动画再生失败"), _T("错误"), MB_ICONWARNING);
        return; // 遇到错误，立即停止执行
    }

    outFile.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
    outFile.close();

    AppendToEditCtrl(_T("成功关闭动画再生。\r\n"));
}


void CSexyBeach3FixDlg::OnBnClickedButton4()
{
    char szSaveName1[MAX_PATH] = "DirectX9.zip";
    bool bSuccess1 = FreeMyResource(IDR_DXZIP, "MYRES", szSaveName1);
    if (bSuccess1) AppendToEditCtrl(_T("成功释放dx9安装程序。\r\n"));
    else MessageBox(_T("释放dx9安装程序失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
    char szSaveName2[MAX_PATH] = "vcredist_x86.exe";
    bool bSuccess2 = FreeMyResource(IDR_VCX86, "MYRES", szSaveName2);
    if (bSuccess2) AppendToEditCtrl(_T("成功释放VC安装程序。\r\n"));
    else MessageBox(_T("释放VC安装程序失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);

    // 获取程序所在目录路径
    CString strExePath;
    GetModuleFileName(NULL, strExePath.GetBuffer(MAX_PATH), MAX_PATH);
    strExePath.ReleaseBuffer();
    strExePath = strExePath.Left(strExePath.ReverseFind('\\')); // 去掉文件名，只保留目录路径

    // 构建安装程序路径
    CString strVcredistPath = strExePath + _T("\\vcredist_x86.exe");
    // 调用安装函数
    BOOL bSuccess3 = InstallVCDX(strVcredistPath, _T("/q /T:c:\\"));
    // 检查执行结果
    if (bSuccess3) AppendToEditCtrl(_T("成功安装驱动程序VCRedist。\r\n"));
    else  MessageBox(_T("安装驱动程序VCRedist失败。"), _T("错误"), MB_ICONWARNING);

    CString strZipFilePath = strExePath + _T("\\DirectX9.zip");
    CString strDestFolderPath = strExePath;
    // 解压 DirectX9.zip 到程序所在目录
    if (ExtractZip(strZipFilePath, strDestFolderPath)) AppendToEditCtrl(_T("成功解压dx9安装程序。\r\n"));
    else {
        MessageBox(_T("解压dx9安装程序失败。"), _T("错误"), MB_ICONWARNING);
    }

    // 调用安装函数
    CString strDxwebsetupPath = strExePath + _T("\\DirectX9\\DXSETUP.exe");
    BOOL bSuccess4 = InstallVCDX(strDxwebsetupPath, _T("/silent"));

    // 检查执行结果
    if (bSuccess4) AppendToEditCtrl(_T("成功安装驱动程序DirectX。\r\n"));
    else  MessageBox(_T("安装驱动程序DirectX失败。"), _T("错误"), MB_ICONWARNING);

    // 删除文件
    CleanQudong();
    // 清除文件夹内的所有文件
    CString strFolderPath = strExePath + _T("\\DirectX9");
    if (DeleteFolderFiles(strFolderPath)) AppendToEditCtrl(_T("成功安装所有驱动程序。\r\n"));
    else MessageBox(_T("DX9安装文件清除失败。"), _T("错误"), MB_ICONWARNING);

}

void CSexyBeach3FixDlg::OnBnClickedButton5()
{
    // 检查每个单选按钮的状态
    int nRadio1State = ((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck();
    int nRadio2State = ((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck();
    int nRadio3State = ((CButton*)GetDlgItem(IDC_RADIO3))->GetCheck();
    int nRadio4State = ((CButton*)GetDlgItem(IDC_RADIO4))->GetCheck();
    int nRadio5State = ((CButton*)GetDlgItem(IDC_RADIO5))->GetCheck();
    int nRadio6State = ((CButton*)GetDlgItem(IDC_RADIO6))->GetCheck();
    int nRadio7State = ((CButton*)GetDlgItem(IDC_RADIO7))->GetCheck();
    int nRadio8State = ((CButton*)GetDlgItem(IDC_RADIO8))->GetCheck();
    int nRadio9State = ((CButton*)GetDlgItem(IDC_RADIO9))->GetCheck();
    int nRadio10State = ((CButton*)GetDlgItem(IDC_RADIO9))->GetCheck();

    //先把沙滩3杀了
    TerminateSB3Process();

    // 获取程序所在目录路径
    CString strExePath;
    GetModuleFileName(NULL, strExePath.GetBuffer(MAX_PATH), MAX_PATH);
    strExePath.ReleaseBuffer();
    strExePath = strExePath.Left(strExePath.ReverseFind('\\')); // 去掉文件名，只保留目录路径

    // 构建源文件路径
    CString strSrcFilePath;
    // 构建目标文件路径
    CString strDestFilePath;

    // 根据单选按钮的状态执行相应的功能
    if (nRadio1State == BST_CHECKED)
    {      
        // 删除文件
        CleantheFolder();
        // 复制文件
        char szSaveName[MAX_PATH] = "d3d9.dll";
        bool bSuccess = FreeMyResource(IDR_1_DLL, "MYRES", szSaveName);
        if (bSuccess) AppendToEditCtrl(_T("成功安装d3d9补丁。\r\n"));
        else MessageBox(_T("安装d3d9补丁失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
    }
    else if (nRadio2State == BST_CHECKED)
    {
        // 删除文件
        CleantheFolder();
        // 复制文件
        char szSaveName[MAX_PATH] = "d3d9.dll";
        bool bSuccess = FreeMyResource(IDR_2_DLL, "MYRES", szSaveName);
        if (bSuccess) AppendToEditCtrl(_T("成功安装d3d9补丁。\r\n"));
        else MessageBox(_T("安装d3d9补丁失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
    }
    else if (nRadio3State == BST_CHECKED)
    {
        // 删除文件
        CleantheFolder();
        // 复制文件
        char szSaveName[MAX_PATH] = "d3d9.dll";
        bool bSuccess = FreeMyResource(IDR_3_DLL, "MYRES", szSaveName);
        if (bSuccess) AppendToEditCtrl(_T("成功安装d3d9补丁。\r\n"));
        else MessageBox(_T("安装d3d9补丁失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
    }
    else if (nRadio10State == BST_CHECKED)
    {
        // 删除文件
        CleantheFolder();
        // 复制文件
        char szSaveName[MAX_PATH] = "d3d9.dll";
        bool bSuccess = FreeMyResource(IDR_4_DLL, "MYRES", szSaveName);
        if (bSuccess) AppendToEditCtrl(_T("成功安装d3d9补丁。\r\n"));
        else MessageBox(_T("安装d3d9补丁失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
    }
    else if (nRadio4State == BST_CHECKED)
    {
        // 删除文件
        CleantheFolder();
        // 复制文件
        char szSaveName1[MAX_PATH] = "D3D8.dll";
        bool bSuccess = FreeMyResource(IDR_DG86D3D8, "MYRES", szSaveName1);
        if (bSuccess) AppendToEditCtrl(_T("安装dgvoodoo(1/6)...\r\n"));
        else MessageBox(_T("安装D3D8.dll失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
        char szSaveName2[MAX_PATH] = "D3D9.dll";
        bSuccess = FreeMyResource(IDR_DG86D3D9, "MYRES", szSaveName2);
        if (bSuccess) AppendToEditCtrl(_T("安装dgvoodoo(2/6)...\r\n"));
        else MessageBox(_T("安装D3D9.dll失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
        char szSaveName3[MAX_PATH] = "D3DImm.dll";
        bSuccess = FreeMyResource(IDR_DG86D3DIMM, "MYRES", szSaveName3);
        if (bSuccess) AppendToEditCtrl(_T("安装dgvoodoo(3/6)...\r\n"));
        else MessageBox(_T("安装D3DImm.dll失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
        char szSaveName4[MAX_PATH] = "DDraw.dll";
        bSuccess = FreeMyResource(IDR_DG86DDRAW, "MYRES", szSaveName4);
        if (bSuccess) AppendToEditCtrl(_T("安装dgvoodoo(4/6)...\r\n"));
        else MessageBox(_T("安装DDraw.dll失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
        char szSaveName5[MAX_PATH] = "dgVoodoo.conf";
        bSuccess = FreeMyResource(IDR_DG86CFG, "MYRES", szSaveName5);
        if (bSuccess) AppendToEditCtrl(_T("安装dgvoodoo(5/6)...\r\n"));
        else MessageBox(_T("安装dgVoodoo.conf失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
        char szSaveName6[MAX_PATH] = "dgVoodooCpl.exe";
        bSuccess = FreeMyResource(IDR_DG86EXE, "MYRES", szSaveName6);
        if (bSuccess) AppendToEditCtrl(_T("安装dgvoodoo成功\r\n"));
        else MessageBox(_T("安装dgVoodooCpl.exe失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
    }
    else if (nRadio5State == BST_CHECKED)
    {
        // 删除文件
        CleantheFolder();

        // 复制文件
        char szSaveName1[MAX_PATH] = "D3D9.dll";
        bool bSuccess = FreeMyResource(IDR_DG64D3D9, "MYRES", szSaveName1);
        if (bSuccess) AppendToEditCtrl(_T("安装dgvoodoo(1/3)...\r\n"));
        else MessageBox(_T("安装D3D9.dll失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
        char szSaveName2[MAX_PATH] = "dgVoodoo.conf";
        bSuccess = FreeMyResource(IDR_DG64CFG, "MYRES", szSaveName2);
        if (bSuccess) AppendToEditCtrl(_T("安装dgvoodoo(2/3)...\r\n"));
        else MessageBox(_T("安装dgVoodoo.conf失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
        char szSaveName3[MAX_PATH] = "dgVoodooCpl.exe";
        bSuccess = FreeMyResource(IDR_DG64EXE, "MYRES", szSaveName3);
        if (bSuccess) AppendToEditCtrl(_T("安装dgvoodoo成功\r\n"));
        else MessageBox(_T("安装dgVoodooCpl.exe失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
        }
    else if (nRadio6State == BST_CHECKED)
    {
        // 删除文件
        CleantheFolder();

        // 复制文件
        char szSaveName0[MAX_PATH] = "d3d8.dll";
        bool bSuccess = FreeMyResource(IDR_X32D3D8, "MYRES", szSaveName0);
        if (bSuccess) AppendToEditCtrl(_T("安装DXVK(1/5)...\r\n"));
        else MessageBox(_T("安装d3d8.dll失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
        char szSaveName1[MAX_PATH] = "d3d9.dll";
        bSuccess = FreeMyResource(IDR_X32D3D9, "MYRES", szSaveName1);
        if (bSuccess) AppendToEditCtrl(_T("安装DXVK(2/5)...\r\n"));
        else MessageBox(_T("安装d3d9.dll失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
        char szSaveName2[MAX_PATH] = "d3d10core.dll";
        bSuccess = FreeMyResource(IDR_X32D3D10, "MYRES", szSaveName2);
        if (bSuccess) AppendToEditCtrl(_T("安装DXVK(3/5)...\r\n"));
        else MessageBox(_T("安装d3d10core.dll失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
        char szSaveName3[MAX_PATH] = "d3d11.dll";
        bSuccess = FreeMyResource(IDR_X32D3D11, "MYRES", szSaveName3);
        if (bSuccess) AppendToEditCtrl(_T("安装DXVK(4/5)...\r\n"));
        else MessageBox(_T("安装d3d11.dll失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
        char szSaveName4[MAX_PATH] = "dxgi.dll";
        bSuccess = FreeMyResource(IDR_X32DXGI, "MYRES", szSaveName4);
        if (bSuccess) AppendToEditCtrl(_T("安装DXVK成功。\r\n"));
        else MessageBox(_T("安装dxgi.dll失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
        }
    else if (nRadio7State == BST_CHECKED)
    {
        // 删除文件
        CleantheFolder();

        // 复制文件
        char szSaveName0[MAX_PATH] = "d3d8.dll";
        bool bSuccess = FreeMyResource(IDR_X64D3D8, "MYRES", szSaveName0);
        if (bSuccess) AppendToEditCtrl(_T("安装DXVK(1/5)...\r\n"));
        else MessageBox(_T("安装d3d8.dll失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
        char szSaveName1[MAX_PATH] = "d3d9.dll";
        bSuccess = FreeMyResource(IDR_X64D3D9, "MYRES", szSaveName1);
        if (bSuccess) AppendToEditCtrl(_T("安装DXVK(2/5)...\r\n"));
        else MessageBox(_T("安装d3d9.dll失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
        char szSaveName2[MAX_PATH] = "d3d10core.dll";
        bSuccess = FreeMyResource(IDR_X64D3D10, "MYRES", szSaveName2);
        if (bSuccess) AppendToEditCtrl(_T("安装DXVK(3/5)...\r\n"));
        else MessageBox(_T("安装d3d10core.dll失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
        char szSaveName3[MAX_PATH] = "d3d11.dll";
        bSuccess = FreeMyResource(IDR_X64D3D11, "MYRES", szSaveName3);
        if (bSuccess) AppendToEditCtrl(_T("安装DXVK(4/5)...\r\n"));
        else MessageBox(_T("安装d3d11.dll失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
        char szSaveName4[MAX_PATH] = "dxgi.dll";
        bSuccess = FreeMyResource(IDR_X64DXGI, "MYRES", szSaveName4);
        if (bSuccess) AppendToEditCtrl(_T("安装DXVK成功。\r\n"));
        else MessageBox(_T("安装dxgi.dll失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);
        }
    if (nRadio8State == BST_CHECKED)
    {
        // 复制文件
        char szSaveName1[MAX_PATH] = "jrxon.bat";
        bool bSuccess = FreeMyResource(IDR_JRXON, "MYRES", szSaveName1);
        if (bSuccess) AppendToEditCtrl(_T("释放修改兼容性的批处理文件...\r\n"));
        else MessageBox(_T("释放修改兼容性的批处理文件失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);


        CString strBatchFilePath = strExePath + _T("\\jrxon.bat");

        SHELLEXECUTEINFO sei = { sizeof(sei) };
        sei.lpVerb = _T("runas"); // 使用管理员权限运行
        sei.lpFile = strBatchFilePath;
        sei.lpParameters = NULL;
        sei.lpDirectory = strExePath;
        sei.nShow = SW_SHOWNORMAL;

        if (!ShellExecuteEx(&sei)) {
            DWORD dwError = GetLastError();
            if (dwError == ERROR_CANCELLED) {
                // 用户取消了 UAC 提示
                MessageBox(_T("用户取消了请求"), _T("错误"), MB_ICONWARNING);
            }
            else {
                // 其他错误
                MessageBox(_T("无法执行批处理文件"), _T("错误"), MB_ICONWARNING);
            }
        }
        else AppendToEditCtrl(_T("修改兼容性成功。\r\n"));
     }
    else if (nRadio9State == BST_CHECKED)
    {
        // 复制文件
        char szSaveName1[MAX_PATH] = "jrxoff.bat";
        bool bSuccess = FreeMyResource(IDR_JRXOFF, "MYRES", szSaveName1);
        if (bSuccess) AppendToEditCtrl(_T("释放修改兼容性的批处理文件...\r\n"));
        else MessageBox(_T("释放修改兼容性的批处理文件失败，请以管理员权限运行本补丁。"), _T("错误"), MB_ICONWARNING);

        CString strBatchFilePath = strExePath + _T("\\jrxoff.bat");
        SHELLEXECUTEINFO sei = { sizeof(sei) };
        sei.lpVerb = _T("runas"); // 使用管理员权限运行
        sei.lpFile = strBatchFilePath;
        sei.lpParameters = NULL;
        sei.lpDirectory = strExePath;
        sei.nShow = SW_SHOWNORMAL;

        if (!ShellExecuteEx(&sei)) {
            DWORD dwError = GetLastError();
            if (dwError == ERROR_CANCELLED) {
                // 用户取消了 UAC 提示
                MessageBox(_T("用户取消了请求"), _T("错误"), MB_ICONWARNING);
            }
            else {
                // 其他错误
                MessageBox(_T("无法执行批处理文件"), _T("错误"), MB_ICONWARNING);
            }
        }
        else AppendToEditCtrl(_T("修改兼容性成功。\r\n"));
    }
}

void CSexyBeach3FixDlg::OnBnClickedExecuteAll()
{
	ExecuteAllFunctions(); // Execute all functionalities

}

void CSexyBeach3FixDlg::ExecuteAllFunctions()
{
	OnBnClickedButton1(); // Execute functionality for button 1
	OnBnClickedButton2(); // Execute functionality for button 2
	OnBnClickedButton3(); // Execute functionality for button 3
	OnBnClickedButton4(); // Execute functionality for button 4
	OnBnClickedButton5(); // Execute functionality for button 5

	// Show completion dialog
    AppendToEditCtrl(_T("一键修复完成。\r\n"));
	MessageBox(_T("一键修复完成"));

}

void CSexyBeach3FixDlg::Reg1() {
    // 获取程序所在目录路径
    CString strExePath;
    GetModuleFileName(NULL, strExePath.GetBuffer(MAX_PATH), MAX_PATH);
    strExePath.ReleaseBuffer();
    strExePath = strExePath.Left(strExePath.ReverseFind('\\')); // 去掉文件名，只保留目录路径

    // 构建注册表键值
    CString strRegPath = _T("SOFTWARE\\Illusion\\");
    CString strValueName;
    CString strValueData;

    // 创建或打开 Illusion 文件夹
    HKEY hKeyIllusion;
    if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, strRegPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, NULL, &hKeyIllusion, NULL) == ERROR_SUCCESS)
    {
        AppendToEditCtrl(_T("Illusion 文件夹创建或打开成功。\r\n"));
    }
    else
    {
        MessageBox(_T("Illusion 文件夹创建或打开失败。"), _T("错误"), MB_ICONWARNING);
        return;
    }

    //SexyBeach3
    strRegPath = _T("SOFTWARE\\Illusion\\SexyBeach3\\");
    HKEY hKeySexyBeach3;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, strRegPath, 0, KEY_WRITE | KEY_READ, &hKeySexyBeach3) == ERROR_SUCCESS)
    {
        AppendToEditCtrl(_T("SexyBeach3文件夹已存在，正在更新注册表值。\r\n"));
    }
    else
    {
        if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, strRegPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, NULL, &hKeySexyBeach3, NULL) == ERROR_SUCCESS)
        {
            AppendToEditCtrl(_T("SexyBeach3文件夹创建成功。\r\n"));
        }
        else
        {
            MessageBox(_T("SexyBeach3文件夹创建或打开失败。"), _T("错误"), MB_ICONWARNING);
            return;
        }
    }
    strValueName = _T("INSTALLDIR");
    strValueData = strExePath;
    RegSetValueEx(hKeySexyBeach3, strValueName, 0, REG_SZ, (const BYTE*)strValueData.GetBuffer(), (strValueData.GetLength() + 1) * sizeof(TCHAR));
    strValueName = _T("PRODUCTNAME");
    strValueData = _T("Sexyビーチ3");
    RegSetValueEx(hKeySexyBeach3, strValueName, 0, REG_SZ, (const BYTE*)strValueData.GetBuffer(), (strValueData.GetLength() + 1) * sizeof(TCHAR));
    strValueName = _T("VERSION");
    DWORD dwValueData = 1;
    RegSetValueEx(hKeySexyBeach3, strValueName, 0, REG_DWORD, (const BYTE*)&dwValueData, sizeof(DWORD));

    // SexyBeach3Plus
    strRegPath = _T("SOFTWARE\\Illusion\\SexyBeach3Plus\\");
    HKEY hKeySexyBeach3Plus;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, strRegPath, 0, KEY_WRITE | KEY_READ, &hKeySexyBeach3Plus) == ERROR_SUCCESS)
    {
        AppendToEditCtrl(_T("SexyBeach3Plus文件夹已存在，正在更新注册表值。\r\n"));
    }
    else
    {
        if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, strRegPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, NULL, &hKeySexyBeach3Plus, NULL) == ERROR_SUCCESS)
        {
            AppendToEditCtrl(_T("SexyBeach3Plus文件夹创建成功。\r\n"));
        }
        else
        {
            MessageBox(_T("SexyBeach3Plus文件夹创建或打开失败。"), _T("错误"), MB_ICONWARNING);
            return;
        }
    }
    strValueName = _T("INSTALLDIR");
    strValueData = strExePath;
    RegSetValueEx(hKeySexyBeach3Plus, strValueName, 0, REG_SZ, (const BYTE*)strValueData.GetBuffer(), (strValueData.GetLength() + 1) * sizeof(TCHAR));
    strValueName = _T("PRODUCTNAME");
    strValueData = _T("Sexyビーチ3～キャラクター追加DISC～");
    RegSetValueEx(hKeySexyBeach3Plus, strValueName, 0, REG_SZ, (const BYTE*)strValueData.GetBuffer(), (strValueData.GetLength() + 1) * sizeof(TCHAR));
    strValueName = _T("VERSION");
    RegSetValueEx(hKeySexyBeach3Plus, strValueName, 0, REG_DWORD, (const BYTE*)&dwValueData, sizeof(DWORD));

    // SexyBeach3PlusG
    strRegPath = _T("SOFTWARE\\Illusion\\SexyBeach3PlusG\\");
    HKEY hKeySexyBeach3PlusG;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, strRegPath, 0, KEY_WRITE | KEY_READ, &hKeySexyBeach3PlusG) == ERROR_SUCCESS)
    {
        AppendToEditCtrl(_T("SexyBeach3PlusG文件夹已存在，正在更新注册表值。\r\n"));
    }
    else
    {
        if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, strRegPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, NULL, &hKeySexyBeach3PlusG, NULL) == ERROR_SUCCESS)
        {
            AppendToEditCtrl(_T("SexyBeach3PlusG文件夹创建成功。\r\n"));
        }
        else
        {
            MessageBox(_T("SexyBeach3PlusG文件夹创建或打开失败。"), _T("错误"), MB_ICONWARNING);
            return;
        }
    }
    strValueName = _T("INSTALLDIR");
    strValueData = strExePath;
    RegSetValueEx(hKeySexyBeach3PlusG, strValueName, 0, REG_SZ, (const BYTE*)strValueData.GetBuffer(), (strValueData.GetLength() + 1) * sizeof(TCHAR));
    strValueName = _T("PRODUCTNAME");
    strValueData = _T("SexyBeach3PlusG");
    RegSetValueEx(hKeySexyBeach3PlusG, strValueName, 0, REG_SZ, (const BYTE*)strValueData.GetBuffer(), (strValueData.GetLength() + 1) * sizeof(TCHAR));
    strValueName = _T("VERSION");
    RegSetValueEx(hKeySexyBeach3PlusG, strValueName, 0, REG_DWORD, (const BYTE*)&dwValueData, sizeof(DWORD));

    RegCloseKey(hKeyIllusion);
    RegCloseKey(hKeySexyBeach3);
    RegCloseKey(hKeySexyBeach3Plus);
    RegCloseKey(hKeySexyBeach3PlusG);
    AppendToEditCtrl(_T("注册完成(1/2)...\r\n"));
}
void CSexyBeach3FixDlg::Reg2() {
    // 获取程序所在目录路径
    CString strExePath;
    GetModuleFileName(NULL, strExePath.GetBuffer(MAX_PATH), MAX_PATH);
    strExePath.ReleaseBuffer();
    strExePath = strExePath.Left(strExePath.ReverseFind('\\')); // 去掉文件名，只保留目录路径

    // 构建注册表键值
    CString strRegPath = _T("SOFTWARE\\WOW6432Node\\Illusion\\");
    CString strValueName;
    CString strValueData;

    // 创建或打开 Illusion 文件夹
    HKEY hKeyIllusion;
    if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, strRegPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, NULL, &hKeyIllusion, NULL) == ERROR_SUCCESS)
    {
        AppendToEditCtrl(_T("Illusion 文件夹创建或打开成功。\r\n"));
    }
    else
    {
        MessageBox(_T("Illusion 文件夹创建或打开失败。"), _T("错误"), MB_ICONWARNING);
        return;
    }

    //SexyBeach3
    strRegPath = _T("SOFTWARE\\WOW6432Node\\Illusion\\SexyBeach3\\");
    HKEY hKeySexyBeach3;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, strRegPath, 0, KEY_WRITE | KEY_READ, &hKeySexyBeach3) == ERROR_SUCCESS)
    {
        AppendToEditCtrl(_T("SexyBeach3文件夹已存在，正在更新注册表值。\r\n"));
    }
    else
    {
        if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, strRegPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, NULL, &hKeySexyBeach3, NULL) == ERROR_SUCCESS)
        {
            AppendToEditCtrl(_T("SexyBeach3文件夹创建成功。\r\n"));
        }
        else
        {
            MessageBox(_T("SexyBeach3文件夹创建或打开失败。"), _T("错误"), MB_ICONWARNING);
            return;
        }
    }
    strValueName = _T("INSTALLDIR");
    strValueData = strExePath;
    RegSetValueEx(hKeySexyBeach3, strValueName, 0, REG_SZ, (const BYTE*)strValueData.GetBuffer(), (strValueData.GetLength() + 1) * sizeof(TCHAR));
    strValueName = _T("PRODUCTNAME");
    strValueData = _T("Sexyビーチ3");
    RegSetValueEx(hKeySexyBeach3, strValueName, 0, REG_SZ, (const BYTE*)strValueData.GetBuffer(), (strValueData.GetLength() + 1) * sizeof(TCHAR));
    strValueName = _T("VERSION");
    DWORD dwValueData = 1;
    RegSetValueEx(hKeySexyBeach3, strValueName, 0, REG_DWORD, (const BYTE*)&dwValueData, sizeof(DWORD));

    // SexyBeach3Plus
    strRegPath = _T("SOFTWARE\\WOW6432Node\\Illusion\\SexyBeach3Plus\\");
    HKEY hKeySexyBeach3Plus;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, strRegPath, 0, KEY_WRITE | KEY_READ, &hKeySexyBeach3Plus) == ERROR_SUCCESS)
    {
        AppendToEditCtrl(_T("SexyBeach3Plus文件夹已存在，正在更新注册表值。\r\n"));
    }
    else
    {
        if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, strRegPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, NULL, &hKeySexyBeach3Plus, NULL) == ERROR_SUCCESS)
        {
            AppendToEditCtrl(_T("SexyBeach3Plus文件夹创建成功。\r\n"));
        }
        else
        {
            MessageBox(_T("SexyBeach3Plus文件夹创建或打开失败。"), _T("错误"), MB_ICONWARNING);
            return;
        }
    }
    strValueName = _T("INSTALLDIR");
    strValueData = strExePath;
    RegSetValueEx(hKeySexyBeach3Plus, strValueName, 0, REG_SZ, (const BYTE*)strValueData.GetBuffer(), (strValueData.GetLength() + 1) * sizeof(TCHAR));
    strValueName = _T("PRODUCTNAME");
    strValueData = _T("Sexyビーチ3～キャラクター追加DISC～");
    RegSetValueEx(hKeySexyBeach3Plus, strValueName, 0, REG_SZ, (const BYTE*)strValueData.GetBuffer(), (strValueData.GetLength() + 1) * sizeof(TCHAR));
    strValueName = _T("VERSION");
    RegSetValueEx(hKeySexyBeach3Plus, strValueName, 0, REG_DWORD, (const BYTE*)&dwValueData, sizeof(DWORD));

    // SexyBeach3PlusG
    strRegPath = _T("SOFTWARE\\WOW6432Node\\Illusion\\SexyBeach3PlusG\\");
    HKEY hKeySexyBeach3PlusG;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, strRegPath, 0, KEY_WRITE | KEY_READ, &hKeySexyBeach3PlusG) == ERROR_SUCCESS)
    {
        AppendToEditCtrl(_T("SexyBeach3PlusG文件夹已存在，正在更新注册表值。\r\n"));
    }
    else
    {
        if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, strRegPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, NULL, &hKeySexyBeach3PlusG, NULL) == ERROR_SUCCESS)
        {
            AppendToEditCtrl(_T("SexyBeach3PlusG文件夹创建成功。\r\n"));
        }
        else
        {
            MessageBox(_T("SexyBeach3PlusG文件夹创建或打开失败。"), _T("错误"), MB_ICONWARNING);
            return;
        }
    }
    strValueName = _T("INSTALLDIR");
    strValueData = strExePath;
    RegSetValueEx(hKeySexyBeach3PlusG, strValueName, 0, REG_SZ, (const BYTE*)strValueData.GetBuffer(), (strValueData.GetLength() + 1) * sizeof(TCHAR));
    strValueName = _T("PRODUCTNAME");
    strValueData = _T("SexyBeach3PlusG");
    RegSetValueEx(hKeySexyBeach3PlusG, strValueName, 0, REG_SZ, (const BYTE*)strValueData.GetBuffer(), (strValueData.GetLength() + 1) * sizeof(TCHAR));
    strValueName = _T("VERSION");
    RegSetValueEx(hKeySexyBeach3PlusG, strValueName, 0, REG_DWORD, (const BYTE*)&dwValueData, sizeof(DWORD));

    RegCloseKey(hKeyIllusion);
    RegCloseKey(hKeySexyBeach3);
    RegCloseKey(hKeySexyBeach3Plus);
    RegCloseKey(hKeySexyBeach3PlusG);
    AppendToEditCtrl(_T("注册完成。\r\n"));
}


void CSexyBeach3FixDlg::CleantheFolder()
{
    // 获取程序所在目录路径
    CString strExePath;
    GetModuleFileName(NULL, strExePath.GetBuffer(MAX_PATH), MAX_PATH);
    strExePath.ReleaseBuffer();
    strExePath = strExePath.Left(strExePath.ReverseFind('\\')); // 去掉文件名，只保留目录路径
    // 构建目标文件路径
    CString strDestFilePath;
        // 删除原文件 d3d9.dll（如果存在）
        strDestFilePath = strExePath + _T("\\d3d8.dll");
        if (PathFileExists(strDestFilePath)) DeleteFile(strDestFilePath);
        // 删除原文件 d3d8.dll（如果存在）
        strDestFilePath = strExePath + _T("\\d3d9.dll");
        if (PathFileExists(strDestFilePath)) DeleteFile(strDestFilePath);
        // 删除原文件 D3DImm.dll（如果存在）
        strDestFilePath = strExePath + _T("\\D3DImm.dll");
        if (PathFileExists(strDestFilePath)) DeleteFile(strDestFilePath);
        // 删除原文件 DDraw.dll（如果存在）
        strDestFilePath = strExePath + _T("\\DDraw.dll");
        if (PathFileExists(strDestFilePath)) DeleteFile(strDestFilePath);
        // 删除原文件 dgVoodoo.conf（如果存在）
        strDestFilePath = strExePath + _T("\\dgVoodoo.conf");
        if (PathFileExists(strDestFilePath)) DeleteFile(strDestFilePath);
        // 删除原文件 dgVoodooCpl.exe（如果存在）
        strDestFilePath = strExePath + _T("\\dgVoodooCpl.exe");
        if (PathFileExists(strDestFilePath)) DeleteFile(strDestFilePath);
        // 删除原文件 d3d10core.dll（如果存在）
        strDestFilePath = strExePath + _T("\\d3d10core.dll");
        if (PathFileExists(strDestFilePath)) DeleteFile(strDestFilePath);
        // 删除原文件 d3d11.dll（如果存在）
        strDestFilePath = strExePath + _T("\\d3d11.dll");
        if (PathFileExists(strDestFilePath)) DeleteFile(strDestFilePath);
        // 删除原文件 dxgi.dll（如果存在）
        strDestFilePath = strExePath + _T("\\dxgi.dll");
        if (PathFileExists(strDestFilePath)) DeleteFile(strDestFilePath);
}
void CSexyBeach3FixDlg::CleanQudong()
{
    // 获取程序所在目录路径
    CString strExePath;
    GetModuleFileName(NULL, strExePath.GetBuffer(MAX_PATH), MAX_PATH);
    strExePath.ReleaseBuffer();
    strExePath = strExePath.Left(strExePath.ReverseFind('\\')); // 去掉文件名，只保留目录路径
    // 构建目标文件路径
    CString strDestFilePath;
    // 删除原文件 DirectX9.zip（如果存在）
    strDestFilePath = strExePath + _T("\\DirectX9.zip");
    if (PathFileExists(strDestFilePath)){
        if(!DeleteFile(strDestFilePath)) MessageBox(_T("删除DirectX9.zip失败"), _T("错误"), MB_ICONWARNING);
    }else MessageBox(_T("未找到应清理的DirectX9.zip"), _T("错误"), MB_ICONWARNING);
    // 删除原文件 vcredist_x86.exe（如果存在）
    strDestFilePath = strExePath + _T("\\vcredist_x86.exe");
    if (PathFileExists(strDestFilePath)) {
        if (!DeleteFile(strDestFilePath)) MessageBox(_T("删除DirectX9.zip失败"), _T("错误"), MB_ICONWARNING);
    }
    else MessageBox(_T("未找到应清理的vcredist_x86.exe"), _T("错误"), MB_ICONWARNING);
    
}

void CSexyBeach3FixDlg::AppendToEditCtrl(const CString& strText)
{
	CString strCurrentText;
	m_EditResult.GetWindowText(strCurrentText);
	strCurrentText = strText + _T("\r\n"); // Add new text and a newline character
	m_EditResult.SetWindowText(strCurrentText);
}

void CSexyBeach3FixDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

void CSexyBeach3FixDlg::RequestAdminPrivileges()
{
    // 获取程序路径
    CString strAppPath;
    GetModuleFileName(NULL, strAppPath.GetBuffer(MAX_PATH), MAX_PATH);
    strAppPath.ReleaseBuffer();

    // 准备启动信息
    SHELLEXECUTEINFO shellInfo = { sizeof(SHELLEXECUTEINFO) };
    shellInfo.lpVerb = _T("runas");
    shellInfo.lpFile = strAppPath;
    shellInfo.nShow = SW_SHOWNORMAL;

    // 启动程序，请求管理员权限
    if (!ShellExecuteEx(&shellInfo))
    {
        MessageBox(_T("请求管理员权限失败！"));
    }
}
