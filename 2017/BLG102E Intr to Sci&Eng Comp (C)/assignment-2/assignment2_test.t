- init:
    run: rm -f assignment2
    blocker: true

- build:
    run: gcc -std=c99 -Wall -Werror assignment.c -o assignment2  # timeout: 2
    blocker: true

- case0:
    run: ./assignment2
    points: 5
    script:
        - expect: "Target: "  # timeout: 2
        - send: "101"
        - expect: "Throw: "                   # timeout: 2
        - send: "18 S"
        - expect: "Points: 101\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "7 T"
        - expect: "Points: 101\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "9 D"
        - expect: "Points: 83\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "1 O"
        - expect: "Points: 58\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "10 T"
        - expect: "Points: 28\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "15 T"
        - expect: "Points: 28\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "12 S"
        - expect: "Points: 16\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "16 S"
        - expect: "Points: 16\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "8 D"
        - expect: "Points: 0\r\n"                   # timeout: 2
    return: 0

- case1:
    run: ./assignment2
    points: 5
    script:
        - expect: "Target: "  # timeout: 2
        - send: "301"
        - expect: "Throw: "                   # timeout: 2
        - send: "1 O"
        - expect: "Points: 301\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "1 I"
        - expect: "Points: 301\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "20 D"
        - expect: "Points: 261\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "20 S"
        - expect: "Points: 241\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "17 S"
        - expect: "Points: 224\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "8 T"
        - expect: "Points: 200\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "1 I"
        - expect: "Points: 150\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "1 O"
        - expect: "Points: 125\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "13 T"
        - expect: "Points: 86\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "8 S"
        - expect: "Points: 78\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "19 T"
        - expect: "Points: 21\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "1 S"
        - expect: "Points: 20\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "10 D"
        - expect: "Points: 0\r\n"                   # timeout: 2
    return: 0
- case2:
    run: ./assignment2
    points: 5
    script:
        - expect: "Target: "  # timeout: 2
        - send: "301"
        - expect: "Throw: "                   # timeout: 2
        - send: "20 I"
        - expect: "Points: 301\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "1 O"
        - expect: "Points: 301\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "10 D"
        - expect: "Points: 281\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "20 S"
        - expect: "Points: 261\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "16 S"
        - expect: "Points: 245\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "20 S"
        - expect: "Points: 225\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "15 S"
        - expect: "Points: 210\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "1 I"
        - expect: "Points: 160\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "1 O"
        - expect: "Points: 135\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "13 T"
        - expect: "Points: 96\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "8 S"
        - expect: "Points: 88\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "19 T"
        - expect: "Points: 31\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "1 S"
        - expect: "Points: 30\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "10 S"
        - expect: "Points: 20\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "10 T"
        - expect: "Points: 20\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "10 D"
        - expect: "Points: 0\r\n"                    # timeout: 2
    return: 0
- case3:
    run: ./assignment2
    points: 5
    script:
        - expect: "Target: "  # timeout: 2
        - send: "101"
        - expect: "Throw: "                   # timeout: 2
        - send: "10 T"
        - expect: "Points: 101\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "5 O"
        - expect: "Points: 101\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "5 D"
        - expect: "Points: 91\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "10 S"
        - expect: "Points: 81\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "17 T"
        - expect: "Points: 30\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "1 T"
        - expect: "Points: 27\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "2 D"
        - expect: "Points: 23\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "1 O"
        - expect: "Points: 23\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "13 T"
        - expect: "Points: 23\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "8 T"
        - expect: "Points: 23\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "9 D"
        - expect: "Points: 5\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "1 S"
        - expect: "Points: 4\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "10 S"
        - expect: "Points: 4\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "10 T"
        - expect: "Points: 4\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "2  D"
        - expect: "Points: 0\r\n"                    # timeout: 2
    return: 0
- case4:
    run: ./assignment2
    points: 5
    script:
        - expect: "Target: "  # timeout: 2
        - send: "501"
        - expect: "Throw: "                   # timeout: 2
        - send: "20 T"
        - expect: "Points: 501\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "10 S"
        - expect: "Points: 501\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "6 O"
        - expect: "Points: 501\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "10 S"
        - expect: "Points: 501\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "20 D"
        - expect: "Points: 461\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "10 T"
        - expect: "Points: 431\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "10 T"
        - expect: "Points: 401\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "15 T"
        - expect: "Points: 356\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "1 I"
        - expect: "Points: 306\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "1 O"
        - expect: "Points: 281\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "13 I"
        - expect: "Points: 231\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "8 T"
        - expect: "Points: 207\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "19 D"
        - expect: "Points: 169\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "20 T"
        - expect: "Points: 109\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "10 S"
        - expect: "Points: 99\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "10 T"
        - expect: "Points: 69\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "10  I"
        - expect: "Points: 19\r\n"                    # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "19  D"
        - expect: "Points: 19\r\n"                    # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "1  S"
        - expect: "Points: 18\r\n"                    # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "9  D"
        - expect: "Points: 0\r\n"                    # timeout: 2
    return: 0
- case5:
    run: ./assignment2
    points: 5
    script:
        - expect: "Target: "  # timeout: 2
        - send: "301"
        - expect: "Throw: "                   # timeout: 2
        - send: "1 O"
        - expect: "Points: 301\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "1 I"
        - expect: "Points: 301\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "20 D"
        - expect: "Points: 261\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "20 S"
        - expect: "Points: 241\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "17 S"
        - expect: "Points: 224\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "8 T"
        - expect: "Points: 200\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "1 I"
        - expect: "Points: 150\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "1 O"
        - expect: "Points: 125\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "13 T"
        - expect: "Points: 86\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "8 S"
        - expect: "Points: 78\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "20 T"
        - expect: "Points: 18\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "11 T"
        - expect: "Points: 18\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "9 D"
        - expect: "Points: 0\r\n"                   # timeout: 2
    return: 0
- case6:
    run: ./assignment2
    points: 4
    script:
        - expect: "Target: "  # timeout: 2
        - send: "16"
        - expect: "Throw: "                   # timeout: 2
        - send: "4 D"
        - expect: "Points: 8\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "4 D"
        - expect: "Points: 0\r\n"                   # timeout: 2
    return: 0
- case7:
    run: ./assignment2
    points: 6
    script:
        - expect: "Target: "  # timeout: 2
        - send: "16"
        - expect: "Throw: "                   # timeout: 2
        - send: "8 S"
        - expect: "Points: 16\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "4 D"
        - expect: "Points: 8\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "4 D"
        - expect: "Points: 0\r\n"                   # timeout: 2
    return: 0
- case8:
    run: ./assignment2
    points: 6
    script:
        - expect: "Target: "  # timeout: 2
        - send: "16"
        - expect: "Throw: "                   # timeout: 2
        - send: "2 T"
        - expect: "Points: 16\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "4 D"
        - expect: "Points: 8\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "4 D"
        - expect: "Points: 0\r\n"                   # timeout: 2
    return: 0
- case9:
    run: ./assignment2
    points: 6
    script:
        - expect: "Target: "  # timeout: 2
        - send: "52"
        - expect: "Throw: "                   # timeout: 2
        - send: "2 I"
        - expect: "Points: 52\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "20 D"
        - expect: "Points: 12\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "6 D"
        - expect: "Points: 0\r\n"                   # timeout: 2
    return: 0
- case10:
    run: ./assignment2
    points: 6
    script:
        - expect: "Target: "  # timeout: 2
        - send: "52"
        - expect: "Throw: "                   # timeout: 2
        - send: "2 O"
        - expect: "Points: 52\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "20 D"
        - expect: "Points: 12\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "6 D"
        - expect: "Points: 0\r\n"                   # timeout: 2
    return: 0
- case11:
    run: ./assignment2
    points: 6
    script:
        - expect: "Target: "  # timeout: 2
        - send: "52"
        - expect: "Throw: "                   # timeout: 2
        - send: "2 D"
        - expect: "Points: 48\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "10 S"
        - expect: "Points: 38\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "19 D"
        - expect: "Points: 0\r\n"                   # timeout: 2
    return: 0
- case12:
    run: ./assignment2
    points: 6
    script:
        - expect: "Target: "  # timeout: 2
        - send: "52"
        - expect: "Throw: "                   # timeout: 2
        - send: "2 D"
        - expect: "Points: 48\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "4 D"
        - expect: "Points: 40\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "20 D"
        - expect: "Points: 0\r\n"                   # timeout: 2
    return: 0
- case13:
    run: ./assignment2
    points: 6
    script:
        - expect: "Target: "  # timeout: 2
        - send: "52"
        - expect: "Throw: "                   # timeout: 2
        - send: "2 D"
        - expect: "Points: 48\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "4 T"
        - expect: "Points: 36\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "18 D"
        - expect: "Points: 0\r\n"                   # timeout: 2
    return: 0
- case14:
    run: ./assignment2
    points: 6
    script:
        - expect: "Target: "  # timeout: 2
        - send: "62"
        - expect: "Throw: "                   # timeout: 2
        - send: "2 D"
        - expect: "Points: 58\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "4 I"
        - expect: "Points: 8\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "4 D"
        - expect: "Points: 0\r\n"                   # timeout: 2
    return: 0
- case15:
    run: ./assignment2
    points: 6
    script:
        - expect: "Target: "  # timeout: 2
        - send: "37"
        - expect: "Throw: "                   # timeout: 2
        - send: "2 D"
        - expect: "Points: 33\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "4 O"
        - expect: "Points: 8\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "4 D"
        - expect: "Points: 0\r\n"                   # timeout: 2
    return: 0
- case16:
    run: ./assignment2
    points: 6
    script:
        - expect: "Target: "  # timeout: 2
        - send: "44"
        - expect: "Throw: "                   # timeout: 2
        - send: "2 D"
        - expect: "Points: 40\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "20 T"
        - expect: "Points: 40\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "20 D"
        - expect: "Points: 0\r\n"                   # timeout: 2
    return: 0
- case17:
    run: ./assignment2
    points: 6
    script:
        - expect: "Target: "  # timeout: 2
        - send: "16"
        - expect: "Throw: "                   # timeout: 2
        - send: "2 D"
        - expect: "Points: 12\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "11 S"
        - expect: "Points: 12\r\n"                   # timeout: 2
        - expect: "Throw: "                   # timeout: 2
        - send: "6 D"
        - expect: "Points: 0\r\n"                   # timeout: 2
    return: 0
