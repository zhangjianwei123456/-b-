#include<iostream>
#include<string.h> 
#include<stdlib.h>
#include <time.h>
using namespace std; 
#define MAX 1000                                         //��������
long bj[MAX], yd[MAX];                                   //�Ƚϴ���������ƶ���������
typedef struct
{
	int key;
}data;

//ͨ�ú���
void show(data R[], long n)
{
	long i;
	cout << " ������Ϊ��" << endl;
	for (i = 1; i <= n; i++)
		cout << R[i].key << " ";
	cout << endl;
}

//ð������
void BubbleSort(data R[], long n)                        
{
	data r[MAX], t;
	long i, j;
	for (i = 0; i <= n; i++)
		r[i] = R[i];
	for (i = 1; i<n; i++)
	for (j = 1; j <= n - i; j++)
	{
		bj[1]++;	                                      //�Ƚϴ�����1
		if (r[j].key>r[j + 1].key)
		{
			t = r[j];
			r[j] = r[j + 1];
			r[j + 1] = t;
			yd[1] += 3;                                   //�ƶ�������3
		}
	}
	cout << " ð������";
	show(r, n);
}

//ֱ�Ӳ�������
void InsertSort(data R[], long n)
{
	data r[MAX];
	long i, j;
	for (i = 0; i <= n; i++)
		r[i] = R[i];
	for (i = 2; i <= n; i++)
	{
		bj[2]++;                                           //�Ƚϴ�����1
		if (r[i].key<r[i - 1].key)                         //��Ҫ��r[i]���������ֱ�
		{
			r[0] = r[i];                                   //�����������ݷ���������� 
			r[i] = r[i - 1];                               //r[i-1]����
			for (j = i - 2; r[0].key<r[j].key; j--)        //�Ӻ���ǰ�Ҳ���λ��
				r[j + 1] = r[j];                           //��¼������ƣ�ֱ���ҵ�����λ��
			r[j + 1] = r[0];                               //��r[0]��ԭr[i]���뵽��ȷλ��
			yd[2] += 3;                                    //ѭ��һ���ƶ�������3
		}
	}
	cout << " ֱ�Ӳ�������";
	show(r, n);
}

//��ѡ������
void SelectSort(data R[], long  n)                        
{
	data r[MAX], t;
	long i, j, k;
	for (i = 0; i <= n; i++)
		r[i] = R[i];
	for (i = 1; i <= n; i++)                              //��r��ѡ��ؼ�����С�ļ�¼
	{
		k = i;
		for (j = i + 1; j <= n; j++)
		{
			bj[3]++;	                                 //�Ƚϴ�����1   
			if (r[j].key<r[k].key)
				k = j;		                             //kָ����˹ؼ�����С�ļ�¼
		}
		if (k != i)
		{
			t = r[k];
			r[k] = r[i];
			r[i] = t;
			yd[3] += 3;                                  //�ƶ�������3
		}
	}
	cout << " ��ѡ������";
	show(r, n);
}

//��������  ��Ŧ
long Partition(data R[], long low, long high)
{                                                        //�Դ�������ӱ�R[low...high]����һ�����򣬷�������λ��
	R[0] = R[low];                                       //�ӱ��һ����¼������
	yd[4]++;                                             //����������1
	while (low<high)
	{
		while (low<high&&R[high].key >= R[0].key)
		{
			bj[4]++;	                                 //�Ƚϴ�����1
			high--;
		}
		if (low<high)
		{
			R[low] = R[high];
			low++;
			yd[4]++;	                                //�ƶ�������1
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
	R[low] = R[0];                                     //�����¼��λ
	yd[4]++;	                                       //����������1
	return low;	                                       //��������λ��
}

//��������
void QuickSort(data R[], long low, long high)
{
	long i, n;
	n = high - low + 1;
	//low=1; high=n;
	if (low<high)
	{
		i = Partition(R, low, high);                  //��R[low...high]һ��Ϊ����i������λ��
		QuickSort(R, low, i - 1);		              //���ӱ�ݹ�����
		QuickSort(R, i + 1, high);			          //���ӱ�ݹ�����
	}

}

//ϣ������
void ShellInsert(data R[], long dk, long n)
{	                                                  //��R��һ��������dk��ϣ����������
	long i, j;
	for (i = dk + 1; i <= n; i++)
	{
		bj[5]++;
		if (R[i].key<R[i - dk].key)                   //��Ҫ��R[i]�������������ӱ�
		{
			R[0] = R[i];                              //�ݴ�R[0]
			yd[5]++;
			for (j = i - dk; j>0 && (R[0].key<R[j].key); j = j - dk)
			{
				bj[5]++;
				R[j + dk] = R[j];                     //��¼���ƣ�ֱ���ҵ�����λ��
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
	cout << " ϣ������";
	show(r, n);
}

//�ѵ���
void HeapAdjust(data R[], long s, long m)          
{                                                  //����R[s+1...m]�Ѿ��Ƕѣ���R[s...m]����Ϊ��R[s]Ϊ���Ĵ����
	long j;
	data rc;
	rc = R[s];
	for (j = 2 * s; j <= m; j = 2 * j)
	{                                              //��key�ϴ�ĺ��ӽ������ɸѡ
		bj[6]++;
		if (j<m&&R[j].key<R[j + 1].key)            //jΪkey�ϴ�ļ�¼���±�
			j = j + 1;
		if (rc.key >= R[j].key)                    //rcӦ������s�� 
			break;
		R[s] = R[j];
		yd[6]++;
		s = j;
	}
	R[s] = rc;
}

//������
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
	cout << " ������";
	show(r, n);
}

//�����ʽ
void Display()
{
	long i, n;
	data R[MAX];
	cout << " ������Ҫ����Ƚϵ����ָ���:" << endl;
	cin >> n;
	for (i = 1; i <= n; i++)
		R[i].key = rand() % 1000;	                      //��������������������������� 
	cout << " ����ǰ������˳��:" << endl;
	for (i = 1; i <= n; i++)
		cout << R[i].key << " ";
	cout << endl;
	BubbleSort(R, n);                                     //ð������ 
	InsertSort(R, n);                                     //ֱ�Ӳ�������
	SelectSort(R, n);                                     //��ѡ������  
	ShellSort(R, n);                                      //ϣ������
	HeapSort(R, n);                                       //������ 
	QuickSort(R, 0, n);                                   //��������
	cout << " ��������"; show(R, n);
}
int main()
{
	Display();
	cout << " �ȽϵĽ��" << endl;
	cout << " ����ʽ" << "\t\t" << " �Ƚϴ���" << "\t" << " �ƶ�����" << endl;
	cout << " ð������" << "\t\t" << bj[1] << "\t\t" << yd[1] << endl;
	cout << " ֱ�Ӳ�������" << "\t\t" << bj[2] << "\t\t" << yd[2] << endl;
	cout << " ��ѡ������" << "\t\t" << bj[3] << "\t\t" << yd[3] << endl;
	cout << " ��������" << "\t\t" << bj[4] << "\t\t" << yd[4] << endl;
	cout << " ϣ������" << "\t\t" << bj[5] << "\t\t" << yd[5] << endl;
	cout << " ������" << "\t\t\t" << bj[6] << "\t\t" << yd[6] << endl;
}

