#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <fstream>

using namespace std;

//template <class T>
class Sorter{
public :
//    virtual void sort(vector<int> arr,int size);
    virtual void sort(vector<int> &arr,int size)=0;
//    ~Sorter();


};

//template <class T>
class ShellSorter: public Sorter{
public :
void sort(vector<int> &arr,int size){
     for (int gap = size/2; gap > 0; gap /= 2)
    {

        for (int i = gap; i < size; i += 1)
        {

            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];

            arr[j] = temp;
        }
    }

}
};

//template <class T>
class QuickSorter: public Sorter{
public :

void swap(int *x,int *y){
int *temp = x;
x=y;
y=temp;
}
int partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {

        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quicksort(vector<int> &arr, int low, int high)
{
//    cout<<low<<endl;
    if (low < high)
    {


        int pi = partition(arr, low, high);


        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

void sort(vector<int> &arr,int size){
quicksort(arr,0,size-1);
}

};

//template <class T>
class SelectionSorter:public Sorter{
public :

    void swap(int *x ,int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
void sort(vector<int> &arr, int n)
{
    int i, j, min_idx;

    for (i = 0; i < n-1; i++)
    {
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;

        swap(&arr[min_idx], &arr[i]);
    }
}
};

class Testbed{
 public:

     void merge(vector<int> &arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }


    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }


    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int> &arr, int l, int r)
{
    if (l < r)
    {

        int m = l+(r-l)/2;

        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}
     /////////////////////////////////////////////////////////////
     vector<int> GenerateRandomList(int min,int max,int size){
     random_device rd;
     mt19937 eng(rd());
     uniform_int_distribution<> distr(min, max);
     vector<int> randomlist;
     for(int i=0;i<size;i++){
        randomlist.push_back(distr(eng));
     }
     return randomlist;
     }

     vector<int> GenerateReverseOrderedList(int min,int max,int size){
     vector<int> reservedorderedlist = GenerateRandomList(min,max,size);
     mergeSort(reservedorderedlist,0,size-1);
     reverse(reservedorderedlist.begin(),reservedorderedlist.end());
     return reservedorderedlist;
     }
     double RunOnce(Sorter *s,vector<int> data,int size){
         clock_t start,end;
         start = clock();
         s->sort(data,size);
         end = clock();
         double timeinmsecs = ((double) (end - start)) * 1000 / CLOCKS_PER_SEC;
         return timeinmsecs;
     }

     double RunAndAverage(Sorter *s,bool type,int min,int max,int size,int sets_num){
         double cumulativetime=0;
         if(type==0){
            for(int i=0;i<sets_num;i++){
               vector<int> temp =  GenerateRandomList(min,max,size);
               cumulativetime+=RunOnce(s,temp,size);}
                }
         else{
               for(int i=0;i<sets_num;i++){
               vector<int> temp =  GenerateReverseOrderedList(min,max,size);
               cumulativetime+=RunOnce(s,temp,size);
               }

         }
         return cumulativetime/sets_num;
     }

     void RunExperient (Sorter *s,bool type,int min,int max,int min_val,int max_val,int sets_num,int step,ofstream &obj){
         double cumulativetime = 0;
         cout <<"set_size"<<setw(20)<<"average_time"<<endl;

     while(min_val<=max_val){
            double averagetime = RunAndAverage(s,type,min,max,min_val,sets_num);
            obj<<min_val<<","<<averagetime<<endl;
            cout <<min_val<<setw(20)<<averagetime<<endl;
            min_val+=step;
     }
     }

};


int main()
{
    Testbed test;
    Sorter *shell = new ShellSorter;
    Sorter *quick = new QuickSorter;
    Sorter *Selection = new SelectionSorter;

   ofstream random_shell("random_shell.csv",ios::app);
   random_shell<<"array_size,"<<"shellTime"<<endl;
   test.RunExperient(shell,0,0,1000,50000,500000,100,1000,random_shell);

      ofstream random_quick("random_quick.csv",ios::app);
   random_quick<<"array_size,"<<"quikcTime"<<endl;
   test.RunExperient(quick,0,0,1000,50000,500000,100,1000,random_quick);

      ofstream random_selection("random_selection.csv",ios::app);
   random_selection<<"array_size,"<<"selectionTime"<<endl;
   test.RunExperient(Selection,0,0,1000,50000,500000,100,1000,random_selection);

   /////////////////////////////////////////////////reserved
//
   ofstream reserved_shell("reserved_shell.csv",ios::app);
   reserved_shell<<"array_size,"<<"shellTime"<<endl;
   test.RunExperient(shell,1,0,1000,50000,500000,100,1000,reserved_shell);

      ofstream reserved_quick("reserved_quick.csv",ios::app);
   reserved_quick<<"array_size,"<<"quikcTime"<<endl;
   test.RunExperient(quick,1,0,1000,50000,500000,100,1000,reserved_quick);
//
      ofstream reserved_selection("reserved_selection.csv",ios::app);
   reserved_selection<<"array_size,"<<"selectionTime"<<endl;
   test.RunExperient(Selection,1,0,1000,1000,50000,100,1000,reserved_selection);












        return 0;
}
