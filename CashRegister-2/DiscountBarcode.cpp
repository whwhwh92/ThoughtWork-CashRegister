#include"DiscountBarcode.h"
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
int ReadDiscountFile()
{
   ifstream fin("DiscountBarcode.txt");
   DiscountBarcode ReadDiscountBarcode;
   char buf[100] = {0};
   int LineNum =0;
   if (! fin.is_open())
	{
	  cout<<"DiscountBarcode file´ò¿ªÊ§°Ü"<<endl;
	  return 0;
	}
   while(!fin.eof())
   {
     
	   if(LineNum == 0)
	   {
	      
		   fin>>ReadDiscountBarcode.type;
		  for(int i =0;i<BarcodeNum;i++)
		  {
		    ReadDiscountBarcode.barcode[i] = 0;
		  }
		  
		  LineNum++;
	   }
	   else
	   {
		   //sscanf(buf,"%s",&ReadPrivilegeBarcode.barcode);
		   fin>>ReadDiscountBarcode.barcode;
		  for(int i =0;i<50;i++)
		   {
			   ReadDiscountBarcode.type[i] = 0;
		   }
		  
	   }
	   DiscountBar.push_back(ReadDiscountBarcode);
   }
   fin.close();
   return 1;
}