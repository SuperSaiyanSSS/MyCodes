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
    getchar();//ע��������Ҫʹ��getline��������Ҫ����ǰ��Ļس�


    vector<string> mold(m,"");//�洢ԭʼģ����Ϣ
    for (int i = 0; i < m; i++)
    {
        string tem1;
        getline(cin, tem1);
        mold[i] = tem1;
    }

    map<string, string> parameters;//�洢���еı��������Ӧ��ֵ
    for (int i = 0; i < n; i++)
    {
        string tem;
        getline(cin, tem);
        string var_name = tem.substr(0, tem.find(" "));
        string value = tem.substr(tem.find(" ") + 1, tem.length() - 1);
        value = value.substr(1, value.length() - 2);//ȥ������
        parameters.insert(pair<string, string>(var_name, value));

    }


    for (int i = 0; i < m; i++)//���д���
    {
        string tem = mold[i];
        while (true)  //���һ�����ж����������Ҫѭ������
        {
            int start = tem.find("{{ ");
            if (start != -1)
            {
                int end = tem.find(" }}");
                if (end != -1)
                {
                    int length = end - start - 3;

                    string old_var = tem.substr(start + 3, length);//�õ�ģ����ı�����
                    string value = "";
                    if (parameters.find(old_var) != parameters.end())//����ñ�����ֵ
                    {
                         value = parameters[old_var];
                    }

                    string t1 = tem.substr(0, start);//ȡ��ǰ�벿��
                    string t2 = tem.substr(end + 3);//ȡ����벿��
                    tem = t1 + value + t2;

                }
                else
                    break;
            }
            else
                break;

        }
        mold[i] = tem;//���µ�ǰ�е�ֵ
    }


    //������
    for (int i = 0; i < mold.size(); i++)
        cout << mold[i] << endl;


    //system("pause");
}
