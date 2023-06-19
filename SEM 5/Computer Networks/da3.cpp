#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
void hamming(int sender[],int receiver[],int n)//hamming code
{
    int paritybitS1 = sender[0] xor sender[1] xor sender[3] xor sender[4] xor sender[6];
    int paritybitS2 = sender[0] xor sender[2] xor sender[3] xor sender[5] xor sender[6];
    int paritybitS3 = sender[1] xor sender[2] xor sender[3] xor sender[7];
    int paritybitS4 = sender[4] xor sender[5] xor sender[6] xor sender[7];

    int paritybitR1 = receiver[0] xor receiver[1] xor receiver[3] xor receiver[4] xor receiver[6];
    int paritybitR2 = receiver[0] xor receiver[2] xor receiver[3] xor receiver[5] xor receiver[6];
    int paritybitR3 = receiver[1] xor receiver[2] xor receiver[3] xor receiver[7];
    int paritybitR4 = receiver[4] xor receiver[5] xor receiver[6] xor receiver[7];

    int syndrome1 = paritybitR1 xor paritybitS1;
    int syndrome2 = paritybitR2 xor paritybitS2;
    int syndrome3 = paritybitR3 xor paritybitS3;
    int syndrome4 = paritybitR4 xor paritybitS4;

    int Syndrome = syndrome4*(8) + syndrome3*(4) + syndrome2*(2) + syndrome1*(1);

    cout<<"Syndrome is: "<<Syndrome<<endl;

    int pos = -1;
    int parityPos = -1;
    switch (Syndrome){
    case 1:{
        pos = -2;
        parityPos = 1; 
        break;
    }
        
    case 2:{
        pos = -2;
        parityPos = 2; 
        break;
    }

    case 3:{
        pos = 1;
        // parityPos = 1; 
        break;
    }
        
    case 4:{
        pos = -1;
        parityPos = 3; 
        break;
    }

    case 5:{
        pos = 2;
        // parityPos = 1; 
        break;
    }
        
    case 6:{
        pos = 3;
        // parityPos = 2; 
        break;
    }

    case 7:{
        pos = 4;
        // parityPos = 1; 
        break;
    }
        
    case 8:{
        pos = -1;
        parityPos = 4; 
        break;
    }

    case 9:{
        pos = 5;
        // parityPos = 1; 
        break;
    }
        
    case 10:{
        pos = 6;
        // parityPos = 2; 
        break;
    }

    case 11:{
        pos = 7;
        // parityPos = 1; 
        break;
    }
        
    case 12:{
        pos = 8;
        // parityPos = 2; 
        break;
    }

    default:{
        pos = -1;
        parityPos = -1;
        break;
    }   
    }

    if(pos == -1 && parityPos == -1){
        cout<<"No Error"<<endl;
    }
    if(parityPos != -1){
        cout<<"Parity position is wrong at position: "<<parityPos<<endl;
    }else{
        cout<<endl;
        cout<<"The sender bits were:   ";
        for(int i = n-1; i>=0; i--){
            cout<<sender[i];
        }
        cout<<endl;
        cout<<"The receiver bits were: ";
        for(int i = n-1; i>=0; i--){
            cout<<receiver[i];
        }
        cout<<endl;
        cout<<"Data bit wrong position: "<<pos<<endl;
        // cout<<endl;
        if(receiver[pos-1] == 1){
            receiver[pos-1] = 0;
        }else{
            receiver[pos-1] = 1;
        }
        cout<<"The corrected receiver bits are: ";
        for(int i = n-1; i>=0; i--){
            cout<<receiver[i];
        }
        cout<<endl;
    }
}
//xor for CRC
void XOR(int* total, int total_bits, int * generator, int generate_n, int index){
    for(int i = 0; i<generate_n; i++){
        if(total[index+i] == generator[i]){
            total[index+i] = 0;
        }else{
            total[index+i] = 1;
        }
    }
}
//function for CRC
void CRC(int* total, int total_bits, int * generator, int generate_n){
    for(int i = 0; i<=total_bits - generate_n; i++){
        if(total[i] == 1){
            XOR(total, total_bits,generator,generate_n, i);
            i--;
            // cout<<"After XOR: ";
            // for(int i = 0; i<total_bits; i++){
            //     cout<<total[i];
            // }
            // cout<<endl;
        }
    }
}
void c_r_c(int sender[], int receiver[],int n)
{
     int n_generator;
    cout<<"Enter the number of bits in generator polynomial: ";
    cin>>n_generator;
    int generator[n_generator];
    cout<<"Enter the generator polynomial: ";
    for(int i = 0; i<n_generator;i++){
        cin>>generator[i];
    }
    cout<<endl;

    cout<<"The sender bits:   ";
    for(int i = 0; i<n; i++){
        cout<<sender[i];
    }
    cout<<endl;

    cout<<"The receiver bits: ";
    for(int i = 0; i<n; i++){
        cout<<receiver[i];
    }
    cout<<endl;

    int total_bits = n + n_generator -1;
    int total_sender[total_bits];
    for(int i = 0; i<n; i++){
        total_sender[i] = sender[i];
    }
    for(int i = n; i<total_bits; i++){
        total_sender[i] = 0;
    }

    // cout<<"After appending zeros to sender bits: ";
    // for(int i = 0; i<total_bits; i++){
    //     cout<<total_sender[i];
    // }
    // cout<<endl;
    
    CRC(total_sender, total_bits, generator, n_generator);

    // cout<<"After performing CRC on sender: ";
    // for(int i = 0; i<total_bits; i++){
    //     cout<<total_sender[i];
    // }
    // cout<<endl;
    cout<<"Check word for sender is: ";
    for(int i = 0; i<n_generator-1; i++){
        cout<<total_sender[n+i];
    }
    cout<<endl;

    cout<<"The sender bits are:   ";
    for(int i = 0; i<n; i++){
        cout<<sender[i];
    }
    for(int i = 0; i<n_generator-1; i++){
        cout<<total_sender[n+i];
    }
    cout<<endl;

    int total_receiver[total_bits];
    for(int i = 0; i<n; i++){
        total_receiver[i] = receiver[i];
    }
    for(int i = 0; i<n_generator; i++){
        total_receiver[n+i] = total_sender[n+i];
    }

    cout<<"The receiver bits are: ";
    for(int i = 0; i<total_bits; i++){
        cout<<total_receiver[i];
    }
    cout<<endl;

    CRC(total_receiver, total_bits, generator, n_generator);

    cout<<"After performing CRC on receiver: ";
    for(int i = 0; i<total_bits; i++){
        cout<<total_receiver[i];
    }
    cout<<endl;
    // cout<<"Check word for receiver is: ";
    bool found_error = false;
    for(int i = 0; i<n_generator; i++){
        // cout<<total_receiver[n+i-1];
        if(total_receiver[n+i-1]){
            // cout<<total_receiver[n+i-1]<<" ";
            // cout<<"Index: "<<n+i<<endl;
            found_error = true;
            break;
        }
    }

    if(found_error){
        cout<<"Error in transmission"<<endl;
    }else{
        cout<<"No error in transmission"<<endl;
    }
}

int main()
{
    int n;
    cout<<"Enter the number of bits: ";
    cin>>n;
    cout<<"Enter the sender bits: ";
    int sender[n];
    for(int i = n-1; i>=0; i--){
        
        cin>>sender[i];
        if(sender[i]>1 )
        {
            cout<<"You have to enter binary digits only!";
            break;
        }
    }
    cout<<endl;

    cout<<"Enter the receiver bits: ";
    int receiver[n];
    for(int i = n-1; i>=0; i--){
        cin>>receiver[i];
        if(receiver[i]>1 or receiver[i]<0)
        {
            cout<<"You have to enter binary digits only!";
            break;
        }
    }
    int choose;
    cout<<"Press 1 if you want to go for Hamming code error correction or Press 0 for crc:";
    cin>>choose;
    switch(choose)
    {
        case 1:{
            hamming(sender,receiver,n);      
            break;      
        }
        case 0:{
            c_r_c(sender,receiver,n);
            break;
        }
        default:
        {
            cout<<"You didn't press 1 or 0";
            break;
        }
}
}