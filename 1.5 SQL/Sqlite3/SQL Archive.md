기본적인 커맨드는 다음과 같다.
```bash
.archive ...             Manage SQL archives
   Each command must have exactly one of the following options:
     -c, --create               Create a new archive
     -u, --update               Add or update files with changed mtime
     -i, --insert               Like -u but always add even if unchanged
     -r, --remove               Remove files from archive
     -t, --list                 List contents of archive
     -x, --extract              Extract files from archive
   Optional arguments:
     -v, --verbose              Print each filename as it is processed
     -f FILE, --file FILE       Use archive FILE (default is current db)
     -a FILE, --append FILE     Open FILE using the apndvfs VFS
     -C DIR, --directory DIR    Read/extract files from directory DIR
     -g, --glob                 Use glob matching for names in archive
     -n, --dryrun               Show the SQL that would have occurred
   Examples:
     .ar -cf ARCHIVE foo bar  # Create ARCHIVE from files foo and bar
     .ar -tf ARCHIVE          # List members of ARCHIVE
     .ar -xvf ARCHIVE         # Verbosely extract files from ARCHIVE
```
[SQLite Archive 공식 참조 문서1](http://sqlite.org/cli.html#sqlite_archive_support)
```sqlite
sqlite> .archive -cf data.sqlar
```
: create sql archive
```sqlite
sqlite> .open data.sqlar
```
: open archive
```sqlite
sqlite> .ar -t
```
: list up current files
```sqlite
sqlite> .ar -i test001.db
```
: insert file
```
sqlite> .ar -x test001.db
```
: extrack file
```
sqlite> .ar -r test001.db
```
: remove file
```
sqlite> .ar -u test001.db
```
: update file

```sqlite
sqlite> select * from sqlar;
name|mode|mtime|sz|data
test001.db|33188|1698672698|24576|x����n..
```
: 모든 아카이브에는 기본적으로 sqlar라는 table이 자동으로 생성된다.
여기에 아카이브에 보관되는 파일들에 대한 정보가 기록된다.

이름만 표시하려면 다음으로 조회한다.
` select name from sqlar order by name;`
