#include <iostream>

int main()
{

    std::cout << "Calculator is running" << std::endl;

    while (true)
    {
        char op;
        float num1, num2;

        std::cin >> op;

        if (op == 'q')
        {
            return 0;
        }

        std::cin >> num1 >> num2;

        std::cout << "Your expression is: " << num1 << " " << op << " " << num2 << std::endl;

        switch (op)
        {

        case '+':
            std::cout << num1 + num2 << std::endl;
            break;

        case '-':
            std::cout << num1 - num2 << std::endl;
            break;

        case '*':
            std::cout << num1 * num2 << std::endl;
            break;

        case '/':
            std::cout << num1 / num2 << std::endl;
            break;

        default:
            std::cout << "Error! operator is not correct" << std::endl;
            break;
        }
    }

    return 0;
}
