The requirement of the light interpreter are
1) Reading from a mdb file, writing to a file.
2) Create one table and view the table name.
3) Table supports two data types (int, string)
4) Insert rows to the table.
5) View table.
6) Update table rowa 
7) Delete table rows
8) Count and outout number of row in the table.

Change the folder path where your mdb files placed. The main.cpp will detect the mdb file in the folder.

Take note that the value only can be one word, I mean if you insert value "Tommy Tam" it will become "TommyTam".

Exmaple of INSERT SQL command
>> INSERT INTO customer (na me,add ress,id)VAL UES (tommy tam ,kuala lumpur,2);

It will detect like this 
>> INSERT INTO customer(name,address,id)VALUES(tommytam,kualalumpur,2);

SQL command
"CREATE TABLE"
"INSERT INTO"
"SELECT COUT"
"SELECT *"
"DELETE"
