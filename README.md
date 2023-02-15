# Postfix-to-Infix
Program takes a postfix math expression and uses a binary tree and stack to convert to an infix expression.

Program is run by typing in the executables name and then your command line postfix expression argument in quotations (""). Command line input should be float numbers with this format Y.YY and
variables in format xY. There should be spaces between them.

Sample input: q1.out "2.00 x1 1.00 - * x2 3.00 / +"

Sample run:
q1 "2.00 x1 1.00 - * x2 3.00 / +"

((2.00*(x1-1.00))+(x2/3.00))
