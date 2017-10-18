#include <iostream>
#include <bitset>
#include <sstream>
#include <fstream>
#include <cassert>
#include <windows.h>

using namespace std;


// �η����� C++�Դ��Ĵη�����������
int cifang(int base, int cishu){
    int num =1;
    if(cishu==0){
        return 1;
    }
    for(int i=0;i<cishu;i++){
        num *= base;
    }
    return num;
}

// ������תʮ����
int twoToten(int two_num){
    int ten_num=0;
    int count=0;
    while(two_num){
        if(two_num%10==1){
            ten_num+=cifang(2, count);
        }
        count++;
        two_num/=10;
    }
    return ten_num;
}


// �ַ���ת����
int stringToInt(string s){
    stringstream ss;
    int a;
    ss<<s;
    ss>>a;
    return a;
}


// ʮ��������ת���������ֱ�ʾ���ַ���
string tenToTwo(int ten_num){
    string two_string = "";
    for(int i=ten_num;i!=0;i=i/2){
        two_string += (i%2?'1':'0');
    }
    return two_string;
}




// ������ת���ɶ��������ֱ�ʾ���ַ���
string nameToBitString(string name){
    int length = name.size();
    string two_string="";
    for(int i=0;i<length;i++){
        two_string += tenToTwo(name[i]-'a');
    }

    return two_string;
}


// ��żУ��
bitset<64> check(bitset<56>s56){
    bitset<64>s64;
    int check_flag = 0;
    int duo_count = 0;
    for(int clock = 0;clock<56;clock+=8) {
        for (int i = clock; i < clock+7; i++) {
            s64[i] = s56[i-duo_count];
            if (s56[i-duo_count] == 1)
                check_flag += 1;
        }
        if (check_flag %2== 1) {
            s64[clock+7] = 1;
        }
        check_flag = 0;
        duo_count++;
    }
    cout<<endl;

    return s64;
}


// ��Կ�û�����64λ��Կ���56λ
int PC_1[] = {57, 49, 41, 33, 25, 17, 9,
              1, 58, 50, 42, 34, 26, 18,
              10,  2, 59, 51, 43, 35, 27,
              19, 11,  3, 60, 52, 44, 36,
              63, 55, 47, 39, 31, 23, 15,
              7, 62, 54, 46, 38, 30, 22,
              14,  6, 61, 53, 45, 37, 29,
              21, 13,  5, 28, 20, 12,  4};

// ѹ���û�����56λ��Կѹ����48λ����Կ
int PC_2[] = {14, 17, 11, 24,  1,  5,
              3, 28, 15,  6, 21, 10,
              23, 19, 12,  4, 26,  8,
              16,  7, 27, 20, 13,  2,
              41, 52, 31, 37, 47, 55,
              30, 40, 51, 45, 33, 48,
              44, 49, 39, 56, 34, 53,
              46, 42, 50, 36, 29, 32};

// ÿ�����Ƶ�λ��
int shiftBits[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};


// ��ȡÿ�ֵ�����Կ
bitset<48>* getEachK(bitset<54> key54, bitset<48> eachK[]){

    //��Ϊ��ʼ��A B������Կ
    bitset<28>key28_A, key28_B;
    for(int i=0;i<28;i++){
        key28_A[i] = key54[i];
        key28_B[i] = key54[28+i];
    }

    for(int i=0;i<16;i++){

        //����ѭ������1��2��
        int shiftCount = shiftBits[i];
        while(shiftCount) {
            int tempA = key28_A[0];
            int tempB = key28_B[0];
            for (int j = 1; j < 27; j++) {
                key28_A[j - 1] = key28_A[j];
                key28_B[j - 1] = key28_B[j];
            }
            key28_A[27] = tempA;
            key28_B[27] = tempB;
            shiftCount--;
        }

        bitset<56> A_B;
        for(int k=0;k<28;k++){
            A_B[k] = key28_A[k];
            A_B[k+28] = key28_B[k];
        }

        bitset<48> thisK;
        for(int k=0;k<48;k++){
            thisK[k] = A_B[PC_2[k]];
        }

        eachK[i] = thisK;
    }

    return eachK;

}


// ��չ�û����� 32λ ��չ�� 48λ
int E[] = {32,  1,  2,  3,  4,  5,
           4,  5,  6,  7,  8,  9,
           8,  9, 10, 11, 12, 13,
           12, 13, 14, 15, 16, 17,
           16, 17, 18, 19, 20, 21,
           20, 21, 22, 23, 24, 25,
           24, 25, 26, 27, 28, 29,
           28, 29, 30, 31, 32,  1};


// S�У�ÿ��S����4x16���û���6λ -> 4λ
int S_BOX[8][4][16] = {
        {
                {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
                {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
                {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
                {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
        },
        {
                {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
                {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
                {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
                {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
        },
        {
                {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
                {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
                {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
                {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
        },
        {
                {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
                {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
                {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
                {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
        },
        {
                {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
                {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
                {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
                {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
        },
        {
                {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
                {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
                {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
                {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
        },
        {
                {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
                {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
                {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
                {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
        },
        {
                {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
                {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
                {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
                {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
        }
};


// P�û���32λ -> 32λ
int P[] = {16,  7, 20, 21,
           29, 12, 28, 17,
           1, 15, 23, 26,
           5, 18, 31, 10,
           2,  8, 24, 14,
           32, 27,  3,  9,
           19, 13, 30,  6,
           22, 11,  4, 25 };



void readTxt(string file)
{
    ifstream infile;
    infile.open(file.data());   //���ļ����������ļ���������
    assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ��������

    char c;
    infile >> noskipws;
    while (!infile.eof())
    {
        infile>>c;
        cout<<c<<endl;

    }
    infile.close();             //�ر��ļ�������
}



bitset<64> plaintext;
bitset<32> plaintext_L;
bitset<32> plaintext_R;

bitset<64> ciphertext;

// test[16]�洢16��ÿ�ֵ�����Կ
bitset<48> test[16];

// 64λ��Կ����Կ��������54λ�桤������Կ
bitset<54>key54;

// S��ӳ��P���û���õ���32λ����
bitset<32> S_flex;

// ��һ�μ��ܺ������
bitset<64> last_encryptedtext;


// ��ȡ��Կ �洢��key54��
void getKey(string key){

    //�趨56λ������Կ
    //��Կ����Ϊ���ֵĵ���-'a'
    string strval = nameToBitString(key);
    cout<<"���������õ�������ԿΪ��"<<key<<endl;
    bitset<56>ss(strval);

    //56λ����żУ����չΪ64λ
    bitset<64>key64;
    key64 = check(ss);

    //64λ��Կ����Կ������54λ�桤������Կ
    for(int i=0;i<54;i++){
        key54[i] = key64[PC_1[i]];
    }

    cout<<"ת���õ����桤������ԿΪ "<<key54<<endl;

    //test[16]�洢16��ÿ�ֵ�����Կ
    getEachK(key54, test);
}

// DES���ܺ���
void encrypt(){

    cout<<"ming wen is "<<plaintext<<endl;
    for(int i=0;i<32;i++){
        plaintext_L[i] = plaintext[i];
        plaintext_R[i] = plaintext[i+32];
    }

    //����16��DES����
    for(int i=0;i<16;i++){
        bitset<32> L, R;
        for(int j=0;j<32;j++){
            L[j] = plaintext_L[j];
            R[j] = plaintext_R[j];
        }


        bitset<48> EA;
        //��չ32λ������48λ
        for(int j=0;j<48;j++){
            EA[j] = R[E[j]];
        }

        bitset<48> EA_J = EA ^ test[i];

        //S�еı��
        for(int count_s=0;count_s<8;count_s++){
            //�ֱ������S�е��к� �к�
            int n, m;
            n = twoToten(EA_J[count_s*6]*10+EA_J[count_s*6+5]);
            m = twoToten(EA_J[count_s*6+1]*1000+EA_J[count_s*6+2]*100+EA_J[count_s*6+3]*10+EA_J[count_s*6+4]);
            int target_s = S_BOX[count_s][n][m];

            //��S��ȡ��������ת��������
            string target_s_s = tenToTwo(target_s);
            target_s = stringToInt(target_s_s);


            S_flex[count_s*4+3] = target_s%10;
            target_s/=10;

            S_flex[count_s*4+2] = target_s%10;
            target_s/=10;

            S_flex[count_s*4+1] = target_s%10;
            target_s/=10;

            S_flex[count_s*4] = target_s%10;
            target_s/=10;

        }


        //�û�P��
        bitset<32> C_temp;
        for(int k=0;k<32;k++){
            C_temp[k] = S_flex[P[k]];
        }

        S_flex = C_temp;

        plaintext_L = R;
        plaintext_R = L ^ S_flex;

        //     cout<<plaintext_L<<endl;
        //      cout<<plaintext_R<<endl;

    }
    cout<<endl;
    cout<<"@@@@@@@@@@@@@@@@@@@"<<endl;
    cout<<plaintext_L<<plaintext_R<<endl;

    cout<<"-------------------------"<<endl;

    //�����Ĵ洢��ȫ�ֱ���
    for(int kk=0;kk<32;kk++){
        plaintext[kk] = plaintext_L[kk];
        plaintext[kk+32] = plaintext_R[kk];
    }

//    fstream file1;
//    file1.open("D://b138.txt", ios::app | ios::out);
//    file1.write((char*)&plaintext,sizeof(plaintext));
//    file1.close();

}


void decrypt(){

    swap(plaintext_L, plaintext_R);

    //����16��DES����
    for(int i=0;i<16;i++){
        bitset<32> L, R;
        for(int j=0;j<32;j++){
            L[j] = plaintext_L[j];
            R[j] = plaintext_R[j];
        }


        bitset<48> EA;
        //��չ32λ������48λ
        for(int j=0;j<48;j++){
            EA[j] = R[E[j]];
        }

        bitset<48> EA_J = EA ^ test[15-i];

        //S�еı��
        for(int count_s=0;count_s<8;count_s++){
            //�ֱ������S�е��к� �к�
            int n, m;
            n = twoToten(EA_J[count_s*6]*10+EA_J[count_s*6+5]);
            m = twoToten(EA_J[count_s*6+1]*1000+EA_J[count_s*6+2]*100+EA_J[count_s*6+3]*10+EA_J[count_s*6+4]);
            int target_s = S_BOX[count_s][n][m];

            //��S��ȡ��������ת��������
            string target_s_s = tenToTwo(target_s);
            target_s = stringToInt(target_s_s);


            S_flex[count_s*4+3] = target_s%10;
            target_s/=10;

            S_flex[count_s*4+2] = target_s%10;
            target_s/=10;

            S_flex[count_s*4+1] = target_s%10;
            target_s/=10;

            S_flex[count_s*4] = target_s%10;
            target_s/=10;

        }

        //�û�P��
        bitset<32> C_temp;
        for(int k=0;k<32;k++){
            C_temp[k] = S_flex[P[k]];
        }

        S_flex = C_temp;

        plaintext_L = R;
        plaintext_R = L ^ S_flex;

    }
    cout<<"@@@@@@@@@@@@@@@@@@@"<<endl;

    //�û�����P- ��PΪ�޲��� P-Ҳ�޲�����

    swap(plaintext_R, plaintext_L);

    for(int i=0;i<32;i++){
        plaintext[i] = plaintext_L[i];
        plaintext[i+32] = plaintext_R[i];
    }
    cout<<"result is "<<plaintext<<endl;


}

void test2(int is_first){

    string filename;
    if(is_first){
        filename = "D:\\for_test.txt";
    }
    else{
        filename = "D:\\loop_test.txt";
        DeleteFile("D:\\loop_test.txt");
    }
    //��ȡ�̶�������
    ifstream t("D:\\drangon_ball.txt");
    stringstream buffer;
    buffer << t.rdbuf();
    string contents(buffer.str());
    cout << "content is " << contents << endl;

    int content_size = contents.size();
    int loop_content = content_size / 8;
    int yushu = content_size % 8;

    //��������ȡ���������ӽ���
    for (int i = 0; i < loop_content; i++) {
        bitset<8> iter[8];
        plaintext = 0;
        for (int j = 0; j < 8; j++) {
            iter[j] = contents[j + 8 * i];
        }
        for (int ii = 0; ii < 8; ii++) {
            for (int jj = 0; jj < 8; jj++) {
                plaintext[ii * 8 + jj] = iter[ii][jj];
            }
        }

        encrypt();

        //�洢����
        cout << plaintext.to_string() << endl;
        fstream file1_e;
        file1_e.open(filename, ios::app | ios::out);
        file1_e.write((char *) &plaintext, sizeof(plaintext));
        file1_e.close();
    }

    bitset<8> iter[8];
    plaintext = 0;
    for (int j = 0; j < yushu; j++) {
        iter[j] = contents[j + 8 * loop_content];
    }
    for (int ii = 0; ii < yushu; ii++) {
        for (int jj = 0; jj < 8; jj++) {
            plaintext[ii * 8 + jj] = iter[ii][jj];
        }
    }

    encrypt();

    // �洢����
    cout << plaintext.to_string() << endl;
    fstream file1_e;
    file1_e.open(filename, ios::app | ios::out);
    file1_e.write((char *) &plaintext, sizeof(yushu));
    file1_e.close();

    if(!is_first){
        string t,ans,ans2;
        int i;
        freopen("D:\\for_test.txt","r",stdin);
        char c;
        while(scanf("%c",&c)!=EOF) ans+=c;
        fclose(stdin);
        freopen("D:\\loop_test.txt","r",stdin);
        while(scanf("%c",&c)!=EOF) ans2+=c;;
        fclose(stdin);
        if(ans.size()!=ans2.size()){cout<<"���������½ʧ�ܣ������Իٳ��򡣡���\n";return;}
        for(i=0;i<ans.size();i++)
            if(ans[i]!=ans2[i]){cout<<"���������½ʧ�ܣ������Իٳ��򡣡���\n";return;}
        cout<<"������ͬ����½�ɹ�\n";
    }


}

int main() {


    cout<<"----150420120 ������----"<<endl;
    cout<<"Ҫ���ܵ�ͼƬ��·���� D:/hit.bmp"<<endl;
    cout<<"Ҫ���ܵ����ֵ�·���� D:/drangon_ball.txt"<<endl;
    cout<<"��ȡ�Ľ����������D�̸�Ŀ¼��"<<endl;
    cout<<"ECBģʽ����ͼƬ�밴1��ECBģʽ���������밴2"<<endl;
    cout<<"CBCģʽ����ͼƬ�밴3��CBCģʽ���������밴4"<<endl;
    cout<<"����ʵ��ĵڶ����밴5"<<endl;
    cout<<"          by supersaiyan"<<endl;

    int choose;
    cin>>choose;

    string key = "�����ħ�˲�ż";
    string end1;
    // ��ȡ��Կ �洢��key54��
    if(choose==5) {
        int first = 1;
        while(1) {
            cin.clear();
            cin.sync();   //������cin.ignore();
            if(first) {
                cout << "���ε�½�������ÿ���" << endl;
                cin >> key;
                getKey(key);
                test2(first);
                first = 0;
            }
            else{
                cin.clear();
                cin.sync();   //������cin.ignore();


                cout<<"����֤���Ŀ����Ƿ���ȷ�������"<<endl;
                cin >> key;
                cout<<"0000000001"<<endl;
                cout<<key<<endl;
                Sleep(2000);
                getKey(key);
                test2(first);
            }
            Sleep(2000);
            cout<<"�Ƿ�����������밴1����������"<<endl;
    //        cin.clear();
      //      cin.sync();   //������cin.ignore();

            cin>>end1;
            if(end1=="1"){
                return 0;
            }
            else{
                cout<<"0000000002"<<endl;
                cout<<end1<<endl;
                Sleep(2000);
              //  cin.ignore(numeric_limits<std::streamsize>::max()); //���cin����������
              //  cin.clear();
              //  cin.sync();   //������cin.ignore();
            }
        }
    }
    else{
        getKey(key);
    }

    if(choose==2) {
        //��ȡ����
        ifstream t("D:\\drangon_ball.txt");
        stringstream buffer;
        buffer << t.rdbuf();
        string contents(buffer.str());
        cout << "content is " << contents << endl;

        int content_size = contents.size();
        int loop_content = content_size / 8;
        int yushu = content_size % 8;

        //��������ȡ���������ӽ���
        for (int i = 0; i < loop_content; i++) {
            bitset<8> iter[8];
            plaintext = 0;
            for (int j = 0; j < 8; j++) {
                iter[j] = contents[j + 8 * i];
            }
            for (int ii = 0; ii < 8; ii++) {
                for (int jj = 0; jj < 8; jj++) {
                    plaintext[ii * 8 + jj] = iter[ii][jj];
                }
            }

            encrypt();

            //�洢����
            cout << plaintext.to_string() << endl;
            fstream file1_e;
            file1_e.open("D://drangon_ball_c_1.txt", ios::app | ios::out);
            file1_e.write((char *) &plaintext, sizeof(plaintext));
            file1_e.close();

            decrypt();

            cout << plaintext.to_string() << endl;
            fstream file1;
            file1.open("D://drangon_ball_d_1.txt", ios::app | ios::out);
            file1.write((char *) &plaintext, sizeof(plaintext));
            file1.close();
        }

        bitset<8> iter[8];
        plaintext = 0;
        for (int j = 0; j < yushu; j++) {
            iter[j] = contents[j + 8 * loop_content];
        }
        for (int ii = 0; ii < yushu; ii++) {
            for (int jj = 0; jj < 8; jj++) {
                plaintext[ii * 8 + jj] = iter[ii][jj];
            }
        }

        encrypt();

        // �洢����
        cout << plaintext.to_string() << endl;
        fstream file1_e;
        file1_e.open("D://drangon_ball_c_1.txt", ios::app | ios::out);
        file1_e.write((char *) &plaintext, sizeof(yushu));
        file1_e.close();

        decrypt();

//    for(int ii=0;ii<yushu;ii++){
//        bitset<8> chars;
//        for(int jj=0;jj<8;jj++){
//            chars[jj] = plaintext[ii*8+jj];
//        }
//        fstream file1;
//        file1.open("D://b137.txt", ios::app | ios::out);
//        file1.write((char*)&chars,sizeof(chars));
//        file1.close();
//    }

        cout << plaintext.to_string() << endl;
        fstream file1;
        file1.open("D://drangon_ball_d_1.txt", ios::app | ios::out);
        file1.write((char *) &plaintext, yushu);
        file1.close();
    }
    else if(choose==1){

        //��ȡ����
        ifstream t("D:\\hit.bmp", ios::binary);
        stringstream buffer;
        buffer << t.rdbuf();
        string contents(buffer.str());
        cout << "content is " << contents << endl;

        int content_size = contents.size();
        int loop_content = content_size / 8;
        int yushu = content_size % 8;

        //��������ȡ���������ӽ���
        for (int i = 0; i < loop_content; i++) {
            bitset<8> iter[8];
            plaintext = 0;
            for (int j = 0; j < 8; j++) {
                iter[j] = contents[j + 8 * i];
            }
            for (int ii = 0; ii < 8; ii++) {
                for (int jj = 0; jj < 8; jj++) {
                    plaintext[ii * 8 + jj] = iter[ii][jj];
                }
            }

            encrypt();

            // �洢����
            cout << plaintext.to_string() << endl;
            fstream file1_c;
            file1_c.open("D://hit_c_1.bmp", ios::binary | ios::app | ios::out);
            file1_c.write((char *) &plaintext, sizeof(plaintext));
            file1_c.close();


            decrypt();

            cout << plaintext.to_string() << endl;
            fstream file1;
            file1.open("D://hit_d_1.bmp", ios::binary | ios::app | ios::out);
            file1.write((char *) &plaintext, sizeof(plaintext));
            file1.close();
        }

        bitset<8> iter[8];
        plaintext = 0;
        for (int j = 0; j < yushu; j++) {
            iter[j] = contents[j + 8 * loop_content];
        }
        for (int ii = 0; ii < yushu; ii++) {
            for (int jj = 0; jj < 8; jj++) {
                plaintext[ii * 8 + jj] = iter[ii][jj];
            }
        }

        encrypt();

        // �洢����
        cout << plaintext.to_string() << endl;
        fstream file1_c;
        file1_c.open("D://hit_c_1.bmp", ios::binary | ios::app | ios::out);
        file1_c.write((char *) &plaintext, sizeof(yushu));
        file1_c.close();


        decrypt();

        cout << plaintext.to_string() << endl;
        fstream file1;
        file1.open("D://hit_d_1.bmp", ios::binary | ios::app | ios::out);
        file1.write((char *) &plaintext, yushu);
        file1.close();

    }
    else if(choose==4){
        //��ȡ����
        ifstream t("D:\\drangon_ball.txt");
        stringstream buffer;
        buffer << t.rdbuf();
        string contents(buffer.str());
        cout << "content is " << contents << endl;

        int content_size = contents.size();
        int loop_content = content_size / 8;
        int yushu = content_size % 8;



        //��������ȡ���������ӽ���
        for (int i = 0; i < loop_content; i++) {
            bitset<8> iter[8];
            plaintext = 0;
            for (int j = 0; j < 8; j++) {
                iter[j] = contents[j + 8 * i];
            }
            for (int ii = 0; ii < 8; ii++) {
                for (int jj = 0; jj < 8; jj++) {
                    plaintext[ii * 8 + jj] = iter[ii][jj];
                }
            }

            // CBCģʽ���е�������
            if(i!=0) {
                for (int count_i = 0; count_i < plaintext.size(); count_i++) {
                    plaintext[i] = last_encryptedtext[i] xor plaintext[i];
                }
            }

            encrypt();

            for(int count_i=0;count_i<plaintext.size();count_i++) {
                last_encryptedtext[count_i] = plaintext[count_i];
            }


            //�洢����
            cout << plaintext.to_string() << endl;
            fstream file1_e;
            file1_e.open("D://drangon_ball_c_2.txt", ios::app | ios::out);
            file1_e.write((char *) &plaintext, sizeof(plaintext));
            file1_e.close();

            if(i!=0) {
                for (int count_i = 0; count_i < plaintext.size(); count_i++) {
                    plaintext[i] = last_encryptedtext[i] xor plaintext[i];
                }
            }

            decrypt();

            for(int count_i=0;count_i<plaintext.size();count_i++) {
                last_encryptedtext[count_i] = plaintext[count_i];
            }

            cout << plaintext.to_string() << endl;
            fstream file1;
            file1.open("D://drangon_ball_d_2.txt", ios::app | ios::out);
            file1.write((char *) &plaintext, sizeof(plaintext));
            file1.close();
        }

        bitset<8> iter[8];
        plaintext = 0;
        for (int j = 0; j < yushu; j++) {
            iter[j] = contents[j + 8 * loop_content];
        }
        for (int ii = 0; ii < yushu; ii++) {
            for (int jj = 0; jj < 8; jj++) {
                plaintext[ii * 8 + jj] = iter[ii][jj];
            }
        }

        encrypt();

        // �洢����
        cout << plaintext.to_string() << endl;
        fstream file1_e;
        file1_e.open("D://drangon_ball_c_2.txt", ios::app | ios::out);
        file1_e.write((char *) &plaintext, sizeof(yushu));
        file1_e.close();

        decrypt();

        cout << plaintext.to_string() << endl;
        fstream file1;
        file1.open("D://drangon_ball_d_2.txt", ios::app | ios::out);
        file1.write((char *) &plaintext, yushu);
        file1.close();

    }
    else if(choose==3){

        //��ȡ����
        ifstream t("D:\\hit.bmp", ios::binary);
        stringstream buffer;
        buffer << t.rdbuf();
        string contents(buffer.str());
        cout << "content is " << contents << endl;

        int content_size = contents.size();
        int loop_content = content_size / 8;
        int yushu = content_size % 8;

        //��������ȡ���������ӽ���
        for (int i = 0; i < loop_content; i++) {
            bitset<8> iter[8];
            plaintext = 0;
            for (int j = 0; j < 8; j++) {
                iter[j] = contents[j + 8 * i];
            }
            for (int ii = 0; ii < 8; ii++) {
                for (int jj = 0; jj < 8; jj++) {
                    plaintext[ii * 8 + jj] = iter[ii][jj];
                }
            }

            // CBCģʽ���е�������
            if(i!=0) {
                for (int count_i = 0; count_i < plaintext.size(); count_i++) {
                    plaintext[i] = last_encryptedtext[i] xor plaintext[i];
                }
            }

            encrypt();

            for(int count_i=0;count_i<plaintext.size();count_i++) {
                last_encryptedtext[count_i] = plaintext[count_i];
            }

            // �洢����
            cout << plaintext.to_string() << endl;
            fstream file1_c;
            file1_c.open("D://hit_c_2.bmp", ios::binary | ios::app | ios::out);
            file1_c.write((char *) &plaintext, sizeof(plaintext));
            file1_c.close();

            // CBCģʽ���е�������
            if(i!=0) {
                for (int count_i = 0; count_i < plaintext.size(); count_i++) {
                    plaintext[i] = last_encryptedtext[i] xor plaintext[i];
                }
            }

            decrypt();

            for(int count_i=0;count_i<plaintext.size();count_i++) {
                last_encryptedtext[count_i] = plaintext[count_i];
            }

            cout << plaintext.to_string() << endl;
            fstream file1;
            file1.open("D://hit_d_2.bmp", ios::binary | ios::app | ios::out);
            file1.write((char *) &plaintext, sizeof(plaintext));
            file1.close();
        }

        bitset<8> iter[8];
        plaintext = 0;
        for (int j = 0; j < yushu; j++) {
            iter[j] = contents[j + 8 * loop_content];
        }
        for (int ii = 0; ii < yushu; ii++) {
            for (int jj = 0; jj < 8; jj++) {
                plaintext[ii * 8 + jj] = iter[ii][jj];
            }
        }

        encrypt();

        // �洢����
        cout << plaintext.to_string() << endl;
        fstream file1_c;
        file1_c.open("D://hit_c_2.bmp", ios::binary | ios::app | ios::out);
        file1_c.write((char *) &plaintext, sizeof(yushu));
        file1_c.close();


        decrypt();

        cout << plaintext.to_string() << endl;
        fstream file1;
        file1.open("D://hit_d_2.bmp", ios::binary | ios::app | ios::out);
        file1.write((char *) &plaintext, yushu);
        file1.close();

    }

    else{
        cout<<"�Ƿ����룡"<<endl;
    }

//    plaintext = 3;
//    encrypt();
//    decrypt();

    return 0;
}