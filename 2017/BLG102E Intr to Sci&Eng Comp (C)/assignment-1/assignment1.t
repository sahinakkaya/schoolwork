- init:
    run: rm -f assignment1
    blocker: true

- build:
    run: gcc -std=c99 -Wall -Werror assignment1.c -o assignment1  # timeout: 2
    blocker: true

- case_1900_1_1_1999:
    run: ./assignment1
    script:
        - expect: "Enter date \\[year month day\\]: "  # timeout: 2
        - send: "1900 1 1"
        - expect: "Enter end year: "                   # timeout: 2
        - send: "1999"
        - expect: "It's a Monday.\r\n"                 # timeout: 2
        - expect: "Same day-and-month on same weekday between 1901 and 1999: 14\r\n"  # timeout: 2
        - expect: _EOF_  # timeout: 2
    return: 0

- case_invalid_11_31:
    run: ./assignment1
    script:
        - expect: "Enter date \\[year month day\\]: "  # timeout: 2
        - send: "2018 11 31"
        - expect: "Invalid date.\r\n"                  # timeout: 2
        - expect: _EOF_                                # timeout: 2
    return: 1
