#include <string>

#include "expresion.hpp"

Queue<char,444> 
Expresion::turnPostfixedQueue(Queue<char,444>& infixQueue) {
    Stack<char,444> operators;
    Queue<char,444> postfixedQueue;

    while(!infixQueue.isEmpty()){
        char currentCharacter = infixQueue.dequeue();

        //Operando 
        if (isOperando(currentCharacter)){
            postfixedQueue.enqueue(currentCharacter);
        
        //Parentesis (
        } else if (currentCharacter == '('){
            operators.push(currentCharacter);

        //Parentesis )
        }else if (currentCharacter == ')'){

            while ((!operators.isEmpty()) && (operators.getTopS() !='(')) {
                postfixedQueue.enqueue(operators.pop());
            }
            if (operators.isEmpty()){
                throw Exception ("Paréntesis no coincidentes: ')' sin coincidencia con '('");
            }
            operators.pop();
        
        //Operador
        }else{
            while ((!operators.isEmpty()) &&
                   (operators.getTopS() != '(' )&&
                   (getInsidePriorityS(operators.getTopS()) >= getOutsidePriorityS(currentCharacter))){
                postfixedQueue.enqueue(operators.pop());
            }
            operators.push(currentCharacter);
        }
    }

    //vaciar operadores que quedan en la pila
    
    while (!operators.isEmpty()){
        char top = operators.pop();
        if (top == '(' || top == ')'){
            throw Exception("Parentesis no coinsidentes: '(' sin ')'");
        }
        postfixedQueue.enqueue(top);
    }
    return postfixedQueue;
}



int Expresion::getOutsidePriorityS(char op) {
    int precedenceO;  //Procedencia afuera de la pila 

    switch (op){
        case '^': 
            precedenceO = 4;
            break;
        case '*': case '/': 
            precedenceO = 2;
            break;
        case '+': case '-': 
            precedenceO = 1;
            break;
        case '(':
            precedenceO = 5;
        break;    
        default:
        throw Exception("Operador desconocido fuera de la pila");  
    }
        return precedenceO;
}


int Expresion::getInsidePriorityS(char op) {
    int precedenceI; //Precedencia adentro de la pila

    switch (op){
         case '^': 
            precedenceI = 3;
            break;
        case '*': case '/': 
            precedenceI = 2;
            break;
        case '+': case '-': 
            precedenceI = 1;
            break;
        case '(':
            precedenceI = 0;
        break;      
        default:
        throw Exception("Operador desconocido dentro de la pila");
    }
        return precedenceI;
}

bool Expresion::isOperando(char character) const {
    return ((toupper(character) >= 'A') && (toupper(character) <= 'Z'));
}

bool Expresion::isValid(const std:: string& str) const {

    for (char character : str ){
        if (!isOperando(character)
        && character != '^' && character != '*'
        && character != '/' && character != '+'
        && character != '-' && character != '('
        && character != ')')  {
            return false; 
        }
    }
    return true;
}

