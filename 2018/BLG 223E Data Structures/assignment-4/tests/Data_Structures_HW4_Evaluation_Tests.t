- init:
    run: rm -f hw4
    blocker: true

- build:
    run: g++ -Wall -Werror hw4.cpp -o hw4  # timeout: 8
    blocker: true

- case1_simple:
    run: ./hw4 simple.txt
    points: 30
    script:
        - expect: "[ \r\n]*The initial Ant sequence is: 1 2 3 [ \r\n]*"                             # timeout: 8
        - expect: "[ \r\n]*The depth of holes are: 1 [ \r\n]*"                                # timeout: 8
        - expect: "[ \r\n]*The final Ant sequence is: 2 3 1 [ \r\n]*"                            # timeout: 8
        - expect: _EOF_                                                                        # timeout: 8
    return: 0

- case2_single_hole:
    run: ./hw4 single_hole.txt
    points: 35
    script:
        - expect: "[ \r\n]*The initial Ant sequence is: 1 2 3 4 5 6 7 [ \r\n]*"                     # timeout: 8
        - expect: "[ \r\n]*The depth of holes are: 6 [ \r\n]*"                                # timeout: 8
        - expect: "[ \r\n]*The final Ant sequence is: 7 6 5 4 3 2 1 [ \r\n]*"                    # timeout: 8
        - expect: _EOF_                                                                       # timeout: 8
    return: 0

- case3_camel:
    run: ./hw4 camel.txt
    points: 35
    script:
        - expect: "[ \r\n]*The initial Ant sequence is: 1 2 3 4 5 6 7 8 9 10 [ \r\n]*"               # timeout: 8
        - expect: "[ \r\n]*The depth of holes are: 1 9 2 8 3 7 4 6 5 4 6 3 7 2 8 1 9 [ \r\n]*"   # timeout: 8
        - expect: "[ \r\n]*The final Ant sequence is: 6 7 8 3 2 1 10 9 4 5 [ \r\n]*"               # timeout: 8
        - expect: _EOF_                                                                        # timeout: 8
    return: 0

