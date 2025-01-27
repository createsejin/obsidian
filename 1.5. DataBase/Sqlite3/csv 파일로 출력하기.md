```sqlite
sqlite> .output test_table1.csv
sqlite> select * from test_table1;

sqlite> .output stdout
sqlite> select * from test_table1;
one, two
hello!, 10
goodbye, 20
hello!, 10
goodbye, 20
"test test", 23
```