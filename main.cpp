#include <iostream>
#include <stack>

#define ASCII_INITIAL_NUMBER_CHARACTER 67 

int main()
{
    std::stack<char> left_stack;
    std::stack<char> middle_stack;
    std::stack<char> right_stack;

    unsigned short int number_of_rings = 0;

    // Função para inicializar a pilha esquerda:
    std::cout << "Digite a quantidade de argolas desejada:\n" << std::endl;
    std::cin >> number_of_rings;

    for (int i = number_of_rings; i > 0; i--)
    {
        left_stack.push(i);
        std::cout << left_stack.top() << " ";
    }
    std::cout << std::endl;
}