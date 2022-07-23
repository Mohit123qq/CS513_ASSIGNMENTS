#include<iostream>
#include<chrono>
#include<fstream>
#include<vector>
#include<bits/stdc++.h>

using namespace std;

int main()
{
    fstream f;
    string r;
    long long int t=0,p=0,l=0;
    vector<long long int>v;
    vector<long long int>d;
    f.open("TEST_6.txt", ios::in | ios::out);
    if(!f)cout<<"error";
    else
    {
        cout<<"open.......................\n";
        srand(time(0));
        for (int i = 0; i < 100; i++)
        {
            t=rand()%1000000 ;
            if(find(v.begin(),v.end(),t)==v.end())
            {
                v.push_back(t);
                f<<"INSERT "<<t<<"\n";
            }
            else
            {
                i--;
            }
        }
        l=0;
        for (int i = 0; 1 ; i++)
        {
            if(l==60000 -100)break;  // THIS WILL GENERATE 60000 CASES
            t=rand()%1000000 ;
            if(find(v.begin(),v.end(),t)==v.end())
            {
                v.push_back(t);
                f<<"INSERT "<<t<<"\n";
                l++;
            }
            else
            {
                i--;
            }
            if(rand()%2)
            {
                p=rand()% v.size();
                if(find(d.begin(),d.end(),p)==d.end())
                {
                   f<<"DELETE "<<v[p]<<"\n";
                   d.push_back(p);
                   l++;
                }
                else
                {
                    continue;
                   
                }
            }
        }
        //  while (!f.eof())
        //  {
        //      f>>r;
        //      if(r=="INSERT")l++;
        //  }
         
        
        cout<<l<<"\n";
        // for (int i = 0; i < v.size(); i++)
        // {
        // //     cout<<rand()%2<<"\n";
        //     //    cout<<i<<" "<<v[i]<<"\n";
        //     //    for (int j = i+1; j < 300; j++)
        //     //    {
        //     //        if(v[i]==v[j])cout<<"at--------> "<<i<<" "<<j<<" "<<v[i]<<"\n";
        //     //    }
               
        // }
        cout<<"\n\n\n";
        cout<<v.size();
    }


    return 0;
}