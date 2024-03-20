#include <iostream>
#include <fstream>
using namespace std;
void readTextFromFile(char* filename, char* lines, int len) 
{
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
    cout << lines << "\n\n";
}
int main(int argc, char *argv[])
{
    const int MAX_TEXT_LENGTH = 1000001; // 1 000 000
    char text[MAX_TEXT_LENGTH];   
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
    char choice2;
    char filename[101];
    if (choice == 'y') 
    {
        x = false;
        cout << "\n\tIs the filename specified on the command line? (y/n) ";
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
        cout << "\n\t" << text;
    }
    if (choice == 'n') 
    {
        cin.ignore();
        cout << "\n\tEnter rhe text.\n\t";
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
    cout << "\n\n";
    char punctuation[] = {'.', ',', ';', ':', '!','?', '(', ')', '[', ']', '{', '}', '<', '>'};
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
    char* word_start = text;
    while (*word_start != '\0') 
    {
        while (*word_start == ' ' || *word_start == '\n' || *word_start == '\t') 
        { 
            word_start++;
        }
        char* word_end = word_start;
        while (*word_end != '\0' && *word_end != ' ' && *word_end != '\n' && *word_end != '\t') 
        {
            word_end++;
        }
        if (word_start == word_end) 
        {
            word_start = word_end;
            continue;
        }
        bool repeated_letters[256] = {0};
        for (char* letter = word_start; letter < word_end; letter++) 
        {
            if (repeated_letters[*letter]) 
            {
                continue;
            }
            for (char* next_letter = letter + 1; next_letter < word_end; next_letter++) 
            {
                if (*letter == *next_letter) 
                {
                    repeated_letters[*letter] = true;
                    break;
                }
            }
        }
        bool has_repeated_letters = false;
        for (size_t i = 0; i < 256; i++)
        {
            if (repeated_letters[i])
            {
                has_repeated_letters = true;
                break;
            }
        }
        if (has_repeated_letters) 
        {
            cout << "\tWord: ";
            for (char* print_letter = word_start; print_letter < word_end; print_letter++)
            {
                cout << *print_letter;
            }
            cout << " | Repeating letters: ";

            for (size_t i = 0; i < 256; i++) 
            {
                if (repeated_letters[i])
                {
                    cout << static_cast<char>(i) << ", ";
                }
            }
            cout << "\b\b.\n\n";
        }
        word_start = word_end;
    }
    cout << "\n\n";
    return 0;
}