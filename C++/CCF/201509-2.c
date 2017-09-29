#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int test_run_year(int y){
	if(y%400==0||(y%4==0&&y%100!=0)){
		return 1;
	}
	return 0;
}

int get_m_first_day(int y, int d, int* target_month, int* target_day){
	int month_day1[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int month_day2[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int m_first_day[12];
	int i;
	m_first_day[0] = 1;
	if(test_run_year(y)==1){

		for(i=1;i<12;i++){
			m_first_day[i] = m_first_day[i-1]+month_day2[i-1];
		}
		for(i=0;i<11;i++){
			if(d>=m_first_day[i]&&d<m_first_day[i+1]){
				*target_month = i+1; 
			}
		}
		if(*target_month==0){
			*target_month=12; 
		}
		*target_day = d-m_first_day[*target_month-1]+1;
	//	return target_month*1000+target_day;
	}
	else{
		for(i=1;i<12;i++){
			m_first_day[i] = m_first_day[i-1]+month_day1[i-1];
		}
		for(i=0;i<11;i++){
			if(d>=m_first_day[i]&&d<m_first_day[i+1]){
				*target_month = i+1; 
			} 
		}
				if(*target_month==0){
			*target_month=12; 
		}
		*target_day = d-m_first_day[*target_month-1]+1;
	}	
	return 0;
}


int main(int argc, char *argv[]) {
	int y, d;
	int *ty, *tm;
	int a=0, b=0;
	ty=&a;
	tm=&b;
	scanf("%d %d", &y, &d);
	int tt = get_m_first_day(y, d, ty, tm);
	printf("%d\n%d\n", *ty, *tm); 
	return 0;
}
