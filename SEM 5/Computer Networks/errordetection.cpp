#include<iostream>

using namespace std;

void XOR(int* total, int total_bits, int * generator, int generate_n, int index){
    for(int i = 0; i<generate_n; i++){
        if(total[index+i] == generator[i]){
            total[index+i] = 0;
        }else{
            total[index+i] = 1;
        }
    }
}

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



int main()
{
    int n;
    cout<<"Enter the number of bits: ";
    cin>>n;
    cout<<"Enter the sender bits: ";
    int sender[n];
    for(int i = 0; i<n; i++){
        cin>>sender[i];
    }

    cout<<"Enter the receiver bits: ";
    int receiver[n];
    for(int i = 0; i<n; i++){
        cin>>receiver[i];
    }

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
    return 0;
}