#include <iostream>

int main() {

  while true {
      char op;
      float num1, num2;

      std::cout << "Enter operator: +, -, *, /: | or q if you want to exit";
      std::cin >> op;

      if (op == 'q')
      {
        return 0;
      }

      std::cout << "Enter two operands: ";
      std::cin >> num1 >> num2;
      

      switch(op) {

        case '+':
          std::cout << num1 << " + " << num2 << " = " << num1 + num2 << endl;
          break;

        case '-':
          std::cout << num1 << " - " << num2 << " = " << num1 - num2 << endl;
          break;

        case '*':
          std::cout << num1 << " * " << num2 << " = " << num1 * num2 << endl;
          break;

        case '/':
          std::cout << num1 << " / " << num2 << " = " << num1 / num2 << endl;
          break;

        default:
          std::cout << "Error! operator is not correct" << endl;
          break;
      }
    }

  return 0;
}