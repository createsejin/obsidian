```
.import FILE TABLE       Import data from FILE into TABLE
   Options:
     --ascii               Use \037 and \036 as column and row separators
     --csv                 Use , and \n as column and row separators
     --skip N              Skip the first N rows of input
     --schema S            Target table to be S.TABLE
     -v                    "Verbose" - increase auxiliary output
   Notes:
     *  If TABLE does not exist, it is created.  The first row of input
        determines the column names.
     *  If neither --csv or --ascii are used, the input mode is derived
        from the ".mode" output mode
     *  If FILE begins with "|" then it is a command that generates the
        input text.
```
만약 --csv나 --ascii 옵션을 주지 않으면 현재 .mode로 설정된 모드로 입력된다. 즉, 만약 콤마 separator인 csv 파일을 .separator = " | "인 상태에서 import 하면 문제가 된다는것. 따라서 `--cvs` 옵션을 반드시 사용하자. 

`sqlite> .import file.csv --csv -v`