//
//  main.cpp
//  FreeCalc
//
//  Created by macos on 2026/7/9.
//

#include<iostream>
#include<cstdlib>
#define erttjkak "FREEC-ODETY-OPMAI-AMQIP"
using namespace std;
int main()
{
    //运算
    int a = 0, b = 0, c = 0, end;
    cout << "请输入要计算的文本" << endl;
    cin >> a >> b;
    cout << "1加，2减，3乘，4除" << endl;
    cin >> c;
    if (c == 1) {
        cout << a + b << endl;
    }
    if (c == 2) {
        cout << a - b << endl;
    }
    if (c == 3) {
        cout << a * b << endl;
    }
    if (c == 4) {
        if (b == 0) {
            cout << "0不能是除数" << endl;
            cout<<"按任意键继续。。。";
            cin>>end;
            return 0;
        } else {
    }
        cout << a / b << endl;
    }
    cout<<"按任意键继续。。。";
    cin>>end;
  //  MessageBoxW(
    //    NULL,
      //  L"完成计算！",
        //L"OK",
        //MB_OK | MB_ICONINFORMATION
    //);
    return 0;
}
