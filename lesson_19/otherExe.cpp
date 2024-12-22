#include <iostream>

using namespace std;

int main(int argc, char* argv[], char* env[])
{
    cout << argv[0] << " begin running" << endl;
    int i = 0;
    for(;argv[i];i++)
    {
        cout << "command argument" << i << ": " << argv[i] << endl;
    }
    for(i = 0;env[i];i++)
    {
        cout << "environment argument" << i << ": " << env[i] << endl;
    }
    cout << argv[0] << " stop running" << endl;
    return 0;
}
