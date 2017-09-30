#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<map>
#include<stdlib.h>
#include<stdio.h>
using namespace std;



int main()
{
    int m, n;
    cin >> m >> n;
    getchar();//注意下面需要使用getline，所以需要处理前面的回车


    vector<string> mold(m,"");//存储原始模板信息
    for (int i = 0; i < m; i++)
    {
        string tem1;
        getline(cin, tem1);
        mold[i] = tem1;
    }

    map<string, string> parameters;//存储所有的变量和其对应的值
    for (int i = 0; i < n; i++)
    {
        string tem;
        getline(cin, tem);
        string var_name = tem.substr(0, tem.find(" "));
        string value = tem.substr(tem.find(" ") + 1, tem.length() - 1);
        value = value.substr(1, value.length() - 2);//去掉引号
        parameters.insert(pair<string, string>(var_name, value));

    }


    for (int i = 0; i < m; i++)//逐行处理
    {
        string tem = mold[i];
        while (true)  //如果一行里有多个变量，需要循环处理
        {
            int start = tem.find("{{ ");
            if (start != -1)
            {
                int end = tem.find(" }}");
                if (end != -1)
                {
                    int length = end - start - 3;

                    string old_var = tem.substr(start + 3, length);//得到模板里的变量名
                    string value = "";
                    if (parameters.find(old_var) != parameters.end())//如果该变量有值
                    {
                         value = parameters[old_var];
                    }

                    string t1 = tem.substr(0, start);//取出前半部分
                    string t2 = tem.substr(end + 3);//取出后半部分
                    tem = t1 + value + t2;

                }
                else
                    break;
            }
            else
                break;

        }
        mold[i] = tem;//更新当前行的值
    }


    //输出结果
    for (int i = 0; i < mold.size(); i++)
        cout << mold[i] << endl;


    //system("pause");
}
