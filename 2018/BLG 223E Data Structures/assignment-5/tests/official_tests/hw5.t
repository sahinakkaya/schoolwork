- init:
    run: rm -f hw5
    blocker: true

- build:
    run: g++ -Wall -Werror hw5.cpp -o hw5                                                    # timeout: 8
    blocker: true

- case1_two_paths:
    run: ./hw5 two_paths.txt
    points: 20
    script:
        - expect: "[ \r\n]*Path Found: 10 5 35[ \r\n]*"                                      # timeout: 8
        - expect: "[ \r\n]*Path Found: 10 15 25[ \r\n]*"                                     # timeout: 8
        - expect: _EOF_                                                                      # timeout: 8
    return: 0

- case2_no_path:
    run: ./hw5 no_path.txt
    points: 20
    script:
        - expect: "[ \r\n]*No Path Found[ \r\n]*"                                            # timeout: 8
        - expect: "[ \r\n]*No Path Found[ \r\n]*"                                            # timeout: 8
        - expect: _EOF_                                                                      # timeout: 8
    return: 0

- case3_one_path_left_subtree:
    run: ./hw5 one_path_left_subtree.txt
    points: 15
    script:
        - expect: "[ \r\n]*Path Found: 10 5 35 256[ \r\n]*"                                  # timeout: 8
        - expect: "[ \r\n]*No Path Found[ \r\n]*"                                            # timeout: 8
        - expect: _EOF_                                                                      # timeout: 8
    return: 0

- case4_one_path_right_subtree:
    run: ./hw5 one_path_right_subtree.txt
    points: 15
    script:
        - expect: "[ \r\n]*No Path Found[ \r\n]*"                                            # timeout: 8
        - expect: "[ \r\n]*Path Found: 10 16 30[ \r\n]*"                                     # timeout: 8
        - expect: _EOF_                                                                      # timeout: 8
    return: 0

- case5_two_paths_left_subtree:
    run: ./hw5 two_paths_left_subtree.txt
    points: 10
    script:
        - expect: "[ \r\n]*Path Found: 10 5 64 227[ \r\n]*"                                  # timeout: 8
        - expect: "[ \r\n]*No Path Found[ \r\n]*"                                            # timeout: 8
        - expect: _EOF_                                                                      # timeout: 8
    return: 0

- case6_two_paths_right_subtree:
    run: ./hw5 two_paths_right_subtree.txt
    points: 10
    script:
        - expect: "[ \r\n]*No Path Found[ \r\n]*"                                            # timeout: 8
        - expect: "[ \r\n]*Path Found: 10 16 25 5[ \r\n]*"                                   # timeout: 8
        - expect: _EOF_                                                                      # timeout: 8
    return: 0

- case7_two_paths_right_subtree_two_paths_left_subtree:
    run: ./hw5 two_paths_right_subtree_two_paths_left_subtree.txt
    points: 10
    script:
        - expect: "[ \r\n]*Path Found: 10 5 2 39[ \r\n]*"                                    # timeout: 8
        - expect: "[ \r\n]*Path Found: 10 16 25 5[ \r\n]*"                                   # timeout: 8
        - expect: _EOF_                                                                      # timeout: 8
    return: 0
