#include "Bank.cpp"

using namespace std;

int main()
{
    window win[WINDOWS];
    Customer list[MAX_CUSTOMER];
    srand((int)time(NULL));
    int customernum=rand() % 100 + 150;//产生今日顾客数量
    for (int i = 0; i < customernum; i++)
    {
        list[i].arrival=rand() % LATESTARRIVAL;
        list[i].service_time=rand() % MAX_SERVICETIME + 10;

        cout << "顾客" << i << "号," << "到达时间为" << 9+list[i].arrival/60 << ":" << list[i].arrival%60;
        cout << ",业务所需时间为" << list[i].service_time << "分钟" << endl;
    }
    
    cout << "今日共有" << customernum << "名顾客" << endl;
    bank_simulator(customernum,list,7,win);

    system("pause");
}