#include "Graph.cpp"

using namespace std;

int main()
{
   MGraph G;
   CreateUDN(G);

   while (1)
   {
   Printcity(G);

   int control=0;
   cout << "1.计算最短路径\n2.删除城市\n其他.退出程序" << endl;
   cin >> control;

   switch (control)
   {
   case 1: 
      GetminRoad(G);
      break;
   
   case 2:   
      Deletecity(G);
      break; 

   default:   
      system("pause"); 
      return 0;
      break;
   }

   system("pause");   
   system("cls");
   }
   return 0;
}
