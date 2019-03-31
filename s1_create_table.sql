create database mydb;
use mydb;

create table sensors(
id int not null auto_increment primary key,
value decimal(10,4),
ip char(15),
time DATETIME DEFAULT CURRENT_TIMESTAMP);

CREATE USER 'me'@'localhost' IDENTIFIED BY 'mypassword';
GRANT ALL PRIVILEGES ON mydb.* TO 'root'@'localhost';
FLUSH PRIVILEGES
