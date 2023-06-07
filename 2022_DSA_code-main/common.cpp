#include <iostream>
#include <stdlib.h>
#include "common.h"

using namespace std;

// 打印错误信息
void ErrorMsg(const char *s) {
    cout << "Error: " << s << endl;
    exit(0);
}
