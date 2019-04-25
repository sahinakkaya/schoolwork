- init:
    run: rm -f hw5
    blocker: true

- build:
    run: g++ -Wall -Werror hw5.cpp -o hw5  # timeout: 8
    blocker: true

- case1_root_equal_target:
    run: ./hw5 root_equal_target.txt
    points: 10
    script:
        - expect: "[ \r\n]*Path Found: 40[ \r\n]*"                      # timeout: 8
        - expect: "[ \r\n]*Path Found: 40[ \r\n]*"                      # timeout: 8
        - expect: _EOF_                                                 # timeout: 8
    return: 0



- case2_full_path_both_side:
    run: ./hw5 full_path_both_side.txt
    points: 10
    script:
        - expect: "[ \r\n]*Path Found: 40 20 7 14 90[ \r\n]*"                      # timeout: 8
        - expect: "[ \r\n]*Path Found: 40 9 54 60 8[ \r\n]*"                      # timeout: 8
        - expect: _EOF_                                                 # timeout: 8
    return: 0



- case3_half_path_both_side:
    run: ./hw5 half_path_both_side.txt
    points: 10
    script:
        - expect: "[ \r\n]*Path Found: 40 20 111 38[ \r\n]*"                      # timeout: 8
        - expect: "[ \r\n]*Path Found: 40 9 54 106[ \r\n]*"                      # timeout: 8
        - expect: _EOF_                                                 # timeout: 8
    return: 0



- case4_no_path_with_high_value_both_side:
    run: ./hw5 no_path_with_high_value_both_side.txt
    points: 15
    script:
        - expect: "[ \r\n]*No Path Found[ \r\n]*"                      # timeout: 8
        - expect: "[ \r\n]*No Path Found[ \r\n]*"                      # timeout: 8
        - expect: _EOF_                                                 # timeout: 8
    return: 0


- case5_no_path_with_low_value_both_side:
    run: ./hw5 no_path_with_low_value_both_side.txt
    points: 15
    script:
        - expect: "[ \r\n]*No Path Found[ \r\n]*"                      # timeout: 8
        - expect: "[ \r\n]*No Path Found[ \r\n]*"                      # timeout: 8
        - expect: _EOF_                                                 # timeout: 8
    return: 0



- case6_no_path_just_right:
    run: ./hw5 no_path_just_right.txt
    points: 20
    script:
        - expect: "[ \r\n]*Path Found: 40 20[ \r\n]*"                      # timeout: 8
        - expect: "[ \r\n]*No Path Found[ \r\n]*"                      # timeout: 8
        - expect: _EOF_                                                 # timeout: 8
    return: 0


- case7_no_path_just_left:
    run: ./hw5 no_path_just_left.txt
    points: 20
    script:
        - expect: "[ \r\n]*No Path Found[ \r\n]*"                      # timeout: 8
        - expect: "[ \r\n]*Path Found: 40 9[ \r\n]*"                      # timeout: 8
        - expect: _EOF_                                                 # timeout: 8
    return: 0




