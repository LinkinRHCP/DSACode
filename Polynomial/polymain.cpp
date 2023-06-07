#include "Poly.cpp"

using namespace std;

int main()
{
   LNode **head=new LNode*[10];
   for(int i=0;i<10;i++) head[i]=NULL;

   char operation1;
   int i;
   do 
   {     
      cout << "1.创建多项式(上限为9个)\n" << "2.打印多项式\n" << "3.删除多项式\n" << "4.多项式计算\n" << "0.退出程序" <<"(输入标号进行操作)" << endl;
      cin >> operation1;
      system("cls");

      switch (operation1)
      {
         case '0':
            break;  
         
         case '1':
            i = 0;
            while (i < 9 && head[i] != NULL) i++;//选择未占用的头指针
            if (i == 9)
            {
               cout << "多项式已满" << endl;
               break;
            }                 
            head[i] = InputList(1);
            Sort_Combine(head[i]);
            break;
         
         case '2':
            ShowAll(head);
            break;

         case '3':
            char number;
            while (1) 
            {
               ShowAll(head);
               cout << "输入要删除的多项式的序号(一次仅删除一个)\n输入0退出" << endl;
               cin >> number; 

               if (number == '0') break;
               else if (number < '1' || number > '9')
               {
                  cout << "非法输入" << endl;
                  system("pause");
                  system("cls");
                  continue;
               }
                
               DeletePoly(head[number-'0'-1]);
               while ((number - '0')<9 && head[number-'0'-1] == NULL && head[number-'0'] != NULL)//删除后前移
               {
                  head[number-'0'-1] =  head[number-'0'];
                  head[number-'0'] = NULL;
                  number++;
               }               
               
               system(" pause");
               system("cls");
            }
            break;

         case '4':

            char operation2;
            int a, b;
            do
            {
               system("cls");
               if (head[8] != NULL)
               {
                  cout << "Warning! 多项式已满,需删除后再进行操作" << endl;
                  break;
               }

               ShowAll(head);
               cout << "\n1.加法\n2.减法\n3.乘法\n4.除法\n(输入0退出)" << endl;
               cin >> operation2;
               switch (operation2)
               {
                  case '0':
                     break;
                  
                  case '1'://加法
                     i=0,a=0,b=0;
                     cout << "输入求和的两多项式的序号" << endl;
                     cin >> a; cin >> b;

                     if (a == 0 || b == 0 || head[a-1]==NULL || head[b-1]==NULL)
                     {
                        cout << "非法输入" <<endl;
                        continue;
                     }

                     while (head[i] != NULL) i++;
                     head[i] = Add_Sub(head[a-1],head[b-1],'+');
                     cout << "结果为:";
                     ShowList_L(head[i]);
                     break;
                  
                  case '2'://减法
                     i=0,a=0,b=0;
                     cout << "按顺序输入被减式和减式的序号" << endl;
                     cin >> a; cin >> b;

                     if (a == 0 || b == 0 || head[a-1]==NULL || head[b-1]==NULL)
                     {
                        cout << "非法输入" <<endl;
                        continue;
                     }

                     while (head[i] != NULL) i++;
                     head[i] = Add_Sub(head[a-1],head[b-1],'-');
                     cout << "结果为:";
                     ShowList_L(head[i]);                    
                     break;
                  
                  case '3'://乘法
                     i=0,a=0,b=0;
                     cout << "输入求积的两多项式的序号" << endl;
                     cin >> a; cin >> b;

                     if (a == 0 || b == 0 || head[a-1]==NULL || head[b-1]==NULL)
                     {
                        cout << "非法输入" <<endl;
                        continue;
                     }

                     while (head[i] != NULL) i++;
                     head[i] = Multiply(head[a-1],head[b-1]);
                     cout << "结果为:";
                     ShowList_L(head[i]);
                     break;
                  
                  case '4'://除法
                     i=0,a=0,b=0;
                     cout << "按顺序输入被除式和除式的序号" << endl;
                     cin >> a; cin >> b;

                     if (a == 0 || b == 0 || head[a-1]==NULL || head[b-1]==NULL)
                     {
                        cout << "非法输入" <<endl;
                        continue;
                     }

                     while (head[i] != NULL) i++;
                     if(i+1 > 8)
                     {
                        cout << "空间不足,请删除后再计算" << endl;
                        continue;
                     }
                    
                     head[i] = Divison(head[a-1],head[b-1]);
                     head[i+1] = Add_Sub(head[a-1],Multiply(head[b-1],head[i]),'-');
                     cout << "商式为:";
                     ShowList_L(head[i]);  
                     cout << "余式为:";
                     ShowList_L(head[i+1]);                  
                     break;

                  default:
                     cout << "非法输入" << endl;
                     break;
               }
              
               system("pause");
            } while (operation2 != '0');
            break;
            
         default:
            cout << "非法输入" << endl;
            break;
      }

      system("pause");
      system("cls");
   }while (operation1 != '0');
   

   return 0;
}
