// Задача reverse2(варіант inplace). Ідея, алгоритм і програма.
#include <iostream>
using namespace std;
size_t my_strlen(char *s)
{
    size_t len = 0;
    while (*s != '\0') 
    {
        len++;
        s++;
    }
    return len;
}
void my_reverse(char* str, int MAX)
{
    char* end = str + my_strlen(str) - 1;
    while (str < end)
    {
        char temp = *str;
        *str++ = *end;
        *end-- = temp;
    }
}
int main() 
{
    const int MAX = 1000001;
    char Text[MAX];
    cout << "\n\tText: ? ";
    cin.getline(Text, MAX);
    cout << "\n\tText: \"" << Text << "\"\n\n";
    my_reverse(Text, MAX);
    cout << "\tReverse: \"" << Text << "\"\n\n";
    return 0;
}