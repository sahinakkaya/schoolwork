- cleanup:
   run: make clean
- compile_and_link:
   run: make # timeout: 10
   blocker: true

- stage_1:  # Script for Table 1 order
   run: ./main
   script:
     - expect: "Table1 ordered:\r\n"   #\r\n means endline
     - expect: "2 massala chicken cost(.*?)43.(\\d+)(\\s*)\r\n" #(\\s*) means 0 or more space.
     - expect: "1 coke cost(.*?)3(\\s*)\r\n"
     - expect: "Tip is 6.(\\d+)(\\s*)\r\n" #(\\d+) means 0 or more number.
     - expect: "Total cost(.*?)57.(\\d+) TL(\\s*)\r\n"
   points: 20

- stage_2: # Script for Table 2 order
   run: ./main
   script: 
     - expect: "(.*?)" # (.*?) means any string is accepted
     - expect: "Table2 ordered:(\\s*)\r\n" 
     - expect: "We don't have enough mughai chicken(\\s*)\r\n"
     - expect: "1 fanta cost(.*?)3(\\s*)\r\n"
     - expect: "1 tea cost(.*?)2(\\s*)\r\n"
     - expect: "Tip is 0.(\\d+)(\\s*)\r\n"
     - expect: "Total cost(.*?)6.(\\d+) TL(\\s*)\r\n"
   points: 20

- stage_3: #Script for Table 3 order
   run: ./main
   script:
     - expect: "(.*?)" # (.*?) means any string is accepted
     - expect: "We don't have enough bbq salad(\\s*)\r\n"
     - expect: "Tip is 0(\\s*)\r\n"
     - expect: "Total cost(.*?)0 TL(\\s*)\r\n"
   points: 20
