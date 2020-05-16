// ExeMaker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//////////////////////////////////////////////////////////
//
// Program to make an Exe File
//
//
//
//

#include <stdio.h>
#include <windows.h>

///////////////////////////////////////////////////////////
//   MSDOS stub program  
//
//
//
//

unsigned char msdos_stub_program[256] = {
	0x4D, 0x5A, 0x50, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x0F, 0x00, 0xFF, 0xFF, 0x00, 0x00, 
	0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 
	0xBA, 0x10, 0x00, 0x0E, 0x1F, 0xB4, 0x09, 0xCD, 0x21, 0xB8, 0x01, 0x4C, 0xCD, 0x21, 0x90, 0x90, 
	0x54, 0x68, 0x69, 0x73, 0x20, 0x70, 0x72, 0x6F, 0x67, 0x72, 0x61, 0x6D, 0x20, 0x6D, 0x75, 0x73, 
	0x74, 0x20, 0x62, 0x65, 0x20, 0x72, 0x75, 0x6E, 0x20, 0x75, 0x6E, 0x64, 0x65, 0x72, 0x20, 0x57, 
	0x69, 0x6E, 0x33, 0x32, 0x0D, 0x0A, 0x24, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/////////////////////////////////////////////
//
//
//  PE signature   "PE\-\o"
//
//

unsigned char pe_signature[4] = 
{
	0x50, 0x45, 0x00, 0x00
};

//////////////////////////////////////////////////////////
//
//
//
//
//



/////////////////////////////////////////////////////////////
//
//
//
//
//
//
//
class CExeFileMaker
{
private:
    IMAGE_FILE_HEADER      gimh;         
    IMAGE_OPTIONAL_HEADER  gopthdr;
    IMAGE_DATA_DIRECTORY   gdir[16];
    IMAGE_SECTION_HEADER   gcode_section;
    IMAGE_SECTION_HEADER   gdata_section;
    IMAGE_SECTION_HEADER   empty_section;
private:
	char *ExeData;
    char *AExeData;
private:
	void WriteDosStub()
	{
       memcpy(ExeData,msdos_stub_program,sizeof(msdos_stub_program));
	}
	void WritePeMagic()
	{
       memcpy(ExeData,pe_signature,4); 
	}

	void WriteImageFileHeader()
     {
         memset(&gimh,0,sizeof(gimh)); 
         gimh.Machine = 0x014C;  // Machine is an Intel 386 or above
         gimh.NumberOfSections = 2;  // 2 sections in this image
         gimh.SizeOfOptionalHeader = 224; 
         gimh.Characteristics = 0x0102 ; 
         memcpy(ExeData,&gimh,sizeof(gimh));
     }

	 void WriteImageDataDirectory( HANDLE handle )
     {

       memset(&gdir[0],0,sizeof(IMAGE_DATA_DIRECTORY)*16);
       /////////////////////////////////
       // Pass 1
       // 
       gdir[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress = ?;
       gdir[IMAGE_DIRECTORY_ENTRY_IMPORT].Size = ?; 
     }

	 void WriteImageOptionalHeader()
     {
       memset(&gopthdr,0,sizeof(gopthdr)); 

       //////////////////////////////////////
	   //
	   //  Pass #1
	   //
	   //
	   //
       gopthdr.Magic       =  0x010b;
       gopthdr.SizeOfCode  = 4096; 
       gopthdr.ImageBase  = 0x00400000;
	   gopthdr.SizeOfUninitializedData = 0x0;
	 
	   gopthdr.SectionAlignment = 4096; 
       gopthdr.FileAlignment  = 4096; 
       gopthdr.MajorOperatingSystemVersion = 0x4; 
       gopthdr.MajorSubsystemVersion = 0x4; 
       gopthdr.Subsystem = 0x3;
       gopthdr.DllCharacteristics = 0x0;  // Not a DLL          
       gopthdr.SizeOfStackReserve = 0x100000;         
       gopthdr.SizeOfStackCommit  = 0x1000;         
       gopthdr.SizeOfHeapReserve  = 0x100000;                  
       gopthdr.SizeOfHeapCommit   = 0x1000;                  
       gopthdr.LoaderFlags        = 0x0;         
       gopthdr.NumberOfRvaAndSizes = 0x10;        

    //  SizeOfInitializedData = ???
    //  AddressOfEntryPoint         ?? ?? ?? ?? ; yet to find out
    //  BaseOfCode                  ?? ?? ?? ?? ; yet to find out
    //  BaseOfData                  ?? ?? ?? ?? ; yet to find out    
    //  SizeOfImage                 ?? ?? ?? ?? ; yet to find out
    //  SizeOfHeaders               ?? ?? ?? ?? ; yet to find out

	////////////////////////////////////////////////////////////
	//  Pass #2
	//
	//
    //
    //
        gopthdr.SizeOfInitializedData = 4096;
		gopthdr.AddressOfEntryPoint = 4096;
		gopthdr.BaseOfCode = 4096;
		gopthdr.BaseOfData = 8192;
		gopthdr.SizeOfImage = 4096*3;
		gopthdr.SizeOfHeaders = 4096;
        memcpy(ExeData,&gopthdr,sizeof(gopthdr); 
    }

/////////////////////////////////////////////////////////////
//
//
//
//
//
//    VirtualSize         00 00 00 00             ; unused
//    VirtualAddress      ?? ?? ?? ??             ; yet to find out
//    SizeOfRawData       20 00 00 00             ; size of code
//    PointerToRawData    ?? ?? ?? ??             ; yet to find out
//    PointerToRelocations 00 00 00 00            ; unused
//    PointerToLinenumbers 00 00 00 00            ; unused
//    NumberOfRelocations  00 00                  ; unused
//    NumberOfLinenumbers  00 00                  ; unused
//    Characteristics     20 00 00 60             ; code, executable, readable
void WriteCodeSectionHeader()
{
   char SectionName[] = {'.','c','o','d','e',0,0,0};
   memset(&gcode_section,0,sizeof(IMAGE_SECTION_HEADER));

   ////////////////////////////////////////////
   //  Pass 1
   //
   memcpy(gcode_section.Name,SectionName,8);   
   gcode_section.SizeOfRawData = 32;
   gcode_section.Characteristics = 0x60000020;


   memcpy(ExeData,&gcode_section,sizeof(IMAGE_SECTION_HEADER));
}


////////////////////////////////////////////////////////
//
//
//
//
//
void WriteDataSectionHeader()
{

   char SectionName[] = {'.','d','a','t','a',0,0,0};
   memset(&gdata_section,0,sizeof(IMAGE_SECTION_HEADER));

   ////////////////////////////////////////////
   //  Pass 1
   //

   memcpy(gdata_section.Name,SectionName,8);   
   gdata_section.SizeOfRawData = 4096;
   gdata_section.Characteristics = 0xc0000040;  // Data segment attribute 
  
   memcpy(ExeData,&gdata_section,sizeof(IMAGE_SECTION_HEADER));
}



void WriteDataSection()
{
   char Data[128];
   char *pData = Data;
   memset(Data,0,128);
   strcpy(pData,"Hello World\n");
   pData +=16;
   * ((long *)pData) = 0;
   memcpy(ExeData,Data,32);


}
///////////////////////////////////////////////////
//
//   6A 00                    ; push      0x00000000
//    68 ?? ?? ?? ??           ; push      offset _written
//    6A 0D                    ; push      0x0000000d
//    68 ?? ?? ?? ??           ; push      offset hello_string
//    6A F5                    ; push      0xfffffff5
//    2E FF 15 ?? ?? ?? ??     ; call      dword ptr cs:__imp__GetStdHandle@4
//    50                       ; push      eax
//    2E FF 15 ?? ?? ?? ??     ; call      dword ptr cs:__imp__WriteConsoleA@20
//    C3               
//
//
//
void WriteCodeSection()
{
   char Code[128];
   int ip=0;
   Code[ip++] = 0x6A;
   Code[ip++] = 0x00;
   Code[ip++] = 0x68;
   *((long *) (void *)&(Code[ip])) =           // offset hello string 
   ip+=4;
   Code[ip++]=0x6A;
   Code[ip++]=0xF5;
   Code[ip++]=0x2E;
   Code[ip++]=0xFF;
   Code[ip++]=0x15;
   *((long *) (void *)&(Code[ip])) =           // offset of GetStdHandle 
   ip+=4;
   Code[ip++]=0x50;
   Code[ip++]=0x2E;
   Code[ip++]=0xFF;
   Code[ip++]=0x15;
   *((long *) (void *)&(Code[ip])) =           // offset of WriteConsoleA 
   Code[ip++]=0xC3;
   memcpy(ExeData,Code,ip);

}

void WriteIIMDesc()
{
  IMAGE_IMPORT_DESCRIPTOR imp;
  memset(&imp,0,sizeof(IMAGE_IMPORT_DESCRIPTOR));
  imp.ForwarderChain = 0xFFFFFFFF;
  imp.FirstThunk = 8280+12;
  imp.OriginalFirstThunk = 8280;
  imp.Name = 8264;
  memcpy(ExeData,&imp,sizeof(IMAGE_IMPORT_DESCRIPTOR));

}

void WriteBlankIIMDesc()
{
   IMAGE_IMPORT_DESCRIPTOR imp;
   memset(&imp,0,sizeof(IMAGE_IMPORT_DESCRIPTOR));
   memcpy(ExeData,&imp,sizeof(IMAGE_IMPORT_DESCRIPTOR));

}

void WriteDllName()
{
  char DllName[16];
  memset(DllName,0,16);
  strcpy(DllName,"Kernel32.dll");
  memcpy(ExeData,DllName,16);
}

void WriteOrgFirstThunkArray()
{
   long FirstThunk[3];

   memset((void *)&FirstThunk[0],0,12);
   FirstThunk[0] = 8304;
   FirstThunk[1] = 8304+16;

   memcpy(ExeData,(void *)&FirstThunk[0],12);
}

void WriteFirstThunkArray()
{
   long FirstThunk[3];
   memset((void *)&FirstThunk[0],0,12);
   FirstThunk[0] = 8304;
   FirstThunk[1] = 8304+16;
   memcpy(ExeData,(void *)&FirstThunk[0],12);
}

void WriteImportByNames()
{
   char ImportString[128];
   char *CurrPtr = &ImportString[0];
   memset(ImportString,0,128];
   int count = 0;
   *CurrPtr++ = 01;
   *CurrPtr++ = 0;
   count +=2;
   strcpy(CurrPtr,"WriteConsoleA");
   count += strlen("WriteConsoleA")+1;
   CurrPtr += strlen("WriteConsoleA")+1;
   *CurrPtr++ = 02;
   *CurrPtr++ = 0;
   count + =2;
   strcpy(CurrPtr,"GetStdHandle");
   count += strlen("GetStdHandle")+1; 
   CurrPtr += strlen("GetStdHandle")+1;
   int nq = (count/32);
   int nr = count%4;

   if (nr != 0 )
	    nq +=1;
   memcpy( ExeData,ImportString,nq*32);
   

  
}

public:
     CExeFileMaker()
	 {
         ExeData = AExeData = (char *)malloc(4096*16);
         memset(ExeData,0,4096*16); 
   	 }


	 void Make()
	 {
		 long Rva = 4096;
		 /////////////////////////////////////////////
		 //
		 //  Write the Dos stub program
		 //
		 //
         WriteDosStub();         
		 ExeData += sizeof(msdos_stub_program);

		 //////////////////////////////////////////////
		 //
		 //  Write PE header
		 //
		 //

		 WritePeMagic();
		 ExeData += sizeof(pe_signature); 

		 ////////////////////////////////////////////
		 // 
		 // Write image file header ...mostly default values
		 //
		 //
		 WriteImageFileHeader();
		 ExeData += sizeof(IMAGE_FILE_HEADER); 

         ////////////////////////////////////
		 //
		 //
		 //
		 //

         WriteImageOptionalHeader();
		 ExeData +=sizeof(IMAGE_OPTIONAL_HEADER);
   
		 ////////////////////////////////////////////////
		 //
		 // Data Directory in EXE
		 //
		 //

         WriteImageDataDirectory();
		 ExeData = ExeData + sizeof(IMAGE_DATA_DIRECTORY)*16;

         /////////////////////////////////////////////////////////////
		 //
		 //
		 //  Code Section
		 //
		 //
		 WriteCodeSectionHeader();
		 ExeData = ExeData + sizeof(IMAGE_SECTION_HEADER);
		 //////////////////////////////////////////////////////////
		 //
		 //  Data Section
		 //
		 //
		 WriteDataSectionHeader();
		 ////////////////////////////////////////////////////////////
		 //
		 //
		 //
		 //
         ExeData = AExeData + 4096;
		 WriteCodeSection();
         ExeData = AExeData + 8192; 
         WriteDataSection();
		 ExeData +=32;
		 Rva =8192+32;
		 ////////////////////////////////////////////////////////
		 //
		 // 
		 //
		 //
         WriteIIMDesc();
		 ExeData +=sizeof(IMAGE_IMPORT_DESCRIPTOR);

		 WriteBlankIIMDesc();
         ExeData +=sizeof(IMAGE_IMPORT_DESCRIPTOR);
         
         WriteDllName();
		 ExeData +=16;

		 Rva = 8304;
         
		 WriteOrgFirstThunkArray();

		 ExeData +=12;

		 WriteFirstThunkArray();
         ExeData +=12; 

         WriteImportByNames();
         

	 }





};
//////////////////////////////////////////////////////////////////////////
//  
//
//
//
//
//

////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//
//
// typedef struct _IMAGE_FILE_HEADER {
//     USHORT  Machine;
//     USHORT  NumberOfSections;
//     ULONG   TimeDateStamp;
//     ULONG   PointerToSymbolTable;
//     ULONG   NumberOfSymbols;
//     USHORT  SizeOfOptionalHeader;
//     USHORT  Characteristics;
//   } IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;
//
// #define IMAGE_SIZEOF_FILE_HEADER             20
//
//



//////////////////////////////////////////////////////////////////////////////////////
//
//
// typedef struct _IMAGE_OPTIONAL_HEADER {
//
// 
//    USHORT  Magic;
//    UCHAR   MajorLinkerVersion;
//    UCHAR   MinorLinkerVersion;
//    ULONG   SizeOfCode;
//    ULONG   SizeOfInitializedData;
//    ULONG   SizeOfUninitializedData;
//    ULONG   AddressOfEntryPoint;
//     ULONG   BaseOfCode;
//     ULONG   BaseOfData;
//    
//    
//      ULONG   ImageBase;
//      ULONG   SectionAlignment;
//      ULONG   FileAlignment;
//      USHORT  MajorOperatingSystemVersion;
//      USHORT  MinorOperatingSystemVersion;
//      USHORT  MajorImageVersion;
//      USHORT  MinorImageVersion;
//      USHORT  MajorSubsystemVersion;
//      USHORT  MinorSubsystemVersion;
//      ULONG   Reserved1;
//      ULONG   SizeOfImage;
//      ULONG   SizeOfHeaders;
//      ULONG   CheckSum;
//      USHORT  Subsystem;
//      USHORT  DllCharacteristics;
//      ULONG   SizeOfStackReserve;
//      ULONG   SizeOfStackCommit;
//      ULONG   SizeOfHeapReserve;
//      ULONG   SizeOfHeapCommit;
//      ULONG   LoaderFlags;
//      ULONG   NumberOfRvaAndSizes;
//      IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
//    } IMAGE_OPTIONAL_HEADER, *PIMAGE_OPTIONAL_HEADER;
//
//
//
//
//
//
//



//////////////////////////////////////////////////////////
//
//
//
//
//







int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

