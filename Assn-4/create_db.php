<?php
        $servername = 'localhost';
        $username = 'root';
        $password = 'root';
        $db = 'loginDB' ;
        $conn = new mysqli($servername, $username, $password);
        if ($conn->connect_error) {
           die("Connection failed: " . $conn->connect_error);
        }

        echo 'Connected successfully<br />';

        $sql = 'CREATE DATABASE '.$db;
        $retval = $conn->query( $sql );
        if(! $retval ) {
            die('Could not create database: ' . $conn->error);
        }
        else{
            echo "Database ".$db." created successfully\n";
        }
        $conn -> close() ;
?>
