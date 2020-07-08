- init:
    run: rm -f assignment4
    blocker: true

- build:
    run: gcc -std=c99 -Wall -Werror assignment4.c -o assignment4  # timeout: 5
    blocker: true

- case1_given_with_hw:
   run: ./assignment4 alice.txt instructions.txt
   points: 10
   script:
        - expect: "[ \r\n]*fight for your right to party[ \r\n]*"  # timeout: 5
        - expect: _EOF_  # timeout: 5
   return: 0


- case2_capitals:
    run: ./assignment4 alice.txt capitals.txt
    points: 10
    script:
    - expect: "[ \r\n]*keep it simple and short[ \r\n]*"  # timeout: 5
    - expect: _EOF_  # timeout: 5
    return: 0


- case3_same_line:
    run: ./assignment4 alice.txt same_line.txt
    points: 10
    script:
    - expect: "[ \r\n]*say a long and sad tale please[ \r\n]*"  # timeout: 5
    - expect: _EOF_  # timeout: 5
    return: 0

- case4_warning:
    run: ./assignment4 alice.txt warning.txt
    points: 10
    script:
    - expect: "[ \r\n]*cross check your home work before you submitted it please[ \r\n]*"  # timeout: 5
    - expect: _EOF_  # timeout: 5
    return: 0


- case5_single_word:
    run: ./assignment4 alice.txt single_word.txt
    points: 10
    script:
    - expect: "[ \r\n]*title[ \r\n]*"  # timeout: 5
    - expect: _EOF_  # timeout: 5
    return: 0


- case6_two_dashes:
    run: ./assignment4 alice.txt two_dashes.txt
    points: 10
    script:
    - expect: "[ \r\n]*i know that well[ \r\n]*"  # timeout: 5
    - expect: _EOF_  # timeout: 5
    return: 0


- case7_single_dash:
    run: ./assignment4 alice.txt single_dash.txt
    points: 10
    script:
    - expect: "[ \r\n]*today go outoftheway sir[ \r\n]*"  # timeout: 5
    - expect: _EOF_  # timeout: 5
    return: 0


- case8_forward_walk:
    run: ./assignment4 alice.txt forward_walk.txt
    points: 10
    script:
    - expect: "[ \r\n]*alice perfectly found her hand[ \r\n]*"  # timeout: 5
    - expect: _EOF_  # timeout: 5
    return: 0


- case9_backward_walk:
    run: ./assignment4 alice.txt backward_walk.txt
    points: 10
    script:
    - expect: "[ \r\n]*hear my voice sir please[ \r\n]*"  # timeout: 5
    - expect: _EOF_  # timeout: 5
    return: 0


- case10_punctuations:
    run: ./assignment4 alice.txt punctuations.txt
    points: 10
    script:
    - expect: "[ \r\n]*it is last trial[ \r\n]*"  # timeout: 5
    - expect: _EOF_  # timeout: 5
    return: 0
