#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
 
bool test_run_year(int year){
	if(year%400==0){
		return true;
	}
	else if(year%4==0&&year%100!=0){
		return true;
	}
	else
		return false;
}

int get_have_spend_days(int y, int m){
	int days;
	int month_day[12] = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
	};
	int all = 0;
	//计算这个月1号离这个年的1 月1号相差几天 
	if(test_run_year(y)!=true){
		switch(m){
			case 12: all+=month_day[10];
			case 11: all+=month_day[9];
			case 10: all+=month_day[8];
			case 9: all+=month_day[7];
			case 8: all+=month_day[6];
			case 7: all+=month_day[5];
			case 6: all+=month_day[4];
			case 5: all+=month_day[3];
			case 4: all+=month_day[2];
			case 3: all+=month_day[1];
			case 2: all+=month_day[0];
			case 1: break; 
			default: break;
		}
	}
	else{
				switch(m){
			case 12: all+=month_day[10];
			case 11: all+=month_day[9];
			case 10: all+=month_day[8];
			case 9: all+=month_day[7];
			case 8: all+=month_day[6];
			case 7: all+=month_day[5];
			case 6: all+=month_day[4];
			case 5: all+=month_day[3];
			case 4: all+=month_day[2];
			case 3: all+=month_day[1];all++;
			case 2: all+=month_day[0];
			case 1: break; 
			default: break;
		}
	}
	return all;
	
} 

//计算这一年的1月1号与1850年1月1号差几天 
int get_days_of_first_day(int y, int m){
	if(y==1850)
		return 0;
	int all = 0;
	for(int i=1850;i<y;i++){
		if(test_run_year(i)){
			all+=366; 
		}
		else{
			all+=365;
		}
	}
	return all;
}

//计算该月的1号是星期几
int first_is_x(int  this_month_1_days){
	int base_x = 2;
	int yushu = this_month_1_days%7;
	base_x += yushu;
	base_x = base_x%7;
	if(base_x==0)
		base_x = 7;
	return base_x;
}
 


int main() {
	int a, b, c, y1, y2;
	cin>>a>>b>>c>>y1>>y2;
	for(int i=y1;i<=y2;i++){
		int this_month_1_days = get_days_of_first_day(i, a)+get_have_spend_days(i, a);
		int base_x = first_is_x(this_month_1_days);
		
		//计算该月的第一个星期X的日期是几号 
		int base_c_day;
		int real_c_day;
		bool nonce = false;; 
		if(c>=base_x){
			base_c_day = c-base_x+1; 
		}
		else{
			base_c_day = c-base_x+8;
		}
		real_c_day = 7*(b-1)+base_c_day;
		//判断是否合法 
		if(a==4||a==6||a==9||a==11){
			if(real_c_day>30){
				nonce = true;
			}
		}
		else if(a==2){
			if(test_run_year(i)){
				if(real_c_day>29)
					nonce = true;
			}
			else
				if(real_c_day>28)
					nonce = true;
		}
		else
			if(real_c_day>31){
				nonce = true;
			}
		if(!nonce){
			if(a<=9&&real_c_day<=9){
				cout<<i<<"/"<<0<<a<<"/"<<0<<real_c_day<<endl;
			}
			else if(a>9&&real_c_day<=9){
				cout<<i<<"/"<<a<<"/"<<0<<real_c_day<<endl;
			}
			else if(a<=9&&real_c_day>9){
				cout<<i<<"/"<<0<<a<<"/"<<real_c_day<<endl; 
			}
			else
				cout<<i<<"/"<<a<<"/"<<real_c_day<<endl;
		} 
		else
			cout<<"none"<<endl;
	}
	
	
	return 0;
}
