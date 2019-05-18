#include <iostream>
#include <string>


int main(){
    std::string expression;
    std::cin >> expression;
    try{
        Expression result(expression);
        std::cout << result.answer();
    }
}