#include "HUFFMAN.cpp"

using namespace std;

int main()
{
   int ASCII[256+EXPAND]={0},chsum=0;
   float all=0,codeall=0;


   if (!Scandata(ASCII,chsum,all)) //若文件未打开
   {
      cout << "程序结束" << endl;
      system("pause");
      return 0;
   }

   HTNode *HT;
   Create_HuffmanTree(HT,ASCII,chsum);
   
   //Print_HuffmanTree(HT,chsum*2-1,0,6000,chsum*16);

   char **HC;
   HuffmanCoding(HT,HC,chsum);

//可选打印HT(三叉表形式)
   // for (int i = 1; i <= chsum*2-1; i++)
   // {
   //    cout << HT[i].ASC << " " << HT[i].weight << " " << HT[i].parent << " " << HT[i].lchild << " " << HT[i].rchild << endl;
   // }
   

   Codedata(HC,ASCII);

//可选打印HC
   // for (int i = 1; i <= chsum; i++)
   // {
   //    cout << HC[i] <<endl;
   // }   

   DeCode(HT,chsum*2-1,codeall);
   cout << "压缩比为" << all*sizeof(char)/(codeall/8) << endl;

   system("pause");
   return 0;
}
