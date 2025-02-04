[Arch Wiki](https://wiki.archlinux.org/title/MariaDB)
```
sudo pacman -S mariadb
sudo mariadb-install-db --user=mysql --basedir=/usr --datadir=/var/lib/mysql
```
```
sudo systemctl start mariadb.service
```
으로 `mariadb.service`를 실행할 수 있다.

다음은 초기 보안 관련 설정이다. 자신의 요구사항에 맞게 선택하면 된다.
```
sudo mariadb-secure-installation

NOTE: RUNNING ALL PARTS OF THIS SCRIPT IS RECOMMENDED FOR ALL MariaDB
      SERVERS IN PRODUCTION USE!  PLEASE READ EACH STEP CAREFULLY!

In order to log into MariaDB to secure it, we'll need the current
password for the root user. If you've just installed MariaDB, and
haven't set the root password yet, you should just press enter here.

Enter current password for root (enter for none):
OK, successfully used password, moving on...

Setting the root password or using the unix_socket ensures that nobody
can log into the MariaDB root user without the proper authorisation.

You already have your root account protected, so you can safely answer 'n'.

Switch to unix_socket authentication [Y/n] n
 ... skipping.

You already have your root account protected, so you can safely answer 'n'.

Change the root password? [Y/n] n
 ... skipping.

By default, a MariaDB installation has an anonymous user, allowing anyone
to log into MariaDB without having to have a user account created for
them.  This is intended only for testing, and to make the installation
go a bit smoother.  You should remove them before moving into a
production environment.

Remove anonymous users? [Y/n] y
 ... Success!

Normally, root should only be allowed to connect from 'localhost'.  This
ensures that someone cannot guess at the root password from the network.

Disallow root login remotely? [Y/n] y
 ... Success!

By default, MariaDB comes with a database named 'test' that anyone can
access.  This is also intended only for testing, and should be removed
before moving into a production environment.

Remove test database and access to it? [Y/n] y
 - Dropping test database...
 ... Success!
 - Removing privileges on test database...
 ... Success!

Reloading the privilege tables will ensure that all changes made so far
will take effect immediately.

Reload privilege tables now? [Y/n] y
 ... Success!

Cleaning up...

All done!  If you've completed all of the above steps, your MariaDB
installation should now be secure.

Thanks for using MariaDB!
```

다음의 명령어로 새로운 User를 만들 수 있다.
```
sudo mariadb -u root -p

MariaDB> CREATE USER 'monty'@'localhost' IDENTIFIED BY 'some_pass';
MariaDB> GRANT ALL PRIVILEGES ON mydb.* TO 'monty'@'localhost';
MariaDB> quit
```
여기에서 `monty`는 사용자 이름이고, `some_pass`는 비밀번호이다. 
여기에서는 `monty` User에게 `mydb.*`의 모든 권한을 `GRANT`해주고 있다.

로그인을 할때에는 다음의 명령어를 사용한다.
```
mariadb -u monty -p -h ip_address db_name
```
여기에서 `-h ip_address`는 처음에 Host를 `localhost`로 지정했다면 생략이 가능하며, 첫 보안 설정에서 `test` db를 제거했다면 `db_name`도 생략이 가능하다.
특정 db에 접속하려면 `db_name`을 지정해줘야하는것 같다.