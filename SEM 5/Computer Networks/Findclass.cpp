#include<bits/stdc++.h>
using namespace std;
char Findclass(char cls[])
{
    char ans[4];//to store the first octet in a particular character array 
    int i=0;
    // for(int x=0;x<12;x++)
    // {
    //     if(cls[i]=='.')
    //     {
    //         ans[i]=cls[i];
    //         i++;
    //     }   
    //     else
    //     {
    //         i--;
    //     }
        
    
    
    while(cls[i]!='.')
    {
        ans[i]=cls[i];
        i++;
    }
    i--;
    int j=0,k=1;
    while(i>=0)
    {
        j=j+(cls[i]-'0')*k;
        k=k*10;
        i--;
    }
    if( j>=0 && j<=127)
    {
        return 'A';//class a
    }
    else if(j>127 and j<=191)
    {
        return 'B';//class b
    }
    else if(j>191 and j<=223)
    {
        return 'C';//class c
    }
    else if(j>223 and j<=239)
    {
        return 'D';//class d
    }
    else if(j>239 and j<=255)
    {
        return 'E';//class e
    }
}
int main()
{
    cout<<"Enter ip address:";
    char cls[12];
    cin>>cls;
    char ip=Findclass(cls);
    cout<<"Given IP address belongs to the class: "<<ip;
}