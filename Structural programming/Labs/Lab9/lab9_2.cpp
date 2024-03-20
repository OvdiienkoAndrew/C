#include <iostream>
#include <fstream>
using namespace std;
void readTextFromFile(char* filename, char* lines, int len) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "\n\tError opening file!\n";
        return;
    }

    if (fin.peek() == ifstream::traits_type::eof()) {
        cout << "\n\tFile is empty!\n";
        fin.close();
        return;
    }

    const int MAX_LEN = 1000000;
    char buf[MAX_LEN+1];
    int idx = 0;
    while (fin.getline(buf, MAX_LEN+1)) {
        if (fin.fail()) {
            cout << "\n\tFile read error!\n";
            fin.close();
            return;
        }
        int len2 = strlen(buf);
        if (idx + len2 + 1 >= len) {
            cout << "\n\tError: buffer exceeded!\n";
            fin.close();
            return;
        }
        memcpy(lines + idx, buf, len2);
        idx += len2;
        lines[idx++] = '\n';
    }
    lines[idx] = '\0';
    fin.close();
    cout << "\n\t" << lines << "\n\n";
}
void my_memmove(char* dest, char* src, int size) 
{
    for (int i=0; i<size; i++) 
    {
        dest[i] = src[i];
    }
}
int my_strspn(char* str1, char* str2) 
{
    if (!str1 || !str2) 
    { // проверка на nullptr
        return -1;
    }
    int len1 = 0;
    while (str1[len1]) {
        bool found = false;
        for (int i = 0; str2[i]; i++) {
            if (str1[len1] == str2[i]) {
                found = true;
                break;
            }
        }
        if (!found) {
            break;
        }
        len1++;
    }
    return len1;
}
int main(int argc, char *argv[])
{
    const int MAX_TEXT_LENGTH = 1000001; // 1 000 000
    char text[MAX_TEXT_LENGTH];
    char text1[MAX_TEXT_LENGTH];
    char text2[MAX_TEXT_LENGTH];     
    cout << "\n\tEnter the text and the program will display words that have repeating characters, as well as all characters that are repeated in this word.\n\tWARNING. Must be no more than 1 000 000 characters.\n\n\tRead text from file? (y/n) ";
    bool x = false;
    char choice;
    while (x == false)
    {
        cin >> choice;
        switch(choice)
        {
            case 'y':
                    x = true;
                    break;
            case 'n':
                    x = true;
                    break;
            default: 
                    cout << "\n\tWhat did you mean?\n\tRetype your input.\n\t";
                    break;
        }
    }
    for(;;)
    {
        cout << "\n\tThis program presents two artificial functions: \"memmove()\", \"strspn()\".\n\n\t The \"memmove()\" function in C++ copies a given number of bytes from one area of memory to another, including the possibility of area intersections. This function allows you to safely copy data to memory locations that may overlap with the original memory area in case the data is copied from right to left.\n\n\tThe \"strspn()\" function in C++ finds the length of the initial substring of the string str, which consists only of characters from the string accept. That is, if str begins with a substring consisting only of the characters of the specified accept string, then strspn will return the length of that substring.\n\tTo use them you need to press:\n\t\t\"m\" - if you want to use only the function \"memmove()\";\n\t\t\"s\" - if you want to use only the function \"strspn()\";\n\t\t\"b\" - if you want to use both functions.\n\t\t\"0\" - end the program.\n\t";
        char choice3;
        x = false;
        while (x == false)
        {
            cin >> choice3;
            switch(choice3)
            {
                case 'm':
                        x = true;
                        break;
                case 's':
                        x = true;
                        break;
                case 'b':
                        x = true;
                        break;
                case '0':
                        cout << "\n\n\tEnd of program.\n\n";
                        return 0;
                default: 
                        cout << "\n\tWhat did you mean?\n\tRetype your input.\n\t";
                        break;
            }
        }
        char filename[101];
        if (choice == 'y') 
        {
            char choice2;
            x = false;
            cout << "\n\tIs the filename specified on the command line? (y/n)\n\t";
            while (x == false)
            {
                cin >> choice2;
                switch(choice2)
                {
                  case 'y':
                            x = true;
                            break;
                  case 'n':
                            x = true;
                            break;
                 default: 
                            cout << "\n\tWhat did you mean?\n\tRetype your input.\n\t";
                            break;
                }
            }
            if (choice2 == 'y')
            {
                if (argc == 2) 
                {
                    strcpy(filename, argv[1]);
                }
                else 
                {
                    cout << "\n\tThe file name was not specified. Enter file name (full file name): ";
                    cin >> filename;
                }
            }
            if (choice2 == 'n')
            {
                cout << "\n\tEnter the file name (full file name): ";
                cin >> filename;
            }
            readTextFromFile(filename, text, MAX_TEXT_LENGTH);
            readTextFromFile(filename, text1, MAX_TEXT_LENGTH);
            readTextFromFile(filename, text2, MAX_TEXT_LENGTH);
        }
        if (choice == 'n')
        {
            if (choice3 == 'm')
            {
                cin.ignore();
                cout << "\n\tEnter the text for implementation the function \"memmove()\".\n\t";
                cin.getline(text, MAX_TEXT_LENGTH);
                while (cin.fail()) 
                {
                    cerr << "\n\tError: input string too long.";
                    cerr << "\n\tEnter the text.\n\t";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.getline(text, MAX_TEXT_LENGTH);
                }
            }
            if (choice3 == 's')
            {
                cin.ignore();
                cout << "\n\tEnter the word 1 for implementation the function \"strspn()\".\n\t";
                cin.getline(text1, MAX_TEXT_LENGTH);
                while (cin.fail()) 
                {
                    cerr << "\n\tError: input string too long.";
                    cerr << "\n\tEnter the word 1 for implementation the function \"strspn()\".\n\t";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.getline(text, MAX_TEXT_LENGTH);
                }
                cout << "\n\tEnter the word 2 for implementation the function \"strspn()\".\n\t";
                cin.getline(text2, MAX_TEXT_LENGTH);
                while (cin.fail()) 
                {
                    cerr << "\n\tError: input string too long.";
                    cerr << "\n\tEnter the word 2 for implementation the function \"strspn()\".\n\t";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.getline(text, MAX_TEXT_LENGTH);
                }
            }
            if (choice3 == 'b')
            {   
                cin.ignore();
                cout << "\n\tEnter the text for implementation the function \"memmove()\".\n\t";
                cin.getline(text, MAX_TEXT_LENGTH);
                while (cin.fail()) 
                {
                    cerr << "\n\tError: input string too long.";
                    cerr << "\n\tEnter the text.\n\t";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.getline(text, MAX_TEXT_LENGTH);
                }
                cout << "\n\tEnter the word 1 for implementation the function \"strspn()\".\n\t";
                cin.getline(text1, MAX_TEXT_LENGTH);
                while (cin.fail()) 
                {
                    cerr << "\n\tError: input string too long.";
                    cerr << "\n\tEnter the word 1 for implementation the function \"strspn()\".\n\t";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.getline(text, MAX_TEXT_LENGTH);
                }
                cout << "\n\tEnter the word 2 for implementation the function \"strspn()\".\n\t";
                cin.getline(text2, MAX_TEXT_LENGTH);
                while (cin.fail()) 
                {
                    cerr << "\n\tError: input string too long.";
                    cerr << "\n\tEnter the word 2 for implementation the function \"strspn()\".\n\t";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.getline(text, MAX_TEXT_LENGTH);
                }
            }
        }
        if (choice3 == 'm')
        {
            char dest[sizeof(text)];
            memmove(dest, text, sizeof(text));
            cout << "\n\tArray content: \"" << text << "\"";
            cout << "\n\n\tProgram use the function \"memmove()\".\n\tA copy of the contents of the previous array: \"" << dest << "\"\n";
            char my_dest[sizeof(text)];
            my_memmove(my_dest, text, sizeof(text));
            cout << "\n\tProgram use the function \"my_memmove()\".\n\tA copy of the contents of the previous array: \"" << my_dest << "\"\n";
        }
        if (choice3 == 's')
        {   
            cout << "\n\tArray content word 1: \"" << text1 << "\"";
            cout << "\n\tArray content word 2: \"" << text2 << "\"";
            cout << "\n\n\tProgram use the function \"strspn()\".\n\tNumber of identical elements in two rows: " << strspn(text1, text2) << ".";
            cout << "\n\n\tProgram use the function \"my_strspn()\".\n\tNumber of identical elements in two rows: " << my_strspn(text1, text2) << ".";
        }
        if (choice3 == 'b')
        {
            char dest[sizeof(text)];
            memmove(dest, text, sizeof(text));
            cout << "\n\tArray content: \"" << text << "\"";
            cout << "\n\n\tProgram use the function \"memmove()\".\n\tA copy of the contents of the previous array: \"" << dest << "\"\n";
            char my_dest[sizeof(text)];
            my_memmove(my_dest, text, sizeof(text));
            cout << "\n\tProgram use the function \"my_memmove()\".\n\tA copy of the contents of the previous array: \"" << my_dest << "\"\n";
        
            cout << "\n\tArray content word 1: \"" << text1 << "\"";
            cout << "\n\tArray content word 2: \"" << text2 << "\"";
            cout << "\n\n\tProgram use the function \"strspn()\".\n\tNumber of identical elements in two rows: " << strspn(text1, text2) << ".\n";
            cout << "\n\n\tProgram use the function \"my_strspn()\".\n\tNumber of identical elements in two rows: " << my_strspn(text1, text2) << ".\n";
        }
        cout << "\n\tBack to menu? (y/n)\n\t";
        char choice6;
        x = false;
        while (x == false)
        {
            cin >> choice6;
            switch(choice6)
            {
              case 'y':
                        cout << "\033[2J\033[H";
                        choice = 'n';
                        x = true;
                        break;
              case 'n':
                        cout << "\n\n\tEnd of program.\n\n";
                        return 0;
                        break;
             default: 
                        cout << "\n\tWhat did you mean?\n\tRetype your input.\n\t";
                        break;
            }
        }
    }
}