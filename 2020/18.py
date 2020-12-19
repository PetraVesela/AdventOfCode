'''
Toggle the parts by changing the operator_precedence arg
Alternative: shunting-yard algorithm? Abstract Syntax Tree
TODO: refactor
'''

import re

def has_operators(expr):
    return '+' in expr or '*' in expr


def find_additions(expr):
    return re.findall(r'\d+ \+ \d+', expr)


def find_multiplications(expr):
    return re.findall(r'\d+ \* \d+', expr)


def evaluate(expr, operator_precedence=0):
    # get stuff in parenthesis first

    has_parenthesis = expr.find('(')
    if has_parenthesis != -1:
        ind = has_parenthesis
        while expr[ind] != ')':
            if expr[ind] == '(':
                has_parenthesis = ind
            ind += 1
        between_pars = expr[has_parenthesis + 1 : ind]
        partial_result = evaluate(between_pars, operator_precedence)
        expr = expr.replace('(' + between_pars + ')', partial_result, 1)

        if has_operators(expr):
            return evaluate(expr, operator_precedence)
        return expr
    else:
        # Get first operand pair and operator
        operations = re.findall(r'\d+ [+|*] \d+', expr)

        if operator_precedence:
            additions = find_additions(expr)
            while additions:
                partial_result = str(eval(additions[0]))
                expr = expr.replace(additions[0], partial_result, 1)
                additions = find_additions(expr)

            multiplications = find_multiplications(expr)
            while multiplications:
                partial_result = str(eval(multiplications[0]))
                expr = expr.replace(multiplications[0], partial_result, 1)
                multiplications = find_multiplications(expr)
        else:
            partial_result = str(eval(operations[0]))
            expr = expr.replace(operations[0], partial_result, 1)

        if has_operators(expr):
            return evaluate(expr, operator_precedence)
        return expr


def main():
    with open("inputs/18.txt", 'r') as file:
        lines = file.read().split('\n')

    print('Part 1: ', sum([int(evaluate(line, operator_precedence=1)) for line in lines]))


if __name__ == "__main__":
    main()
