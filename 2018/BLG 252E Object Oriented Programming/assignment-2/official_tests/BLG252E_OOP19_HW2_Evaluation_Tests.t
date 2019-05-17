- case1_operator_constructor:
    run: ./01_operator_constructor
    points: 5
    script:
        - expect: "[ \r\n]*X=1 Y=2 SIZE=3[ \r\n]*"                                     # timeout: 20
        - expect: _EOF_                                                                # timeout: 20
    return: 0

- case2_operator_reset:
    run: ./02_operator_reset 
    points: 5
    script:
        - expect: "[ \r\n]*X=1 Y=2 SIZE=3[ \r\n]*"                                     # timeout: 20
        - expect: "[ \r\n]*X=4 Y=5 SIZE=6[ \r\n]*"                                     # timeout: 20
        - expect: _EOF_                                                                # timeout: 20
    return: 0

- case3_arithmetic_operator_sign_valid:
    run: ./03_arithmetic_operator_sign_valid
    points: 5
    script:
        - expect: "[ \r\n]*SIGN=[+][ \r\n]*"                                           # timeout: 20
        - expect: "[ \r\n]*SIGN=-[ \r\n]*"                                             # timeout: 20
        - expect: "[ \r\n]*SIGN=x[ \r\n]*"                                             # timeout: 20
        - expect: "[ \r\n]*SIGN=/[ \r\n]*"                                             # timeout: 20
        - expect: _EOF_                                                                # timeout: 20
    return: 0

- case4_arithmetic_operator_sign_invalid:
    run: ./04_arithmetic_operator_sign_invalid
    points: 5
    script:
        - expect: "[ \r\n]*SIGN parameter is invalid![ \r\n]*"                         # timeout: 20
        - expect: _EOF_                                                                # timeout: 20
    return: 0

- case5_arithmetic_operator_print_operator:
    run: ./05_arithmetic_operator_print_operator
    points: 7
    script:
        - expect: "[ \r\n]*ARITHMETIC_OPERATOR[[][+][]], CENTER_LOCATION[[]1,2[]], SIZE[[]3[]][ \r\n]*"     # timeout: 20
        - expect: "[ \r\n]*ARITHMETIC_OPERATOR[[]-[]], CENTER_LOCATION[[]4,5[]], SIZE[[]6[]][ \r\n]*"       # timeout: 20
        - expect: "[ \r\n]*ARITHMETIC_OPERATOR[[]x[]], CENTER_LOCATION[[]7,8[]], SIZE[[]9[]][ \r\n]*"       # timeout: 20
        - expect: "[ \r\n]*ARITHMETIC_OPERATOR[[]/[]], CENTER_LOCATION[[]1,3[]], SIZE[[]5[]][ \r\n]*"       # timeout: 20
        - expect: _EOF_                                                                # timeout: 20
    return: 0


- case6_operator_grid_only_place_no_error:
    run: ./06_operator_grid_only_place_no_error
    points: 7
    script:
        - expect: "[ \r\n]*SUCCESS: Operator [+] with size 1 is placed on [(]3,5[)].[ \r\n]*"  # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator - with size 1 is placed on [(]7,6[)].[ \r\n]*"    # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator x with size 1 is placed on [(]5,3[)].[ \r\n]*"    # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator / with size 1 is placed on [(]2,4[)].[ \r\n]*"    # timeout: 20
        - expect: "[ \r\n]*DESTRUCTOR: GIVE BACK[[]7,7[]] chars.[ \r\n]*"                      # timeout: 20
        - expect: "[ \r\n]*DESTRUCTOR: GIVE BACK[[]4[]] Operators.[ \r\n]*"                    # timeout: 20
        - expect: _EOF_                                                                        # timeout: 20
    return: 0

- case7_operator_grid_place_move_no_error:
    run: ./07_operator_grid_place_move_no_error
    points: 7
    script:
        - expect: "[ \r\n]*SUCCESS: Operator [+] with size 1 is placed on [(]3,5[)].[ \r\n]*"  # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator - with size 1 is placed on [(]7,6[)].[ \r\n]*"    # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator x with size 1 is placed on [(]5,3[)].[ \r\n]*"    # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator / with size 1 is placed on [(]2,4[)].[ \r\n]*"    # timeout: 20
        - expect: "[ \r\n]*SUCCESS: - moved from [(]7,6[)] to [(]6,6[)].[ \r\n]*"              # timeout: 20
        - expect: "[ \r\n]*SUCCESS: [+] moved from [(]3,5[)] to [(]3,6[)].[ \r\n]*"            # timeout: 20
        - expect: "[ \r\n]*SUCCESS: x moved from [(]5,3[)] to [(]6,3[)].[ \r\n]*"              # timeout: 20
        - expect: "[ \r\n]*SUCCESS: / moved from [(]2,4[)] to [(]2,3[)].[ \r\n]*"              # timeout: 20
        - expect: "[ \r\n]*DESTRUCTOR: GIVE BACK[[]7,7[]] chars.[ \r\n]*"                      # timeout: 20
        - expect: "[ \r\n]*DESTRUCTOR: GIVE BACK[[]4[]] Operators.[ \r\n]*"                    # timeout: 20
        - expect: _EOF_                                                                        # timeout: 20
    return: 0

- case8_operator_grid_no_error_jump:
    run: ./08_operator_grid_no_error_jump
    points: 7
    script:
        - expect: "[ \r\n]*SUCCESS: Operator [+] with size 1 is placed on [(]2,2[)].[ \r\n]*"  # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator x with size 2 is placed on [(]5,3[)].[ \r\n]*"    # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator / with size 2 is placed on [(]4,3[)].[ \r\n]*"    # timeout: 20
        - expect: "[ \r\n]*SUCCESS: x moved from [(]5,3[)] to [(]5,5[)].[ \r\n]*"              # timeout: 20
        - expect: "[ \r\n]*SUCCESS: x moved from [(]5,5[)] to [(]3,5[)].[ \r\n]*"              # timeout: 20
        - expect: "[ \r\n]*SUCCESS: [+] moved from [(]2,2[)] to [(]3,2[)].[ \r\n]*"            # timeout: 20
        - expect: "[ \r\n]*DESTRUCTOR: GIVE BACK[[]7,7[]] chars.[ \r\n]*"                      # timeout: 20
        - expect: "[ \r\n]*DESTRUCTOR: GIVE BACK[[]3[]] Operators.[ \r\n]*"                    # timeout: 20
        - expect: _EOF_                                                                        # timeout: 20
    return: 0

- case9_operator_grid_conflict_error:
    run: ./09_operator_grid_conflict_error
    points: 7
    script:
        - expect: "[ \r\n]*SUCCESS: Operator x with size 1 is placed on [(]2,2[)].[ \r\n]*"                 # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator x with size 1 is placed on [(]2,3[)].[ \r\n]*"                 # timeout: 20
        - expect: "[ \r\n]*CONFLICT ERROR: Operator x with size 1 can not be placed on [(]2,4[)].[ \r\n]*"  # timeout: 20
        - expect: "[ \r\n]*SUCCESS: x moved from [(]2,2[)] to [(]2,4[)].[ \r\n]*"                           # timeout: 20
        - expect: "[ \r\n]*CONFLICT ERROR: x can not be moved from [(]2,3[)] to [(]2,4[)].[ \r\n]*"         # timeout: 20
        - expect: "[ \r\n]*CONFLICT ERROR: x can not be moved from [(]2,3[)] to [(]2,2[)].[ \r\n]*"         # timeout: 20
        - expect: "[ \r\n]*SUCCESS: x moved from [(]2,4[)] to [(]2,2[)].[ \r\n]*"                           # timeout: 20
        - expect: "[ \r\n]*DESTRUCTOR: GIVE BACK[[]3,5[]] chars.[ \r\n]*"                      # timeout: 20
        - expect: "[ \r\n]*DESTRUCTOR: GIVE BACK[[]2[]] Operators.[ \r\n]*"                    # timeout: 20
        - expect: _EOF_                                                                        # timeout: 20
    return: 0

- case10_operator_grid_border_error:
    run: ./10_operator_grid_border_error
    points: 7
    script:
        - expect: "[ \r\n]*SUCCESS: Operator [+] with size 2 is placed on [(]3,3[)].[ \r\n]*"             # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator - with size 2 is placed on [(]6,3[)].[ \r\n]*"               # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator / with size 1 is placed on [(]3,6[)].[ \r\n]*"               # timeout: 20
        - expect: "[ \r\n]*BORDER ERROR: Operator x with size 1 can not be placed on [(]6,6[)].[ \r\n]*"  # timeout: 20
        - expect: "[ \r\n]*SUCCESS: / moved from [(]3,6[)] to [(]4,6[)].[ \r\n]*"                         # timeout: 20
        - expect: "[ \r\n]*SUCCESS: [+] moved from [(]3,3[)] to [(]3,4[)].[ \r\n]*"                       # timeout: 20
        - expect: "[ \r\n]*BORDER ERROR: - can not be moved from [(]6,3[)] to [(]6,2[)].[ \r\n]*"         # timeout: 20
        - expect: "[ \r\n]*DESTRUCTOR: GIVE BACK[[]6,7[]] chars.[ \r\n]*"                                 # timeout: 20
        - expect: "[ \r\n]*DESTRUCTOR: GIVE BACK[[]3[]] Operators.[ \r\n]*"                               # timeout: 20
        - expect: _EOF_                                                                                   # timeout: 20
    return: 0

- case11_operator_grid_plus_rotate:
    run: ./11_operator_grid_plus_rotate
    points: 7
    script:
        - expect: "[ \r\n]*SUCCESS: Operator [+] with size 1 is placed on [(]2,2[)].[ \r\n]*"   # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator [+] with size 1 is placed on [(]5,3[)].[ \r\n]*"   # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator [+] with size 1 is placed on [(]5,6[)].[ \r\n]*"   # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator [+] with size 1 is placed on [(]2,6[)].[ \r\n]*"   # timeout: 20
        - expect: "[ \r\n]*SUCCESS: [+] moved from [(]2,2[)] to [(]3,2[)].[ \r\n]*"             # timeout: 20
        - expect: "[ \r\n]*SUCCESS: [+] moved from [(]2,6[)] to [(]2,5[)].[ \r\n]*"             # timeout: 20
        - expect: "[ \r\n]*SUCCESS: [+] moved from [(]5,6[)] to [(]4,6[)].[ \r\n]*"             # timeout: 20
        - expect: "[ \r\n]*SUCCESS: [+] moved from [(]5,3[)] to [(]5,4[)].[ \r\n]*"             # timeout: 20
        - expect: "[ \r\n]*DESTRUCTOR: GIVE BACK[[]6,7[]] chars.[ \r\n]*"                       # timeout: 20
        - expect: "[ \r\n]*DESTRUCTOR: GIVE BACK[[]4[]] Operators.[ \r\n]*"                     # timeout: 20
        - expect: _EOF_                                                                         # timeout: 20
    return: 0

- case12_operator_grid_minus_adjacent:
    run: ./12_operator_grid_minus_adjacent
    points: 7
    script:
        - expect: "[ \r\n]*SUCCESS: Operator - with size 2 is placed on [(]1,3[)].[ \r\n]*"   # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator - with size 1 is placed on [(]1,7[)].[ \r\n]*"   # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator - with size 1 is placed on [(]2,7[)].[ \r\n]*"   # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator - with size 2 is placed on [(]3,3[)].[ \r\n]*"   # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator - with size 3 is placed on [(]4,4[)].[ \r\n]*"   # timeout: 20
        - expect: "[ \r\n]*SUCCESS: - moved from [(]1,3[)] to [(]2,3[)].[ \r\n]*"             # timeout: 20
        - expect: "[ \r\n]*SUCCESS: - moved from [(]2,7[)] to [(]3,7[)].[ \r\n]*"             # timeout: 20
        - expect: "[ \r\n]*SUCCESS: - moved from [(]1,7[)] to [(]2,7[)].[ \r\n]*"             # timeout: 20
        - expect: "[ \r\n]*SUCCESS: - moved from [(]4,4[)] to [(]5,4[)].[ \r\n]*"             # timeout: 20
        - expect: "[ \r\n]*SUCCESS: - moved from [(]3,7[)] to [(]4,7[)].[ \r\n]*"             # timeout: 20
        - expect: "[ \r\n]*SUCCESS: - moved from [(]4,7[)] to [(]4,6[)].[ \r\n]*"             # timeout: 20
        - expect: "[ \r\n]*SUCCESS: - moved from [(]5,4[)] to [(]5,5[)].[ \r\n]*"             # timeout: 20
        - expect: "[ \r\n]*DESTRUCTOR: GIVE BACK[[]5,8[]] chars.[ \r\n]*"                     # timeout: 20
        - expect: "[ \r\n]*DESTRUCTOR: GIVE BACK[[]5[]] Operators.[ \r\n]*"                   # timeout: 20
        - expect: _EOF_                                                                       # timeout: 20
    return: 0

- case13_operator_grid_div_border_conflict:
    run: ./13_operator_grid_div_border_conflict
    points: 7
    script:
        - expect: "[ \r\n]*SUCCESS: Operator / with size 1 is placed on [(]3,2[)].[ \r\n]*"          # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator / with size 2 is placed on [(]3,3[)].[ \r\n]*"          # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator / with size 1 is placed on [(]4,3[)].[ \r\n]*"          # timeout: 20
        - expect: "[ \r\n]*BORDER ERROR: / can not be moved from [(]3,3[)] to [(]3,2[)].[ \r\n]*"    # timeout: 20
        - expect: "[ \r\n]*CONFLICT ERROR: / can not be moved from [(]3,3[)] to [(]3,2[)].[ \r\n]*"  # timeout: 20
        - expect: "[ \r\n]*BORDER ERROR: / can not be moved from [(]3,3[)] to [(]3,4[)].[ \r\n]*"    # timeout: 20
        - expect: "[ \r\n]*CONFLICT ERROR: / can not be moved from [(]3,3[)] to [(]3,4[)].[ \r\n]*"  # timeout: 20
        - expect: "[ \r\n]*BORDER ERROR: / can not be moved from [(]3,3[)] to [(]2,3[)].[ \r\n]*"    # timeout: 20
        - expect: "[ \r\n]*CONFLICT ERROR: / can not be moved from [(]3,3[)] to [(]2,3[)].[ \r\n]*"  # timeout: 20
        - expect: "[ \r\n]*BORDER ERROR: / can not be moved from [(]3,3[)] to [(]4,3[)].[ \r\n]*"    # timeout: 20
        - expect: "[ \r\n]*CONFLICT ERROR: / can not be moved from [(]3,3[)] to [(]4,3[)].[ \r\n]*"  # timeout: 20
        - expect: "[ \r\n]*DESTRUCTOR: GIVE BACK[[]5,5[]] chars.[ \r\n]*"                            # timeout: 20
        - expect: "[ \r\n]*DESTRUCTOR: GIVE BACK[[]3[]] Operators.[ \r\n]*"                          # timeout: 20
        - expect: _EOF_                                                                              # timeout: 20
    return: 0

- case14_operator_grid_crowded:
    run: ./14_operator_grid_crowded
    points: 7
    script:
        - expect: "[ \r\n]*SUCCESS: Operator x with size 1 is placed on [(]2,2[)].[ \r\n]*"                 # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator [+] with size 1 is placed on [(]2,4[)].[ \r\n]*"               # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator x with size 1 is placed on [(]2,6[)].[ \r\n]*"                 # timeout: 20
        - expect: "[ \r\n]*BORDER ERROR: Operator / with size 9 can not be placed on [(]2,1[)].[ \r\n]*"    # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator - with size 3 is placed on [(]9,4[)].[ \r\n]*"                 # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator / with size 3 is placed on [(]5,4[)].[ \r\n]*"                 # timeout: 20
        - expect: "[ \r\n]*CONFLICT ERROR: Operator - with size 3 can not be placed on [(]5,4[)].[ \r\n]*"  # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator - with size 1 is placed on [(]5,2[)].[ \r\n]*"                 # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator / with size 1 is placed on [(]7,6[)].[ \r\n]*"                 # timeout: 20
        - expect: "[ \r\n]*SUCCESS: Operator [+] with size 1 is placed on [(]5,6[)].[ \r\n]*"               # timeout: 20
        - expect: "[ \r\n]*CONFLICT ERROR: x can not be moved from [(]2,2[)] to [(]4,2[)].[ \r\n]*"         # timeout: 20
        - expect: "[ \r\n]*SUCCESS: - moved from [(]5,2[)] to [(]10,2[)].[ \r\n]*"                          # timeout: 20
        - expect: "[ \r\n]*SUCCESS: x moved from [(]2,2[)] to [(]4,2[)].[ \r\n]*"                           # timeout: 20
        - expect: "[ \r\n]*CONFLICT ERROR: [+] can not be moved from [(]2,4[)] to [(]2,3[)].[ \r\n]*"       # timeout: 20
        - expect: "[ \r\n]*SUCCESS: [+] moved from [(]2,4[)] to [(]2,2[)].[ \r\n]*"                         # timeout: 20
        - expect: "[ \r\n]*SUCCESS: / moved from [(]7,6[)] to [(]7,3[)].[ \r\n]*"                           # timeout: 20
        - expect: "[ \r\n]*SUCCESS: x moved from [(]2,6[)] to [(]7,6[)].[ \r\n]*"                           # timeout: 20
        - expect: "[ \r\n]*BORDER ERROR: - can not be moved from [(]10,2[)] to [(]10,9[)].[ \r\n]*"         # timeout: 20
        - expect: "[ \r\n]*BORDER ERROR: / can not be moved from [(]5,4[)] to [(]2,4[)].[ \r\n]*"           # timeout: 20
        - expect: "[ \r\n]*CONFLICT ERROR: / can not be moved from [(]5,4[)] to [(]2,4[)].[ \r\n]*"         # timeout: 20
        - expect: "[ \r\n]*DESTRUCTOR: GIVE BACK[[]10,7[]] chars.[ \r\n]*"                                  # timeout: 20
        - expect: "[ \r\n]*DESTRUCTOR: GIVE BACK[[]8[]] Operators.[ \r\n]*"                                 # timeout: 20
        - expect: _EOF_                                                                                     # timeout: 20
    return: 0

