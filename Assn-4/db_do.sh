mysqladmin -u root -p drop secure_login
mysqladmin -u root -p create secure_login
mysql -u root -p secure_login < secure_login.sql
