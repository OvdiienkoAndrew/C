#include <iostream>
using namespace std;
const int N_LEN = 1000;
void strcpy(char* dest, char* src)
{
    int i = 0;
    while (src[i] != '\0' && i < N_LEN + 1)
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}
int strlen(char*s)
{
    int i;
    for(i=0; s[i]!='\0'; ++i)
    ;
    return i;
}
void swap(char * & a, char * & b)
{
    char* t = a; a=b; b=t;
}
void sort(char** s, int n)
{
    for(int i=0; i<n-1; ++i)
        for(int j=i+1; j<n; ++j)
            if(strlen(s[i]) > strlen(s[j]))
                swap(s[i], s[j]);
}
int main()
{
    int n;
    cout << "\nN ? = ";
    cin >> n;
    cout << "\n";
    char **s = new char*[n];
    for(int i=0; i<n; ++i)
    {
        char buf[N_LEN+1];
        cout << "String[" << i << "] ? = ";
        cin >> buf;
        int len = strlen(buf);
        s[i] = new char[len+1];
        strcpy(s[i], buf);
    }
    sort(s, n);
    cout << "\n\nSort:\n\n\n";
    for(int i=0; i<n; ++i)
        cout << "String[" << i << "] = " << s[i] << endl;
    cout << "\n\n";
    return 0;
}