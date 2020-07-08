from math import floor


def day_of_week(y, m, d):
    if m <= 2:
        m += 12
        y -= 1
    j = y // 100
    k = y % 100
    t1 = floor(13 * (m + 1) / 5)
    t2 = floor(k / 4)
    t3 = floor(j / 4)
    z = (d + t1 + k + t2 + t3 + 5 * j) % 7
    return z


def sundays1(start, end):
    n = 0
    for y in range(start, end + 1):
        for m in range(1, 13):
            if day_of_week(y, m, 1) == 1:
                n += 1
    return n


def leap(y):
    return (y % 4 == 0) and (y % 100 != 0) or (y % 400 == 0)


def days_in_month(m, y):
    if m == 2:
        days = 29 if leap(y) else 28
    elif (m == 4) or (m == 6) or (m == 9) or (m == 11):
        days = 30
    else:
        days = 31
    return days


def sundays2(start, end):
    n = 0
    weekday = 2
    for y in range(start, end + 1):
        for m in range(1, 13):
            days = days_in_month(m, y)
            weekday += days % 7
            if weekday % 7 == 0:
                n += 1
    return n


print(sundays1(1901, 2000))
print(sundays2(1901, 2000))
