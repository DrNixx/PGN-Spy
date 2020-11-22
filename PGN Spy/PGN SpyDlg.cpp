// MIT License
// 
// Copyright(c) 2016 Michael J. Gleason
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "stdafx.h"
#include "PGN Spy.h"
#include "PGN SpyDlg.h"
#include "Analysis.h"
#include "AnalysisDlg.h"
#include "ResultsDlg.h"
#include "ResString.h"
#include "strings/PGN_Spy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
   CAboutDlg();

// Dialog Data
   enum { IDD = IDD_ABOUTBOX };

   protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   virtual BOOL OnInitDialog();

// Implementation
protected:
   DECLARE_MESSAGE_MAP()
public:
   CString m_sCredits;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
, m_sCredits(_T(""))
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Text(pDX, IDC_CREDITS, m_sCredits);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_sCredits = _LSA( IDS_THIS_PROJECT_WOULD_HAVE_BEEN_MUCH_MORE );
   UpdateData(FALSE);

   return TRUE;  // return TRUE  unless you set the focus to a control
}



// CPGNSpyDlg dialog




CPGNSpyDlg::CPGNSpyDlg(CWnd* pParent /*=NULL*/)
   : CDialog(CPGNSpyDlg::IDD, pParent)
   , m_sInputFile("")
{
   m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPGNSpyDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Text(pDX, IDC_INPUTANALYSE, m_sInputFile);
   DDX_Text(pDX, IDC_PLAYER, m_vEngineSettings.m_sPlayerName);
   DDX_Text(pDX, IDC_ENGINE, m_vEngineSettings.m_sEnginePath);
   DDX_Text(pDX, IDC_SEARCHDEPTH, m_vEngineSettings.m_iSearchDepth);
   DDV_MinMaxInt(pDX, m_vEngineSettings.m_iSearchDepth, 1, 50);
   DDX_Text(pDX, IDC_BOOKDEPTH, m_vEngineSettings.m_iBookDepth);
   DDV_MinMaxInt(pDX, m_vEngineSettings.m_iBookDepth, 0, 30);
   DDX_Text(pDX, IDC_NUMTHREADS, m_vEngineSettings.m_iNumThreads);
   DDV_MinMaxInt(pDX, m_vEngineSettings.m_iNumThreads, 1, 128);
   DDX_Text(pDX, IDC_MINTIME, m_vEngineSettings.m_iMinTime);
   DDV_MinMaxInt(pDX, m_vEngineSettings.m_iMinTime, 1, 60000);
   DDX_Text(pDX, IDC_MAXTIME, m_vEngineSettings.m_iMaxTime);
   DDV_MinMaxInt(pDX, m_vEngineSettings.m_iMaxTime, 1, 60000);
   DDX_Text(pDX, IDC_HASHSIZE, m_vEngineSettings.m_iHashSize);
   // 0 - default engine value
   DDV_MinMaxInt(pDX, m_vEngineSettings.m_iHashSize, 0, 8192);
   DDX_Text(pDX, IDC_VARIATIONS, m_vEngineSettings.m_iNumVariations);
   DDV_MinMaxInt(pDX, m_vEngineSettings.m_iNumVariations, 1, 10);
}

BEGIN_MESSAGE_MAP(CPGNSpyDlg, CDialog)
   ON_WM_SYSCOMMAND()
   ON_WM_PAINT()
   ON_WM_QUERYDRAGICON()
   //}}AFX_MSG_MAP
   ON_BN_CLICKED(IDC_BROWSEANALYSE, &CPGNSpyDlg::OnBnClickedBrowseanalyse)
   ON_BN_CLICKED(IDC_BROWSEENGINE, &CPGNSpyDlg::OnBnClickedBrowseengine)
   ON_BN_CLICKED(IDC_RUNANALYSIS, &CPGNSpyDlg::OnBnClickedRunanalysis)
   ON_BN_CLICKED(IDC_HELPPLAYER, &CPGNSpyDlg::OnBnClickedHelpplayer)
   ON_BN_CLICKED(IDC_HELPDEPTH, &CPGNSpyDlg::OnBnClickedHelpdepth)
   ON_BN_CLICKED(IDC_HELPBOOKDEPTH, &CPGNSpyDlg::OnBnClickedHelpbookdepth)
   ON_BN_CLICKED(IDC_HELPTHREADS, &CPGNSpyDlg::OnBnClickedHelpthreads)
   ON_BN_CLICKED(IDC_HELPMINTIME, &CPGNSpyDlg::OnBnClickedHelpmintime)
   ON_BN_CLICKED(IDC_HELPMAXTIME, &CPGNSpyDlg::OnBnClickedHelpmaxtime)
   ON_BN_CLICKED(IDC_HELPPHASHSIZE, &CPGNSpyDlg::OnBnClickedHelpphashsize)
   ON_BN_CLICKED(IDC_SAVESETTINGS, &CPGNSpyDlg::OnBnClickedSavesettings)
   ON_BN_CLICKED(IDC_FORCEDMOVEHELP, &CPGNSpyDlg::OnBnClickedForcedmovehelp)
   ON_BN_CLICKED(IDC_UNCLEARPOSITIONHELP, &CPGNSpyDlg::OnBnClickedUnclearpositionhelp)
   ON_BN_CLICKED(IDC_EQUALPOSITIONHELP, &CPGNSpyDlg::OnBnClickedEqualpositionhelp)
   ON_BN_CLICKED(IDC_LOSINGTHRESHOLDHELP, &CPGNSpyDlg::OnBnClickedLosingthresholdhelp)
   ON_BN_CLICKED(IDC_NUMVARIATIONSHELP, &CPGNSpyDlg::OnBnClickedNumvariationshelp)
   ON_BN_CLICKED(IDC_LOADRESULTS, &CPGNSpyDlg::OnBnClickedLoadresults)
END_MESSAGE_MAP()


// CPGNSpyDlg message handlers

BOOL CPGNSpyDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   // Add "About..." menu item to system menu.

   // IDM_ABOUTBOX must be in the system command range.
   ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
   ASSERT(IDM_ABOUTBOX < 0xF000);

   CMenu* pSysMenu = GetSystemMenu(FALSE);
   if (pSysMenu != NULL)
   {
      CString strAboutMenu;
      strAboutMenu.LoadString(IDS_ABOUTBOX);
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

   if (!m_vEngineSettings.LoadSettingsFromRegistry())
      m_vEngineSettings = CEngineSettings(); //failed to load, so restore defaults
   UpdateData(FALSE);

   return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPGNSpyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
   if ((nID & 0xFFF0) == IDM_ABOUTBOX)
   {
      CAboutDlg dlgAbout;
      dlgAbout.DoModal();
   }
   else
   {
      CDialog::OnSysCommand(nID, lParam);
   }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPGNSpyDlg::OnPaint()
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
      CDialog::OnPaint();
   }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPGNSpyDlg::OnQueryDragIcon()
{
   return static_cast<HCURSOR>(m_hIcon);
}

void CPGNSpyDlg::OnBnClickedBrowseanalyse()
{
   if (!UpdateData())
      return;
   CFileDialog vFileDialog(TRUE,"pgn","*.pgn",OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_DONTADDTORECENT,"Portable Game Notation file (*.pgn)|*.pgn|All files (*.*)|*.*||",this);
   if (vFileDialog.DoModal() != IDOK)
      return;
   m_sInputFile = vFileDialog.GetPathName();
   UpdateData(FALSE);
}

void CPGNSpyDlg::OnBnClickedBrowseengine()
{
   if (!UpdateData())
      return;
   CFileDialog vFileDialog(TRUE,"exe","*.exe",OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_DONTADDTORECENT,"Chess Engines (*.exe)|*.exe|All files (*.*)|*.*||",this);
   if (vFileDialog.DoModal() != IDOK)
      return;
   m_vEngineSettings.m_sEnginePath = vFileDialog.GetPathName();
   UpdateData(FALSE);
}

bool CPGNSpyDlg::ConvertFileForAnalysis(CString OUT &sConvertedFile)
{
   sConvertedFile = GetConvertedPGNFilePath();
   CFile vFile;
   if (!vFile.Open(sConvertedFile, CFile::modeCreate | CFile::modeWrite))
   {
      MessageBox(_LSA( IDS_FAILED_TO_CREATE_TEMPORARY_OUTPUT ),_LSA( IDS_PGN_SPY ), MB_ICONEXCLAMATION);
      return false;
   }
   vFile.Close();

   CString sCommandLine = " -Wuci \"-o" + sConvertedFile + "\" \"" + m_sInputFile + "\"";

   PROCESS_INFORMATION vProcessInfo;
   STARTUPINFO vStartupInfo = {0};
   vStartupInfo.cb = sizeof(vStartupInfo);
   vStartupInfo.dwFlags = STARTF_USESHOWWINDOW;
   vStartupInfo.wShowWindow = SW_HIDE;
   if (!CreateProcess(GetConverterFilePath(), sCommandLine.GetBuffer(), NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &vStartupInfo, &vProcessInfo))
   {
      sCommandLine.ReleaseBuffer();
      MessageBox(_LSA( IDS_FAILED_TO_LAUNCH_CONVERTER_PLEASE ),_LSA( IDS_PGN_SPY ), MB_ICONEXCLAMATION);
      return false;
   }
   sCommandLine.ReleaseBuffer();
   WaitForSingleObject(vProcessInfo.hProcess, INFINITE);
   CloseHandle(vProcessInfo.hProcess);
   CloseHandle(vProcessInfo.hThread);

   return true;
}

void CPGNSpyDlg::OnBnClickedRunanalysis()
{
   if (!ValidateSettings())
      return;

   //validate file paths
   if (!PathFileExists(m_sInputFile))
   {
      MessageBox(_LSA( IDS_THE_SPECIFIED_INPUT_FILE_DOES_NOT ), _LSA( IDS_PGN_SPY ), MB_ICONEXCLAMATION);
      return;
   }

   CString sTemporaryFile;
   if (!ConvertFileForAnalysis(sTemporaryFile))
   {
      MessageBox(_LSA( IDS_FAILED_TO_CONVERT_THE_PGN_FILE_INTO_THE ),_LSA( IDS_PGN_SPY ), MB_ICONEXCLAMATION);
      return;
   }

   //file is converted; now process it
   CAnalysisDlg vAnalyserDlg;
   vAnalyserDlg.m_sConvertedPGN = sTemporaryFile;
   vAnalyserDlg.m_vEngineSettings = m_vEngineSettings;
   vAnalyserDlg.DoModal();

   //delete temporary file
   DeleteFile(sTemporaryFile);

   if (vAnalyserDlg.m_avGames.GetSize() == 0)
   {
      MessageBox(_LSA( IDS_NO_RESULTS_TO_DISPLAY ), _LSA( IDS_PGN_SPY ), MB_ICONEXCLAMATION);
      return;
   }
   if (vAnalyserDlg.m_bCancelled)
      return;
   
   //now launch the window to process and display the results
   CResultsDlg vResultsDlg;
   vResultsDlg.m_avGames.Copy(vAnalyserDlg.m_avGames);
   vResultsDlg.m_vEngineSettings = m_vEngineSettings;
   vResultsDlg.DoModal();
}

void CPGNSpyDlg::OnBnClickedSavesettings()
{
   if (!ValidateSettings())
      return;

   if (!m_vEngineSettings.SaveSettingsToRegistry())
      MessageBox(_LSA( IDS_FAILED_TO_SAVE_SETTINGS ), _LSA( IDS_PGN_SPY ), MB_ICONEXCLAMATION);
   else
      MessageBox(_LSA( IDS_SETTINGS_SAVED ), _LSA( IDS_PGN_SPY ), MB_ICONINFORMATION);
}

bool CPGNSpyDlg::ValidateSettings()
{
   if (!UpdateData())
      return false;

   if (m_vEngineSettings.m_iMinTime > m_vEngineSettings.m_iMaxTime)
   {
      MessageBox(_LSA( IDS_THE_MINIMUM_TIME_FOR_ANALYSIS_MUST_NOT ), _LSA( IDS_PGN_SPY ), MB_ICONEXCLAMATION);
      return false;
   }

   if (!PathFileExists(m_vEngineSettings.m_sEnginePath))
   {
      MessageBox(_LSA( IDS_THE_SPECIFIED_ENGINE_DOES_NOT_EXIST ), _LSA( IDS_PGN_SPY ), MB_ICONEXCLAMATION);
      return false;
   }

   SYSTEM_INFO vSysInfo;
   GetSystemInfo(&vSysInfo);
   if (m_vEngineSettings.m_iNumThreads > (int)vSysInfo.dwNumberOfProcessors)
   {
      MessageBox(_LSA( IDS_YOU_HAVE_ENTERED_MORE_THREADS_THAN_THE ), _LSA( IDS_PGN_SPY ), MB_ICONEXCLAMATION);
      return false;
   }

   return true;
}

void CPGNSpyDlg::OnBnClickedHelpplayer()
{
   CString sMessage = _LSA( IDS_IF_PLAYER_NAME_IS_ENTERED_STATISTICS );
   MessageBox(sMessage, _LSA( IDS_PGN_SPY ), MB_ICONINFORMATION);
}

void CPGNSpyDlg::OnBnClickedHelpdepth()
{
   CString sMessage = _LSA( IDS_SPECIFY_THE_MINIMUM_NUMBER_OF_PLIES_TO );
   MessageBox(sMessage, _LSA( IDS_PGN_SPY ), MB_ICONINFORMATION);
}

void CPGNSpyDlg::OnBnClickedHelpbookdepth()
{
   CString sMessage = _LSA( IDS_SPECIFY_THE_NUMBER_OF_OPENING_MOVES_TO );
   MessageBox(sMessage, _LSA( IDS_PGN_SPY ), MB_ICONINFORMATION);
}

void CPGNSpyDlg::OnBnClickedHelpthreads()
{
   CString sMessage = _LSA( IDS_SPECIFY_THE_NUMBER_OF_THREADS_TO_USE );
                      _LSA( IDS_THIS_NUMBER_CAN_BE_ADJUSTED_WHILE );
   MessageBox(sMessage, _LSA( IDS_PGN_SPY ), MB_ICONINFORMATION);
}

void CPGNSpyDlg::OnBnClickedHelpmintime()
{
   CString sMessage = _LSA( IDS_SPECIFY_THE_MINIMUM_TIME_IN );
   MessageBox(sMessage, _LSA( IDS_PGN_SPY ), MB_ICONINFORMATION);
}

void CPGNSpyDlg::OnBnClickedHelpmaxtime()
{
   CString sMessage = _LSA( IDS_SPECIFY_THE_MAXIMUM_TIME_IN );
   MessageBox(sMessage, _LSA( IDS_PGN_SPY ), MB_ICONINFORMATION);
}

void CPGNSpyDlg::OnBnClickedHelpphashsize()
{
   CString sMessage = _LSA( IDS_SPECIFY_THE_SIZE_OF_THE_ENGINE_MEMORY );
   MessageBox(sMessage, _LSA( IDS_PGN_SPY ), MB_ICONINFORMATION);
}

void CPGNSpyDlg::OnBnClickedForcedmovehelp()
{
   CString sMessage = _LSA( IDS_FOR_ETC_ANALYSIS_MOVES_WHERE_THE_NEXT );
   MessageBox(sMessage, _LSA( IDS_PGN_SPY ), MB_ICONINFORMATION);
}

void CPGNSpyDlg::OnBnClickedUnclearpositionhelp()
{
   CString sMessage = _LSA( IDS_FOR_ETC_ANALYSIS_MOVES_WHERE_THE_NEXT1 );
   MessageBox(sMessage, _LSA( IDS_PGN_SPY ), MB_ICONINFORMATION);
}

void CPGNSpyDlg::OnBnClickedEqualpositionhelp()
{
   CString sMessage = _LSA( IDS_POSITIONS_WHERE_NEITHER_SIDE_IS_AHEAD );
   MessageBox(sMessage, _LSA( IDS_PGN_SPY ), MB_ICONINFORMATION);
}

void CPGNSpyDlg::OnBnClickedLosingthresholdhelp()
{
   CString sMessage = _LSA( IDS_POSITIONS_WHERE_THE_PLAYER_BEHIND_BY );
   MessageBox(sMessage, _LSA( IDS_PGN_SPY ), MB_ICONINFORMATION);
}

void CPGNSpyDlg::OnBnClickedNumvariationshelp()
{
   CString sMessage = _LSA( IDS_SPECIFY_THE_NUMBER_OF_TOP_ENGINE_MOVES );
   MessageBox(sMessage, _LSA( IDS_PGN_SPY ), MB_ICONINFORMATION);
}

void CPGNSpyDlg::OnBnClickedLoadresults()
{
   CFileDialog vFileDialog(TRUE, "xml", "*.xml", OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_DONTADDTORECENT, "PGN Spy files (*.xml)|*.xml|All files (*.*)|*.*||", this);
   if (vFileDialog.DoModal() != IDOK)
      return;
   CArray <CGame, CGame> avGames;
   CEngineSettings vEngineSettings;
   if (!LoadGameArrayFromFile(vFileDialog.GetPathName(), avGames, vEngineSettings))
   {
      MessageBox(_LSA( IDS_FAILED_TO_LOAD_GAME_FILE ), _LSA( IDS_PGN_SPY ), MB_ICONEXCLAMATION);
      return;
   }

   CResultsDlg vResultsDlg;
   vResultsDlg.m_avGames.Copy(avGames);
   vResultsDlg.m_vEngineSettings = vEngineSettings;
   vResultsDlg.DoModal();
}
