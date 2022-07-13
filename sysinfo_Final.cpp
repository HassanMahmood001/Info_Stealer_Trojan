#include <stdio.h>
#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "user32.lib")

#include <iostream>
#include <ctime>
#include <Lmcons.h>
using namespace std;


void DisplayDriveTypes()
{
   TCHAR szDrives[MAX_PATH+1];
   DWORD dwLen = GetLogicalDriveStrings(MAX_PATH, szDrives);
   TCHAR* pLetter = szDrives;
   while(*pLetter)
   {
      UINT nType = GetDriveType(pLetter);
      printf(("Drive %c: is "), *pLetter);
      switch(nType)
      {
        case DRIVE_FIXED:
           printf(("Fixed Drive.\n") );
           break;
   
        case DRIVE_CDROM:
           printf(("CD/DVD Drive.\n") );
           break;
        
        // Process other types
     }
 
     while(*++pLetter) ;  // Notice Semi-colon!
     pLetter++;
   }
}

void DisplayDriveStrings()
{
   TCHAR szDrives[MAX_PATH+1];
  
   GetLogicalDriveStrings(MAX_PATH, szDrives);

   TCHAR* pLetter = szDrives;
   while(*pLetter)
   {
     printf(("Drive %s present\n"), pLetter);
     // _tprintf( _T("Drive %c: present\n"), *pLetter);

     // Find the null terminator for this string
     while(*++pLetter) ;  // Notice Semi-colon!
  
     // And the next *possible* drive letter,
     // Or get the termination of all drive letters.
     pLetter++;
  }
}

void DisplayDrives()
{
   DWORD dwDrivesMap = GetLogicalDrives();

   // Start with A: drive
   char cDrive='A';
   
   for (DWORD dwBitMask = 1; dwDrivesMap != 0;)
   {
      if (dwDrivesMap & dwBitMask)
      {
         printf(("%c: drive present\n"), cDrive);

        // Discard this bit from DrivesMap
        dwDrivesMap &= ~dwBitMask;
      }
  
      // Next letter
      cDrive++;
   
     // Move to next (1, 2, 4, 8..32...128...)
     dwBitMask *= 2 ; // OR dwBitMask <<= 1; 
   }
}

void DisplayDriveSizes()
{
   TCHAR szDrives[MAX_PATH+1];
   DWORD dwLen = GetLogicalDriveStrings(MAX_PATH, szDrives);
   TCHAR* pLetter = szDrives;

   ULARGE_INTEGER liFree, liTotal;
   while(*pLetter)
   {
      //  Get size, ignoring disk-quotas.
      GetDiskFreeSpaceEx(pLetter, NULL, &liTotal, &liFree);

      // Display information
      printf (("Drive %c: has\n\tBytes Total: %I64u (%.2f GB)\n \tBytes Available: %I64u (%.2f GB)\n\n")
                
                 ,*pLetter, 
                 liTotal.QuadPart, liTotal.QuadPart / (float)(1<<30), 
                 liFree.QuadPart, liFree.QuadPart/(float)(1<<30) );

   
      while(*++pLetter);  
      pLetter++;
   }
}
void DisplayVolumeInformations()
{
   TCHAR szVolume[MAX_PATH+1];
   TCHAR szFileSystem[MAX_PATH+1]; 
 
   DWORD dwSerialNumber, dwMaxLen, dwSystemFlags;
  
   // Same stuff!
   TCHAR szDrives[MAX_PATH+1];
   DWORD dwLen = GetLogicalDriveStrings(MAX_PATH, szDrives);
   TCHAR* pLetter = szDrives;

   BOOL bSuccess;
  
   while(*pLetter)
   {
      bSuccess = GetVolumeInformation(pLetter, // The source
                         szVolume, MAX_PATH,   // Volume Label (LABEL)
                         &dwSerialNumber,&dwMaxLen, // Serial Number (VOL)
                         &dwSystemFlags, 
                         szFileSystem, MAX_PATH); // File System (NTFS, FAT...)

      if(bSuccess)
      {
         printf(("Information about volume %c:\n"), *pLetter);
        
         // LABEL command
         printf(("\tVolume Label: %s\n"), szVolume);
        
         // Standard formal to display serial number (VOL command)
         printf(("\tSerial Number: %X-%X\n"), 
                     HIWORD(dwSerialNumber), LOWORD(dwSerialNumber));

         // File-System
         printf(("\tFile System: %s\n\n"), szFileSystem);
      }
      else
      {
        printf (("Cannot retrieve Volume information for %s\n\n"), pLetter);
      }
    
      while(*++pLetter) ;  // Notice Semi-colon!
      pLetter++;
   }
}

void DisplayMonitorResolution()
{
   int nWidth = GetSystemMetrics(SM_CXSCREEN);
   int nHeight = GetSystemMetrics(SM_CYSCREEN);

   printf(("Current Resolution is - Width: %d, Height: %d"), nWidth, nHeight);
   // Current Resolution is - Width: 1920, Height: 1080
}

void DisplayWindowsVersion()
{
 DWORD dwWinVer;
 dwWinVer = GetVersion();

 
 printf (("\n\nWindows version: %d.%d.%d"),
            LOBYTE(LOWORD(dwWinVer)), HIBYTE(LOWORD(dwWinVer)),  // LoWord
            HIWORD(dwWinVer));
}

void DisplayWindowsVersionEx()
{
   OSVERSIONINFOEX osvInfo ={0}; 
   osvInfo.dwOSVersionInfoSize = sizeof(osvInfo);
 
   // Need to typecast, function takes OSVERSIONINFO
   GetVersionEx( (OSVERSIONINFO*)&osvInfo );


   printf(("\n\nBuild: %d\n"), osvInfo.dwBuildNumber);

   printf(("\nProduct Type: ") );

   switch(osvInfo.wProductType)
   {
      case VER_NT_WORKSTATION:
           printf(("Workstation\n") );
           break;
 
      case VER_NT_SERVER:
           printf(("Server\n") );
           break;
 
      case VER_NT_DOMAIN_CONTROLLER:
          printf(("Domain Controller\n") );
          break;
   }
}


int main()
{
 

TCHAR name [ UNLEN + 1 ];
DWORD size = UNLEN + 1;

if (GetUserName( (TCHAR*)name, &size ))
wcout << L"Hello User, " << name << L"!";
else
cout << "\nHello, unnamed person!\n";

TCHAR nameBuf[MAX_COMPUTERNAME_LENGTH + 2];
DWORD nameBufSize;

nameBufSize = sizeof nameBuf - 1;
if (GetComputerName(nameBuf, &nameBufSize) == TRUE) {
printf(("\n\nYour computer name is %s\n"), nameBuf);
}

printf("%s\n", getenv("\nUSERPROFILE"));  // Print user's home directory.

DisplayWindowsVersion();
printf("\n");
DisplayWindowsVersionEx();

SYSTEM_INFO siSysInfo;

   // Copy the hardware information to the SYSTEM_INFO structure. 

   GetSystemInfo(&siSysInfo); 

   // Display the contents of the SYSTEM_INFO structure. 

   printf("Hardware information: \n");  
   printf("  OEM ID: %u\n", siSysInfo.dwOemId);
   printf("  Number of processors: %u\n", 
      siSysInfo.dwNumberOfProcessors); 
   printf("  Page size: %u\n", siSysInfo.dwPageSize); 
   printf("  Processor type: %u\n", siSysInfo.dwProcessorType); 
   printf("  Minimum application address: %lx\n", 
      siSysInfo.lpMinimumApplicationAddress); 
   printf("  Maximum application address: %lx\n", 
      siSysInfo.lpMaximumApplicationAddress); 
   printf("  Active processor mask: %u\n", 
      siSysInfo.dwActiveProcessorMask); 
printf("\n");
DisplayDrives();
printf("\n");
DisplayDriveStrings();
printf("\n");
DisplayDriveTypes();
printf("\n");
DisplayDriveSizes();
printf("\n");
DisplayVolumeInformations();
printf("\n");
DisplayMonitorResolution();
printf("\n");

system("sysinfo_Final.exe > Info.txt");
system("systeminfo");

exit(0);
}
