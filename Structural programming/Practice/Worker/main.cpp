// Програма "Радник"
#include <iostream>
using namespace std;
int main()
{
   int num;
   cout << "\n\n\n\n\n\t\t\t\t\tУ тебе є вільна хвилинка? (0/1)\n";
   while (cin >> num)
    {
        switch(num)
        {
        case 0:
            printf("\033c ");
            cout << "\n\n\n\n\n\t\t\t\tЧого не робиш свої справи, лінки? (0/1)\n";
            while (cin >> num)
            {
                switch(num)
                {
                case 0:
                    printf("\033c ");
                    cout << "\n\n\n\n\nЯ вважаю, що спочатку треба зробити легкі завдання, а потім перейти до важких. Згоден? (0/1)";
                    while (cin >> num)
                    {
                        switch(num)
                        {
                            case 0:
                                printf("\033c ");
                                cout << "\n\n\n\n\nТоді увімкни улюблену музику та спробуй виконати завдання з найближчим терміном.\n";
                                return 0;
                            break;
                            case 1:
                                printf("\033c ");
                                cout << "\n\n\n\n\nІз улюбленими хітами працювати веселіше.\n";
                                return 0;
                            break;
                        }
                    }
                break; 
                case 1:
                    printf("\033c ");
                    cout << "\n\n\n\n\nВажко перші 10 хвилин, як впоратись із ними, ніхто не відірве тобі від роботи. Спробуєш? (0/1)\n";
                    while (cin >> num)
                    {
                        switch(num)
                        {
                            case 0:
                                printf("\033c ");
                                cout << "\n\n\n\n\nТоді - ходи підняком. Або спробуй протриматись 10 хвилин, а далі дорога в одну сторону - на взліт.\n";
                                return 0;
                            break;
                            case 1:
                                printf("\033c ");
                                cout << "\n\n\n\n\n\t\t\t\t\tТак тримати, удачі.\n";
                                return 0;
                            break;
                        }
                    }
                break;
                }
            }
        break;
        case 1:
            printf("\033c ");
            cout << "\n\n\n\n\n\t\t\t\t\tНа вулиці гарна погода? (0/1)";
            while (cin >> num)
            {
                switch(num)
                {
                    case 0:
                    printf("\033c ");
                    cout << "\n\n\n\n\n\t\t\t\t\tУ тебе є шахи, і чи вмієш грати в них? (1/0)";
                    while (cin >> num)
                    {
                        switch(num)
                        {
                            case 0:
                                printf("\033c ");
                                cout << "\n\n\n\n\n\t\t\tПочитай книгу, повчи іноземні мови.\n";
                                return 0;
                            break;
                            case 1:
                                printf("\033c ");
                                cout << "\n\n\n\n\nЗіграй у шахи із друзями. Або сам із собою – так складніше, бо ти завжди знаєш, що задумав твій супротивник.\n";
                                return 0;
                            break;
                        }
                    }
                    break;
                    case 1:
                    printf("\033c ");
                    cout << "\n\n\n\n\n\t\t\t\t\tЗараз сонечко сяє? (0/1)\n";
                    while (cin >> num)
                    {
                        switch(num)
                        {
                            case 0:
                                printf("\033c ");
                                cout << "\n\n\n\n\nСпробуй відгадати загадку.\nЛетіли дві ворони. Одна біла, друга на північ. Скільки цвяхів без капелюха, якщо козир – піка?";
                                return 0;
                            break;
                            case 1:
                                printf("\033c ");
                                cout << "\n\n\n\n\n\t\t\t\tСпробуй пробігти 10-15 км. або сходити до парку.\n";
                                return 0;
                            break;
                        }
                    }
                    break;
                }
            }
        break;
        }
    }
}  
