/*====================================Infix Form Calculator====================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct node;
typedef struct node* pointer; //define a pointer to node

typedef struct node //define contents of each node
{
    char data; //data : numbers, parenthesis, operands
    int number;
    pointer next; //pointer to next node
};

typedef pointer Stack; //define a shortcut to Stack
typedef pointer Node; //define a shortcut to aimed position in Stack

Stack createStack() //creates stacks' base
{
    Stack s;
    s = (pointer)malloc(sizeof(struct node));
    s->next = NULL;
    return s;
}

Node createNode(char data) //returns created node in memory with specific data.
{
    Node newNode;
    newNode = (pointer)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->number = NULL;
    newNode->next = NULL;
    return newNode;
}

char topOfStack(Stack s) //returns top node in the Stack
{
    Node top = s->next;
    if(top!=NULL)
        return top->data;
    else
        return NULL;
}

void pushToStack(Stack s, char data) //pushes new node on the stack
{
    Node newNode; //node pointer to deal with nodes in stack.
    newNode = createNode(data);
    newNode->number = NULL;

    newNode->next = s->next;
    s->next = newNode;
}

Node popFromStack(Stack s) //pops top node from the stack
{
    Node nextNode,flag; //nextNode pointer to top of stack , flag : is a copy of top node
    nextNode = s->next;

    if(nextNode==NULL)
        return NULL;

    flag = (pointer)malloc(sizeof(struct node));
    flag ->data = nextNode->data;
    flag->number = nextNode->number;
    s->next = nextNode->next;
    free(nextNode);
    return flag;
}
////////////////////////////////////////////////////////////////
/* these functions ends with "Int" just for Stack of integers */
Node createNodeOfInt(int number) //returns created node in memory with specific data.
{
    Node newNode;
    newNode = (pointer)malloc(sizeof(struct node));
    newNode->number = number;
    newNode->data = NULL;
    newNode->next = NULL;
    return newNode;
}

int topOfStackOfInt(Stack s) //returns top node in the Stack
{
    Node top = s->next;
    if(top!=NULL)
        return top->number;
    else
        return NULL;
}

void pushToStackOfInt(Stack s, int number) //pushes new node on the stack of integers
{
    Node newNode; //node pointer to deal with nodes in stack.
    newNode = createNodeOfInt(number);
    newNode->data = NULL;

    newNode->next = s->next;
    s->next = newNode;
}

////////////////////////////////////////////////////////////////

void moveElements(Stack source, Stack destination) // moves elements from source stack to destination stack
{
    Node current;
    while(1)
    {
        current = popFromStack(source);
        if(current==NULL)
            break;

        if(current->data==NULL)
            pushToStackOfInt(destination,current->number);
        else if(current->number==NULL)
            pushToStack(destination,current->data);
        free(current);
    }
}

void deleteContents(Stack s) //deletes contents of given stack means make it empty.
{
    Node nextNode,flag;
    nextNode = s->next;
    s->next = NULL;

    if(s==NULL)
        printf("Stack is not excited!!\n");

    else if(nextNode==NULL)
        printf("Stack is empty!!\n");

    else
        while(nextNode!=NULL)
        {
            flag = nextNode->next;
            free(nextNode);
            nextNode = flag;
        }
}

void printElementsOfStack(Stack s) //prints elements in given Stack.
{
    Node current; //Node pointer to deal with nodes in any stack.
    Stack temp = createStack();

    moveElements(s,temp); // moving elements from basic stack to temporary stack

    while(1) // loop to return elements from temporary stack to basic stack
    {
        current = popFromStack(temp);
        if(current==NULL)
            break;

        if(current->number==NULL)
        {
            pushToStack(s,current->data);
            printf("%c",current->data);
        }
        else if(current->data==NULL)
        {
            pushToStackOfInt(s,current->number);
            printf("%d",current->number);
        }
        free(current);
    }
    free(temp);
    printf("\n");
}

void printElementsOfStackOnFile(Stack s, FILE *fptOutput) //prints elements in given Stack on given file
{
    Node current; //Node pointer to deal with nodes in any stack.
    Stack temp = createStack();

    moveElements(s,temp); // moving elements from basic stack to temporary stack

    while(1) // loop to return elements from temporary stack to basic stack
    {
        current = popFromStack(temp);
        if(current==NULL)
            break;

        if(current->number==NULL)
        {
            pushToStack(s,current->data);
            fprintf(fptOutput,"%c",current->data);
        }
        else if(current->data==NULL)
        {
            pushToStackOfInt(s,current->number);
            fprintf(fptOutput,"%d",current->number);
        }
        free(current);
    }
    free(temp);
    fprintf(fptOutput,"\n");
}

int valid(char equation[], int choiceOfPrint) // checks if given equation is valid or not , choiceOfPrint : prints reason of invalidity or print "Valid" if eq. is valid.
{
    int checker1 = 0, checker2 = 0, checker3 = 0, checker4 = 0; //checker from checker1 to checker4 to check closed parenthesis
    int i=0;

    while(i<strlen(equation)) //loop to check validity of given equation that stored in given stack
    {

        /* checking if there is number before open parenthesis or after close parenthesis without operands between them */
        if((equation[i]>=48 && equation[i]<=57) && (equation[i+1]=='(')) //char value from 48 to 57 included are numbers from 0 to 9
        {
            if(choiceOfPrint==1)
                printf("Not Valid : there is no operator between %c(\n",equation[i]);
            return 0;
        }
        if((equation[i]>=48 && equation[i]<=57) && (equation[i+1]=='[')) //char value from 48 to 57 included are numbers from 0 to 9
        {
            if(choiceOfPrint==1)
                printf("Not Valid : there is no operator between %c[\n",equation[i]);
            return 0;
        }
        if((equation[i]==')') && (equation[i+1]>=48 && equation[i+1]<=57)) //char value from 48 to 57 included are numbers from 0 to 9
        {
            if(choiceOfPrint==1)
                printf("Not Valid : there is no operator between )%c\n",equation[i+1]);
            return 0;
        }
        if((equation[i]==']') && (equation[i+1]>=48 && equation[i+1]<=57)) //char value from 48 to 57 included are numbers from 0 to 9
        {
            if(choiceOfPrint==1)
                printf("Not Valid : there is no operator between ]%c\n",equation[i+1]);
            return 0;
        }

        /* checking if two operators respectively without number between them */
        if(equation[i]=='*' && equation[i+1]=='/')
        {
            if(choiceOfPrint==1)
                printf("Not Valid : there is no number between two operands %c %c\n",equation[i],equation[i+1]);
            return 0;
        }
        else if(equation[i]=='/' && equation[i+1]=='*')
        {
            if(choiceOfPrint==1)
                printf("Not Valid : there is no number between two operands %c %c\n",equation[i],equation[i+1]);
            return 0;
        }
        else if(equation[i]=='*' && equation[i+1]=='*')
        {
            if(choiceOfPrint==1)
                printf("Not Valid : there is no number between two operands %c %c\n",equation[i],equation[i+1]);
            return 0;
        }
        else if(equation[i]=='/' && equation[i+1]=='/')
        {
            if(choiceOfPrint==1)
                printf("Not Valid : there is no number between two operands %c %c\n",equation[i],equation[i+1]);
            return 0;
        }

        /* checking parenthesis */
        if(equation[i]=='(')
            checker1 = 1;

        else if(equation[i]==')')
            checker2 = 1;

        if(checker1==1 && checker2==1)
        {
            checker1 = 0;
            checker2 = 0;
        }

        if(equation[i]=='[')
            checker3 = 1;

        else if(equation[i]==']')
            checker4 = 1;

        if(checker3==1 && checker4==1)
        {
            checker3 = 0;
            checker4 = 0;
        }
        ++i;
    }

    //end of loop...

    if(checker1==1 && checker2==0)
    {
        if(choiceOfPrint==1)
            printf("Not Valid : ( not closed\n");
        return 0;
    }
    else if(checker1==0 && checker2==1)
    {
        if(choiceOfPrint==1)
            printf("Not Valid : ) not opened\n");
        return 0;
    }

    if(checker3==1 && checker4==0)
    {
        if(choiceOfPrint==1)
            printf("Not Valid : [ not closed\n");
        return 0;
    }
    else if(checker3==0 && checker4==1)
    {
        if(choiceOfPrint==1)
            printf("Not Valid : ] not opened\n");
        return 0;
    }

    if(choiceOfPrint==1)
        printf("Valid!\n");

    return 1;
}

int checkOperator(char data) // checks if given char is operator and return number related to priority.
{
    switch(data)
    {
    case '+' :
        return 1;
    case '-' :
        return 1;
    case '*' :
        return 2;
    case '/' :
        return 2;
    case '^' :
        return 3;
    }
    return 0;
}

Stack convertInfixToPrefix(Stack equation) //converts given infix form to prefix form in store it in stack.
{
    Stack temp = createStack(); //temp : temporary stack to store operators and parenthesis but not numbers!
    Stack postfix = createStack(); //postfix : stack to store postfix expression.
    Stack prefix = createStack(); //prefix : stack to store prefix expression.
    Node current; //node pointer to deal with nodes in any stack.

    while(1) //loop to reverse parenthesis is stack of equation
    {
        current = popFromStack(equation);
        if(current==NULL)
            break;

        if(current->data==NULL)
            pushToStackOfInt(temp,current->number);
        else if(current->number==NULL)
        {
            if(current->data == '(')
                current->data = ')';
            else if(current->data == ')')
                current->data = '(';

            if(current->data == '[')
                current->data = ']';
            else if(current->data == ']')
                current->data = '[';

            free(current);
            pushToStack(temp,current->data);
        }
    }
    moveElements(temp,equation); // moving elements from temporary stack to equation stack

    // now equation is reversed equation

    while(1) //loop to store postfix form of result string in postfix stack.
    {
        current = popFromStack(equation);
        if(current==NULL)
            break;

        if(current->number!=NULL) //means that is number
        {
            pushToStackOfInt(postfix,current->number);
        }
        else if(current->data!=NULL && current->data=='(')
            pushToStack(temp,current->data);

        else if(current->data!=NULL && current->data==')')
        {
            while(1) //loop to pop the operations from temp stack until access close notation ')' included.
            {
                current = popFromStack(temp);
                pushToStack(postfix,current->data);
                free(current);
                if(topOfStack(temp)=='(')
                {
                    current = popFromStack(temp);
                    free(current);
                    break;
                }
            }
        }
        else if(current->data!=NULL && current->data=='[')
            pushToStack(temp,current->data);

        else if(current->data!=NULL && current->data==']')
        {
            while(1) //loop to pop the operations from temp stack until access close notation ']' included.
            {
                current = popFromStack(temp);
                pushToStack(postfix,current->data);
                free(current);
                if(topOfStack(temp)=='[')
                {
                    current = popFromStack(temp);
                    free(current);
                    break;
                }
            }
        }
        else if((current->data!=NULL) && (checkOperator(current->data)>=1 && checkOperator(current->data)<=3))  //checks given character is operator or not
        {
            while(1) //loop keeps pop processing until priority of top of stack greater than or equal priority of given operator.
            {
                if( checkOperator(topOfStack(temp)) > checkOperator(current->data) ) //checks precedence of operators
                    pushToStack(postfix,popFromStack(temp)->data);

                else
                {
                    pushToStack(temp,current->data);
                    break;
                }
            }
        }
        else if(current->data!=NULL && current->data==' ')
            pushToStack(postfix,current->data);
    }

    while(1) //loop to complete postfix expression
    {
        current = popFromStack(temp);
        if(current==NULL)
            break;

        pushToStack(postfix,current->data);
        free(current);
    }
    free(temp);

    moveElements(postfix,prefix);
    free(postfix);

    return prefix;
}


int prefixEvaluator(Stack prefix) //gets prefix equation represented in stack such that top of the stack is right side from equation.
{
    /*
    current : node pointer to deal with nodes in stack.
    temp : temporary stack to store the result and numbers in it.
    resultOfOperation : result of any operation between two numbers in stack
    num1 : last number pushed to stack.
    num2 : before last number pushed in stack.
    result : result of all operations that means result of given prefix form.
    */
    Node current;
    Stack temp = createStack();
    int resultOfOperation = 0;
    int num1, num2, result;
    /*
    while(1) : loop to evaluate the prefix form,
    such that it will keep gets integers and chars
    from prefix equation from right side exactly,
    when it get operator, it will evaluate result
    of two pops integers such that first pop will be first number
    and second pop will be second number,
    and operator evaluate numbers,
    after that the result will push to temp stack,
    and so on...
    lastly the loop will pushes result of equation in temp stack.
    */
    while(1)
    {
        current = popFromStack(prefix);
        if(current==NULL)
            break;

        if(current->data==NULL) //means node contains integer not operator , if that happened push it to temp stack
            pushToStackOfInt(temp,current->number);

        else if(current->number==NULL) //means node contains char not integer
        {
            if(current->data==' ') //we will not push spaces in the stack to avoid errors , so we will continue to next node
                continue;

            else //that means almost operator
            {
                num1 = popFromStack(temp)->number;
                num2 = popFromStack(temp)->number;

                if(checkOperator(current->data)==1) // 1 : means operator will be addition or subtraction
                {
                    if(current->data == '+')
                        resultOfOperation = num1 + num2;

                    else if(current->data == '-')
                        resultOfOperation = num1 - num2;
                }
                else if(checkOperator(current->data)==2) // 2 : means operator will be multiplication or division
                {
                    if(current->data == '*')
                        resultOfOperation = num1 * num2;

                    else if(current->data == '/')
                        resultOfOperation = num1 / num2;
                }
                else if(checkOperator(current->data)==3) // 3 : means operator will be power
                    resultOfOperation = pow(num1,num2);

                pushToStackOfInt(temp,resultOfOperation);
            }
        }

    }

    result = popFromStack(temp)->number;
    return result;
}

int readFile(int choiceOfPrint) // function reads file contain equations , choiceOfPrint : to choice either show contents or give No. of eqs.
{
    FILE *fptInput; //input file
    char nameOfFile[26]; //name of input file
    char data[100]; //equation line in file
    int counter = 0; //counter : to count number of equations

    if(choiceOfPrint==1)
    {
        printf("Enter name of file : ");
        printf("\n* Hint : in***.txt\n");
        scanf("%s",nameOfFile);


        while(1) //loop will run until user enter name of file and it input.txt
        {
            if(strcmp(nameOfFile,"input.txt")==0)
                break;
            printf("\nEnter name of excited file please!\n");
            scanf("%s",nameOfFile);
        }
        printf("\nEquations in file are : \n\n");

    }

    fptInput = fopen("input.txt","r");
    fscanf(fptInput,"%s",data);

    while(1)
    {
        ++counter;
        if(choiceOfPrint==1)
        {
            printf("Eq.%d : ",counter);
            printf("%s\n",data);
        }
        if(fscanf(fptInput,"%s",data)==EOF)
            break;
    }
    fclose(fptInput);
    return counter;
}

void menu() //contains menu of operations user want to do.
{
    printf("\n\n====================Menu====================\n\n");
    printf("1. Read the file containing the equations.\n");
    printf("2. Check the validity of equations then convert valid equations from infix to prefix .\n");
    printf("3. Evaluate the prefix expressions and print the results of each equation.\n");
    printf("4. Print invalid equations.\n");
    printf("5. Print all equations to a file (output.txt) indicating for each input equation if it is valid or not and if valid, print out the prefix expression and its result.\n");
    printf("6. Exit.\n");
}

void controller() //function creates a Stack and fill it with given Infix form equation stored in input file and control the operations
{
    /*
    fptInput : input file ,fptOutput : output file
    i : index for string , counter : to count number of equations
    result : result of prefix form
    choice : choice of list
    j,m : index for 2D string "equations"
    numberOfLines : number of equations in input file , gives 0 to function readFile that means we need just number or equations not print equations in file.
    number : integer value of number represented in string
    data : equation line in file
    equations : to store all equations in file
    s : array of stack of collection of integers and characters
    prefix : array of stacks store prefix just!
    */
    FILE *fptInput, *fptOutput;
    int i = 0, counter = 0;
    int result;
    int choice;
    int j = 0, m = 0;
    int numberOfLines = readFile(0);
    int number =0;
    char data[100];
    char equations[numberOfLines][100];
    Stack s[numberOfLines];
    Stack prefix[numberOfLines];

    fptInput = fopen("input.txt","r");
    fptOutput = fopen("output.txt","w");
    fscanf(fptInput,"%s",data);

    while(1) //loop to read equations from input file
    {
        s[j] = createStack();
        while(i < strlen(data)) //loop to store given equation in stack s
        {
            if(data[i]>=48 && data[i]<=57)
            {
                number = number * 10 + ( data[i] - '0' );
                while(1)
                {
                    if(data[i+1]>=48 && data[i+1]<=57)
                    {
                        number = number * 10 + ( data[i+1] - '0' );
                        ++i;
                    }
                    else
                    {
                        pushToStackOfInt(s[j],number);
                        pushToStack(s[j],' ');
                        number = 0;
                        break;
                    }
                }
            }
            else if(data[i]=='+' && data[i+1]=='+')
            {
                pushToStack(s[j],data[i]);
                ++i;
            }
            else if(data[i]=='-' && data[i+1]=='-')
            {
                pushToStack(s[j],'+');
                ++i;
            }
            else if(data[i]=='-' && data[i+1]=='+')
            {
                pushToStack(s[j],'-');
                ++i;
            }
            else if(data[i]=='+' && data[i+1]=='-')
            {
                pushToStack(s[j],'-');
                ++i;
            }
            else
                pushToStack(s[j],data[i]);

            ++i;
        }
        strcpy(equations[j],data);
        i=0;
        ++counter;
        fprintf(fptOutput,"Eq.%d : ",counter);
        fprintf(fptOutput,"%s\n",data);
        fprintf(fptOutput,"\n");
        if(fscanf(fptInput,"%s",data)==EOF)
            break;
        ++j;
        ++m;
    }

    fclose(fptInput);

    for(int i = 0; i < numberOfLines; i++)
    {
        prefix[i] = createStack();
        if (valid(equations[i],0) == 1)
            prefix[i] = convertInfixToPrefix(s[i]);
    }

    while(1) //loop will run until user enter 6 to exit.
    {
        menu();
        printf("Enter Number of choice you want please : ");
        scanf("%d",&choice);
        printf("\n");

        if(choice==6)
        {
            printf("\n\n====================Thx<3====================\n\n");
            break;
        }


        switch(choice) //process operations relate to choice
        {
        case 1 : //to read from file
            readFile(1);
            break;
        case 2 : //to check validity and prints prefix form
            for(int i = 0; i < numberOfLines; i++)
            {
                printf("Equation No.%d : %s\n",i+1,equations[i]);
                if (valid(equations[i],1) == 1)
                {
                    printf("Prefix Form is of equation No.%d: ",i+1);
                    printElementsOfStack(prefix[i]);
                    printf("\n");
                    fprintf(fptOutput,"Prefix Form is of equation No.%d: ",i+1);
                    printElementsOfStackOnFile(prefix[i],fptOutput);
                    fprintf(fptOutput,"\n");
                }
            }
            printf("\n");
            break;

        case 3 : //evaluates prefix and prints result
            for(int i = 0; i < numberOfLines; i++)
            {
                if(prefix[i]->next==NULL)
                    continue;

                result = prefixEvaluator(prefix[i]);
                printf("Result of equation %d is : %d\n",(i+1),result);
                printf("\n");
                fprintf(fptOutput,"Result of equation %d is : %d\n",(i+1),result);
                fprintf(fptOutput,"\n");
            }
            break;

        case 4 : //prints invalid equations
            printf("Invalid equations are : \n");
            for(int i = 0; i < numberOfLines; i++)
            {

                if (valid(equations[i],0) == 0)
                {
                    printf("Equation No.%d : %s\n",(i+1),equations[i]);

                }
            }
            break;

        case 5 : //print all equations to a file (output.txt)...etc
            fclose(fptOutput);
            printf("Done!!\n");
            break;

        default :
            printf("Enter invalid number of choice please!!\n");
        }
    }
    fclose(fptOutput);
}

int main()
{
    printf("====================================Welcome To Prefix Converter Program====================================\n\n");
    controller();
    return 0;
}

