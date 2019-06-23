#include<iostream>
#include<string.h> 
#include<stdlib.h>
#include <time.h>
using namespace std; 
#define MAX 1000                                         //待排序表表长
long bj[MAX], yd[MAX];                                   //比较次数数组和移动次数数组
typedef struct
{
	int key;
}data;

//通用函数
void show(data R[], long n)
{
	long i;
	cout << " 排序结果为：" << endl;
	for (i = 1; i <= n; i++)
		cout << R[i].key << " ";
	cout << endl;
}

//冒泡排序
void BubbleSort(data R[], long n)                        
{
	data r[MAX], t;
	long i, j;
	for (i = 0; i <= n; i++)
		r[i] = R[i];
	for (i = 1; i<n; i++)
	for (j = 1; j <= n - i; j++)
	{
		bj[1]++;	                                      //比较次数加1
		if (r[j].key>r[j + 1].key)
		{
			t = r[j];
			r[j] = r[j + 1];
			r[j + 1] = t;
			yd[1] += 3;                                   //移动次数加3
		}
	}
	cout << " 冒泡排序";
	show(r, n);
}

//直接插入排序
void InsertSort(data R[], long n)
{
	data r[MAX];
	long i, j;
	for (i = 0; i <= n; i++)
		r[i] = R[i];
	for (i = 2; i <= n; i++)
	{
		bj[2]++;                                           //比较次数加1
		if (r[i].key<r[i - 1].key)                         //需要将r[i]插入有序字表
		{
			r[0] = r[i];                                   //将带插入数据放入监视哨中 
			r[i] = r[i - 1];                               //r[i-1]后移
			for (j = i - 2; r[0].key<r[j].key; j--)        //从后向前找插入位置
				r[j + 1] = r[j];                           //记录逐个后移，直到找到插入位置
			r[j + 1] = r[0];                               //将r[0]即原r[i]插入到正确位置
			yd[2] += 3;                                    //循环一次移动次数加3
		}
	}
	cout << " 直接插入排序";
	show(r, n);
}

//简单选择排序
void SelectSort(data R[], long  n)                        
{
	data r[MAX], t;
	long i, j, k;
	for (i = 0; i <= n; i++)
		r[i] = R[i];
	for (i = 1; i <= n; i++)                              //在r中选择关键字最小的记录
	{
		k = i;
		for (j = i + 1; j <= n; j++)
		{
			bj[3]++;	                                 //比较次数加1   
			if (r[j].key<r[k].key)
				k = j;		                             //k指向此趟关键字最小的记录
		}
		if (k != i)
		{
			t = r[k];
			r[k] = r[i];
			r[i] = t;
			yd[3] += 3;                                  //移动次数加3
		}
	}
	cout << " 简单选择排序";
	show(r, n);
}

//快速排序  枢纽
long Partition(data R[], long low, long high)
{                                                        //对待排序表子表R[low...high]进行一趟排序，返回枢轴位置
	R[0] = R[low];                                       //子表第一个记录做枢轴
	yd[4]++;                                             //交换次数加1
	while (low<high)
	{
		while (low<high&&R[high].key >= R[0].key)
		{
			bj[4]++;	                                 //比较次数加1
			high--;
		}
		if (low<high)
		{
			R[low] = R[high];
			low++;
			yd[4]++;	                                //移动次数加1
		}
		while (low<high&&R[low].key <= R[0].key)
		{
			bj[4]++;
			low++;
		}
		if (low<high)
		{
			R[high] = R[low];
			high--;
			yd[4]++;
		}
	}
	R[low] = R[0];                                     //枢轴记录到位
	yd[4]++;	                                       //交换次数加1
	return low;	                                       //返回枢轴位置
}

//快速排序
void QuickSort(data R[], long low, long high)
{
	long i, n;
	n = high - low + 1;
	//low=1; high=n;
	if (low<high)
	{
		i = Partition(R, low, high);                  //将R[low...high]一分为二，i是枢轴位置
		QuickSort(R, low, i - 1);		              //左子表递归排序
		QuickSort(R, i + 1, high);			          //右子表递归排序
	}

}

//希尔排序
void ShellInsert(data R[], long dk, long n)
{	                                                  //对R做一趟增量是dk的希尔插入排序
	long i, j;
	for (i = dk + 1; i <= n; i++)
	{
		bj[5]++;
		if (R[i].key<R[i - dk].key)                   //需要将R[i]插入有序增量子表
		{
			R[0] = R[i];                              //暂存R[0]
			yd[5]++;
			for (j = i - dk; j>0 && (R[0].key<R[j].key); j = j - dk)
			{
				bj[5]++;
				R[j + dk] = R[j];                     //记录后移，直到找到插入位置
				yd[5]++;
			}
			R[j + dk] = R[0]; yd[5]++;
		}
	}
}
void ShellSort(data R[], long n)
{
	data r[MAX];
	long i;
	for (i = 1; i <= n; i++)
		r[i] = R[i];
	for (long dk = n; dk >= 1; dk /= 2)
		ShellInsert(r, dk, n);
	cout << " 希尔排序";
	show(r, n);
}

//堆调整
void HeapAdjust(data R[], long s, long m)          
{                                                  //假设R[s+1...m]已经是堆，将R[s...m]调整为以R[s]为根的大根堆
	long j;
	data rc;
	rc = R[s];
	for (j = 2 * s; j <= m; j = 2 * j)
	{                                              //沿key较大的孩子结点向下筛选
		bj[6]++;
		if (j<m&&R[j].key<R[j + 1].key)            //j为key较大的记录的下标
			j = j + 1;
		if (rc.key >= R[j].key)                    //rc应插入在s上 
			break;
		R[s] = R[j];
		yd[6]++;
		s = j;
	}
	R[s] = rc;
}

//堆排序
void HeapSort(data R[], long n)
{
	data r[MAX], t;
	long i;
	for (i = 1; i <= n; i++)
		r[i] = R[i];
	for (i = n / 2; i>0; i--)
		HeapAdjust(r, i, n);
	for (i = n; i>1; i--)
	{
		t = r[1];
		r[1] = r[i];
		r[i] = t;
		yd[6] += 3;
		HeapAdjust(r, 1, i - 1);
	}
	cout << " 堆排序";
	show(r, n);
}

//输出格式
void Display()
{
	long i, n;
	data R[MAX];
	cout << " 请输入要排序比较的数字个数:" << endl;
	cin >> n;
	for (i = 1; i <= n; i++)
		R[i].key = rand() % 1000;	                      //随机函数产生待排数放入待排序表 
	cout << " 排序前的数字顺序:" << endl;
	for (i = 1; i <= n; i++)
		cout << R[i].key << " ";
	cout << endl;
	BubbleSort(R, n);                                     //冒泡排序 
	InsertSort(R, n);                                     //直接插入排序
	SelectSort(R, n);                                     //简单选择排序  
	ShellSort(R, n);                                      //希尔排序
	HeapSort(R, n);                                       //堆排序 
	QuickSort(R, 0, n);                                   //快速排序
	cout << " 快速排序"; show(R, n);
}
int main()
{
	Display();
	cout << " 比较的结果" << endl;
	cout << " 排序方式" << "\t\t" << " 比较次数" << "\t" << " 移动次数" << endl;
	cout << " 冒泡排序" << "\t\t" << bj[1] << "\t\t" << yd[1] << endl;
	cout << " 直接插入排序" << "\t\t" << bj[2] << "\t\t" << yd[2] << endl;
	cout << " 简单选择排序" << "\t\t" << bj[3] << "\t\t" << yd[3] << endl;
	cout << " 快速排序" << "\t\t" << bj[4] << "\t\t" << yd[4] << endl;
	cout << " 希尔排序" << "\t\t" << bj[5] << "\t\t" << yd[5] << endl;
	cout << " 堆排序" << "\t\t\t" << bj[6] << "\t\t" << yd[6] << endl;
}

