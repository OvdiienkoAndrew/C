#include <iostream>
#include <fstream>
using namespace std;
void readTextFromFile(char* filename, char* lines, int len) 
{
    ifstream fin(filename);
    if (!fin.is_open()) 
    {
        cout << "\n\tError opening file!\n";
        return;
    }

    if (fin.peek() == ifstream::traits_type::eof()) 
    {
        cout << "\n\tFile is empty!\n";
        fin.close();
        return;
    }

    const int MAX_LEN = 80;
    char buf[MAX_LEN+1];
    int idx = 0;
    while (fin.getline(buf, MAX_LEN+1)) 
    {
        if (fin.fail()) 
        {
            cout << "\n\tFile read error!\n";
            fin.close();
            return;
        }
        int len2 = strlen(buf);
        if (idx + len2 + 1 >= len) 
        {
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
void replacePunctuation(char* text) 
{
    char punctuation[] = {'.', ',', ';', ':', '!','?', '(', ')', '[', ']', '{', '}'};
    int len = sizeof(punctuation) / sizeof(punctuation[0]);

    for (int i = 0; text[i] != '\0'; i++) 
    {
        for (int j = 0; j < len; j++) 
        {
            if (text[i] == punctuation[j]) 
            { 
                text[i] = ' '; 
                break;
            }
        }
    }
}
void r1(char* text) {
    char punctuation[] = {' '};
    int len = sizeof(punctuation) / sizeof(punctuation[0]);

    for (int i = 0; text[i] != '\0'; i++) 
    {
        for (int j = 0; j < len; j++) 
        {
            if (text[i] == punctuation[j]) 
            {
                text[i++] = '\n';
                text[i] = '\t';
                break;
            }
        }
    }
}
void my_memmove(char* dest, char* src, int size) 
{
    for (int i=0; i<size; i++) 
    {
        dest[i] = src[i];
    }
}
void coutfile(char dest[81], char searchChar, int count, char* word)
{
    cout << "\n\tText: \"" << dest << "\"\n\tSearch letter \"" << searchChar << "\".\n\n\tWord:\n\n\t";
    cout << word;
    cout << "\n\tNumber of words that contain the character \"" << searchChar << "\": " << count << ".";
}
void printtofile(char* filename, char dest[81], char searchChar, int count, char* word)
{
    ofstream file(filename);
    if (!file.is_open()) 
    {
        cerr << "\tError opening file.\n";
        return;
    }
    file << "\n\tText: \"" << dest << "\"\n\tSearch letter \"" << searchChar << "\".\n\n\tWord:\n\n\t";
    file << word;
    file << "\n\tNumber of words that contain the character \"" << searchChar << "\": " << count << ".";
    file.close();
}

int main(int argc, char *argv[])
{
    char filename[101];
    char filename2[101];
    const int MAX_TEXT_LENGTH = 80;
    char text[MAX_TEXT_LENGTH + 1];
    cout << "\n\tThe length of the text line mustn't exceed 80 characters.\n\tRead text from file? (y/n)\n\t";
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
    if (choice == 'y')
    {
        char choice2;
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
        readTextFromFile(filename, text, MAX_TEXT_LENGTH + 1);
        cout << "\n\tDisplay input file text on screen? (y/n)\n\t";
        char choice3;
        x = false;
        while (x == false)
        {
            cin >> choice3;
            switch(choice3)
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
        if (choice3 == 'y')
        {
            cout << text;
        }
    }
    if (choice == 'n')
    {
        cin.ignore();
        cout << "\n\tEnter the text.\n\t";
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
    char dest[81];
    my_memmove(dest, text, 81);
    replacePunctuation(text);
    char searchChar;
    cout << "\n\tEnter a letter to search for: ";
    cin >> searchChar;
    cout << endl;
    int count = 0;
    char word1[81] = {0};
    char *word = strtok(text, " \r\n"); // используем строку разделителей, включая символ возврата каретки
    while (word != NULL)
    {
        if (strchr(word, searchChar) != NULL)
        {
            ++count;
            cout << "\t" << word << endl;
            strcat(word1, word);
            strcat(word1, " " );
        }
        word = strtok(NULL, " \r\n"); // также используем строку разделителей второй раз
    }
    r1(word1);
    cout << "\n\tNumber of words that contain the character \"" << searchChar << "\": " << count << ".";
    x = false;
    cout << "\n\n\tWrite data to a file? (y/n) ";
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
    if (choice == 'y') 
    {
        cout << "\n\tThe name of the output file will end with \"_out.\" and extension \".dat\".";
        cout << "\n\tThe first 1-3 characters can be taken from the names of the input file:";
        cout << "\n\t\"1\" - copy the first character of the input file;";
        cout << "\n\t\"2\" - copy the first two characters of the input file;";
        cout << "\n\t\"3\" - copy the first three characters of the input file;";
        cout << "\n\t\"w\" - write your own 1-3 characters.\n\t";
        char choice5;
        x = false;
        while (x == false)
        {
            cin >> choice5;
            switch(choice5)
            {
                case '1':
                        strncpy(filename2, filename, 1);
                        filename2[1] = '\0'; // задаем конец строки
                        x = true;
                        break;

                case '2':
                        strncpy(filename2, filename, 2);
                        filename2[2] = '\0';
                        x = true;
                        break;

                case '3':
                        strncpy(filename2, filename, 3);
                        filename2[3] = '\0';
                        x = true;
                        break;

                case 'w':
                        cin.ignore();
                        cout << "\n\tEnter the first 1-3 letters of the file name: ";
                        cin >> filename2;
                        if(!cin || strlen(filename2) > 3 || strlen(filename2) < 1)
                        {   
                            for (int i=0; i< 101; i++)
                            {
                                filename2[i] = 0;
                            }
                            strcpy(filename2, "bot");
                        }
                        x = true;
                        break;
                default: 
                        cout << "\n\tWhat did you mean?\n\tRetype your input.\n\t";
                        break;
            }
        }
        char filename3[] = "_out.dat";
        strcat(filename2, filename3);
        cout << "\n\tOutput file name: \"" << filename2 << "\".";
        printtofile(filename2, dest, searchChar, count, word1);
        cout << "\n\tDisplay the contents of the output file? (y/n)";
        char choice6;
        x = false;
        while (x == false)
        {
            cin >> choice6;
            switch(choice6)
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
        if (choice6 == 'y')
        {
            coutfile(dest, searchChar, count, word1);
        }
    }
    cout << "\n\n";
    return 0;
}