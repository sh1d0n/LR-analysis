#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <unordered_map>
#include <fstream>

typedef std::unordered_map<char, std::string> MyMap;

std::unordered_map<int, MyMap> tableFromFile()
{
    std::unordered_map<int, MyMap> table;
    std::ifstream in("input.in");
    if(in.is_open())
    {
        int i_size, j_size;
        in >> i_size >> j_size;
        for(int i = 0; i < i_size; i++)
        {
            int firstKey;
            in >> firstKey;
            for(int j = 0; j < j_size; j++)
            {
                char secondKey;
                in >> secondKey;
                in >> table[firstKey][secondKey];
            }
        }
    }
    else
    {
        std::cout << "File not found!" << std::endl;
        system("pause");
        exit(0);
    }

    return table;
}

std::string correctInput(std::vector<char> alphabet)
{
    std::string word;
    bool finish = true;
    while(finish)
    {
        std::cout << "Enter your word >> ";
        std::cin >> word;

        bool mistake;
        for (size_t i = 0; i < word.size(); i++)
        {
            mistake = true;
            for (size_t j = 0; j < alphabet.size(); j++)
            {
                if (word[i] == alphabet[j])
                {
                    mistake = false;
                    break;
                }
            }
            if (mistake)
            {
                break;
            }
        }

        switch (mistake)
        {
            case true:
                std::cout << "There is a mistake in the word! Try again...\n" << std::endl;
                break;
            case false:
                finish = false;
                break;
        }
    }

    return word;
}

int main()
{
    std::unordered_map<int, MyMap> table = tableFromFile();

    std::vector<char> alphabet {'a', 'c', 'f'};
    std::string word = correctInput(alphabet);
    word += '$';

    std::stack<int> store;
    store.push(0);
    std::string active;
    std::string line = word;

    for(size_t i = 0; i < word.size();)
    {
        std::string action;
        action = table[store.top()][word[i]];
        if(action[0] == 'S')
        {
            active += word[i];
            std::string num;
            for(size_t j = 1; j < action.size(); j++)
            {
                num += action[j];
            }
            store.push(std::stoi(num));
            i++;
            line.erase(line.begin());
            std::cout << "Performing a shift:" << std::endl;
        }
        else if(action[0] == 'R')
        {
            std::cout << "Performing a convolution:" << std::endl;
            std::cout << "Rule execution: ";
            char rule = action[1];
            int p;
            switch(rule)
            {
                case '1':
                    for(int j = 0; j < 4; j++)
                    {
                        active.pop_back();
                        store.pop();
                    }
                    active += 'S';
                    p = std::stoi(table[store.top()][active[active.size() - 1]]);
                    store.push(p);
                    std::cout << "S->SaAc (1)" << std::endl;
                    break;
                case '2':
                    active.pop_back();
                    store.pop();
                    active += 'S';
                    p = std::stoi(table[store.top()][active[active.size() - 1]]);
                    store.push(p);
                    std::cout << "S->f (2)" << std::endl;
                    break;
                case '3':
                    for(int j = 0; j < 3; j++)
                    {
                        store.pop();
                        active.pop_back();
                    }
                    active += 'S';
                    p = std::stoi(table[store.top()][active[active.size() - 1]]);
                    store.push(p);
                    std::cout << "S->aAc (3)" << std::endl;
                    break;
                case '4':
                    for(int j = 0; j < 3; j++)
                    {
                        store.pop();
                        active.pop_back();
                    }
                    active += 'A';
                    p = std::stoi(table[store.top()][active[active.size() - 1]]);
                    store.push(p);
                    std::cout << "A->cfC (4)" << std::endl;
                    break;
                case '5':
                    for(int j = 0; j < 2; j++)
                    {
                        store.pop();
                        active.pop_back();
                    }
                    active += 'A';
                    p = std::stoi(table[store.top()][active[active.size() - 1]]);
                    store.push(p);
                    std::cout << "A->cf (5)" << std::endl;
                    break;
                case '6':
                    for(int j = 0; j < 2; j++)
                    {
                        store.pop();
                        active.pop_back();
                    }
                    active += 'C';
                    p = std::stoi(table[store.top()][active[active.size() - 1]]);
                    store.push(p);
                    std::cout << "C->aC (6)" << std::endl;
                    break;
                case '7':
                    active.pop_back();
                    store.pop();
                    active += 'C';
                    p = std::stoi(table[store.top()][active[active.size() - 1]]);
                    store.push(p);
                    std::cout << "C->a (7)" << std::endl;
                    break;
            }
        }
        else if(action[0] == 'F')
        {
            std::cout << "\nThe word belongs to this language" << std::endl;
            break;
        }
        else if(action[0] == 'e')
        {
            std::cout << "\nThe word does not belong to this language" << std::endl;
            break;
        }

        std::cout << "Word on the stack: " << active << std::endl;
        std::cout << "Word per line: " << line << "\n" << std::endl;
    }



    system("pause");
}