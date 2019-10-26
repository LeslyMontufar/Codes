def taxes(salary, sum_tax):
    if salary <= 2000:
        tax = 0
        newsalary = 0
    elif salary > 2000 and salary <= 3000:
        tax = 0.08
        newsalary = 2000
    elif salary > 3000 and salary <= 4500:
        tax = 0.18
        newsalary = 3000
    else:
        tax = 0.28
        newsalary = 4500
    sum_tax = sum_tax + (salary - newsalary)*tax
    if newsalary == 0:
        return sum_tax
    else:
        return taxes(newsalary, sum_tax)
tax = taxes(float(input()), 0)
if tax != 0:
    print('R$ {:.2f}'.format(tax))
else:
    print('Isento')
