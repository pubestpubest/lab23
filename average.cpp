#include<iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    if(argc==1)
        cout<<"Please input numbers to find average.";
    else{
        float sum{};
        for (int i = 1; i < argc; i++){
            sum+=atof(argv[i]);
        }
        cout<<"---------------------------------\n";
        cout<<"Average of "<<argc-1<<" numbers = "<<sum/(float)(argc-1);
        cout<<"\n---------------------------------\n";
    }
    return 0;
}

